package com.hisilicon.multiscreen.protocol.message;

/**
 * Keyboard value. MAX value is #define KEY_WIMAX 246 in last version. MAX value
 * is 511.Key mapping file is
 * \device\hisilicon\godbox\prebuilt\Vendor_0001_Product_0001.kl .<br>
 * CN:按键键值信息 原键值上限#define KEY_WIMAX 246 现键值上限 511,单板上按键映射文件为：
 * \device\hisilicon\godbox\prebuilt\Vendor_0001_Product_0001.kl
 */
public class KeyInfo
{
    /**
     * Reserve.<br>
     * 保留.
     */
    public static final int KEYCODE_UNKNOWN = 0; // 保留

    /**
     * Home key.<br>
     * Home键.
     */
    public static final int KEYCODE_HOME = 102;

    /**
     * Back key.<br>
     * 返回键.
     */
    public static final int KEYCODE_BACK = 158; // 代表后退键

    /**
     * 0.<br>
     * 0键.
     */
    public static final int KEYCODE_0 = 11; // 代表 0 )(Shift)

    /**
     * 1.<br>
     * 1键.
     */
    public static final int KEYCODE_1 = 2; // 代表 1 !(Shift) //改为linux

    /**
     * 2.<br>
     * 2键.
     */
    public static final int KEYCODE_2 = 3; // 代表 2

    /**
     * 3.<br>
     * 3键.
     */
    public static final int KEYCODE_3 = 4; // 代表 3 #(Shift)

    /**
     * 4.<br>
     * 4键.
     */
    public static final int KEYCODE_4 = 5; // 代表 4 $(Shift)

    /**
     * 5.<br>
     * 5键.
     */
    public static final int KEYCODE_5 = 6; // 代表 5 %(Shift)

    /**
     * 6.<br>
     * 6键.
     */
    public static final int KEYCODE_6 = 7; // 代表 6 ^(Shift)

    /**
     * 7.<br>
     * 7键.
     */
    public static final int KEYCODE_7 = 8; // 代表 7 &(Shift)

    /**
     * 8.<br>
     * 8键.
     */
    public static final int KEYCODE_8 = 9; // 代表 8 *(Shift)

    /**
     * 9.<br>
     * 9键.
     */
    public static final int KEYCODE_9 = 10; // 代表 9 ((Shift)

    /**
     * Up key.<br>
     * 方向键上.
     */
    public static final int KEYCODE_DPAD_UP = 103; // 代表上键

    /**
     * Down key.<br>
     * 方向键下.
     */
    public static final int KEYCODE_DPAD_DOWN = 108; // 代表下键

    /**
     * Left key.<br>
     * 方向键左.
     */
    public static final int KEYCODE_DPAD_LEFT = 105; // 代表左键

    /**
     * Right key.<br>
     * 方向键右.
     */
    public static final int KEYCODE_DPAD_RIGHT = 106; // 代表右键

    /**
     * a.<br>
     * 小写a.
     */
    public static final int KEYCODE_a = 30;

    /**
     * b.<br>
     * 小写b.
     */
    public static final int KEYCODE_b = 48;

    /**
     * c.<br>
     * 小写c.
     */
    public static final int KEYCODE_c = 46;

    /**
     * d.<br>
     * 小写d.
     */
    public static final int KEYCODE_d = 32;

    /**
     * e.<br>
     * 小写e.
     */
    public static final int KEYCODE_e = 18;

    /**
     * f.<br>
     * 小写f.
     */
    public static final int KEYCODE_f = 33;

    /**
     * g.<br>
     * 小写g.
     */
    public static final int KEYCODE_g = 34;

    /**
     * h.<br>
     * 小写h.
     */
    public static final int KEYCODE_h = 35;

    /**
     * i.<br>
     * 小写i.
     */
    public static final int KEYCODE_i = 23;

    /**
     * j.<br>
     * 小写j.
     */
    public static final int KEYCODE_j = 36;

    /**
     * k.<br>
     * 小写k.
     */
    public static final int KEYCODE_k = 37;

    /**
     * l.<br>
     * 小写L.
     */
    public static final int KEYCODE_l = 38;

