#include "ui_input.h"

#include "input.h"
#include "input_events.h"

#include "lvgl.h"

static lv_indev_t *indev_keypad;

// ========================================
// READ CALLBACK
// ========================================

static void keypad_read(
    lv_indev_t *indev,
    lv_indev_data_t *data
)
{
    input_event_t event;

    if (input_get_event(&event)) {

        if (event.type == INPUT_EVENT_PRESS) {

            data->state =
                LV_INDEV_STATE_PRESSED;

            switch (event.key) {

                case '2':
                    data->key = LV_KEY_UP;
                    break;

                case '8':
                    data->key = LV_KEY_DOWN;
                    break;

                case '5':
                    data->key = LV_KEY_ENTER;
                    break;

                case 'D':
                    data->key = LV_KEY_ESC;
                    break;

                default:
                    data->key = 0;
                    break;
            }

        } else {

            data->state =
                LV_INDEV_STATE_RELEASED;
        }

    } else {

        data->state =
            LV_INDEV_STATE_RELEASED;
    }
}

// ========================================
// INIT
// ========================================

void ui_input_init(void)
{
    indev_keypad =
        lv_indev_create();

    lv_indev_set_type(
        indev_keypad,
        LV_INDEV_TYPE_KEYPAD
    );

    lv_indev_set_read_cb(
        indev_keypad,
        keypad_read
    );
}

// ========================================
// GROUP
// ========================================

void ui_input_set_group(
    lv_group_t *group
)
{
    lv_indev_set_group(
        indev_keypad,
        group
    );
}