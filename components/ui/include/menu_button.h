#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "lvgl.h"

/*
 * Button IDs
 */

typedef enum
{
    MENU_BUTTON_BATTERY,
    MENU_BUTTON_COMM,
    MENU_BUTTON_SETTINGS,
    MENU_BUTTON_MESSAGES

} menu_button_id_t;

/*
 * Button Create
 */

lv_obj_t *menu_button_create(
    lv_obj_t *parent,
    lv_group_t *group,

    menu_button_id_t id,

    const char *value_text,
    const char *label_text,

    int x,
    int y
);

#endif