#ifndef _KEY_SELF
#define _KEY_SELF

#include "panel.h"
/*********************************************************
 *
 *   KEYLED_TYPE_DEF = 0: 74HC164
 *   KEYLED_TYPE_DEF = 1: PT6961
 *   KEYLED_TYPE_DEF = 2: CT1642
 *   KEYLED_TYPE_DEF = 3: PT6964
 *   KEYLED_TYPE_DEF = 4: FD650
 *
 ********************************************************/
#define KEYLED_TYPE_DEF 2

int key_get(KEY_STU* val);
int key_init(void);
void key_deinit(void);
#endif
