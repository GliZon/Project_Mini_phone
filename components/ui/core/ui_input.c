#include "ui_input.h"

#include "input.h"
#include "input_events.h"
#include "ui_event.h"
#include "ui_event_dispatcher.h"

#include "lvgl.h"

#include "esp_log.h"

static const char *TAG = "UI_INPUT";

#define UI_INPUT_QUEUE_LEN 8

static lv_indev_t *indev_keypad;

static bool g_raw_mode;

/*
 * LVGL Key Queue
 */

static uint32_t g_lv_queue[UI_INPUT_QUEUE_LEN];
static uint8_t  g_lv_head;
static uint8_t  g_lv_tail;

static uint32_t g_lv_active_key;
static bool     g_lv_active_pressed;

/*
 * UI Event Queue
 */

static ui_event_type_t g_ui_queue[UI_INPUT_QUEUE_LEN];
static uint8_t         g_ui_head;
static uint8_t         g_ui_tail;

// ========================================
// QUEUES
// ========================================

static uint8_t queue_next(
    uint8_t index
)
{
    return (uint8_t)(
        (index + 1) % UI_INPUT_QUEUE_LEN
    );
}

static void lv_queue_push(
    uint32_t key
)
{
    uint8_t next =
        queue_next(g_lv_head);

    if(next == g_lv_tail)
    {
        return;
    }

    g_lv_queue[g_lv_head] = key;

    g_lv_head = next;
}

static void ui_queue_push(
    ui_event_type_t type
)
{
    uint8_t next =
        queue_next(g_ui_head);

    if(next == g_ui_tail)
    {
        return;
    }

    g_ui_queue[g_ui_head] = type;

    g_ui_head = next;
}

// ========================================
// KEY TRANSLATION
// ========================================

static ui_event_type_t key_to_ui_event(
    char key
)
{
    if(
        key >= '0' &&
        key <= '9'
    )
    {
        return (ui_event_type_t)(
            UI_EVENT_0 + (key - '0')
        );
    }

    switch(key)
    {
        case 'A': return UI_EVENT_A;
        case 'B': return UI_EVENT_B;
        case 'C': return UI_EVENT_C;
        case 'D': return UI_EVENT_D;

        case '*': return UI_EVENT_STAR;
        case '#': return UI_EVENT_HASH;

        default:
            return UI_EVENT_NONE;
    }
}

static uint32_t key_to_lv_key(
    char key
)
{
    switch(key)
    {
        case '2': return LV_KEY_PREV;
        case '8': return LV_KEY_NEXT;
        case '5': return LV_KEY_ENTER;
        case 'D': return LV_KEY_ESC;

        default:
            return 0;
    }
}

// ========================================
// READ CALLBACK
// ========================================

static void keypad_read(
    lv_indev_t *indev,
    lv_indev_data_t *data
)
{
    /*
     * A press is reported one read, its release
     * the next, so LVGL sees a complete click.
     */

    if(g_lv_active_pressed)
    {
        data->key = g_lv_active_key;

        data->state =
            LV_INDEV_STATE_RELEASED;

        g_lv_active_pressed = false;

        data->continue_reading =
            (g_lv_head != g_lv_tail);

        return;
    }

    if(g_lv_head != g_lv_tail)
    {
        g_lv_active_key =
            g_lv_queue[g_lv_tail];

        g_lv_tail =
            queue_next(g_lv_tail);

        g_lv_active_pressed = true;

        data->key = g_lv_active_key;

        data->state =
            LV_INDEV_STATE_PRESSED;

        data->continue_reading = true;

        return;
    }

    data->state =
        LV_INDEV_STATE_RELEASED;

    data->continue_reading = false;
}

// ========================================
// PUMP
// ========================================

void ui_input_poll(void)
{
    input_event_t event;

    if(!input_get_event(&event))
    {
        return;
    }

    if(event.type != INPUT_EVENT_PRESS)
    {
        return;
    }

    ui_event_type_t type =
        key_to_ui_event(event.key);

    ESP_LOGI(
        TAG,
        "key '%c' press -> ui_event %d (raw=%d)",
        event.key,
        (int)type,
        (int)g_raw_mode
    );

    if(type != UI_EVENT_NONE)
    {
        ui_queue_push(type);
    }

    if(g_raw_mode)
    {
        return;
    }

    uint32_t lv_key =
        key_to_lv_key(event.key);

    if(lv_key != 0)
    {
        lv_queue_push(lv_key);
    }
}

void ui_input_process_events(void)
{
    while(g_ui_head != g_ui_tail)
    {
        ui_event_t event =
        {
            .type = g_ui_queue[g_ui_tail]
        };

        g_ui_tail =
            queue_next(g_ui_tail);

        ESP_LOGI(
            TAG,
            "dispatching ui_event %d",
            (int)event.type
        );

        ui_event_post(&event);
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

    ESP_LOGI(TAG, "keypad indev ready");
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

void ui_input_set_raw_mode(
    bool raw
)
{
    g_raw_mode = raw;

    if(raw)
    {
        /*
         * The previous screen's group points at
         * freed objects once the screen is
         * cleaned, so drop it.
         */

        lv_indev_set_group(
            indev_keypad,
            NULL
        );
    }
}
