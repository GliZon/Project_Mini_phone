#include "text_editor_screen.h"
#include "text_editor.h"
#include "screen_manager.h"
#include "ui_input.h"
#include "lvgl.h"
#include "ui_event.h"

#include "esp_log.h"

static const char *TAG = "TEXT_EDITOR_SCR";



/*
 * UI Objects
 */

static lv_obj_t *title_label;
static lv_obj_t *text_label;
static lv_obj_t *help_label;



/*
 * Return Targets
 */

static screen_id_t g_return_on_save =
    SCREEN_HOME;

static screen_id_t g_return_on_cancel =
    SCREEN_HOME;



/*
 * Open
 */

void text_editor_screen_open(
    text_editor_model_t *model,
    screen_id_t return_on_save,
    screen_id_t return_on_cancel
)
{
    text_editor_begin(model);

    if(!text_editor_is_active())
    {
        return;
    }

    g_return_on_save =
        return_on_save;

    g_return_on_cancel =
        return_on_cancel;

    screen_manager_load(
        SCREEN_TEXT_EDITOR
    );
}



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
        model->title ? model->title : "Edit"
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

    ESP_LOGI(
        TAG,
        "handle_event: type=%d active=%d text='%s'",
        (int)event->type,
        (int)text_editor_is_active(),
        text_editor_get_text()
    );

    /*
     * Save and cancel are taken here rather than
     * in text_editor so the screen knows which
     * outcome happened and where to go next.
     */

    if(event->type == UI_EVENT_D)
    {
        text_editor_save();

        screen_manager_load(
            g_return_on_save
        );

        return;
    }

    if(event->type == UI_EVENT_A)
    {
        text_editor_cancel();

        screen_manager_load(
            g_return_on_cancel
        );

        return;
    }

    text_editor_handle_input(event);

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

    lv_obj_set_style_bg_color(
        screen,
        lv_color_black(),
        0
    );

    ui_input_set_raw_mode(true);



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

    /*
     * The panel is 160x128 (see board.h), so the
     * box has to fit that, not a desktop-sized
     * guess.
     */

    lv_obj_t *text_box =
        lv_obj_create(screen);

    lv_obj_set_size(
        text_box,
        150,
        68
    );

    lv_obj_align(
        text_box,
        LV_ALIGN_TOP_MID,
        0,
        22
    );

    lv_obj_set_style_radius(
        text_box,
        4,
        0
    );

    lv_obj_set_style_bg_color(
        text_box,
        lv_color_hex(0x202020),
        0
    );

    lv_obj_set_style_bg_opa(
        text_box,
        LV_OPA_COVER,
        0
    );

    lv_obj_set_style_border_width(
        text_box,
        1,
        0
    );

    lv_obj_set_style_border_color(
        text_box,
        lv_color_hex(0x404040),
        0
    );

    lv_obj_set_style_shadow_width(
        text_box,
        0,
        0
    );

    lv_obj_set_style_pad_all(
        text_box,
        0,
        0
    );

    lv_obj_clear_flag(
        text_box,
        LV_OBJ_FLAG_SCROLLABLE
    );

    text_label =
        lv_label_create(text_box);

    /*
     * A label nested in a plain lv_obj_create()
     * container inherits that object's text color
     * instead of the screen's default, which can
     * land close enough to the card background to
     * be unreadable. Set it explicitly.
     */

    lv_obj_set_style_text_color(
        text_label,
        lv_color_white(),
        0
    );

    lv_obj_set_width(
        text_label,
        144
    );

    lv_label_set_long_mode(
        text_label,
        LV_LABEL_LONG_WRAP
    );

    lv_obj_align(
        text_label,
        LV_ALIGN_TOP_LEFT,
        3,
        3
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

    lv_obj_set_style_text_color(
        help_label,
        lv_color_hex(0x808080),
        0
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