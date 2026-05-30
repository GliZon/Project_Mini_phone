#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include "ui_event.h"

#include "lvgl.h"

#include <stdint.h>



/*
 * Settings Item IDs
 */

typedef enum
{
    SETTINGS_ITEM_DEVICE_NAME,
    SETTINGS_ITEM_DEVICE_TYPE,
    SETTINGS_ITEM_MESSAGE_MODE,

    SETTINGS_ITEM_COUNT

} settings_item_id_t;



/*
 * Setting Item
 */

typedef struct
{
    lv_obj_t *container;

    lv_obj_t *label;

    lv_obj_t *value;

} settings_item_t;



/*
 * Settings Screen
 */

typedef struct
{
    lv_group_t *group;

    lv_obj_t *title;

    settings_item_t items[
        SETTINGS_ITEM_COUNT
    ];

    lv_obj_t *btn_back;

} settings_screen_t;



/*
 * Lifecycle
 */

void settings_screen_create(void);

void settings_screen_destroy(void);

void settings_screen_on_enter(void);

void settings_screen_on_exit(void);

void settings_screen_update(
    uint32_t dt_ms
);



/*
 * Events
 */

void settings_screen_handle_event(
    ui_event_t *event
);

#endif