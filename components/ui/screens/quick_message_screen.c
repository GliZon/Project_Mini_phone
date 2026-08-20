#include "quick_message_screen.h"

#include "message_service.h"
#include "screen_manager.h"
#include "ui_input.h"
#include "app_state.h"

#include "lvgl.h"

#include <stdio.h>



static lv_obj_t *g_rows[
    MAX_QUICK_MESSAGES
];



/*
 * Digit To Index
 *
 * 1..9 map to slots 0..8. 0 is not a slot.
 */

static int event_to_slot(
    ui_event_type_t type
)
{
    if(
        type >= UI_EVENT_1 &&
        type <= UI_EVENT_9
    )
    {
        return (int)(type - UI_EVENT_1);
    }

    return -1;
}



/*
 * Event Handler
 */

void quick_message_screen_handle_event(
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

    int slot =
        event_to_slot(event->type);

    if(slot < 0)
    {
        return;
    }

    const char *text =
        message_service_get_quick_message(
            (uint8_t)slot
        );

    if(
        text == NULL ||
        text[0] == '\0'
    )
    {
        return;
    }

    message_service_stage_outgoing(text);

    screen_manager_load(
        SCREEN_RECIPIENT
    );
}



/*
 * Lifecycle
 */

void quick_message_screen_destroy(void)
{
    for(
        int i = 0;
        i < MAX_QUICK_MESSAGES;
        i++
    )
    {
        g_rows[i] = NULL;
    }
}

void quick_message_screen_on_enter(void)
{
}

void quick_message_screen_on_exit(void)
{
}

void quick_message_screen_update(
    uint32_t dt_ms
)
{
    (void)dt_ms;
}



/*
 * Create
 */

void quick_message_screen_create(void)
{
    lv_obj_t *screen =
        lv_screen_active();

    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );

    /*
     * Digits pick a slot directly, so LVGL must
     * not consume them for navigation.
     */

    ui_input_set_raw_mode(true);



    /*
     * Title
     */

    lv_obj_t *title =
        lv_label_create(screen);

    lv_label_set_text(
        title,
        "Quick Messages"
    );

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        3
    );



    /*
     * Slots
     */

    uint8_t count =
        message_service_get_quick_message_count();

    /*
     * The panel is 160x128 (see board.h), so 9
     * rows have to run 2 columns wide - a single
     * column at a legible row height runs off the
     * bottom.
     */

    static const int16_t COL_X[2] = { 2, 81 };
    static const int16_t COL_W    = 77;
    static const int16_t ROW_H    = 13;
    static const int16_t ROW_PITCH= 15;
    static const int16_t START_Y  = 14;

    for(
        uint8_t i = 0;
        i < count;
        i++
    )
    {
        char buffer[QUICK_MESSAGE_LEN + 8];

        snprintf(
            buffer,
            sizeof(buffer),
            "%u %s",
            (unsigned)(i + 1),
            message_service_get_quick_message(i)
        );

        int col = i % 2;
        int slot_row = i / 2;

        lv_obj_t *row =
            lv_obj_create(screen);

        lv_obj_set_size(
            row,
            COL_W,
            ROW_H
        );

        lv_obj_align(
            row,
            LV_ALIGN_TOP_LEFT,
            COL_X[col],
            START_Y + (slot_row * ROW_PITCH)
        );

        lv_obj_set_style_radius(
            row,
            3,
            0
        );

        lv_obj_set_style_bg_color(
            row,
            lv_color_hex(0x202020),
            0
        );

        lv_obj_set_style_bg_opa(
            row,
            LV_OPA_COVER,
            0
        );

        lv_obj_set_style_border_width(
            row,
            1,
            0
        );

        lv_obj_set_style_border_color(
            row,
            lv_color_hex(0x404040),
            0
        );

        lv_obj_set_style_shadow_width(
            row,
            0,
            0
        );

        lv_obj_set_style_pad_all(
            row,
            0,
            0
        );

        lv_obj_clear_flag(
            row,
            LV_OBJ_FLAG_SCROLLABLE
        );

        g_rows[i] =
            lv_label_create(row);

        lv_obj_set_width(
            g_rows[i],
            COL_W - 6
        );

        lv_label_set_long_mode(
            g_rows[i],
            LV_LABEL_LONG_DOT
        );

        lv_label_set_text(
            g_rows[i],
            buffer
        );

        lv_obj_align(
            g_rows[i],
            LV_ALIGN_LEFT_MID,
            3,
            0
        );
    }



    /*
     * Help
     */

    lv_obj_t *help =
        lv_label_create(screen);

    lv_obj_set_style_text_color(
        help,
        lv_color_hex(0x808080),
        0
    );

    lv_label_set_text(
        help,
        "1-9=SEND  A=BACK"
    );

    lv_obj_align(
        help,
        LV_ALIGN_BOTTOM_MID,
        0,
        -3
    );
}
