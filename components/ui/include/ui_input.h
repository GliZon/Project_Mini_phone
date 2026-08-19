#ifndef UI_INPUT_H
#define UI_INPUT_H

#include "lvgl.h"

#include <stdbool.h>

void ui_input_init(void);

void ui_input_set_group(lv_group_t *group);

/*
 * Raw Mode
 *
 * Screens that read digits themselves opt in so
 * LVGL group navigation does not swallow the same
 * keys. Detaches the indev group while active.
 */

void ui_input_set_raw_mode(bool raw);

/*
 * Pump
 *
 * poll() drains the keypad and queues both the
 * LVGL keys and the ui_events. process_events()
 * dispatches the ui_events, and must run outside
 * lv_timer_handler() because handlers rebuild the
 * screen.
 */

void ui_input_poll(void);

void ui_input_process_events(void);

#endif
