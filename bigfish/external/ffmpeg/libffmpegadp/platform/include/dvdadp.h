/*
 */

#ifndef AVFORMAT_DVDADP_H
#define AVFORMAT_DVDADP_H
#define C_ADT_SIZE (0x2FF)

typedef struct tagHI_SVR_DVD_PROTOCOL_MEMBER_S
{
    uint32_t dvdName;
    void *dvd;  /* dvd struct , type should be dvdnav_t */

    uint32_t cur_blk_pos;
    uint32_t seek_target;
    uint32_t buf_offset;
    uint32_t total_blk_len;

    int32_t eof;

    int32_t nr_of_title;
    int32_t title;
    uint64_t title_length;
    int32_t nr_of_chapter;
    uint64_t *chapter_length;

    int64_t time_base;
    uint32_t cell_start_time;
    uint32_t cell_end_time;

    uint8_t video_aspect;
    uint32_t video_height;
    uint32_t video_width;

    uint8_t nr_of_audio;
    uint16_t u16AudLangCode[8];

    uint8_t nr_of_supic;
    uint16_t u16SubLangCode[32];
    int32_t i32SubStCode[32];
    uint32_t dvdpalette[16];

    uint8_t tunit;
    uint16_t nr_tmap;
    uint32_t *toffset;

    uint8_t b_IsClose;
    int64_t cell_timebase[C_ADT_SIZE];
    int cell_adr[C_ADT_SIZE][C_ADT_SIZE];
    int fps;

} HI_SVR_DVD_PROTOCOL_MEMBER_S;

#endif /* AVFORMAT_DVDADP_H */
