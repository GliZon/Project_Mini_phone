#include "comm_screen.h"

#include "screen_manager.h"
#include "ui_input.h"

#include "lvgl.h"

#include <stdio.h>
#include <stdint.h>



static comm_screen_t g_comm;



/*
 * Forward Declarations
 */

static void comm_screen_refresh(void);

static void fake_scan_results(void);

static void scan_event_cb(
    lv_event_t *e
);

static void back_event_cb(
    lv_event_t *e
);

static void device_event_cb(
    lv_event_t *e
);



/*
 * Refresh UI
 */

static void comm_screen_refresh(void)
{
    app_state_t *state =
        app_state_get();

    char buffer[64];



    /*
     * Status
     */

    switch(state->comm_state)
    {
        case COMM_STATE_IDLE:

            lv_label_set_text(
                g_comm.status,
                "No Devices"
            );

            break;



        case COMM_STATE_SCANNING:

            lv_label_set_text(
                g_comm.status,
                "Scanning..."
            );

            break;



        case COMM_STATE_DEVICE_LIST:

            snprintf(
                buffer,
                sizeof(buffer),
                "Devices Found: %d",
                state->device_count
            );

            lv_label_set_text(
                g_comm.status,
                buffer
            );

            break;



        case COMM_STATE_PAIRING:

            snprintf(
                buffer,
                sizeof(buffer),
                "Pairing: %s",

                state->devices[
                    state->selected_device
                ].name
            );

            lv_label_set_text(
                g_comm.status,
                buffer
            );

            break;



        case COMM_STATE_RESULT:

            lv_label_set_text(
                g_comm.status,

                state->pairing_success ?
                "Pair Success" :
                "Pair Failed"
            );

            break;
    }



    /*
     * Device Rows
     */

    for(int i = 0; i < MAX_DEVICES; i++)
    {
        if(i < state->device_count)
        {
            /*
             * Name
             */

            lv_label_set_text(
                g_comm.device_items[i].name,
                state->devices[i].name
            );



            /*
             * Pair Status
             */

            lv_label_set_text(
                g_comm.device_items[i].status,

                state->devices[i].paired ?
                "[P]" :
                "[-]"
            );



            /*
             * Show Row
             */

            lv_obj_clear_flag(
                g_comm.device_items[i].container,
                LV_OBJ_FLAG_HIDDEN
            );
        }
        else
        {
            /*
             * Hide Row
             */

            lv_obj_add_flag(
                g_comm.device_items[i].container,
                LV_OBJ_FLAG_HIDDEN
            );
        }
    }
}



/*
 * Fake Scan Results
 */

static void fake_scan_results(void)
{
    app_state_t *state =
        app_state_get();



    state->comm_state =
        COMM_STATE_DEVICE_LIST;

    state->device_count =
        3;



    /*
     * Device A
     */

    snprintf(
        state->devices[0].name,
        DEVICE_NAME_LEN,
        "DEVICE_A"
    );

    state->devices[0].paired =
        true;



    /*
     * Device B
     */

    snprintf(
        state->devices[1].name,
        DEVICE_NAME_LEN,
        "DEVICE_B"
    );

    state->devices[1].paired =
        false;



    /*
     * Device C
     */

    snprintf(
        state->devices[2].name,
        DEVICE_NAME_LEN,
        "DEVICE_C"
    );

    state->devices[2].paired =
        false;



    comm_screen_refresh();
}



/*
 * Device Selected
 */

static void device_event_cb(
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



    int index =
        (int)(uintptr_t)
        lv_obj_get_user_data(obj);



    app_state_t *state =
        app_state_get();



    /*
     * Selected Device
     */

    state->selected_device =
        index;



    /*
     * Pairing State
     */

    state->comm_state =
        COMM_STATE_PAIRING;

    comm_screen_refresh();



    /*
     * TEMP
     * Fake Pairing Result
     */

    state->pairing_success =
        true;

    state->devices[index].paired =
        true;

    state->comm_state =
        COMM_STATE_RESULT;

    comm_screen_refresh();
}



/*
 * Scan Button
 */

static void scan_event_cb(
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



    app_state_t *state =
        app_state_get();



    /*
     * Scanning State
     */

    state->comm_state =
        COMM_STATE_SCANNING;

    state->device_count =
        0;



    comm_screen_refresh();



    /*
     * TEMP
     * Fake Scan
     */

    fake_scan_results();
}



/*
 * Back Button
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

void comm_screen_handle_event(
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

void comm_screen_destroy(void)
{
}

void comm_screen_on_enter(void)
{
}

void comm_screen_on_exit(void)
{
}

void comm_screen_update(
    uint32_t dt_ms
)
{
}



/*
 * Screen Create
 */

