#include "key.h"
#include "main.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} key_pin_t;

static const key_pin_t key_pins[4] = 
{
{KEY_1_GPIO_Port, KEY_1_Pin},
{KEY_2_GPIO_Port, KEY_2_Pin},
{KEY_3_GPIO_Port, KEY_3_Pin},
{KEY_4_GPIO_Port, KEY_4_Pin},
};

static const key_event_t key_events[4] = 
{
    KEY_LEFT,
    KEY_RIGHT,
    KEY_OK,
    KEY_BACK,
}; 

static uint8_t key_state[4] = {0};//按键状态
static uint8_t key_count[4] = {0};//读到相同状态次数

void key_init(void)
{
    for (int i = 0; i < 4; i++)
    {
        key_state[i] = 0;
        key_count[i] = 0;
    }
}

key_event_t key_scan(void)
{
    key_event_t event = KEY_NONE;
    
    for (int i = 0; i < 4; i++)
    {
        uint8_t raw = (HAL_GPIO_ReadPin(key_pins[i].port, key_pins[i].pin) == GPIO_PIN_RESET) ? 1 : 0;//按键按下raw=1,松开raw=0
        
        if(raw != key_state[i])
        {
            if(++key_count[i] >=2)//20ms防抖
            {
                key_state[i] = raw;
                key_count[i] = 0;

                if(raw){event = key_events[i];}
            }
        }
        else
        {
            key_count[i] = 0;
        }
    }

    return event;
}    