#include "screen_manager.h"
#include "ui_event.h"
#include "home_screen.h"
#include "settings_screen.h"
#include "messages_screen.h"
#include "battery_screen.h"
#include "comm_screen.h"
#include "text_editor_screen.h"
#include "quick_message_screen.h"
#include "recipient_screen.h"
#include "ui_input.h"

#include "lvgl.h"

#include "esp_log.h"

static const char *TAG = "SCREEN_MGR";

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

    /*
     * Screens that want raw digits opt back in
     * from their own create().
     */

    ui_input_set_raw_mode(false);

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

        case SCREEN_TEXT_EDITOR:
            text_editor_screen_create();
            break;

        case SCREEN_QUICK_MESSAGES:
            quick_message_screen_create();
            break;

        case SCREEN_RECIPIENT:
            recipient_screen_create();
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
    ESP_LOGI(
        TAG,
        "handle_event: screen=%d type=%d",
        (int)current_screen,
        (int)event->type
    );

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

        case SCREEN_TEXT_EDITOR:
            text_editor_screen_handle_event(event);
            break;

        case SCREEN_QUICK_MESSAGES:
            quick_message_screen_handle_event(event);
            break;

        case SCREEN_RECIPIENT:
            recipient_screen_handle_event(event);
            break;

        default:
            break;
    }
}