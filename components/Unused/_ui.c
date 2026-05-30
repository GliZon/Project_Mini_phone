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
// LVGL DRAW BUFFER
// ========================================

static lv_color_t draw_buf[LCD_WIDTH * 20];

// ========================================
// LVGL FLUSH CALLBACK
// ========================================

// static void lvgl_flush_cb(
//     lv_display_t *disp,
//     const lv_area_t *area,
//     uint8_t *px_map
// )
// {
//     display_flush(
//         area->x1,
//         area->y1,
//         area->x2,
//         area->y2,
//         px_map
//     );

//     lv_display_flush_ready(disp);
// }

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

    // =========================
    // MENU LIST
    // =========================

    lv_obj_t *list =
        lv_list_create(
            lv_screen_active()
        );

    lv_obj_set_size(
        list,
        120,
        140
    );

    lv_obj_center(list);

    lv_obj_t *btn1 =
        lv_list_add_button(list, NULL, "Messages");

    lv_obj_t *btn2 =
        lv_list_add_button(list, NULL, "WiFi");

    lv_obj_t *btn3 =
        lv_list_add_button(list, NULL, "Settings");

    lv_obj_t *btn4 =
        lv_list_add_button(list, NULL, "About");

    lv_group_add_obj(group, btn1);
    lv_group_add_obj(group, btn2);
    lv_group_add_obj(group, btn3);
    lv_group_add_obj(group, btn4);

    // =========================
    // GROUP
    // =========================

    lv_group_t *group =
        lv_group_create();

    lv_group_add_obj(group, list);

    ui_input_set_group(group);

    ESP_LOGI(TAG, "UI initialized");
}

// ========================================
// UI TASK
// ========================================

void ui_task(void)
{
    while (1) {

        lv_timer_handler();

        vTaskDelay(pdMS_TO_TICKS(16));
    }
}