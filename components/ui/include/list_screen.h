#pragma once

#include <stdint.h>



typedef struct
{
    const char *title;

    uint16_t item_count;

    const char *(*get_item_text)(
        void *context,
        uint16_t index
    );

    void (*on_item_selected)(
        void *context,
        uint16_t index
    );

    void *context;

} list_screen_model_t;



void list_screen_open(
    list_screen_model_t *model
);



list_screen_model_t *list_screen_get_model(
    void
);