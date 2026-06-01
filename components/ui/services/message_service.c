#include "message_service.h"

#include "app_state.h"

#include <string.h>


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