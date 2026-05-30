#include "messages_screen.h"
#include "ui_event.h"
#include "lvgl.h"

// Even Handler
void messages_screen_handle_event(
    ui_event_t *event
)
{
    switch(event->type)
    {
        default:
            break;
    }
}

void messages_screen_destroy(void)
{
}

void messages_screen_on_enter(void)
{
}

void messages_screen_on_exit(void)
{
}

void messages_screen_update(uint32_t dt_ms)
{
}

void messages_screen_create(void)
{
    lv_obj_t *label =
        lv_label_create(
            lv_screen_active()
        );

    lv_label_set_text(
        label,
        "Messages Screen"
    );

    lv_obj_center(label);
}

