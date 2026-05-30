#include "settings_screen.h"

#include "screen_manager.h"
#include "ui_input.h"
// #include "app_state.h"
#include "settings_service.h"
#include "lvgl.h"

#include <stdio.h>



static settings_screen_t g_settings;



/*
 * Refresh
 */

static void settings_screen_refresh(void)
{
    // app_state_t *state =
    //     app_state_get();



    /*
     * Device Name
     */

    lv_label_set_text(
        g_settings.items[
            SETTINGS_ITEM_DEVICE_NAME
        ].value,

        // state->device_name
        settings_service_get_device_name()
    );



    /*
     * Device Type
     */

    lv_label_set_text(
        g_settings.items[
            SETTINGS_ITEM_DEVICE_TYPE
        ].value,

        // device_type_to_string(
        //     state->device_type
        // )
        device_type_to_string(
        settings_service_get_device_type()
        )
    );



    /*
     * Message Mode
     */

    lv_label_set_text(
        g_settings.items[
            SETTINGS_ITEM_MESSAGE_MODE
        ].value,

        // message_mode_to_string(
        //     state->message_mode
        // )
        message_mode_to_string(
            settings_service_get_message_mode()
        )
    );
}



/*
 * Setting Row Event
 */

static void setting_item_event_cb(
    lv_event_t *e
)
{
    if(
        lv_event_get_code(e)
        != LV_EVENT_CLICKED
    )
    {
        return;
    }



    lv_obj_t *obj =
        lv_event_get_target(e);



    settings_item_id_t index =
        (settings_item_id_t)
        (uintptr_t)
        lv_obj_get_user_data(obj);



    // app_state_t *state =
    //     app_state_get();



    switch(index)
    {
        /*
         * Device Name
         */

        case SETTINGS_ITEM_DEVICE_NAME:

            /*
             * Future:
             * Open keyboard screen
             */

            break;



        /*
         * Device Type
         */

        case SETTINGS_ITEM_DEVICE_TYPE:

            // switch(state->device_type)
            // {
            //     case DEVICE_TYPE_D:

            //         state->device_type =
            //             DEVICE_TYPE_G;

            //         break;



            //     case DEVICE_TYPE_G:

            //         state->device_type =
            //             DEVICE_TYPE_C;

            //         break;



            //     case DEVICE_TYPE_C:

            //         state->device_type =
            //             DEVICE_TYPE_D;

            //         break;
            // }
            settings_service_cycle_device_type();
            break;



        /*
         * Message Mode
         */

        case SETTINGS_ITEM_MESSAGE_MODE:

            // switch(state->message_mode)
            // {
            //     case MESSAGE_MODE_NONE:

            //         state->message_mode =
            //             MESSAGE_MODE_INSTANT;

            //         break;



            //     case MESSAGE_MODE_INSTANT:

            //         state->message_mode =
            //             MESSAGE_MODE_WRITE;

            //         break;



            //     case MESSAGE_MODE_WRITE:

            //         state->message_mode =
            //             MESSAGE_MODE_NONE;

            //         break;
            // }
            settings_service_cycle_message_mode();

            break;



        default:
            break;
    }



    settings_screen_refresh();
}



/*
 * Back
 */

static void back_event_cb(
    lv_event_t *e
)
{
    if(
        lv_event_get_code(e)
        == LV_EVENT_CLICKED
    )
    {
        screen_manager_load(
            SCREEN_HOME
        );
    }
}



/*
 * Event Handler
 */

void settings_screen_handle_event(
    ui_event_t *event
)
{
    switch(event->type)
    {
        default:
            break;
    }
}



/*
 * Lifecycle
 */

void settings_screen_destroy(void)
{
}

void settings_screen_on_enter(void)
{
}

void settings_screen_on_exit(void)
{
}

void settings_screen_update(
    uint32_t dt_ms
)
{
}



/*
 * Create
 */

