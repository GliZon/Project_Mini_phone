#ifndef COMM_SCREEN_H
#define COMM_SCREEN_H

#include "ui_event.h"
#include "app_state.h"

#include "lvgl.h"

#include <stdint.h>


typedef struct
{
    lv_obj_t *container;

    lv_obj_t *name;

    lv_obj_t *status;

} device_item_t;


void comm_screen_create(void);

void comm_screen_destroy(void);

void comm_screen_on_enter(void);

void comm_screen_on_exit(void);

void comm_screen_update(
    uint32_t dt_ms
);

void comm_screen_handle_event(
    ui_event_t *event
);



typedef struct
{
    lv_group_t *group;

    lv_obj_t *title;

    lv_obj_t *status;

    device_item_t device_items[MAX_DEVICES];

    lv_obj_t *btn_scan;

    lv_obj_t *btn_back;

} comm_screen_t;

#endif

