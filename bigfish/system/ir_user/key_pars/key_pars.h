#ifndef _KEY_PARS_HEADER_
#define _KEY_PARS_HEADER_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct {
	unsigned long long ir_keycode;
	unsigned int linux_keycode;
}hikeycode;

#define KEYNUMMAX 100
typedef struct _key_arry {
    char keyname[64];
    char keynum;
    long long key_predata;
    hikeycode hi_keycode[KEYNUMMAX];
}_key_arry;
void get_keycode(_key_arry *keyarry, int keyarry_num);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
