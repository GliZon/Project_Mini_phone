#include "keyboard.h"
#include "driver/gpio.h"

static const char keymap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

static const gpio_num_t cols[4] = {
    GPIO_NUM_26,
    GPIO_NUM_25,
    GPIO_NUM_33,
    GPIO_NUM_32,
};

static const gpio_num_t rows[4] = {
    GPIO_NUM_13,
    GPIO_NUM_12,
    GPIO_NUM_14,
    GPIO_NUM_27
};


void keyboard_init(void)
{
    for (int i = 0; i < 4; i++) {

        gpio_set_direction(rows[i], GPIO_MODE_OUTPUT);
        gpio_set_level(rows[i], 1);

        gpio_set_direction(cols[i], GPIO_MODE_INPUT);
        gpio_pullup_en(cols[i]);
    }
}

char keyboard_scan(void)
{
    for (int r = 0; r < 4; r++) {

        // all rows HIGH
        for (int i = 0; i < 4; i++) {
            gpio_set_level(rows[i], 1);
        }

        // current row LOW
        gpio_set_level(rows[r], 0);

        for (int c = 0; c < 4; c++) {

            if (gpio_get_level(cols[c]) == 0) {

                return keymap[r][c];
            }
        }
    }

    return '\0';
}