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

static char g_last_key =
    '\0';

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

    g_last_key = '\0';
    g_last_press_ms = 0;
    g_cycle_index = 0;
}



/*
 * Save
 */

void text_editor_save(
    void
)
{
    if(g_model == NULL)
    {
        return;
    }

    if(g_model->buffer == NULL)
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
    const input_event_t *event
)
{
    if(event == NULL)
    {
        return;
    }

    if(
        event->type !=
        INPUT_EVENT_PRESS
    )
    {
        return;
    }

    switch(event->key)
    {
        case 'A':

            text_editor_cancel();
            return;

        case 'D':

            text_editor_save();
            return;

        case '*':

            text_editor_backspace();
            return;

        case '0':

            text_editor_append_char(
                ' '
            );
            return;
    }

    if(
        event->key < '2' ||
        event->key > '9'
    )
    {
        return;
    }

    uint32_t now =
        lv_tick_get();

    uint8_t digit =
        event->key - '0';

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
        event->key &&
        (now - g_last_press_ms)
        <
        MULTITAP_TIMEOUT_MS
    )
    {
        g_cycle_index++;

        g_cycle_index %= count;

        text_editor_replace_last_char(
            letters[
                g_cycle_index
            ]
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
        event->key;

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