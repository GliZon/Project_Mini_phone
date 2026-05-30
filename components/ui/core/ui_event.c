#include "ui_event_dispatcher.h"

#include "screen_manager.h"

void ui_event_post(
    ui_event_t *event
)
{
    screen_manager_handle_event(
        event
    );
}