    /**
     * m.<br>
     * 小写m.
     */
    public static final int KEYCODE_m = 50;

    /**
     * n.<br>
     * 小写n.
     */
    public static final int KEYCODE_n = 49;

    /**
     * o.<br>
     * 小写o.
     */
    public static final int KEYCODE_o = 24;

    /**
     * p.<br>
     * 小写p.
     */
    public static final int KEYCODE_p = 25;

    /**
     * q.<br>
     * 小写q.
     */
    public static final int KEYCODE_q = 16;

    /**
     * r.<br>
     * 小写r.
     */
    public static final int KEYCODE_r = 19;

    /**
     * s.<br>
     * 小写s.
     */
    public static final int KEYCODE_s = 31;

    /**
     * t.<br>
     * 小写t.
     */
    public static final int KEYCODE_t = 20;

    /**
     * u.<br>
     * 小写u.
     */
    public static final int KEYCODE_u = 22;

    /**
     * v.<br>
     * 小写v.
     */
    public static final int KEYCODE_v = 47;

    /**
     * w.<br>
     * 小写w.
     */
    public static final int KEYCODE_w = 17;

    /**
     * x.<br>
     * 小写x.
     */
    public static final int KEYCODE_x = 45;

    /**
     * y.<br>
     * 小写y.
     */
    public static final int KEYCODE_y = 21;

    /**
     * z.<br>
     * 小写z.
     */
    public static final int KEYCODE_z = 44;

    /**
     * Comma.<br>
     * 逗号.
     */
    public static final int KEYCODE_COMMA = 51; // 代表,

    /**
     * Dot.<br>
     * 句号.
     */
    public static final int KEYCODE_DOT = 52; // 代表.

    /**
     * Left shift.<br>
     * 左shift键.
     */
    public static final int KEYCODE_SHIFT_LEFT = 42; // 代表Shift

    /**
     * Right shift.<br>
     * 右shift键.
     */
    public static final int KEYCODE_SHIFT_RIGHT = 54; // 代表Shift

    /**
     * Tab key.<br>
     * Tab键.
     */
    public static final int KEYCODE_TAB = 15; // 代表Tab

    /**
     * Space key.<br>
     * 空格键.
     */
    public static final int KEYCODE_SPACE = 57; // 代表空格

    /**
     * Enter key.<br>
     * 回车键.
     */
    public static final int KEYCODE_ENTER = 28; // 代表回车

    /**
     * Delete Key.<br>
     * 退格键.
     */
    public static final int KEYCODE_DEL = 14; // 代表Delete

    /**
     * Backticks.<br>
     * 反引号 `
     */
    public static final int KEYCODE_GRAVE = 41; // 代表` ~(Shift)

    /**
     * Minus key.<br>
     * 减号 -
     */
    public static final int KEYCODE_MINUS = 12; // 代表- _(Shift)

    /**
     * Underline key.<br>
     * 下划线
     */
    public static final int KEYCODE_UNDERLINE = 312; // 代表_

    /**
     * Equal key.<br>
     * 等号键 =
     */
    public static final int KEYCODE_EQUALS = 13; // 代表= +(Shift)

    /**
     * Left bracket.<br>
     * 左中括号 [
     */
    public static final int KEYCODE_LEFT_BRACKET = 26; // 代表[ {(Shift)

    /**
     * Right bracket.<br>
     * 右中括号 ]
     */
    public static final int KEYCODE_RIGHT_BRACKET = 27; // 代表] }(Shift)

    /**
     * Backslash.<br>
     * 反斜杠 \
     */
    public static final int KEYCODE_BACKSLASH = 43; // 代表\ |(Shift)

    /**
     * Semicolon.<br>
     * 分号 :
     */
    public static final int KEYCODE_SEMICOLON = 39; // 代表; :(Shift)

    /**
     * Apostrophe.<br>
     * 单引号键 '
     */
    public static final int KEYCODE_APOSTROPHE = 40; // 代表' "(Shift)

    /**
     * Slash.<br>
     * 斜杠 /
     */
    public static final int KEYCODE_SLASH = 53; // 代表/ ?(Shift)

