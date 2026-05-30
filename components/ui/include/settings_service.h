#pragma once

#include "app_state.h"

void settings_service_cycle_device_type(void);

void settings_service_cycle_message_mode(void);

const char *settings_service_get_device_name(void);

device_type_t settings_service_get_device_type(void);

message_mode_t settings_service_get_message_mode(void);

void settings_service_set_device_name(
    const char *name
);