#include "text_editor.h"

#include "lvgl.h"

#include <string.h>

/*
 * Active Model
 */

static text_editor_model_t *g_model =
    NULL;

/*
 * Working Buffer
 */

static char g_edit_buffer[
    TEXT_EDITOR_MAX_LEN
];

/*
 * Multi Tap State
 */

static ui_event_type_t g_last_key =
    UI_EVENT_NONE;

static uint32_t g_last_press_ms =
    0;

static uint8_t g_cycle_index =
    0;

/*
 * Key Map
 */

static const char *g_keymap[10] =
{
    "",
    "",
    "ABC",
    "DEF",
    "GHI",
    "JKL",
    "MNO",
    "PQRS",
    "TUV",
    "WXYZ"
};

/*
 * Helpers
 */

static int event_to_digit(
    ui_event_type_t type
)
{
    switch(type)
    {
        case UI_EVENT_0: return 0;
        case UI_EVENT_1: return 1;
        case UI_EVENT_2: return 2;
        case UI_EVENT_3: return 3;
        case UI_EVENT_4: return 4;
        case UI_EVENT_5: return 5;
        case UI_EVENT_6: return 6;
        case UI_EVENT_7: return 7;
        case UI_EVENT_8: return 8;
        case UI_EVENT_9: return 9;

        default:
            return -1;
    }
}

/*
 * Begin Editing
 */

void text_editor_begin(
    text_editor_model_t *model
)
{
    if(model == NULL)
    {
        return;
    }

    if(
        model->max_length == 0 ||
        model->max_length >
        TEXT_EDITOR_MAX_LEN
    )
    {
        return;
    }

    g_model = model;

    memset(
        g_edit_buffer,
        0,
        sizeof(g_edit_buffer)
    );

    if(model->buffer)
    {
        strncpy(
            g_edit_buffer,
            model->buffer,
            sizeof(g_edit_buffer) - 1
        );
    }

    g_last_key =
        UI_EVENT_NONE;

    g_last_press_ms =
        0;

    g_cycle_index =
        0;
}

void text_editor_open(
    text_editor_model_t *model
)
{
    text_editor_begin(
        model
    );
}

/*
 * Save
 */

void text_editor_save(
    void
)
{
    if(
        g_model == NULL ||
        g_model->buffer == NULL
    )
    {
        return;
    }

    strncpy(
        g_model->buffer,
        g_edit_buffer,
        g_model->max_length - 1
    );

    g_model->buffer[
        g_model->max_length - 1
    ] = '\0';

    if(g_model->on_done)
    {
        g_model->on_done(
            g_model->context,
            g_model->buffer
        );
    }

    g_model = NULL;

    memset(
        g_edit_buffer,
        0,
        sizeof(g_edit_buffer)
    );
}

/*
 * Cancel
 */

void text_editor_cancel(
    void
)
{
    g_model = NULL;

    memset(
        g_edit_buffer,
        0,
        sizeof(g_edit_buffer)
    );
}

/*
 * Append
 */

bool text_editor_append_char(
    char c
)
{
    if(g_model == NULL)
    {
        return false;
    }

    size_t len =
        strlen(g_edit_buffer);

    if(
        len >=
        (g_model->max_length - 1)
    )
    {
        return false;
    }

    g_edit_buffer[len] = c;
    g_edit_buffer[len + 1] = '\0';

    return true;
}

/*
 * Replace Last
 */

bool text_editor_replace_last_char(
    char c
)
{
    size_t len =
        strlen(g_edit_buffer);

    if(len == 0)
    {
        return false;
    }

    g_edit_buffer[len - 1] = c;

    return true;
}

/*
 * Backspace
 */

bool text_editor_backspace(
    void
)
{
    size_t len =
        strlen(g_edit_buffer);

    if(len == 0)
    {
        return false;
    }

    g_edit_buffer[len - 1] = '\0';

    return true;
}

/*
 * Input Handler
 */

void text_editor_handle_input(
    const ui_event_t *event
)
{
    if(event == NULL)
    {
        return;
    }

    switch(event->type)
    {
        case UI_EVENT_A:
            text_editor_cancel();
            return;

        case UI_EVENT_D:
            text_editor_save();
            return;

        case UI_EVENT_STAR:
            text_editor_backspace();
            return;

        case UI_EVENT_0:
            text_editor_append_char(' ');
            return;

        default:
            break;
    }

    int digit =
        event_to_digit(
            event->type
        );

    if(
        digit < 2 ||
        digit > 9
    )
    {
        return;
    }

    uint32_t now =
        lv_tick_get();

    const char *letters =
        g_keymap[digit];

    uint8_t count =
        strlen(letters);

    if(count == 0)
    {
        return;
    }

    if(
        g_last_key ==
        event->type &&
        (now - g_last_press_ms)
        <
        MULTITAP_TIMEOUT_MS
    )
    {
        g_cycle_index++;

        g_cycle_index %= count;

        text_editor_replace_last_char(
            letters[g_cycle_index]
        );
    }
    else
    {
        g_cycle_index = 0;

        text_editor_append_char(
            letters[0]
        );
    }

    g_last_key =
        event->type;

    g_last_press_ms =
        now;
}

/*
 * Accessors
 */

text_editor_model_t *text_editor_get_model(
    void
)
{
    return g_model;
}

const char *text_editor_get_text(
    void
)
{
    return g_edit_buffer;
}

uint16_t text_editor_get_length(
    void
)
{
    return strlen(
        g_edit_buffer
    );
}

bool text_editor_is_active(
    void
)
{
    return (
        g_model != NULL
    );
}