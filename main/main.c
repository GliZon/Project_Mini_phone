#include "display.h"
#include "ui.h"
#include "lvgl.h"
#include "input.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui_splash.h"
#include "colors.h"
#include "app_state.h"

void color_check(void){
    display_fill(BLACK);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(RED);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(WHITE);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(BLUE);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(GREEN);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(ORANGE);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(YELLOW);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(LGRAY);

    vTaskDelay(pdMS_TO_TICKS(5000));
    display_fill(CYAN);

    vTaskDelay(pdMS_TO_TICKS(5000));
}


static void app_task(void *arg)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    display_init();

    display_rotation(
        DISPLAY_ROTATION_90
    );

    display_fill(BLACK);
    vTaskDelay(pdMS_TO_TICKS(100));

    ui_show_splash();

    input_init();
    app_state_init();


    vTaskDelay(pdMS_TO_TICKS(1000));
    ui_init();

    while(1)
    {
        ui_task();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    xTaskCreatePinnedToCore(
        app_task,
        "app_task",
        8192,
        NULL,
        5,
        NULL,
        1
    );
}