void comm_screen_create(void)
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

    g_comm.group =
        lv_group_create();



    /*
     * Title
     */

    g_comm.title =
        lv_label_create(screen);

    lv_label_set_text(
        g_comm.title,
        "Communication"
    );

    lv_obj_align(
        g_comm.title,
        LV_ALIGN_TOP_MID,
        0,
        3
    );



    /*
     * Status
     */

    g_comm.status =
        lv_label_create(screen);

    lv_obj_align(
        g_comm.status,
        LV_ALIGN_TOP_LEFT,
        10,
        22
    );



    /*
     * Device Rows
     */

    for(int i = 0; i < MAX_DEVICES; i++)
    {
        /*
         * Container
         */

        g_comm.device_items[i].container =
            lv_btn_create(screen);

        lv_obj_set_size(
            g_comm.device_items[i].container,
            150,
            13
        );

        lv_obj_align(
            g_comm.device_items[i].container,
            LV_ALIGN_TOP_MID,
            0,
            40 + (i * 24)
        );



        /*
         * Store Index
         */

        lv_obj_set_user_data(
            g_comm.device_items[i].container,
            (void *)(uintptr_t)i
        );



        /*
         * Default Style
         */

        lv_obj_set_style_radius(
            g_comm.device_items[i].container,
            0,
            LV_PART_MAIN
        );

        lv_obj_set_style_bg_color(
            g_comm.device_items[i].container,
            lv_color_hex(0x202020),
            LV_PART_MAIN | LV_STATE_DEFAULT
        );

        lv_obj_set_style_border_width(
            g_comm.device_items[i].container,
            0,
            LV_PART_MAIN | LV_STATE_DEFAULT
        );

        lv_obj_set_style_border_color(
            g_comm.device_items[i].container,
            lv_color_hex(0x404040),
            LV_PART_MAIN | LV_STATE_DEFAULT
        );



        /*
         * Focus Style
         */

        lv_obj_set_style_bg_color(
            g_comm.device_items[i].container,
            lv_palette_main(LV_PALETTE_BLUE),
            LV_PART_MAIN | LV_STATE_FOCUSED
        );

        lv_obj_set_style_border_color(
            g_comm.device_items[i].container,
            lv_color_white(),
            LV_PART_MAIN | LV_STATE_FOCUSED
        );



        /*
         * Name Label
         */

        g_comm.device_items[i].name =
            lv_label_create(
                g_comm.device_items[i].container
            );

        lv_obj_align(
            g_comm.device_items[i].name,
            LV_ALIGN_LEFT_MID,
            5,
            0
        );



        /*
         * Status Label
         */

        g_comm.device_items[i].status =
            lv_label_create(
                g_comm.device_items[i].container
            );

        lv_obj_align(
            g_comm.device_items[i].status,
            LV_ALIGN_RIGHT_MID,
            -5,
            0
        );



        /*
         * Click Event
         */

        lv_obj_add_event_cb(
            g_comm.device_items[i].container,
            device_event_cb,
            LV_EVENT_CLICKED,
            NULL
        );



        /*
         * Hidden Initially
         */

        lv_obj_add_flag(
            g_comm.device_items[i].container,
            LV_OBJ_FLAG_HIDDEN
        );



        /*
         * Add To Navigation
         */

        lv_group_add_obj(
            g_comm.group,
            g_comm.device_items[i].container
        );
    }



    /*
     * Scan Button
     */

    g_comm.btn_scan =
        lv_btn_create(screen);

    lv_obj_set_size(
        g_comm.btn_scan,
        50,
        15
    );

    lv_obj_align(
        g_comm.btn_scan,
        LV_ALIGN_BOTTOM_LEFT,
        15,
        -10
    );



    lv_obj_t *scan_label =
        lv_label_create(
            g_comm.btn_scan
        );

    lv_label_set_text(
        scan_label,
        "Scan"
    );

    lv_obj_center(
        scan_label
    );



    lv_obj_add_event_cb(
        g_comm.btn_scan,
        scan_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );



    /*
     * Back Button
     */

    g_comm.btn_back =
        lv_btn_create(screen);

    lv_obj_set_size(
        g_comm.btn_back,
        50,
        15
    );

    lv_obj_align(
        g_comm.btn_back,
        LV_ALIGN_BOTTOM_RIGHT,
        -10,
        -10
    );



    lv_obj_t *label_back =
        lv_label_create(
            g_comm.btn_back
        );

    lv_label_set_text(
        label_back,
        "Back"
    );

    lv_obj_center(
        label_back
    );



    lv_obj_add_event_cb(
        g_comm.btn_back,
        back_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );



    /*
     * Navigation Group
     */

    lv_group_add_obj(
        g_comm.group,
        g_comm.btn_scan
    );

    lv_group_add_obj(
        g_comm.group,
        g_comm.btn_back
    );



    /*
     * Input
     */

    ui_input_set_group(
        g_comm.group
    );



    lv_group_focus_obj(
        g_comm.btn_scan
    );



    /*
     * Initial State
     */

    app_state_t *state =
        app_state_get();

    state->comm_state =
        COMM_STATE_IDLE;

    state->device_count =
        0;



    /*
     * Initial Render
     */

    comm_screen_refresh();
}