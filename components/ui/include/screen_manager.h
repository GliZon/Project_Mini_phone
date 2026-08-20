#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "ui_event.h"

typedef enum
{
    SCREEN_HOME,
    SCREEN_SETTINGS,
    SCREEN_MESSAGES,
    SCREEN_BATTERY,
    SCREEN_COMM,
    SCREEN_TEXT_EDITOR,
    SCREEN_QUICK_MESSAGES,
    SCREEN_RECIPIENT

} screen_id_t;



void screen_manager_load(
    screen_id_t screen
);

/*
 * Applies the pending load() request, if any.
 * Must run outside lv_timer_handler()'s call
 * stack - see the comment on screen_manager_load()
 * for why.
 */

void screen_manager_process(
    void
);



void screen_manager_handle_event(
    ui_event_t *event
);

#endif