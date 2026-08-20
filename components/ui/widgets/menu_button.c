#include "menu_button.h"
#include "lvgl.h"
#include "ui_event.h"
#include "screen_manager.h"
#include "ui_event_dispatcher.h"


static void menu_button_event_cb(
    lv_event_t *e
);

lv_obj_t *menu_button_create(
    lv_obj_t *parent,
    lv_group_t *group,

    menu_button_id_t id,

    const char *value_text,
    const char *label_text,

    int x,
    int y
)
{
    /*
     * Button
     */

    lv_obj_t *btn =
        lv_btn_create(parent);

    lv_obj_set_pos(
        btn,
        x,
        y
    );

    /*
    * Button IDs
    */
    lv_obj_set_user_data(
        btn,
        (void *)id
    );

    lv_obj_add_event_cb(
        btn,
        menu_button_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );

    /*
     * Card Size
     */

    lv_obj_set_size(
        btn,
        72,
        44
    );

    /*
     * Base Style
     */

    lv_obj_set_style_radius(
        btn,
        3, //boxy or what?
        LV_PART_MAIN
    );

    lv_obj_set_style_outline_width(
        btn,
        0,
        LV_PART_MAIN
    );

    lv_obj_set_style_shadow_width(
        btn,
        0,
        LV_PART_MAIN
    );

    lv_obj_set_style_pad_all(
        btn,
        0,
        LV_PART_MAIN
    );

    /*
     * Default State
     */

    lv_obj_set_style_bg_color(
        btn,
        lv_color_hex(0x202020),
        LV_PART_MAIN | LV_STATE_DEFAULT
    );

    lv_obj_set_style_border_width(
        btn,
        1,
        LV_PART_MAIN | LV_STATE_DEFAULT
    );

    lv_obj_set_style_border_color(
        btn,
        lv_color_hex(0x404040),
        LV_PART_MAIN | LV_STATE_DEFAULT
    );

    /*
     * Focus State
     */

    lv_obj_set_style_bg_color(
        btn,
        lv_color_hex(0x303030),
        LV_PART_MAIN | LV_STATE_FOCUSED
    );

    lv_obj_set_style_border_width(
        btn,
        1,
        LV_PART_MAIN | LV_STATE_FOCUSED
    );

    lv_obj_set_style_border_color(
        btn,
        lv_palette_main(LV_PALETTE_BLUE),
        LV_PART_MAIN | LV_STATE_FOCUSED
    );

    /*
     * Disable Scroll
     */

    lv_obj_clear_flag(
        btn,
        LV_OBJ_FLAG_SCROLLABLE
    );

    /*
     * TOP VALUE LABEL
     */

    lv_obj_t *value =
        lv_label_create(btn);

    lv_obj_set_style_text_color(
        value,
        lv_color_white(),
        0
    );

    lv_label_set_text(
        value,
        value_text
    );

    lv_obj_align(
        value,
        LV_ALIGN_TOP_LEFT,
        6,
        3
    );

    /*
     * Divider Line
     */

    lv_obj_t *line =
        lv_obj_create(btn);

    lv_obj_set_size(
        line,
        60,
        1
    );

    lv_obj_align(
        line,
        LV_ALIGN_CENTER,
        0,
        0 //4
    );

    lv_obj_set_style_bg_color(
        line,
        lv_color_hex(0x505050),
        0
    );

    lv_obj_set_style_border_width(
        line,
        0,
        0
    );

    /*
     * Bottom Label
     */

    lv_obj_t *label =
        lv_label_create(btn);

    lv_obj_set_style_text_color(
        label,
        lv_color_white(),
        0
    );

    lv_label_set_text(
        label,
        label_text
    );

    lv_obj_align(
        label,
        LV_ALIGN_BOTTOM_LEFT,
        6,
        -3
    );

    lv_obj_add_event_cb(
        btn,
        menu_button_event_cb,
        LV_EVENT_CLICKED,
        NULL
    );
    /*
     * Group
     */

    lv_group_add_obj(
        group,
        btn
    );

    return btn;
}

static void menu_button_event_cb(
    lv_event_t *e
)
{
    lv_event_code_t code =
        lv_event_get_code(e);

    if(code != LV_EVENT_CLICKED)
    {
        return;
    }

    lv_obj_t *btn =
        lv_event_get_target(e);

    menu_button_id_t id =
        (menu_button_id_t)
        lv_obj_get_user_data(btn);

    ui_event_t event = {
        .type = UI_EVENT_MENU_BUTTON,
        .menu_button_id = id
    };

    ui_event_post(
        &event
    );
}