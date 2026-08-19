#include "settings_screen.h"
#include "list_screen.h"
#include "screen_manager.h"
#include "ui_input.h"
// #include "app_state.h"
#include "settings_service.h"
#include "lvgl.h"
#include "text_editor_screen.h"
#include <string.h>
#include "text_editor.h"


static void settings_screen_refresh(
    void
);

// #include <stdio.h>

static list_screen_model_t g_settings_model;
static char g_device_name_buffer[32];
static settings_screen_t g_settings;


// editor_text_screen
static void on_device_name_done(
    void *context,
    const char *text
)
{
    settings_service_set_device_name(
        text
    );

    settings_screen_refresh();
}

static text_editor_model_t
g_device_name_editor =
{
    .title = "Device Name",

    .buffer = g_device_name_buffer,

    .max_length = 32,

    .on_done = on_device_name_done,

    .context = NULL
};

    // text_editor_open(
    //     &g_name_editor
    // );

    // screen_manager_load(
    //     SCREEN_TEXT_EDITOR
    // );

// list_screen
static const char *settings_get_item_text(
    void *context,
    uint16_t index
)
{
    switch(index)
    {
        case SETTINGS_ITEM_DEVICE_NAME:
            return "Name";

        case SETTINGS_ITEM_DEVICE_TYPE:
            return "Type";

        case SETTINGS_ITEM_MESSAGE_MODE:
            return "MsgMode";

        default:
            return "";
    }
}


static void settings_on_item_selected(
    void *context,
    uint16_t index
)
{
    switch(index)
    {
        case SETTINGS_ITEM_DEVICE_NAME:

            strncpy(
                g_device_name_buffer,

                settings_service_get_device_name(),

                sizeof(g_device_name_buffer)
            );

            text_editor_begin(
                &g_device_name_editor
            );

            break;

        case SETTINGS_ITEM_DEVICE_TYPE:

            settings_service_cycle_device_type();

            break;

        case SETTINGS_ITEM_MESSAGE_MODE:

            settings_service_cycle_message_mode();

            break;

        default:

            break;
    }
}

/*
 * Refresh
 */

static void settings_screen_refresh(void)
{
    // Device Labels
    lv_label_set_text(
        g_settings.items[SETTINGS_ITEM_DEVICE_NAME].value,
        settings_service_get_device_name()
    );

    // Device Types
    lv_label_set_text(
        g_settings.items[
            SETTINGS_ITEM_DEVICE_TYPE
        ].value,

        device_type_to_string(
            settings_service_get_device_type()
        )
    );

    // Message Mode
    lv_label_set_text(
        g_settings.items[
            SETTINGS_ITEM_MESSAGE_MODE
        ].value,

        message_mode_to_string(
            settings_service_get_message_mode()
        )
    );
}

// Settings Rows Events
static void setting_item_event_cb(lv_event_t *e)
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

    uint16_t index =
        (uint16_t)
        (uintptr_t)
        lv_obj_get_user_data(obj);

    if(
        index < g_settings_model.item_count &&
        g_settings_model.on_item_selected
    )
    {
        g_settings_model.on_item_selected(
            g_settings_model.context,
            index
        );
    }
    settings_screen_refresh();
}


//Back
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

// Event Handler
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


// Lifecycle
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


// Create
void settings_screen_create(void)
{
    lv_obj_t *screen =
        lv_screen_active();

    // Background
    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );

    g_settings_model.title = "Settings";
    g_settings_model.item_count = SETTINGS_ITEM_COUNT;
    g_settings_model.get_item_text = settings_get_item_text;
    g_settings_model.on_item_selected = settings_on_item_selected;
    g_settings_model.context = NULL;

    // Group
    g_settings.group = lv_group_create();

    // Title
    g_settings.title = lv_label_create(screen);
    lv_label_set_text(g_settings.title, g_settings_model.title);

    lv_obj_align(
        g_settings.title,
        LV_ALIGN_TOP_MID,
        0,
        3
    );



    // /*
    //  * Setting Labels
    //  */

    // const char *labels[
    //     SETTINGS_ITEM_COUNT
    // ] =
    // {
    //     "Name",
    //     "Type",
    //     "MsgMode"
    // };

    // Create Rows
    for(
        int i = 0;
        i < SETTINGS_ITEM_COUNT;
        i++
    )
    {
        // Container
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

        // Styles
        lv_obj_set_style_radius(
            g_settings.items[i].container,
            5,
            0
        );

        // Default
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

        // Focused
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
        
        // Remove Shadows
        lv_obj_set_style_shadow_width(
            g_settings.items[i].container,
            0,
            0
        );
        
        // Left Label
        g_settings.items[i].label =
            lv_label_create(
                g_settings.items[i].container
            );

        lv_label_set_text(
            g_settings.items[i].label,
            g_settings_model.get_item_text(
                g_settings_model.context,
                i
            )
        );

        lv_obj_align(
            g_settings.items[i].label,
            LV_ALIGN_LEFT_MID,
            5,
            0
        );
        
        // Right Value
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

        // User Data
        lv_obj_set_user_data(
            g_settings.items[i].container,
            (void *)(uintptr_t)i
        );

        // Event
        lv_obj_add_event_cb(
            g_settings.items[i].container,
            setting_item_event_cb,
            LV_EVENT_CLICKED,
            NULL
        );

        // Group
        lv_group_add_obj(
            g_settings.group,
            g_settings.items[i].container
        );
    }

    // Back Button
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