    /**
     * At sign.<br>
     * CN:艾特符号。
     */
    public static final int KEYCODE_AT = 303; // 代表@ 2(Shift)

    /**
     * Sigh.<br>
     * 感叹号 !
     */
    public static final int KEYCODE_SIGH = 302; // 代表!

    /**
     * # .<br>
     * # 号
     */
    public static final int KEYCODE_WELL = 304; // 代表#

    /**
     * Percent sign.<br>
     * 百分号 %
     */
    public static final int KEYCODE_PERCENT = 306; // 代表%

    /**
     * ^ .<br>
     * ^ 号
     */
    public static final int KEYCODE_AND = 307; // 代表^

    /**
     * & .<br>
     * & 号
     */
    public static final int KEYCODE_ANDD = 308; // 代表&

    /**
     * * .<br>
     * * 号
     */
    public static final int KEYCODE_STAR = 309; // 代表*

    /**
     * Left bracket.<br>
     * 左括号 (
     */
    public static final int KEYCODE_LEFTBRACKET = 310; // 代表(

    /**
     * right bracket.<br>
     * 右括号 )
     */
    public static final int KEYCODE_RIGHTBRACKET = 311; // 代表)

    /**
     * Add key.<br>
     * 加号 +
     */
    public static final int KEYCODE_ADD = 78; // 代表+

    /**
     * ~ .<br>
     * 波浪号 ~
     */
    public static final int KEYCODE_REVERSE = 341; // 代表~

    /**
     * ? .<br>
     * 问号 ?
     */
    public static final int KEYCODE_ASK = 120; // 代表?

    /**
     * < .<br>
     * 小于号 <
     */
    public static final int KEYCODE_LESS_THAN = 351; // 代表 <

    /**
     * > .<br>
     * 大于号 >
     */
    public static final int KEYCODE_BIG_THAN = 352; // 代表 >

    /**
     * { .<br>
     * 左大括号 {
     */
    public static final int KEYCODE_LEFT_BIG_BRACKET = 326; // 代表{

    /**
     * } .<br>
     * 右大括号 }
     */
    public static final int KEYCODE_RIGHT_BIG_BRACKET = 327; // 代表}

    /**
     * : .<br>
     * 冒号 :
     */
    public static final int KEYCODE_COLON = 339; // 代表:

    /**
     * " .<br>
     * 双引号 "
     */
    public static final int KEYCODE_DOUBLE_QUOTATION = 340; // 代表”

    /**
     * |.<br>
     * | 号
     */
    public static final int KEYCODE_OR = 343; // 代表|

    /**
     * $ .<br>
     * $ 号
     */
    public static final int KEYCODE_DOLLAR = 305; // 代表$ 305

    /**
     * A.<br>
     * 大写 A.
     */
    public static final int KEYCODE_A = 230;

    /**
     * B.<br>
     * 大写 B.
     */
    public static final int KEYCODE_B = 248;

    /**
     * C.<br>
     * 大写 C.
     */
    public static final int KEYCODE_C = 246;

    /**
     * D.<br>
     * 大写 D.
     */
    public static final int KEYCODE_D = 232;

    /**
     * E.<br>
     * 大写 E.
     */
    public static final int KEYCODE_E = 218;

    /**
     * F.<br>
     * 大写 F.
     */
    public static final int KEYCODE_F = 233;

    /**
     * G.<br>
     * 大写 G.
     */
    public static final int KEYCODE_G = 234;

    /**
     * H.<br>
     * 大写 H.
     */
    public static final int KEYCODE_H = 235;

    /**
     * I.<br>
     * 大写 I.
     */
    public static final int KEYCODE_I = 223;

    /**
     * J.<br>
     * 大写 J.
     */
    public static final int KEYCODE_J = 236;

    /**
     * K.<br>
     * 大写 K.
     */
    public static final int KEYCODE_K = 237;

    /**
     * L.<br>
     * 大写 L.
     */
    public static final int KEYCODE_L = 238;

    /**
     * M.<br>
     * 大写 M.
     */
    public static final int KEYCODE_M = 250;

