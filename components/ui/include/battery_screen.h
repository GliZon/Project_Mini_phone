#ifndef BATTERY_SCREEN_H
#define BATTERY_SCREEN_H

#include "ui_event.h"

#include <stdint.h>



void battery_screen_create(void);

void battery_screen_destroy(void);

void battery_screen_on_enter(void);

void battery_screen_on_exit(void);

void battery_screen_update(
    uint32_t dt_ms
);

void battery_screen_handle_event(
    ui_event_t *event
);

#endif