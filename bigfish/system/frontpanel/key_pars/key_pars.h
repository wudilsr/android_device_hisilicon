#ifndef KEY_PARS__SELF
#define _KEY_PARS_SELF

typedef struct {
	unsigned long long bottom_keycode;
	unsigned int linux_keycode;
}hikeycode;

#define KEYNUMMAX 10
typedef struct _key_arry {
    char keyname[64];
    char keynum;
    long long key_predata;
    hikeycode hi_keycode[KEYNUMMAX];
};
void get_keycode(struct _key_arry *keyarry, int keyarry_num);
#endif
