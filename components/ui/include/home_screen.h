#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "lvgl.h"
#include "ui_event.h"

typedef struct
{
    lv_group_t *group;

    lv_obj_t *title;

    lv_obj_t *btn_battery;
    lv_obj_t *btn_comm;
    lv_obj_t *btn_settings;
    lv_obj_t *btn_messages;

} home_screen_t;

void home_screen_create(void);

void home_screen_destroy(void);

void home_screen_on_enter(void);

void home_screen_on_exit(void);

void home_screen_update(uint32_t dt_ms);

void home_screen_handle_event(
    ui_event_t *event
);

#endif