    /**
     * N.<br>
     * 大写 N.
     */
    public static final int KEYCODE_N = 249;

    /**
     * O.<br>
     * 大写 O.
     */
    public static final int KEYCODE_O = 224;

    /**
     * P.<br>
     * 大写 P.
     */
    public static final int KEYCODE_P = 225;

    /**
     * Q.<br>
     * 大写 Q.
     */
    public static final int KEYCODE_Q = 216;

    /**
     * R.<br>
     * 大写 R.
     */
    public static final int KEYCODE_R = 219;

    /**
     * S.<br>
     * 大写 S.
     */
    public static final int KEYCODE_S = 231;

    /**
     * T.<br>
     * 大写 T.
     */
    public static final int KEYCODE_T = 220;

    /**
     * U.<br>
     * 大写 U.
     */
    public static final int KEYCODE_U = 222;

    /**
     * V.<br>
     * 大写 V.
     */
    public static final int KEYCODE_V = 247;

    /**
     * W.<br>
     * 大写 W.
     */
    public static final int KEYCODE_W = 317; // 217 is search

    /**
     * X.<br>
     * 大写 X
     */
    public static final int KEYCODE_X = 245;

    /**
     * Y.<br>
     * 大写 Y.
     */
    public static final int KEYCODE_Y = 221;

    /**
     * Z.<br>
     * 大写 Z.
     */
    public static final int KEYCODE_Z = 244;

    /**
     * Simulate remote control down.<br>
     * CN:模拟遥控器按键按下。
     */
    public static final short KEY_EVENT_DOWN = 1;

    /**
     * Simulate remote control UP.<br>
     * CN:模拟遥控器按键抬起。
     */
    public static final short KEY_EVENT_UP = 0;

    /**
     * Channel increment.<br>
     * 频道加
     */
    public static final int KEYCODE_CH_INC = 0x192;

    /**
     * Channel decrease.<br>
     * 频道减
     */
    public static final int KEYCODE_CH_DEC = 0x193;

    /**
     * Volume up.<br>
     * 音量+
     */
    public static final int KEYCODE_VOLUME_UP = 115;

    /**
     * Volume down.<br>
     * 音量-
     */
    public static final int KEYCODE_VOLUME_DOWN = 114;

    /**
     * Menu.<br>
     * 菜单键
     */
    public static final int KEYCODE_MENU = 139; // 本地Menu

    /**
     * Search.<br>
     * 搜索键
     */
    public static final int KEYCODE_SEARCH = 217;

    /**
     * Video Play.<br>
     * 视频播放/暂停键
     */
    public static final int KEYCODE_PLAY = 164;

    /**
     * Video Stop.<br>
     * 视频停止键
     */
    public static final int KEYCODE_STOP = 128;

    /**
     * Media information.<br>
     * 媒体信息键
     */
    public static final int KEYCODE_INFO = 0x166; // 虚拟遥控器上的info, 165 0x166

    /**
     * Video fast back.<br>
     * 视频快退键
     */
    public static final int KEYCODE_SCALE_LEFT = 168; // KEY_REWIND 168

    /**
     * Video fast forward.<br>
     * 视频快进键
     */
    public static final int KEYCODE_SCALE_RIGHT = 159; // FORWARD=159 ||
                                                       // MEDIA_FAST_FORWARD=208

    /**
     * Previous song.<br>
     * 歌曲后退（上一首）
     */
    public static final int KEYCODE_PREVIOUS = 0x68;

    /**
     * Next song.<br>
     * 歌曲前进（下一首）
     */
    public static final int KEYCODE_NEXT = 0x6d;

    /**
     * Change the resolution.<br>
     * 上一频道/分辨率切换
     */
    public static final int KEYCODE_MORE = 479;

    /**
     * Mute.<br>
     * 静音键
     */
    public static final int KEYCODE_MUTE = 113;

    /**
     * Simulate remote control's F1.<br>
     * 模拟遥控器-绿色按键F1
     */
    public static final int KEYCODE_GREEN = 0x3b;

