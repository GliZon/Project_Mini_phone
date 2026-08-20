#include "ui.h"
#include "ui_input.h"
#include "ui_styles.h"
#include "screen_manager.h"
#include "display.h"
#include "board.h"
#include "lvgl.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// static lv_color_t draw_buf[
//     LCD_WIDTH * 20
// ];
static lv_color_t draw_buf[
    LCD_WIDTH * LCD_HEIGHT
];


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

    // vTaskDelay(pdMS_TO_TICKS(20));

    // lv_display_flush_ready(disp);
}

static void lvgl_tick_cb(void *arg)
{
    lv_tick_inc(5);
}

void ui_init(void)
{
    lv_init();

    lv_display_t *disp =
        lv_display_create(
            LCD_WIDTH,
            LCD_HEIGHT
        );
        
    display_set_lvgl_display(disp);

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
        // LV_DISPLAY_RENDER_MODE_FULL
    );

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
        5000
    );
    ui_input_init();

    ui_styles_init();

    screen_manager_load(
        SCREEN_HOME
    );

    /*
     * Safe here: nothing is on the LVGL callback
     * stack yet, so applying immediately renders
     * Home without waiting for the first tick.
     */

    screen_manager_process();
}

void ui_task(void)
{
    ui_input_poll();

    lv_timer_handler();

    /*
     * Both run after the handler: LVGL click
     * callbacks (Back, menu buttons, settings
     * rows) and our own ui_event handlers can
     * both call screen_manager_load(), which now
     * only records the request. Applying it here,
     * and dispatching ui_events here, keeps
     * lv_obj_clean()/create() off the call stack
     * lv_timer_handler() is still using when a
     * click callback is what triggered the load.
     */

    ui_input_process_events();

    screen_manager_process();
}
// void ui_task(void)
// {
//     uint32_t delay =
//         lv_timer_handler();

//     if(delay > 20)
//     {
//         delay = 20;
//     }

//     vTaskDelay(
//         pdMS_TO_TICKS(delay)
//     );
// }