#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "input_events.h"
#include "text_editor_screen.h"

#define TEXT_EDITOR_MAX_LEN 256

void text_editor_begin(
    text_editor_model_t *model#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "input_events.h"

#define TEXT_EDITOR_MAX_LEN 256
#define MULTITAP_TIMEOUT_MS 1000

/*
 * Save Callback
 */

typedef void (*text_done_cb_t)(
    void *context,
    const char *text
);

/*
 * Editor Model
 */

typedef struct
{
    const char *title;

    char *buffer;

    uint16_t max_length;

    text_done_cb_t on_done;

    void *context;

} text_editor_model_t;

/*
 * Lifecycle
 */

void text_editor_begin(
    text_editor_model_t *model
);

void text_editor_save(
    void
);

void text_editor_cancel(
    void
);

/*
 * Input
 */

void text_editor_handle_input(
    const input_event_t *event
);

/*
 * Text Operations
 */

bool text_editor_append_char(
    char c
);

bool text_editor_replace_last_char(
    char c
);

bool text_editor_backspace(
    void
);

/*
 * Accessors
 */

text_editor_model_t *text_editor_get_model(
    void
);

const char *text_editor_get_text(
    void
);

uint16_t text_editor_get_length(
    void
);
);

void text_editor_handle_input(
    const input_event_t *event
);

const char *text_editor_get_text(
    void
);

bool text_editor_append_char(
    char c
);

bool text_editor_backspace(
    void
);

bool text_editor_replace_last_char(
    char c
);

void text_editor_save(
    void
);

void text_editor_cancel(
    void
);