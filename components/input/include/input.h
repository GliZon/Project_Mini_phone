// #ifndef INPUT_H
// #define INPUT_H

// void input_init(void);

// char input_get_key(void);

// #endif

#pragma once

#include <stdbool.h>
#include "input_events.h"

void input_init(void);

bool input_get_event(input_event_t *event);