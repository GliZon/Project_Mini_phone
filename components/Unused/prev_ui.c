#include "ui.h"
#include "ui_input.h"

#include "display.h"
#include "board.h"

#include "lvgl.h"

#include "esp_log.h"
#include "esp_timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "UI";

// ========================================
// DRAW BUFFER
// ========================================

static lv_color_t draw_buf[LCD_WIDTH * 20];

// ========================================
// FLUSH CALLBACK
// ========================================

static void lvgl_flush_cb(
    lv_display_t *disp,
    const lv_area_t *area,
    uint8_t *px_map
)
{
    lv_draw_sw_rgb565_swap(
        px_map,
        lv_area_get_size(area)
    );

    display_flush(
        area->x1,
        area->y1,
        area->x2,
        area->y2,
        px_map
    );
    lv_display_flush_ready(disp);
}

// ========================================
// LVGL TICK
// ========================================
static void lvgl_tick_cb(void *arg)
{
    lv_tick_inc(2);
}

// ========================================
// UI INIT
// ========================================

void ui_init(void)
{
    lv_init();

    // =========================
    // DISPLAY
    // =========================

    lv_display_t *disp =
        lv_display_create(
            LCD_WIDTH,
            LCD_HEIGHT
        );

    lv_display_set_color_format(
        disp,
        LV_COLOR_FORMAT_RGB565
    );

    lv_display_set_flush_cb(
        disp,
        lvgl_flush_cb
    );

    lv_display_set_buffers(
        disp,
        draw_buf,
        NULL,
        sizeof(draw_buf),
        LV_DISPLAY_RENDER_MODE_PARTIAL
    );

    // =========================
    // TICK TIMER
    // =========================

    const esp_timer_create_args_t timer_args = {
        .callback = lvgl_tick_cb,
        .name = "lvgl_tick"
    };

    esp_timer_handle_t timer;

    esp_timer_create(
        &timer_args,
        &timer
    );

    esp_timer_start_periodic(
        timer,
        2000
    );

    // =========================
    // INPUT
    // =========================

    ui_input_init();

    // =========================
    // SCREEN STYLE
    // =========================

    lv_obj_set_style_bg_color(
        lv_screen_active(),
        lv_color_white(),
        0
    );

    lv_obj_set_style_bg_opa(
        lv_screen_active(),
        LV_OPA_COVER,
        0
    );

// ========================================
// GROUP
// ========================================

lv_group_t *group = lv_group_create();

// ========================================
// FOCUS STYLE
// ========================================

static lv_style_t style_focus;

lv_style_init(&style_focus);

lv_style_set_border_width(
    &style_focus,
    3
);

lv_style_set_border_color(
    &style_focus,
    lv_palette_main(LV_PALETTE_BLUE)
);

lv_style_set_border_opa(
    &style_focus,
    LV_OPA_COVER
);

// ========================================
// BUTTON OBJECTS
// ========================================

    lv_obj_t *btn_messages;
    lv_obj_t *btn_wifi;
    lv_obj_t *btn_settings;

// ========================================
// MESSAGES BUTTON
// ========================================

btn_messages =
    lv_btn_create(
        lv_screen_active()
    );

lv_obj_set_size(
    btn_messages,
    100,
    30
);

lv_obj_align(
    btn_messages,
    LV_ALIGN_TOP_MID,
    0,
    10
);

lv_obj_add_style(
    btn_messages,
    &style_focus,
    LV_STATE_FOCUSED
);

lv_obj_t *label1 =
    lv_label_create(
        btn_messages
    );

lv_label_set_text(
    label1,
    "Messages"
);

lv_obj_center(label1);

lv_group_add_obj(
    group,
    btn_messages
);

// ========================================
// WIFI BUTTON
// ========================================

btn_wifi =
    lv_btn_create(
        lv_screen_active()
    );

lv_obj_set_size(
    btn_wifi,
    100,
    30
);

lv_obj_align(
    btn_wifi,
    LV_ALIGN_TOP_MID,
    0,
    50
);

lv_obj_add_style(
    btn_wifi,
    &style_focus,
    LV_STATE_FOCUSED
);

lv_obj_t *label2 =
    lv_label_create(
        btn_wifi
    );

lv_label_set_text(
    label2,
    "WiFi"
);

lv_obj_center(label2);

lv_group_add_obj(
    group,
    btn_wifi
);

// ========================================
// SETTINGS BUTTON
// ========================================

btn_settings =
    lv_btn_create(
        lv_screen_active()
    );

lv_obj_set_size(
    btn_settings,
    100,
    30
);

lv_obj_align(
    btn_settings,
    LV_ALIGN_TOP_MID,
    0,
    90
);

lv_obj_add_style(
    btn_settings,
    &style_focus,
    LV_STATE_FOCUSED
);

lv_obj_t *label3 =
    lv_label_create(
        btn_settings
    );

lv_label_set_text(
    label3,
    "Settings"
);

lv_obj_center(label3);

lv_group_add_obj(
    group,
    btn_settings
);

// ========================================
// INPUT GROUP
// ========================================

ui_input_set_group(group);

// Focus FIRST button initially
lv_group_focus_obj(
    btn_messages
);

    // Initial focus

    lv_group_focus_obj(
        btn_messages
    );

    ESP_LOGI(
        TAG,
        "UI initialized"
    );
}

// ========================================
// UI TASK
// ========================================

void ui_task(void)  
{
    lv_timer_handler();
}