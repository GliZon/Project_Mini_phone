#include "message_service.h"

#include "app_state.h"
#include "comm_service.h"

#include "esp_log.h"

#include <string.h>


static const char *TAG = "MSG_SERVICE";


/*
 * Quick Message Count
 */

uint8_t message_service_get_quick_message_count(
    void
)
{
    return MAX_QUICK_MESSAGES;
}


/*
 * Quick Message Getter
 */

const char *message_service_get_quick_message(
    uint8_t index
)
{
    app_state_t *state = app_state_get();

    if(index >= MAX_QUICK_MESSAGES)
    {
      static const char *EMPTY = "";
      return EMPTY;
    }
    return state->message.quick_messages[index];
}



/*
 * Quick Message Setter
 */

void message_service_set_quick_message(
    uint8_t index,
    const char *text
)
{
    app_state_t *state =
        app_state_get();

    if(index >= MAX_QUICK_MESSAGES)
    {
        return;
    }

    strncpy(
        state->message.quick_messages[index],
        text,
        QUICK_MESSAGE_LEN - 1
    );

    state->message.quick_messages[index]
        [QUICK_MESSAGE_LEN - 1] = '\0';
}



/*
 * Draft Getter
 */

const char *message_service_get_draft(
    void
)
{
    return app_state_get()->message.draft;
}



/*
 * Draft Setter
 */

void message_service_set_draft(
    const char *text
)
{
    app_state_t *state =
        app_state_get();

    strncpy(
        state->message.draft,
        text,
        MESSAGE_DRAFT_LEN - 1
    );

    state->message.draft[
        MESSAGE_DRAFT_LEN - 1
    ] = '\0';
}



/*
 * Stage Outgoing
 */

void message_service_stage_outgoing(
    const char *text
)
{
    app_state_t *state =
        app_state_get();

    if(text == NULL)
    {
        state->message.outgoing[0] = '\0';
        return;
    }

    strncpy(
        state->message.outgoing,
        text,
        MESSAGE_DRAFT_LEN - 1
    );

    state->message.outgoing[
        MESSAGE_DRAFT_LEN - 1
    ] = '\0';
}



/*
 * Outgoing Getter
 */

const char *message_service_get_outgoing(
    void
)
{
    return app_state_get()->message.outgoing;
}



/*
 * Clear Outgoing
 */

void message_service_clear_outgoing(
    void
)
{
    app_state_get()->message.outgoing[0] = '\0';
}



/*
 * Recipient Setter
 */

void message_service_set_recipient(
    uint8_t recipient
)
{
    app_state_get()->message.recipient =
        recipient;
}



/*
 * Recipient Getter
 */

uint8_t message_service_get_recipient(
    void
)
{
    return app_state_get()->message.recipient;
}



/*
 * Send
 */

bool message_service_send(
    void
)
{
    app_state_t *state =
        app_state_get();

    if(state->message.outgoing[0] == '\0')
    {
        return false;
    }

    uint8_t recipient =
        state->message.recipient;

    /*
     * Radio backend is not wired yet, so the
     * transport is a log line. Call sites and
     * the result contract stay the same once
     * it lands.
     */

    if(recipient == MESSAGE_RECIPIENT_ALL)
    {
        ESP_LOGI(
            TAG,
            "SEND [ALL] %s",
            state->message.outgoing
        );
    }
    else
    {
        device_info_t *device =
            comm_service_get_device(
                recipient
            );

        ESP_LOGI(
            TAG,
            "SEND [%s] %s",
            device ? device->name : "?",
            state->message.outgoing
        );
    }

    message_service_clear_outgoing();

    return true;
}