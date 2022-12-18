#ifndef SUBTITLE_H_INCLUDED
#define SUBTITLE_H_INCLUDED

#include <utils/Vector.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_TYPES_H
#include FT_TRUETYPE_TABLES_H

#include <harfbuzz-shaper.h>
#include <harfbuzz-global.h>
#include <harfbuzz-gpos.h>

#include "harfbuzz-freetype.h"

#include "libxml/parser.h"
#include "libxml/tree.h"
#include <utils/RefBase.h>
#include "hi_unf_so.h"
#include <utils/threads.h>

namespace android {

#ifndef uint8
typedef unsigned char uint8;
#endif
#ifndef uint16
typedef unsigned short uint16;
#endif
#ifndef uint32
typedef unsigned int uint32;
#endif
#ifndef MIN
#define MIN(a,b)  ((a) < (b))?(a):(b)
#endif
#ifndef MAX
#define MAX(a,b)  ((a) > (b))?(a):(b)
#endif

/* configure file path */
#define SYSTEM_CONFIG_PATH "/etc/default_font_config.xml"
#define USER_DATA_CONFIG_PATH "/data/data/com.hisilicon.android.videoplayer/font_config.xml"

#define SUB_CHAR_MAX_LEN      (1024)
#define DEFAULTWINDOW_WIDTH   (1280.0)
#define DEFAULTWINDOW_HEIGHT  (720.0)

/** glyph images handle and position struct */
struct GlyphPos{
    FT_Glyph glyph; /**< glyph images handle, Defined::FT_Glyph  */
    int      xpos;  /** the glyph's start position of x-axis directions */
    int      ypos;  /** the glyph's start position of y-axis directions */
    int      row;   /** the glyph image's row */
};

/** the pointer of GlyphPos */
typedef struct GlyphPos* PGlyphPos;

/** Alignment enum */
enum alignment{
    LEFT =0,    /**< Left-aligned */
    CENTER,     /**< Center-aligned */
    RIGHT,      /**< Right-aligned */
    SUBTITLE_FONT_ALIGN_BUTT
};

/** Subtitle font style enum */
typedef enum HI_FONT_DRAW_ENUM
{
    HI_FONT_DRAW_NORMAL = 0,    /**< normal */
    HI_FONT_DRAW_SHADOW,        /**< shadow */
    HI_FONT_DRAW_HOLLOW,        /**< hollow */
    HI_FONT_DRAW_EMBOLDEN,      /**< embolden */
    HI_FONT_DRAW_ITALTIC,       /**< italtic */
    HI_FONT_DRAW_STROKE,        /**< stroke */
    HI_FONT_DRAW_BUTT
}HI_FONT_DRAW_E;

/** Input Subtitle data type enum */
typedef enum SUBTITLE_DATA_TYPE_ENUM
{
    SUBTITLE_DATA_TYPE_TEXT = 0,/**< Text */
    SUBTITLE_DATA_TYPE_GFX,     /**< bitmap */
    SUBTITLE_DATA_TYPE_BULT
}SUBTITLE_DATA_TYPE_E;

/** the struct of text subtitle data */
typedef struct SUBTITLE_TEXT_DATA_STRUCT
{
    unsigned int *pTxtUnicode; /**< text unicode data */
    int          txtlen;       /**< len */
}SUBTITLE_TEXT_S;

/** the struct of subtitle info */
typedef struct SUBTITLE_DATA_STRUCT
{
    SUBTITLE_DATA_TYPE_E etype; /**< type of subtitle data, Defined::SUBTITLE_DATA_TYPE_E */
    unsigned int mGfxWidth;     /**< bitmap width */
    unsigned int mGfxHeight;    /**< bitmap height */
    unsigned int y_org;         /**< orginal y before crop */
    int mTxtLen;                /**< text len */
    union
    {
        HI_UNF_SO_GFX_S  stGfx;  /**< bitmap data info */
        SUBTITLE_TEXT_S  stText; /**< text data info, not use now */
    }unSubtitleData;
    struct SUBTITLE_DATA_STRUCT *next;
}SUBTITLE_DATA_S;

/** rgb32 pixel struct */
union Pixel32
{
    Pixel32()
    : integer(0) { }
    Pixel32(uint8 ri, uint8 gi, uint8 bi, uint8 ai = 255)
    {
        b = bi;
        g = gi;
        r = ri;
        a = ai;
    }
    uint32 integer;
    struct  {
#ifdef BIG_ENDIAN
        uint8 a, b, g, r;
#else
// BIG_ENDIAN
        uint8 r, g, b, a;
#endif // BIG_ENDIAN
    };
};

/** the stroke bitmap info struct */
struct FontBitmap
{
    FontBitmap() { }
    FontBitmap(int x,int y,int w,int h,int _pitch, unsigned char* _buffer=NULL,
        int _x=0,int _y=0,int _r=0)
        : bearingX(x),bearingY(y),width(w),height(h),pitch(_pitch),
        x_pos(_x),y_pos(_y),rows(_r),buffer(_buffer) { }
    void AdjustCoordinate(int _x, int _y,int _r){
        x_pos = _x;
        y_pos = _y;
        rows= _r;
    }
    int bearingX,bearingY;
    int width, height;
    int pitch, x_pos,y_pos,rows;
    unsigned char* buffer;
};

/*vector FontBitMap*/
typedef Vector<FontBitmap> FontBitmaps;

/** store a point(x,y) */
struct Vec2{
    Vec2() { }
    Vec2(int a, int b)
        : x(a), y(b) { }
    int x, y;
};

/** Computing a series of points of the range */
struct Vec2Rect
{
    Vec2Rect() { }
    Vec2Rect(int left, int top, int right, int bottom)
        : xmin(left), xmax(right), ymin(top), ymax(bottom) { }
    void Include(const Vec2 &r)  {
        xmin = MIN(xmin, r.x);
        ymin = MIN(ymin, r.y);
        xmax = MAX(xmax, r.x);
        ymax = MAX(ymax, r.y);
    }
    int Width() const { return xmax - xmin + 1; }
    int Height() const { return ymax - ymin + 1; }
    int xmin, xmax, ymin, ymax; /**< Save the minimum and maximum values of the x-axis and y-axis */
};

/** subtitle manager class */
class SubtitleFontManager :  public RefBase
{
public:
       SubtitleFontManager(int vo_width, int vo_height, uint8* aData,int pixformat);
       ~SubtitleFontManager();

/** recaculate bitmap subtitle information, remove trailing blank line */
int    getBmpData(void *pGfx);

/** free Glyph image */
void   resetSrtGlyph();

/** clear current frame buffer */
void   clearBmpBuffer(int index);

/** clear subtitle data list */
void   clearSubDataList();

/** insert elemt to subtitle data list */
void   insertSubDataList(SUBTITLE_DATA_S* p);

/** update subtitle display configure */
int    resetSubtitleConfig(int vo_width, int vo_height, void* DrawBuffer,int pixformat);

/** set language type */
int    setLanguageType(int lang);

/** get language type */
int    getLanguageType(int& lang);

/** set subtitle font color. hexadecimal value, RGB pixel-format */
int    setSubColor(unsigned int color32);

/** set subtitle font style */
int    setFontDrawType(int type);

/** get subtitle font style */
int    getFontDrawType(int &type);

/** switch subtile to display */
int    setDisableSubtitle( int IsSub);

/** get the status which switch subtile to display */
int    getDisableSubtitle( int &IsSub);

/** set font style by italic */
void   setGlyphSlot_Italic( FT_GlyphSlot  slot );

/** change font style back by normal */
void   setGlyphSlot_Normal( FT_GlyphSlot  slot );

/** set font style by hollow */
int    setDrawHollow(FT_Library library, FT_Glyph *pglyph);

/** set font style by embolden */
int    setDrawEmbolden(FT_Library library, FT_Glyph *pglyph);

/** fit font edge. left_border:0 ~ mWinwidth/2, bottom:0 ~ mWinheight */
int    setBorder(int left_border,int bottom);

/** set subtitle font display position. horizontal:0 ~ 100, bottom:0 ~ mWinheight */
int    setSubPlace(int horizontal,int bottom);

/** set subtitle horizontal of display position. horizontal:0 ~ 100 */
int    setHorizontal(int horizontal);

/** set subtitle vertical of display position. bottom:0 ~ mWinheight */
int    setVertical(int bottom);

/** set subtitle start position of subtile */
int    setStartPos(int startx,int starty);

/** set font alignment */
int    setAlignment(int ali);

/** set text font line spacing */
int    setLineSpacing(int linespace);

/** set text font space, the distance between the font */
int    setFontspace(int fontspace);

/** set font background color */
int    setBkgroundcolor(unsigned int bkgroundcolor);

/** set font size */
int    setFontSize(int size);

/** change the font */
int    setFontPath(const char* fontpath);

/** change the font config file*/
int    setConfigPath(const char* configPath);

/** update the text data */
//int    setSubtitle(unsigned int* unicode,int len);
int setSubtitle(unsigned int* unicode,int len, unsigned char* rawtxt, int rawlen);//

/** convert utf-8 codes into unicode codes */
int    String_UTF8ToUnicode(unsigned char * textUTF8 ,int textlen, unsigned int *unicode, int &strCount );

/** get subtitle configure fram xml file */
void   readStyleXml();

int   getSubString(unsigned char* pSubString);

/** load bitmap or font glyph to buffer */
int    loadBmpToBuffer(int index = 0);

/** get vertical value */
int    getBottomPos(unsigned int &bottom);

/** computing line min value and max value by row index */
FT_BBox getLineBox(int row);

/** get rows of the current frame subtitle */
int    getRowNum();

/** get path of font */
int    getFontPath(char *path);

/** get font size */
int    getFontSize(int &size);

/** get font color */
int    getSubColor(unsigned int &color);

/** get background color */
int    getBkgroundcolor(unsigned int &color);

/** get way of alignment */
int    getAlignment(int &ali);

/** get font display horizontal and vertical value */
int    getSubPlace(int &horizontal,int &bottom);

/** get font line spacing value */
int    getLineSpace(int &linespace);

/** get font space value */
int    getFontspace(int &space);

/** set the original canvas size of the original image */
int    setRawPicSize(int width, int height);

/** reset font ratio, for subtitle display */
int    resetFontRatio(int width,int height);

/** type, 0: normal 2d subtitle, 1: sbs subtitle, 2: tab subtitle */
int    setSubFramePackType(int type);

bool   mIsXBMC;

HB_ShaperItem  *mpShaperItem;

private:
    float          mRatio;      /**< the ratio of subtitle surface and standard screen(1280x720) */
    float          mPicRatio;   /**< the bitmap subtitle ratio value */
    int            mWinwidth;   /**< the width of screen */
    int            mWinheight;  /**< the height of screen */
    int            mSubwidth;   /**< the width of subtitle display, the same as mWinwidth */
    int            mSubheight;  /**< the height of subtitle display, the same as mWinheight*/
    int            mBottompos;  /**< the distance of screen bottom and subtitle font */
    unsigned char* buffer;      /**< the buffer of subtitle drawing */
    char           mFontpath[SUB_CHAR_MAX_LEN];/**< the subtitle font path */
    char           mConfigPath[SUB_CHAR_MAX_LEN];/**< the subtitle config path */
    int            mFontsize;   /**< font size */
    unsigned int   srtcode[SUB_CHAR_MAX_LEN + 4]; /**< the unicodes of the text at current frame */
    int            srtlen;      /**< the length of unicodes*/
    unsigned int   subcolor;    /**< font's color */
    unsigned int   mbkgroundcolor;/**< background color */
    FT_Library     library;     /**< freetype library */
    FT_Face        face;        /**< freetype face */
    int            bmp8bitSize; /**< bmp8bit buffer size **/
    unsigned char* bmp8bit;     /**< save the unicodes text buffer(8 bits) from freetype */
    GlyphPos       glyphs[SUB_CHAR_MAX_LEN]; /**< save glyphs and position of the fonts from unicode text */
    alignment      align;       /**< the alighment of text */
    bool           mIsInitLib ; /**< tag whether freetype library is initial */
    bool           mIsNewFace;  /**< tag whether freetype face is initial */
    bool           mIsSetFontSize;/**< tag whether font size need to set */
    bool           mIsSetSubPlace;/**< tag whether font position need to set */
    bool           mLoadFaceSuccessed;/**< tag face whether has been loaded. */
    int            mstartx;     /**< save the subtitle start position of x-axis */
    int            mstarty;     /**< save the subtitle start position of y-axis */
    int            mFontLinespace;/**< the font line spacing */
    int            mFontspace;  /**< the font space */
    int            mHorizontal; /**< the horizontal position of subtitle */
    int            mLanguageType;/**< the language type of text */
    bool           mIsGfx;      /**< tag whether the subtitle is bitmap subtitle data */
    SUBTITLE_DATA_S *pstSubData;/**< bitmap subtitle data */
    int            mRawPicSize; /**< the bitmap original canvas size */
    int            mRawPicWidth;/**< the bitmap original canvas width */
    int            mRawPicHeight;/**< the bitmap original canvas height */
    int            mfontDrawType;/**< the style of font */
    int            DisableSubtitle;/**< tag subtitle display is close */
    bool           IsDrawShadow; /**< check the current font style is shadow */
    int            mOldx;       /**< save the x value of the subtitle frame in the screen */
    int            mOldy;       /**< save the y value of the subtitle frame in the screen */
    int            mOldWidth;   /**< save the width value of the subtitle frame */
    int            mOldHeight;  /**< save the height value of the subtitle frame */
    int            mPixformat;  /**< save the subtitle surface buffer pixelformat */
    xmlDocPtr      mDoc;        /**< the pointer of xmlDoc subtitle xml configure */
    FontBitmaps    mFontBmps;   /**< save font bitmap vector from freetype, use in stroke font style */
    Mutex          mSubListLock;  /**< mutex for use pstSubData list*/
    int            mSubFramePackType; /**< subtitle type, 0:normal 2d subtitle, 1:sbs subtitle, 2:tab subtitle */
    unsigned char  mRawSub[SUB_CHAR_MAX_LEN]; /**< the unicodes of the text at current frame */
    int            mRawSublen;    /**< font's color */

/** read font bitmap from freetype by unicodes text */
int    loadSrtToBitmap();

/** render font bitmap from freetype, to get font bitmap position */
int    RenderBitmap();

/** draw bitmap subtitle */
int    RenderGfx();

/** clear the subtitle surface buffer */
int    resetBmpBuffer();

/** init freetype and face, set font size and reset buffer */
int    loadFace();

/** load every font glyph from text, and save font's position, caculate text line */
int    loadSrtToGlyph();

/** load font glyph from a line of text, and save font's position, caculate text line */
int    loadArabSrtToGlyph();

/** Read bitmap information from glyph */
void   renderGlyph();

/** get bitmap data from FT_Bitmap, size and position */
void   drawBitmap(FT_Bitmap*  bitmap, FT_Int x, FT_Int y);

/** get utf8 code length by first byte in utf-code  */
int    getChLength(unsigned char c);

/** convert a utf8-code to unicode */
uint16 Character_UTF8ToUnicode(char* characterUTF8,int start,int len);

/** convert UTF8-code stream into unicode stream */
int    UTF8ToUNICODE(unsigned char *byte, int& index, int bytelen, unsigned int& unicode);

/** read subtitle style from a xml path */
xmlNodePtr readxml();

/** get a node information from xmlNode */
char*  getProp(xmlNodePtr nodeptr,const char* prop);

/** Image scaling */
void   ResizeImage(
           float Ratio,
           unsigned char *InImage, // Source image data
           unsigned char *OutImage, // Destination image data
           int SWidth, // Source image width
           int SHeight, // Source image height
           int DWidth, // Destination rectangle width
           int DHeight, // Destination rectangle height
           int dstWholeWidth, // Destination image width
           int dstWholeHeight, // Destination image height
           int FromLeftX,  // Destination image x
           int FromTopY //Destination image y
           );
};//End SubtitleFontManager

};
#endif // SUBTITLE_H_INCLUDED
