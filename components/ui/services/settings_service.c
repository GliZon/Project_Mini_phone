#include "settings_service.h"

#include "app_state.h"



void settings_service_cycle_device_type(void)
{
    app_state_t *state =
        app_state_get();

    switch(state->device_type)
    {
        case DEVICE_TYPE_D:

            state->device_type =
                DEVICE_TYPE_G;

            break;

        case DEVICE_TYPE_G:

            state->device_type =
                DEVICE_TYPE_C;

            break;

        case DEVICE_TYPE_C:

            state->device_type =
                DEVICE_TYPE_D;

            break;
    }
}



void settings_service_cycle_message_mode(void)
{
    app_state_t *state =
        app_state_get();

    switch(state->message_mode)
    {
        case MESSAGE_MODE_NONE:

            state->message_mode =
                MESSAGE_MODE_INSTANT;

            break;

        case MESSAGE_MODE_INSTANT:

            state->message_mode =
                MESSAGE_MODE_WRITE;

            break;

        case MESSAGE_MODE_WRITE:

            state->message_mode =
                MESSAGE_MODE_NONE;

            break;
    }
}



const char *settings_service_get_device_name(void)
{
    return app_state_get()->device_name;
}



device_type_t settings_service_get_device_type(void)
{
    return app_state_get()->device_type;
}



message_mode_t settings_service_get_message_mode(void)
{
    return app_state_get()->message_mode;
}