// #ifndef INPUT_EVENTS_H
// #define INPUT_EVENTS_H

// typedef struct {
//     char key;
//     int pressed;
// } input_event_t;

// #endif

#pragma once

#include <stdbool.h>

typedef enum {
    INPUT_EVENT_NONE = 0,
    INPUT_EVENT_PRESS,
    INPUT_EVENT_RELEASE
} input_event_type_t;

typedef struct {
    char key;
    input_event_type_t type;
} input_event_t;