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

static screen_id_t g_pending_screen =
    SCREEN_HOME;

static bool g_pending;

/*
 * Load
 *
 * Every caller - LVGL click callbacks (Back,
 * menu buttons, settings rows) and our own
 * ui_event handlers alike - used to run
 * lv_obj_clean() and rebuild the screen
 * synchronously, right here. Click callbacks run
 * from inside lv_timer_handler(), so that tore
 * down objects LVGL was still using mid-event and
 * corrupted its object tree - the settings-item
 * crash. This just records what was asked for;
 * screen_manager_process() does the real work
 * once per tick, after lv_timer_handler() has
 * returned.
 */

void screen_manager_load(
    screen_id_t screen
)
{
    g_pending_screen = screen;

    g_pending = true;
}

bool screen_manager_is_pending(void)
{
    return g_pending;
}

void screen_manager_process(void)
{
    if(!g_pending)
    {
        return;
    }

    g_pending = false;

    lv_obj_clean(
        lv_screen_active()
    );

    current_screen = g_pending_screen;

    /*
     * Screens that want raw digits opt back in
     * from their own create().
     */

    ui_input_set_raw_mode(false);

    switch(current_screen)
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