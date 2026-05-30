#pragma once

#include "lvgl.h"
#include <stdint.h>

typedef enum
{
    DISPLAY_ROTATION_0,
    DISPLAY_ROTATION_90,
    DISPLAY_ROTATION_180,
    DISPLAY_ROTATION_270
} display_rotation_t;

void display_init();

void display_set_lvgl_display(
    lv_display_t *disp
);

void display_fill(uint16_t color);

void display_flush(
    int x1,
    int y1,
    int x2,
    int y2,
    const void *color_data
);

void display_rotation(display_rotation_t rotation);

//settler
void display_set_lvgl_display(
    lv_display_t *disp
);