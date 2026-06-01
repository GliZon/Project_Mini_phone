#pragma once

#include <stdint.h>



typedef void (*text_done_cb_t)(
    void *context,
    const char *text
);



typedef struct
{
    const char *title;

    char *buffer;

    uint16_t max_length;

    text_done_cb_t on_done;

    void *context;

} text_editor_model_t;



void text_editor_open(
    text_editor_model_t *model
);



text_editor_model_t *text_editor_get_model(
    void
);