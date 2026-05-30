#include "ui_splash.h"

#include "display.h"
#include "board.h"

#include <stdint.h>
#include <stddef.h>

extern const uint8_t splash_raw_start[]
    asm("_binary_splash_raw_start");

extern const uint8_t splash_raw_end[]
    asm("_binary_splash_raw_end");

void ui_show_splash(void)
{
    size_t splash_size =
        splash_raw_end -
        splash_raw_start;

    (void)splash_size;

    display_flush(
        44,
        25,
        123,
        104,
        splash_raw_start
    );
}