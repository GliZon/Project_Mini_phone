#include "input.h"
#include "keyboard.h"

static char last_key = '\0';

void input_init(void)
{
    keyboard_init();
}

bool input_get_event(input_event_t *event)
{
    char current_key = keyboard_scan();

    // NEW PRESS
    if (current_key != '\0' && last_key == '\0') {

        last_key = current_key;

        event->key = current_key;
        event->type = INPUT_EVENT_PRESS;

        return true;
    }

    // RELEASE
    if (current_key == '\0' && last_key != '\0') {

        event->key = last_key;
        event->type = INPUT_EVENT_RELEASE;

        last_key = '\0';

        return true;
    }

    return false;
}