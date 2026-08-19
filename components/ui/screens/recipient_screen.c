#include "recipient_screen.h"

#include "message_service.h"
#include "comm_service.h"
#include "screen_manager.h"
#include "ui_input.h"
#include "app_state.h"

#include "lvgl.h"

#include <stdio.h>



static lv_obj_t *g_status;

static bool g_sent;



/*
 * Send
 */

static void send_to(
    uint8_t recipient,
    const char *label
)
{
    message_service_set_recipient(
        recipient
    );

    bool ok =
        message_service_send();

    if(ok)
    {
        char buffer[DEVICE_NAME_LEN + 16];

        snprintf(
            buffer,
            sizeof(buffer),
            "Sent to %s",
            label
        );

        lv_label_set_text(
            g_status,
            buffer
        );
    }
    else
    {
        lv_label_set_text(
            g_status,
            "Nothing to send"
        );
    }

    g_sent = ok;
}



/*
 * Event Handler
 */

void recipient_screen_handle_event(
    ui_event_t *event
)
{
    if(event == NULL)
    {
        return;
    }

    if(event->type == UI_EVENT_A)
    {
        screen_manager_load(
            SCREEN_MESSAGES
        );

        return;
    }

    if(g_sent)
    {
        return;
    }

    if(event->type == UI_EVENT_0)
    {
        send_to(
            MESSAGE_RECIPIENT_ALL,
            "ALL"
        );

        return;
    }

    if(
        event->type < UI_EVENT_1 ||
        event->type > UI_EVENT_9
    )
    {
        return;
    }

    uint8_t index =
        (uint8_t)(event->type - UI_EVENT_1);

    if(
        index >=
        comm_service_get_device_count()
    )
    {
        return;
    }

    device_info_t *device =
        comm_service_get_device(index);

    send_to(
        index,
        device ? device->name : "?"
    );
}



/*
 * Lifecycle
 */

void recipient_screen_destroy(void)
{
    g_status = NULL;
}

void recipient_screen_on_enter(void)
{
}

void recipient_screen_on_exit(void)
{
}

void recipient_screen_update(
    uint32_t dt_ms
)
{
    (void)dt_ms;
}



/*
 * Create
 */

void recipient_screen_create(void)
{
    lv_obj_t *screen =
        lv_screen_active();

    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );

    ui_input_set_raw_mode(true);

    g_sent = false;



    /*
     * Title
     */

    lv_obj_t *title =
        lv_label_create(screen);

    lv_label_set_text(
        title,
        "Send To"
    );

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        3
    );



    /*
     * Outgoing Preview
     */

    lv_obj_t *preview =
        lv_label_create(screen);

    lv_obj_set_width(
        preview,
        200
    );

    lv_label_set_long_mode(
        preview,
        LV_LABEL_LONG_DOT
    );

    lv_label_set_text(
        preview,
        message_service_get_outgoing()
    );

    lv_obj_align(
        preview,
        LV_ALIGN_TOP_LEFT,
        10,
        18
    );



    /*
     * Broadcast
     */

    lv_obj_t *all_row =
        lv_label_create(screen);

    lv_label_set_text(
        all_row,
        "0  ALL"
    );

    lv_obj_align(
        all_row,
        LV_ALIGN_TOP_LEFT,
        10,
        36
    );



    /*
     * Known Devices
     */

    uint8_t count =
        comm_service_get_device_count();

    for(
        uint8_t i = 0;
        i < count;
        i++
    )
    {
        device_info_t *device =
            comm_service_get_device(i);

        if(device == NULL)
        {
            continue;
        }

        char buffer[DEVICE_NAME_LEN + 8];

        snprintf(
            buffer,
            sizeof(buffer),
            "%u  %s",
            (unsigned)(i + 1),
            device->name
        );

        lv_obj_t *row =
            lv_label_create(screen);

        lv_label_set_text(
            row,
            buffer
        );

        lv_obj_align(
            row,
            LV_ALIGN_TOP_LEFT,
            10,
            48 + (i * 12)
        );
    }



    /*
     * Status
     */

    g_status =
        lv_label_create(screen);

    lv_label_set_text(
        g_status,

        count > 0
            ? "0=ALL  1-9=DEVICE"
            : "No devices paired"
    );

    lv_obj_align(
        g_status,
        LV_ALIGN_BOTTOM_MID,
        0,
        -15
    );



    /*
     * Help
     */

    lv_obj_t *help =
        lv_label_create(screen);

    lv_label_set_text(
        help,
        "A=BACK"
    );

    lv_obj_align(
        help,
        LV_ALIGN_BOTTOM_MID,
        0,
        -3
    );
}
