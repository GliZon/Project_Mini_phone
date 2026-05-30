#include "ui_styles.h"

lv_style_t style_focus;
lv_style_t style_menu_btn;

void ui_styles_init(void)
{
    // ========================================
    // FOCUS STYLE
    // ========================================

    lv_style_init(&style_focus);

    lv_style_set_border_width(
        &style_focus,
        1 //3
    );

    lv_style_set_border_color(
        &style_focus,
        lv_palette_main(LV_PALETTE_BLUE)
    );

    lv_style_set_border_opa(
        &style_focus,
        LV_OPA_COVER
    );

    // ========================================
    // MENU BUTTON STYLE
    // ========================================

    lv_style_init(&style_menu_btn);

    lv_style_set_radius(
        &style_menu_btn,
        8
    );

    lv_style_set_bg_color(
        &style_menu_btn,
        lv_palette_main(LV_PALETTE_GREY)
    );

    lv_style_set_bg_opa(
        &style_menu_btn,
        LV_OPA_COVER
    );

    lv_style_set_text_color(
        &style_menu_btn,
        lv_color_white()
    );
}