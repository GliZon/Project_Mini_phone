#pragma once

#include "ui_event.h"

#include <stdint.h>

/*
 * Lifecycle
 */

void recipient_screen_create(
    void
);

void recipient_screen_destroy(
    void
);

void recipient_screen_on_enter(
    void
);

void recipient_screen_on_exit(
    void
);

void recipient_screen_update(
    uint32_t dt_ms
);

void recipient_screen_handle_event(
    ui_event_t *event
);
