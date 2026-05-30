#include "freertos/FreeRTOS.h"
#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "display.h"
#include "esp_log.h"
#include "board.h"


static lv_display_t *s_disp = NULL;


// DISPLAY OFFSETS
static uint16_t x_offset = 0;
static uint16_t y_offset = 0;

// GAMMA TUNING PARAMETERS
uint8_t gamma1[] = {
            0x02, 0x1C, 0x07, 0x12,
            0x37, 0x32, 0x29, 0x2D,
            0x29, 0x25, 0x2B, 0x39,
            0x00, 0x01, 0x03, 0x10
        };

uint8_t gamma2[] = {
            0x03, 0x1D, 0x07, 0x06,
            0x2E, 0x2C, 0x29, 0x2D,
            0x2E, 0x2E, 0x37, 0x3F,
            0x00, 0x00, 0x02, 0x10
        };


// TAG
static const char *TAG = "DISPLAY";


static esp_lcd_panel_io_handle_t io_handle;


//CALLBACK
// static bool color_transfer_done_cb(
//     esp_lcd_panel_io_handle_t panel_io,
//     esp_lcd_panel_io_event_data_t *edata,
//     void *user_ctx
// )
// {
//     lv_display_t *disp =
//         (lv_display_t *)user_ctx;

//     lv_display_flush_ready(disp);

//     return false;
// }
static bool color_transfer_done_cb(
    esp_lcd_panel_io_handle_t panel_io,
    esp_lcd_panel_io_event_data_t *edata,
    void *user_ctx
)
{
    if(s_disp)
    {
        lv_display_flush_ready(s_disp);
    }

    return false;
}


// ========================================
// LOW LEVEL LCD HELPERS
// ========================================
static void lcd_cmd(uint8_t cmd)
{
    esp_lcd_panel_io_tx_param(
        io_handle,
        cmd, //0x2C before color transmit
        NULL,
        0
    );
}


static void lcd_data(
    uint8_t cmd,
    const void *data,
    size_t len
)
{
    esp_lcd_panel_io_tx_param(
        io_handle,
        cmd,
        data,
        len
    );
}

// ========================================
// ST7735 INIT
// ========================================

static void st7735_init(void)
{
    lcd_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(150));

    lcd_cmd(0x11);
    vTaskDelay(pdMS_TO_TICKS(500));

    uint8_t color_mode = 0x05;
    lcd_data(0x3A, &color_mode, 1);

    uint8_t madctl = 0xC0;
    lcd_data(0x36, &madctl, 1);

    lcd_cmd(0x13);

    lcd_cmd(0x29);

    lcd_data(0xE0, gamma1, sizeof(gamma1));

    lcd_data(0xE1, gamma2, sizeof(gamma2));

    vTaskDelay(pdMS_TO_TICKS(100));
}

// ========================================
// ADDRESS WINDOW
// ========================================

static void st7735_set_window(
    uint16_t x0,
    uint16_t y0,
    uint16_t x1,
    uint16_t y1
)
{
    x0 += x_offset;
    x1 += x_offset;

    y0 += y_offset;
    y1 += y_offset;

    uint8_t data[4];

    data[0] = x0 >> 8;
    data[1] = x0 & 0xFF;
    data[2] = x1 >> 8;
    data[3] = x1 & 0xFF;

    lcd_data(0x2A, data, 4);

    data[0] = y0 >> 8;
    data[1] = y0 & 0xFF;
    data[2] = y1 >> 8;
    data[3] = y1 & 0xFF;

    lcd_data(0x2B, data, 4);
}

// ========================================
// INIT
// ========================================

// void display_init()
void display_init(lv_display_t *disp)
{
    spi_bus_config_t buscfg = {
        .sclk_io_num = LCD_SCLK,
        .mosi_io_num = LCD_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz =
            LCD_WIDTH *
            LCD_HEIGHT *
            sizeof(uint16_t),
        // .max_transfer_sz =
        //     LCD_WIDTH *
        //     20 *
        //     sizeof(uint16_t),
    };

    ESP_ERROR_CHECK(
        spi_bus_initialize(
            SPI2_HOST,
            &buscfg,
            SPI_DMA_CH_AUTO
        )
    );

    // esp_lcd_panel_io_spi_config_t io_config = {
    //     .dc_gpio_num = LCD_DC,
    //     .cs_gpio_num = LCD_CS,
    //     .pclk_hz = 10 * 1000 * 1000,
    //     .lcd_cmd_bits = 8,
    //     .lcd_param_bits = 8,
    //     .spi_mode = 0,
    //     .trans_queue_depth = 10,
    // };
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = LCD_DC,
        .cs_gpio_num = LCD_CS,
        .pclk_hz = 10 * 1000 * 1000,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,

        .on_color_trans_done =
            color_transfer_done_cb,

        // .user_ctx = disp,
    };

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_io_spi(
            (esp_lcd_spi_bus_handle_t)SPI2_HOST,
            &io_config,
            &io_handle
        )
    );

    gpio_config_t rst = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << LCD_RST),
    };

    gpio_config(&rst);

    gpio_set_level(LCD_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(100));

    gpio_set_level(LCD_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(100));

    st7735_init();

    ESP_LOGI(TAG, "ST7735 initialized");
}

// ========================================
// FLUSH
// ========================================

void display_flush(
    int x1,
    int y1,
    int x2,
    int y2,
    const void *color_data
)
{
    st7735_set_window(
        x1,
        y1,
        x2,
        y2
    );


    esp_lcd_panel_io_tx_color(
        io_handle,
        0x2C,
        color_data,
        (x2 - x1 + 1) *
        (y2 - y1 + 1) *
        sizeof(uint16_t)
    );
}

// ========================================
// FILL
// ========================================

void display_fill(uint16_t color)
{
    static uint16_t buffer[LCD_WIDTH];

    for (int i = 0; i < LCD_WIDTH; i++)
    {
        buffer[i] =
            (color << 8) |
            (color >> 8);
        // buffer[i] = color;
    }

    for (int y = 0; y < LCD_HEIGHT; y++)
    {
        display_flush(
            0,
            y,
            LCD_WIDTH - 1,
            y,
            buffer
        );
    }
}

// ========================================
// ROTATION
// ========================================

void display_rotation(
    display_rotation_t rotation
)
{
    uint8_t madctl = 0;

    switch (rotation)
    {
        case DISPLAY_ROTATION_0:

            // madctl = 0xC0;
            // madctl = 0xC8;
            madctl = 0x60;

            x_offset = 2;
            y_offset = 1;

            break;

        case DISPLAY_ROTATION_90:

            madctl = 0x60; //A0, A8, 60(Good), 70 (Good), 20(good)

            x_offset = 0; //1,0,0,1,3
            y_offset = 0; //2,0,1,0,0

            break;

        case DISPLAY_ROTATION_180:

            madctl = 0x00;

            x_offset = 2;
            y_offset = 1;

            break;

        case DISPLAY_ROTATION_270:

            madctl = 0x60;

            x_offset = 1;
            y_offset = 2;

            break;
    }

    lcd_data(0x36, &madctl, 1);
}




//setter
void display_set_lvgl_display(
    lv_display_t *disp
)
{
    s_disp = disp;
}

