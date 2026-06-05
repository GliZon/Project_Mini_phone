#pragma once

#include "ui_event.h"

#include <stdint.h>

/*
 * Lifecycle
 */

void text_editor_screen_create(
    void
);

void text_editor_screen_destroy(
    void
);

void text_editor_screen_on_enter(
    void
);

void text_editor_screen_on_exit(
    void
);

void text_editor_screen_update(
    uint32_t dt_ms
);

void text_editor_screen_handle_event(
    ui_event_t *event
);

/*
 * Refresh UI
 */

void text_editor_screen_refresh(
    void
);