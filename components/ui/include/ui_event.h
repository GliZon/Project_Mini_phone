#ifndef UI_EVENT_H
#define UI_EVENT_H

#include "menu_button.h"

typedef enum
{
    UI_EVENT_NONE,

    UI_EVENT_UP,    
    UI_EVENT_DOWN,
    UI_EVENT_LEFT,
    UI_EVENT_RIGHT,

    UI_EVENT_OK,
    UI_EVENT_BACK,

    UI_EVENT_0,
    UI_EVENT_1,
    UI_EVENT_2,
    UI_EVENT_3,
    UI_EVENT_4,
    UI_EVENT_5,
    UI_EVENT_6,
    UI_EVENT_7,
    UI_EVENT_8,
    UI_EVENT_9,

    UI_EVENT_STAR,
    UI_EVENT_HASH,


    UI_EVENT_A,
    UI_EVENT_B,
    UI_EVENT_C,
    UI_EVENT_D,

    UI_EVENT_MENU_BUTTON

} ui_event_type_t;

typedef struct
{
    ui_event_type_t type;

    menu_button_id_t menu_button_id;

} ui_event_t;

#endif