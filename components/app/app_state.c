#include "app_state.h"

#include <string.h>



static app_state_t g_app_state;




void app_state_init(void)
{
    memset(
        &g_app_state,
        0,
        sizeof(g_app_state)
    );

    /*
     * Defaults
     */

    strcpy(
        g_app_state.device_name,
        "DEVICE"
    );

        strcpy(
        g_app_state.message.quick_messages[0],
        "HELP"
    );

    strcpy(
        g_app_state.message.quick_messages[1],
        "COME HERE"
    );

    strcpy(
        g_app_state.message.quick_messages[2],
        "LOW BATTERY"
    );

    g_app_state.message.draft[0] = '\0';

    g_app_state.device_type = DEVICE_TYPE_D;
    
    g_app_state.selected_device = 0;

    g_app_state.device_count = 0;

    g_app_state.first_boot = true;

    g_app_state.battery_percent = 100;

    g_app_state.runtime_seconds = 0;

    g_app_state.charging = false;

    g_app_state.message_mode = MESSAGE_MODE_NONE;
}



app_state_t *app_state_get(void)
{
    return &g_app_state;
}



const char *device_type_to_string(
    device_type_t type
)
{
    switch(type)
    {
        case DEVICE_TYPE_D:
            return "D";

        case DEVICE_TYPE_G:
            return "G";

        case DEVICE_TYPE_C:
            return "C";

        default:
            return "?";
    }
}


const char *message_mode_to_string(
    message_mode_t mode
)
{
    switch(mode)
    {
        case MESSAGE_MODE_NONE:
            return "NONE";

        case MESSAGE_MODE_INSTANT:
            return "FAST";

        case MESSAGE_MODE_WRITE:
            return "WRITE";

        default:
            return "?";
    }
}
