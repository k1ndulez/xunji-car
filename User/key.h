#ifndef KEY_H
#define KEY_H

#include <stdint.h>

void key_init(void);

typedef enum {
    KEY_NONE = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,//左一
    KEY_RIGHT,//左二
    KEY_OK,//左三
    KEY_BACK,//左四
} key_event_t;


key_event_t key_scan(void);
#endif