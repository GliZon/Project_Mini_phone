#include "text_editor_screen.h"
#include "text_editor.h"
#include "lvgl.h"



/*
 * UI Objects
 */

static lv_obj_t *title_label;
static lv_obj_t *text_label;
static lv_obj_t *help_label;



/*
 * Refresh
 */

void text_editor_screen_refresh(
    void
)
{
    text_editor_model_t *model =
        text_editor_get_model();

    if(model == NULL)
    {
        return;
    }

    lv_label_set_text(
        title_label,
        model->title
    );

    lv_label_set_text(
        text_label,
        text_editor_get_text()
    );
}



/*
 * Event Handler
 */

void text_editor_screen_handle_event(
    ui_event_t *event
)
{
    if(event == NULL)
    {
        return;
    }

    text_editor_handle_input(
        &event->input
    );

    text_editor_screen_refresh();
}



/*
 * Create
 */

void text_editor_screen_create(
    void
)
{
    lv_obj_t *screen =
        lv_screen_active();



    /*
     * Title
     */

    title_label =
        lv_label_create(screen);

    lv_obj_align(
        title_label,
        LV_ALIGN_TOP_MID,
        0,
        10
    );



    /*
     * Edited Text
     */

    text_label =
        lv_label_create(screen);

    lv_obj_align(
        text_label,
        LV_ALIGN_TOP_LEFT,
        10,
        40
    );



    /*
     * Help
     */

    help_label =
        lv_label_create(screen);

    lv_label_set_text(
        help_label,
        "*=DEL  0=SPACE\n"
        "A=CANCEL D=SAVE"
    );

    lv_obj_align(
        help_label,
        LV_ALIGN_BOTTOM_MID,
        0,
        -10
    );



    text_editor_screen_refresh();
}



/*
 * Destroy
 */

void text_editor_screen_destroy(
    void
)
{
    title_label = NULL;
    text_label  = NULL;
    help_label  = NULL;
}



/*
 * Enter
 */

void text_editor_screen_on_enter(
    void
)
{
    text_editor_screen_refresh();
}



/*
 * Exit
 */

void text_editor_screen_on_exit(
    void
)
{
}



/*
 * Update
 */

void text_editor_screen_update(
    uint32_t dt_ms
)
{
    (void)dt_ms;

    /*
     * Optional:
     * later add blinking cursor here
     */
}