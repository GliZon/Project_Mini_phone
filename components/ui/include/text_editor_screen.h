#pragma once

#include "ui_event.h"
#include "text_editor.h"
#include "screen_manager.h"

#include <stdint.h>

/*
 * Open
 *
 * The one entry point callers use. Begins the
 * edit, remembers where each outcome returns to,
 * and loads the editor.
 */

void text_editor_screen_open(
    text_editor_model_t *model,
    screen_id_t return_on_save,
    screen_id_t return_on_cancel
);

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