void settings_screen_create(void)
{
    lv_obj_t *screen =
        lv_screen_active();



    /*
     * Background
     */

    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );



    /*
     * Group
     */

    g_settings.group =
        lv_group_create();



    /*
     * Title
     */

    g_settings.title =
        lv_label_create(screen);

    lv_label_set_text(
        g_settings.title,
        "Settings"
    );

    lv_obj_align(
        g_settings.title,
        LV_ALIGN_TOP_MID,
        0,
        3
    );



    /*
     * Setting Labels
     */

    const char *labels[
        SETTINGS_ITEM_COUNT
    ] =
    {
        "Name",
        "Type",
        "MsgMode"
    };



    /*
     * Create Rows
     */

    for(
        int i = 0;
        i < SETTINGS_ITEM_COUNT;
        i++
    )
    {
        /*
         * Container
         */

        g_settings.items[i].container =
            lv_btn_create(screen);

        lv_obj_set_size(
            g_settings.items[i].container,
            160,
            18
        );

        lv_obj_align(
            g_settings.items[i].container,
            LV_ALIGN_TOP_MID,
            0,
            25 + (i * 28)
        );



        /*
         * Style
         */

        lv_obj_set_style_radius(
            g_settings.items[i].container,
            5,
            0
        );



        /*
         * Default
         */

        lv_obj_set_style_bg_color(
            g_settings.items[i].container,
            lv_color_hex(0x202020),
            LV_PART_MAIN | LV_STATE_DEFAULT
        );

        lv_obj_set_style_border_width(
            g_settings.items[i].container,
            1,
            LV_PART_MAIN | LV_STATE_DEFAULT
        );

        lv_obj_set_style_border_color(
            g_settings.items[i].container,
            lv_color_hex(0x404040),
            LV_PART_MAIN | LV_STATE_DEFAULT
        );



        /*
         * Focused
         */

        lv_obj_set_style_bg_color(
            g_settings.items[i].container,
            lv_color_hex(0x303030),
            LV_PART_MAIN | LV_STATE_FOCUSED
        );

        lv_obj_set_style_border_width(
            g_settings.items[i].container,
            1,
            LV_PART_MAIN | LV_STATE_FOCUSED
        );

        lv_obj_set_style_border_color(
            g_settings.items[i].container,
            lv_palette_main(
                LV_PALETTE_BLUE
            ),
            LV_PART_MAIN | LV_STATE_FOCUSED
        );



        /*
         * Remove Shadow
         */

        lv_obj_set_style_shadow_width(
            g_settings.items[i].container,
            0,
            0
        );



        /*
         * Left Label
         */

        g_settings.items[i].label =
            lv_label_create(
                g_settings.items[i].container
            );

        lv_label_set_text(
            g_settings.items[i].label,
            labels[i]
        );

        lv_obj_align(
            g_settings.items[i].label,
            LV_ALIGN_LEFT_MID,
            5,
            0
        );



        /*
         * Right Value
         */

        g_settings.items[i].value =
            lv_label_create(
                g_settings.items[i].container
            );

        lv_obj_align(
            g_settings.items[i].value,
            LV_ALIGN_RIGHT_MID,
            -5,
            0
        );



        /*
         * User Data
         */

        lv_obj_set_user_data(
            g_settings.items[i].container,
            (void *)(uintptr_t)i
        );



        /*
         * Event
         */

        lv_obj_add_event_cb(
            g_settings.items[i].container,
            setting_item_event_cb,
            LV_EVENT_CLICKED,
            NULL
        );



        /*
         * Group
         */

        lv_group_add_obj(
            g_settings.group,
            g_settings.items[i].container
        );
    }



    /*
     * Back Button
     */

    g_settings.btn_back =
        lv_btn_create(screen);

    lv_obj_set_size(
        g_settings.btn_back,
        50,
        20
    );

    lv_obj_align(
        g_settings.btn_back,
        LV_ALIGN_BOTTOM_MID,
        0,
        -5
    );



    lv_obj_set_style_shadow_width(
        g_settings.btn_back,
        0,
        0
    );



    lv_obj_t *label_back =
        lv_label_create(
            g_settings.btn_back
        );

    lv_label_set_text(
        label_back,
        "Back"
    );

    lv_obj_center(
        label_back
    );



    lv_obj_add_event_cb(
        g_settings.btn_back,
        back_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );



    /*
     * Group
     */

    lv_group_add_obj(
        g_settings.group,
        g_settings.btn_back
    );



    /*
     * Input
     */

    ui_input_set_group(
        g_settings.group
    );



    /*
     * Default Focus
     */

    lv_group_focus_obj(
        g_settings.items[
            SETTINGS_ITEM_DEVICE_NAME
        ].container
    );



    /*
     * Initial Render
     */

    settings_screen_refresh();
}