#include "home_screen.h"
#include "ui_input.h"
#include "ui_event.h"
#include "menu_button.h"
#include "screen_manager.h"
#include "lvgl.h"


static home_screen_t g_home;

/*
 * Event Handler
 */

void home_screen_handle_event(
    ui_event_t *event
)
{
    switch(event->type)
    {
        case UI_EVENT_MENU_BUTTON:

            switch(event->menu_button_id)
            {
                case MENU_BUTTON_BATTERY:

                    screen_manager_load(
                        SCREEN_BATTERY
                    );

                    break;

                case MENU_BUTTON_COMM:

                    screen_manager_load(
                        SCREEN_COMM
                    );

                    break;

                case MENU_BUTTON_SETTINGS:

                    screen_manager_load(
                        SCREEN_SETTINGS
                    );

                    break;

                case MENU_BUTTON_MESSAGES:

                    screen_manager_load(
                        SCREEN_MESSAGES
                    );

                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}

/*
 * Create Screen
 */

void home_screen_create(void)
{
    // lv_obj_clean(
    //     lv_screen_active()
    // );

    lv_obj_t *screen =
        lv_screen_active();

    /*
     * Screen Background
     */

    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );

    lv_obj_set_style_bg_opa(
        screen,
        LV_OPA_COVER,
        0
    );

    /*
     * Input Group
     */

    g_home.group =
        lv_group_create();

    /*
     * Buttons
     */

    g_home.btn_battery =
        menu_button_create(
            screen,
            g_home.group,

            MENU_BUTTON_BATTERY,

            "100%",
            "BATRY",

            5,
            22
        );

    g_home.btn_comm =
        menu_button_create(
            screen,
            g_home.group,

            MENU_BUTTON_COMM,

            "D|2",
            "COM",

            85,
            22
        );

    g_home.btn_settings =
        menu_button_create(
            screen,
            g_home.group,

            MENU_BUTTON_SETTINGS,

            "",
            "SETING",

            5,
            78
        );

    g_home.btn_messages =
        menu_button_create(
            screen,
            g_home.group,

            MENU_BUTTON_MESSAGES,

            "",
            "MSG",

            85,
            78
        );

    /*
     * Input System
     */

    ui_input_set_group(
        g_home.group
    );

    /*
     * Default Focus
     */

    lv_group_focus_obj(
        g_home.btn_battery
    );
}
