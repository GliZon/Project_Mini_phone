#include "messages_screen.h"

#include "screen_manager.h"
#include "ui_input.h"
#include "text_editor_screen.h"
#include "text_editor.h"
#include "message_service.h"
#include "app_state.h"

#include "lvgl.h"

#include <string.h>



typedef enum
{
    MESSAGE_MENU_QUICK_MESSAGES,
    MESSAGE_MENU_WRITE_MESSAGE,
    MESSAGE_MENU_INBOX,

    MESSAGE_MENU_COUNT

} message_menu_item_t;



static lv_group_t *g_group;

static lv_obj_t *g_buttons[
    MESSAGE_MENU_COUNT
];

static char g_compose_buffer[
    MESSAGE_DRAFT_LEN
];



/*
 * Compose
 *
 * Runs while the editor screen is up, so it
 * touches state only, never this screen's
 * objects.
 */

static void on_compose_done(
    void *context,
    const char *text
)
{
    (void)context;

    message_service_set_draft(text);

    message_service_stage_outgoing(text);
}

static text_editor_model_t g_compose_editor =
{
    .title = "Write Message",

    .buffer = g_compose_buffer,

    .max_length = MESSAGE_DRAFT_LEN,

    .on_done = on_compose_done,

    .context = NULL
};



/*
 * Menu Event
 */

static void menu_item_event_cb(
    lv_event_t *e
)
{
    if(
        lv_event_get_code(e)
        != LV_EVENT_CLICKED
    )
    {
        return;
    }

    uint32_t index =
        (uint32_t)(uintptr_t)
        lv_obj_get_user_data(
            lv_event_get_target(e)
        );

    switch(index)
    {
        case MESSAGE_MENU_QUICK_MESSAGES:

            screen_manager_load(
                SCREEN_QUICK_MESSAGES
            );

            break;

        case MESSAGE_MENU_WRITE_MESSAGE:

            strncpy(
                g_compose_buffer,

                message_service_get_draft(),

                sizeof(g_compose_buffer) - 1
            );

            g_compose_buffer[
                sizeof(g_compose_buffer) - 1
            ] = '\0';

            text_editor_screen_open(
                &g_compose_editor,
                SCREEN_RECIPIENT,
                SCREEN_MESSAGES
            );

            break;

        case MESSAGE_MENU_INBOX:

            /*
             * Future:
             * SCREEN_INBOX
             */

            break;

        default:
            break;
    }
}



/*
 * Back
 */

static void back_event_cb(
    lv_event_t *e
)
{
    if(
        lv_event_get_code(e)
        == LV_EVENT_CLICKED
    )
    {
        screen_manager_load(
            SCREEN_HOME
        );
    }
}



/*
 * Event Handler
 */

void messages_screen_handle_event(
    ui_event_t *event
)
{
    switch(event->type)
    {
        default:
            break;
    }
}



/*
 * Lifecycle
 */

void messages_screen_destroy(void)
{
}

void messages_screen_on_enter(void)
{
}

void messages_screen_on_exit(void)
{
}

void messages_screen_update(
    uint32_t dt_ms
)
{
}



/*
 * Create
 */

void messages_screen_create(void)
{
    lv_obj_t *screen =
        lv_screen_active();

    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );



    /*
     * Group
     */

    g_group =
        lv_group_create();



    /*
     * Title
     */

    lv_obj_t *title =
        lv_label_create(screen);

    lv_label_set_text(
        title,
        "Messages"
    );

    lv_obj_align(
        title,
        LV_ALIGN_TOP_MID,
        0,
        5
    );



    const char *labels[
        MESSAGE_MENU_COUNT
    ] =
    {
        "Quick Messages",
        "Write Message",
        "Inbox"
    };



    /*
     * Menu Buttons
     */

    for(
        int i = 0;
        i < MESSAGE_MENU_COUNT;
        i++
    )
    {
        g_buttons[i] =
            lv_btn_create(screen);

        lv_obj_set_size(
            g_buttons[i],
            150,
            20
        );

        lv_obj_align(
            g_buttons[i],
            LV_ALIGN_TOP_MID,
            0,
            30 + (i * 28)
        );

        lv_obj_set_user_data(
            g_buttons[i],
            (void *)(uintptr_t)i
        );

        lv_obj_add_event_cb(
            g_buttons[i],
            menu_item_event_cb,
            LV_EVENT_CLICKED,
            NULL
        );

        lv_obj_t *label =
            lv_label_create(
                g_buttons[i]
            );

        lv_label_set_text(
            label,
            labels[i]
        );

        lv_obj_center(label);

        lv_group_add_obj(
            g_group,
            g_buttons[i]
        );
    }



    /*
     * Back
     */

    lv_obj_t *btn_back =
        lv_btn_create(screen);

    lv_obj_set_size(
        btn_back,
        60,
        20
    );

    lv_obj_align(
        btn_back,
        LV_ALIGN_BOTTOM_MID,
        0,
        -5
    );

    lv_obj_add_event_cb(
        btn_back,
        back_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );

    lv_obj_t *back_label =
        lv_label_create(btn_back);

    lv_label_set_text(
        back_label,
        "Back"
    );

    lv_obj_center(
        back_label
    );

    lv_group_add_obj(
        g_group,
        btn_back
    );



    /*
     * Input
     */

    ui_input_set_group(
        g_group
    );



    /*
     * Default Focus
     */

    lv_group_focus_obj(
        g_buttons[
            MESSAGE_MENU_QUICK_MESSAGES
        ]
    );
}