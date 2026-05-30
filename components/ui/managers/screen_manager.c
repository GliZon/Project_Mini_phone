#include "screen_manager.h"
#include "ui_event.h"
#include "home_screen.h"
#include "settings_screen.h"
#include "messages_screen.h"
#include "battery_screen.h"
#include "comm_screen.h"

#include "lvgl.h"

static screen_id_t current_screen =
    SCREEN_HOME;

void screen_manager_load(
    screen_id_t screen
)
{
    lv_obj_clean(
        lv_screen_active()
    );

    current_screen = screen;

    switch(screen)
    {
        case SCREEN_HOME:
            home_screen_create();
            break;

        case SCREEN_BATTERY:
            battery_screen_create();
            break;

        case SCREEN_COMM:
            comm_screen_create();
            break;

        case SCREEN_SETTINGS:
            settings_screen_create();
            break;

        case SCREEN_MESSAGES:
            messages_screen_create();
            break;

        default:
            break;
    }

    lv_refr_now(NULL); //Force Refresh
}


void screen_manager_handle_event(
    ui_event_t *event
)
{
    switch(current_screen)
    {
        case SCREEN_HOME:
            home_screen_handle_event(event);
            break;

        case SCREEN_SETTINGS:
            settings_screen_handle_event(event);
            break;

        case SCREEN_MESSAGES:
            messages_screen_handle_event(event);
            break;
        
        case SCREEN_BATTERY:
            battery_screen_handle_event(event);
            break;

        case SCREEN_COMM:
            comm_screen_handle_event(event);
            break;

        default:
            break;
    }
}