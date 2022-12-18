/*
* Copyright (C) 2009 The Android Open Source Project
* Copyright (c) 2010, Code Aurora Forum
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include <stdlib.h>
#include <android/log.h>
#include "QCOM_ColorCvt.h"
#include "ahplayerdef.h"
extern "C"
{
    #include "../../arm_neon/yuv2rgb_neon.h"
}
#define TAG "QCOM_ColorCvt"

static const int NV12TILE_BLOCK_WIDTH_HALF = 32;
static const int NV12TILE_BLOCK_WIDTH = 64;
static const int NV12TILE_BLOCK_HEIGHT = 32;

static const int NV12TILE_BLOCK_SIZE = NV12TILE_BLOCK_WIDTH* NV12TILE_BLOCK_HEIGHT;
static const int NV12TILE_BLOCK_GROUP_SIZE = NV12TILE_BLOCK_SIZE*4;
static unsigned char* s_mClip = NULL;
static unsigned char s_uBlockLine[NV12TILE_BLOCK_WIDTH_HALF] = {0};
static unsigned char s_vBlockLine[NV12TILE_BLOCK_WIDTH_HALF] = {0};
//srcLen: len of src, ULen = VLen = srcLen/2
void cvtNV12BlockLine2YV12BlockLine(uint8_t* u_dst,uint8_t* v_dst,const uint8_t* src,int blockWidth_half)
{
    uint8_t* udst = u_dst;
    uint8_t* vdst = v_dst;
    for(int i = 0;i<blockWidth_half;i++)
    {
        *udst++ = *src++;
        *vdst++ = *src++;
    }
}

static uint8_t* initClip()
{
    static const signed kClipMin = -278;
    static const signed kClipMax = 535;

    if (s_mClip == NULL) {
        s_mClip = new uint8_t[kClipMax - kClipMin + 1];

        for (signed i = kClipMin; i <= kClipMax; ++i) {
            s_mClip[i - kClipMin] = (i < 0) ? 0 : (i > 255) ? 255 : (uint8_t)i;
        }
    }

    return &s_mClip[-kClipMin];
}

// GetTiledMemBlockNum
// Calculate the block number within tiled memory where the given frame space
// block resides.
//
// Arguments:
// bx - Horizontal coordinate of block in frame space
// by - Vertical coordinate of block in frame space
// nbx - Number of columns of blocks in frame space
// nby - Number of rows of blocks in frame space
static size_t nv12TileGetTiledMemBlockNum(
        size_t bx, size_t by,
        size_t nbx, size_t nby) {
    //

    // Due to the zigzag pattern we have that blocks are numbered like:
    //
    // | Column (by)
    // | 0 1 2 3 4 5 6 7
    // -------|---------------------------------------
    // 0 | 0 1 6 7 8 9 14 15
    // R 1 | 2 3 4 5 10 11 12 13
    // o 2 | 16 17 22 23 24 25 30 31
    // w 3 | 18 19 20 21 26 27 28 29
    // 4 | 32 33 38 39 40 41 46 47
    // (bx) 5 | 34 35 36 37 42 43 44 45
    // 6 | 48 49 50 51 52 53 54 55

    // From this we can see that:

    // For even rows:
    // - The first block in a row is always mapped to memory block by*nbx.
    // - For all even rows, except for the last one when nby is odd, from the first
    // block number an offset is then added to obtain the block number for
    // the other blocks in the row. The offset is bx plus the corresponding
    // number in the series [0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, ...], which can be
    // expressed as ((bx+2) & ~(3)).
    // - For the last row when nby is odd the offset is simply bx.
    //
    // For odd rows:
    // - The first block in the row is always mapped to memory block
    // (by & (~1))*nbx + 2.
    // - From the first block number an offset is then added to obtain the block
    // number for the other blocks in the row. The offset is bx plus the
    // corresponding number in the series [0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, ...],
    // which can be expressed as (bx & ~(3)).

    size_t base; // Number of memory block of the first block in row by
    size_t offs; // Offset from base

    if((by & 1)==0) {
        base = by * nbx;
        if((nby & 1) && (by == (nby - 1))) {
            // Last row when nby is odd
            offs = bx;
        }
        else {
            offs = bx + ((bx + 2) & ~3);
        }
    }
    else {
        base = (by & (~1))*nbx + 2;
        offs = bx + (bx & ~3);
    }

    return base + offs;
}

//Compute the RGB 565 values from the Y ,Cb Cr values
static void nv12TileComputeRGB(
        uint8_t **dstPtr, const uint8_t *blockUV,
        const uint8_t *blockY, size_t blockWidth,
        size_t dstSkip) {

    uint8_t *dest_ptr = *dstPtr;

    uint8_t *kAdjustedClip = initClip();

    for(size_t i = 0; i < blockWidth; i++) {
        signed y1 = (signed)blockY[i] - 16;;
        signed u = (signed)blockUV[i & ~1] - 128;
        signed v = (signed)blockUV[(i & ~1)+1]- 128;

        signed u_b = u * 517;
        signed u_g = -u * 100;
        signed v_g = -v * 208;
        signed v_r = v * 409;

        signed tmp1 = y1 * 298;
        signed b1 = (tmp1 + u_b) / 256;
        signed g1 = (tmp1 + v_g + u_g) / 256;
        signed r1 = (tmp1 + v_r) / 256;
        unsigned int rgb1 =
            ((kAdjustedClip[r1] >> 3) << 11)
            | ((kAdjustedClip[g1] >> 2) << 5)
            | (kAdjustedClip[b1] >> 3);

        dest_ptr[i * 2] = rgb1 & 0xFF;
        dest_ptr[(i * 2) + 1] = (rgb1 >> 8) & 0xFF;
    }

    dest_ptr += dstSkip;
    *dstPtr = dest_ptr;
}
static void nv12TileComputeRGBA(
        uint8_t **dstPtr, const uint8_t *blockUV,
        const uint8_t *blockY, size_t blockWidth,
        size_t dstSkip) {

    uint8_t *dest_ptr = *dstPtr;

    uint8_t *kAdjustedClip = initClip();

    for(size_t i = 0; i < blockWidth; i++) {
        signed y1 = (signed)blockY[i] - 16;;
        signed u = (signed)blockUV[i & ~1] - 128;
        signed v = (signed)blockUV[(i & ~1)+1]- 128;

        signed u_b = u * 517;
        signed u_g = -u * 100;
        signed v_g = -v * 208;
        signed v_r = v * 409;

        signed tmp1 = y1 * 298;
        signed b1 = (tmp1 + u_b) / 256;
        signed g1 = (tmp1 + v_g + u_g) / 256;
        signed r1 = (tmp1 + v_r) / 256;
        dest_ptr[i * 4 + 3] = 0xFF;
        dest_ptr[(i * 4) + 2] = kAdjustedClip[b1];
        dest_ptr[(i * 4) + 1] = kAdjustedClip[g1];
        dest_ptr[(i * 4) ] = kAdjustedClip[r1] ;
    }

    dest_ptr += dstSkip;
    *dstPtr = dest_ptr;
}

// TraverseBlock
// Function that iterates through the rows of Luma and Chroma blocks
// simultaneously, passing pointers to the rows to compute RGB565 values.
// Since there is twice as much data for Luma, Chroma row pointers are provided
// only when passing an even Luma row pointer.Since the same values apply for
// the next Luma (odd) row the can save the pointer if needed.
static void nv12TileTraverseBlock(
        uint8_t **dstPtr, const uint8_t *blockY,
        const uint8_t *blockUV, size_t blockWidth,
        size_t blockHeight, size_t dstSkip) {

    const uint8_t *block_UV = NULL;
    int blockWidth_half = blockWidth>>1;
    for(size_t row = 0; row < blockHeight; row++) {
        if(row & 1) {
            // Only Luma, the converter can use the previous values if needed
#if HAVE_NEON
//            cvtNV12BlockLine2YV12BlockLine(s_uBlockLine,s_vBlockLine,block_UV,blockWidth_half);
//            yv12_to_rgb565_neon((uint16_t*)(*dstPtr),blockY,s_uBlockLine,s_vBlockLine,blockWidth,0);
        yuv422_2_rgba_neon(*dstPtr,blockY,s_uBlockLine,s_vBlockLine,blockWidth,1,blockWidth,blockWidth_half,blockWidth<<2);
            *dstPtr += dstSkip;
#else
            nv12TileComputeRGBA(dstPtr, block_UV, blockY, blockWidth, dstSkip);
#endif
            blockUV += NV12TILE_BLOCK_WIDTH;
        }
        else {
            block_UV = blockUV;
#if HAVE_NEON
            cvtNV12BlockLine2YV12BlockLine(s_uBlockLine,s_vBlockLine,block_UV,blockWidth_half);
//            yv12_to_rgb565_neon((uint16_t*)(*dstPtr),blockY,s_uBlockLine,s_vBlockLine,blockWidth,0);
        yuv422_2_rgba_neon(*dstPtr,blockY,s_uBlockLine,s_vBlockLine,blockWidth,1,blockWidth,blockWidth_half,blockWidth<<2);
            *dstPtr += dstSkip;
#else
            nv12TileComputeRGBA(dstPtr, block_UV, blockY, blockWidth, dstSkip);
#endif
        }
        blockY += NV12TILE_BLOCK_WIDTH;
    }
}

//Conversion from NV12 tiled to 16 bit RGB565
void convertNV12Tile(
        size_t width, size_t height,
        const void *srcBits, size_t srcSkip,
        void *dstBits, size_t dstSkip) {
    if(dstSkip <width * 2)
        {
        __android_log_print(ANDROID_LOG_INFO, TAG, "dstSkip < width*2");
        }
    if((dstSkip & 3) != 0)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "(dstSkip & 3) != 0");
    }

    uint8_t *base_ptr = (uint8_t *)dstBits;
    uint8_t *dst_ptr = NULL;

    // Absolute number of columns of blocks in the Luma and Chroma spaces
    size_t abx = (width - 1) / NV12TILE_BLOCK_WIDTH + 1;

    // Number of columns of blocks in the Luma and Chroma spaces rounded to
    // the next multiple of 2
    size_t nbx = (abx + 1) & ~1;

    // Number of rows of blocks in the Luma space
    size_t nby_y = (height - 1) / NV12TILE_BLOCK_HEIGHT + 1;

    // Number of rows of blocks in the Chroma space
    size_t nby_uv = (height / 2 - 1) / NV12TILE_BLOCK_HEIGHT + 1;

    // Calculate the size of the Luma section
    size_t size_y = nbx * nby_y * NV12TILE_BLOCK_SIZE;

    if((size_y % NV12TILE_BLOCK_GROUP_SIZE) != 0) {
        size_y = (((size_y-1) / NV12TILE_BLOCK_GROUP_SIZE)+1)
                 * NV12TILE_BLOCK_GROUP_SIZE;
    }

    // Pointers to the start of the Luma and Chroma spaces
    const uint8_t *src_y = (const uint8_t*)srcBits;
    const uint8_t *src_uv = src_y + size_y;

    // Iterate
    for(size_t by = 0, rows_left = height; by < nby_y;
            by++, rows_left -= NV12TILE_BLOCK_HEIGHT) {
        for(size_t bx = 0, cols_left = width; bx < abx;
                bx++, cols_left -= NV12TILE_BLOCK_WIDTH) {
            size_t block_width = (cols_left > NV12TILE_BLOCK_WIDTH ?
                    NV12TILE_BLOCK_WIDTH : cols_left);
            size_t block_height = (rows_left > NV12TILE_BLOCK_HEIGHT ?
                    NV12TILE_BLOCK_HEIGHT : rows_left);
            // Address of Luma data for this block
            size_t block_address = (nv12TileGetTiledMemBlockNum(bx, by, nbx, nby_y)
                     * NV12TILE_BLOCK_SIZE);
            const uint8_t *block_y = src_y + block_address;

            // Address of Chroma data for this block
            // since we have half the data for Chroma the same row number is used
            // for two consecutive Luma rows, but we have to offset the base pointer
            // by half a block for odd rows
            block_address = (nv12TileGetTiledMemBlockNum(bx, by/2, nbx, nby_uv)
                    * NV12TILE_BLOCK_SIZE);
            const uint8_t *block_uv = src_uv + block_address + ((by & 1) ? NV12TILE_BLOCK_SIZE/2 : 0);

            // We have started a new block, calculate the destination pointer
            dst_ptr = base_ptr +
            by * NV12TILE_BLOCK_HEIGHT*width*4 +
            bx * NV12TILE_BLOCK_WIDTH*4;
            nv12TileTraverseBlock(&dst_ptr, block_y,
                    block_uv, block_width,
                    block_height, dstSkip);
        }
    }
}
