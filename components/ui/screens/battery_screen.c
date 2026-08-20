#include "battery_screen.h"

#include "screen_manager.h"
#include "ui_input.h"
#include "app_state.h"

#include "lvgl.h"

#include "esp_system.h"



typedef struct
{
    lv_group_t *group;

    lv_obj_t *label_percent;

    lv_obj_t *label_runtime;

    lv_obj_t *label_status;

} battery_screen_t;



static battery_screen_t g_battery;


/*
 * Refresh
 */

static void battery_screen_refresh(void)
{
    app_state_t *state =
        app_state_get();

    char buffer[64];


    /*
     * Battery %
     */

    snprintf(
        buffer,
        sizeof(buffer),
        "Battery: %d%%",
        state->battery_percent
    );

    lv_label_set_text(
        g_battery.label_percent,
        buffer
    );


    /*
     * Runtime
     */

    uint32_t hours =
        state->runtime_seconds / 3600;

    uint32_t minutes =
        (state->runtime_seconds % 3600) / 60;

    snprintf(
        buffer,
        sizeof(buffer),
        "Runtime: %luh %lum",
        hours,
        minutes
    );

    lv_label_set_text(
        g_battery.label_runtime,
        buffer
    );



    /*
     * Charging Status
     */

    lv_label_set_text(
        g_battery.label_status,

        state->charging ?
        "Status: Charging" :
        "Status: Normal"
    );
}



/*
 * Event Handler
 */

void battery_screen_handle_event(
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

void battery_screen_destroy(void)
{
}

void battery_screen_on_enter(void)
{
}

void battery_screen_on_exit(void)
{
}

void battery_screen_update(
    uint32_t dt_ms
)
{
    battery_screen_refresh();
}



/*
 * Button Events
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



static void restart_event_cb(
    lv_event_t *e
)
{
    if(
        lv_event_get_code(e)
        == LV_EVENT_CLICKED
    )
    {
        esp_restart();
    }
}



/*
 * Screen Create
 */

void battery_screen_create(void)
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

    g_battery.group =
        lv_group_create();



    /*
     * Title
     */

    lv_obj_t *title =
        lv_label_create(screen);

    lv_obj_set_style_text_color(
        title,
        lv_color_white(),
        0
    );

    lv_label_set_text(
        title,
        "Battery"
    );

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        5
    );



    /*
     * Battery %
     */

    g_battery.label_percent =
        lv_label_create(screen);

    lv_obj_set_style_text_color(
        g_battery.label_percent,
        lv_color_white(),
        0
    );

    lv_obj_align(
        g_battery.label_percent,
        LV_ALIGN_TOP_LEFT,
        10,
        25
    );



    /*
     * Runtime
     */

    g_battery.label_runtime =
        lv_label_create(screen);

    lv_obj_set_style_text_color(
        g_battery.label_runtime,
        lv_color_white(),
        0
    );

    lv_obj_align(
        g_battery.label_runtime,
        LV_ALIGN_TOP_LEFT,
        10,
        40
    );



    /*
     * Status
     */

    g_battery.label_status =
        lv_label_create(screen);

    lv_obj_set_style_text_color(
        g_battery.label_status,
        lv_color_white(),
        0
    );

    lv_obj_align(
        g_battery.label_status,
        LV_ALIGN_TOP_LEFT,
        10,
        55
    );



    /*
     * Restart Button
     */

    lv_obj_t *btn_restart =
        lv_btn_create(screen);

    lv_obj_set_size(
        btn_restart,
        60,
        20
    );

    lv_obj_align(
        btn_restart,
        LV_ALIGN_BOTTOM_LEFT,
        10,
        -10
    );

    lv_obj_t *lbl_restart =
        lv_label_create(btn_restart);

    lv_obj_set_style_text_color(
        lbl_restart,
        lv_color_white(),
        0
    );

    lv_label_set_text(
        lbl_restart,
        "Restart"
    );

    lv_obj_center(
        lbl_restart
    );



    lv_obj_add_event_cb(
        btn_restart,
        restart_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );



    /*
     * Back Button
     */

    lv_obj_t *btn_back =
        lv_btn_create(screen);

    lv_obj_set_size(
        btn_back,
        60,
        20
    );

    lv_obj_align(
        btn_back,
        LV_ALIGN_BOTTOM_RIGHT,
        -10,
        -10
    );

    lv_obj_t *lbl_back =
        lv_label_create(btn_back);

    lv_obj_set_style_text_color(
        lbl_back,
        lv_color_white(),
        0
    );

    lv_label_set_text(
        lbl_back,
        "Back"
    );

    lv_obj_center(
        lbl_back
    );



    lv_obj_add_event_cb(
        btn_back,
        back_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );



    /*
     * Group
     */

    lv_group_add_obj(
        g_battery.group,
        btn_restart
    );

    lv_group_add_obj(
        g_battery.group,
        btn_back
    );



    /*
     * Input
     */

    ui_input_set_group(
        g_battery.group
    );



    lv_group_focus_obj(
        btn_restart
    );



    /*
     * Initial Refresh
     */

    battery_screen_refresh();
}