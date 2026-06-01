#pragma once

#include "app_state.h"

#include <stdbool.h>
#include <stdint.h>



/*
 * State
 */

comm_state_t comm_service_get_state(
    void
);



/*
 * Devices
 */

uint8_t comm_service_get_device_count(
    void
);



device_info_t *comm_service_get_device(
    uint8_t index
);



uint8_t comm_service_get_selected_device(
    void
);



bool comm_service_get_pairing_result(
    void
);



/*
 * Actions
 */

void comm_service_reset(
    void
);



void comm_service_start_scan(
    void
);



void comm_service_pair_device(
    uint8_t index
);