#include "comm_service.h"

#include "app_state.h"

#include <stdio.h>



/*
 * Get State
 */

comm_state_t comm_service_get_state(
    void
)
{
    return app_state_get()->comm_state;
}



/*
 * Device Count
 */

uint8_t comm_service_get_device_count(
    void
)
{
    return app_state_get()->device_count;
}



/*
 * Get Device
 */

device_info_t *comm_service_get_device(
    uint8_t index
)
{
    app_state_t *state =
        app_state_get();

    if(index >= state->device_count)
    {
        return NULL;
    }

    return &state->devices[index];
}



/*
 * Selected Device
 */

uint8_t comm_service_get_selected_device(
    void
)
{
    return app_state_get()->selected_device;
}



/*
 * Pair Result
 */

bool comm_service_get_pairing_result(
    void
)
{
    return app_state_get()->pairing_success;
}



/*
 * Reset Comm State
 */

void comm_service_reset(
    void
)
{
    app_state_t *state =
        app_state_get();

    state->comm_state =
        COMM_STATE_IDLE;

    state->device_count =
        0;

    state->selected_device =
        0;

    state->pairing_success =
        false;
}



/*
 * Fake Scan
 */

static void fake_scan_results(
    void
)
{
    app_state_t *state =
        app_state_get();

    state->comm_state =
        COMM_STATE_DEVICE_LIST;

    state->device_count =
        3;



    /*
     * Device A
     */

    snprintf(
        state->devices[0].name,
        DEVICE_NAME_LEN,
        "DEVICE_A"
    );

    state->devices[0].paired =
        true;



    /*
     * Device B
     */

    snprintf(
        state->devices[1].name,
        DEVICE_NAME_LEN,
        "DEVICE_B"
    );

    state->devices[1].paired =
        false;



    /*
     * Device C
     */

    snprintf(
        state->devices[2].name,
        DEVICE_NAME_LEN,
        "DEVICE_C"
    );

    state->devices[2].paired =
        false;
}



/*
 * Start Scan
 */

void comm_service_start_scan(
    void
)
{
    app_state_t *state =
        app_state_get();

    state->comm_state =
        COMM_STATE_SCANNING;

    state->device_count =
        0;

    /*
     * TEMP
     * Fake Scan
     */

    fake_scan_results();
}



/*
 * Pair Device
 */

void comm_service_pair_device(
    uint8_t index
)
{
    app_state_t *state =
        app_state_get();

    if(index >= state->device_count)
    {
        return;
    }

    state->selected_device =
        index;

    state->comm_state =
        COMM_STATE_PAIRING;

    /*
     * TEMP
     * Fake Pairing
     */

    state->pairing_success =
        true;

    state->devices[index].paired =
        true;

    state->comm_state =
        COMM_STATE_RESULT;
}