    /**
     * Simulate remote control's F2.<br>
     * 模拟遥控器-红色按键F2
     */
    public static final int KEYCODE_RED = 0x3c;

    /**
     * Simulate remote control's F3.<br>
     * 模拟遥控器-黄色按键F3
     */
    public static final int KEYCODE_YELLOW = 0x3d;

    /**
     * Simulate remote control's F4.<br>
     * 模拟遥控器-蓝色按键F4
     */
    public static final int KEYCODE_BLUE = 0x3e;

    /*
     * F1-F12的键值 key 59 F1 key 60 F2 key 61 F3 key 62 F4 key 63 F5 key 64 F6 key
     * 65 F7 key 66 F8 key 67 F9 key 68 F10 key 87 F11 key 88 F12
     */

    public static final int KEYCODE_F12 = 0x58;

    private int mKeyCode; // 对应键值

    private int mX; // 起点x坐标

    private int mY; // 起点y坐标

    private int mWidth; // 宽

    private int mHeight; // 高

    /**
     * Constructor with parameters.<br>
     * CN:按键信息构造函数.
     * @param keyCode - key code.<br>
     *        CN:键值.
     * @param x - starting coordinates of the x-axis.<br>
     *        CN:x轴起点坐标.
     * @param y - starting coordinates of the y-axis.<br>
     *        CN:y轴起点坐标.
     * @param width - width of virtual keyboard.<br>
     *        CN:虚拟键盘宽度.
     * @param height - height of virtual keyboard.<br>
     *        CN:虚拟键盘高度.
     */
    public KeyInfo(int keyCode, int x, int y, int width, int height)
    {
        mKeyCode = keyCode;
        mX = x;
        mY = y;
        mWidth = width;
        mHeight = height;
    }

    /**
     * Get key code.<br>
     * CN:获取键值.
     * @return - key code.<br>
     *         CN:键值.
     */
    public int getKeyCode()
    {
        return mKeyCode;
    }

    /**
     * Set key code.<br>
     * CN:设置键值.
     * @param keyCode - key code.<br>
     *        CN:键值.
     */
    public void setKeyCode(int keyCode)
    {
        mKeyCode = keyCode;
    }

    /**
     * Get x coordinate.<br>
     * CN:获取x轴起点坐标.
     * @return - x coordinate.<br>
     *         CN:x轴起点坐标.
     */
    public int getX()
    {
        return mX;
    }

    /**
     * Set x coordinate.<br>
     * CN:设置x轴起点坐标
     * @param x - x coordinate.<br>
     *        CN:x轴起点坐标.
     */
    public void setX(int x)
    {
        mX = x;
    }

    /**
     * Get y coordinate.<br>
     * CN:获取y轴起点坐标.
     * @return - y coordinate.<br>
     *         CN:y轴起点坐标.
     */
    public int getY()
    {
        return mY;
    }

    /**
     * Set y coordinate.<br>
     * CN:设置y轴起点坐标.
     * @param y - y coordinate.<br>
     *        CN:y轴起点坐标.
     */
    public void setY(int y)
    {
        mY = y;
    }

    /**
     * Get width of virtual keyboard.<br>
     * CN:获取虚拟键盘宽度.
     * @return - width of virtual keyboard.<br>
     *         CN:虚拟键盘宽度.
     */
    public int getWidth()
    {
        return mWidth;
    }

    /**
     * Set width of virtual keyboard.<br>
     * CN:设置虚拟键盘宽度.
     * @param width - width of virtual keyboard.<br>
     *        CN:虚拟键盘宽度.
     */
    public void setWidth(int width)
    {
        mWidth = width;
    }

    /**
     * Get height of virtual keyboard.<br>
     * CN:获取虚拟键盘高度
     * @return - height of virtual keyboard.<br>
     *         CN:虚拟键盘高度.
     */
    public int getHeight()
    {
        return mHeight;
    }

    /**
     * Set height of virtual keyboard.<br>
     * CN:设置虚拟键盘高度
     * @param height - height of virtual keyboard.<br>
     *        CN:虚拟键盘高度.
     */
    public void setHeight(int height)
    {
        mHeight = height;
    }
}
