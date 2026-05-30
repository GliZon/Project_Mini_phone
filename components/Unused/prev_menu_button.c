//Previous_button state.

// #include "menu_button.h"
// #include "lvgl.h"

// lv_obj_t *menu_button_create(
//     lv_obj_t *parent,
//     lv_group_t *group,
//     const char *text,
//     int x,
//     int y
// )
// {
//     lv_obj_t *btn =
//         lv_btn_create(parent);

//     lv_obj_set_pos(
//         btn,
//         x,
//         y
//     );

//     lv_obj_set_size(
//         btn,
//         66,
//         52
//     );

//     /*
//      * Base Style
//      */

//     lv_obj_set_style_radius(
//         btn,
//         8,
//         LV_PART_MAIN
//     );

//     lv_obj_set_style_outline_width(
//         btn,
//         0,
//         LV_PART_MAIN
//     );

//     lv_obj_set_style_border_width(
//         btn,
//         0,
//         LV_PART_MAIN
//     );

//     lv_obj_set_style_shadow_width(
//         btn,
//         0,
//         LV_PART_MAIN
//     );

//     lv_obj_set_style_pad_all(
//         btn,
//         0,
//         LV_PART_MAIN
//     );

//     /*
//      * Default State
//      */

//     lv_obj_set_style_bg_color(
//         btn,
//         lv_color_hex(0x202020),
//         LV_PART_MAIN | LV_STATE_DEFAULT
//     );

//     /*
//      * Focused State
//      */

//     lv_obj_set_style_bg_color(
//         btn,
//         lv_color_hex(0x505050),
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     );

//     lv_obj_set_style_border_width(
//         btn,
//         2,
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     );

//     lv_obj_set_style_border_color(
//         btn,
//         lv_palette_main(LV_PALETTE_BLUE),
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     );

//     /*
//      * Disable Scroll
//      */

//     lv_obj_clear_flag(
//         btn,
//         LV_OBJ_FLAG_SCROLLABLE
//     );

//     /*
//      * Label
//      */

//     lv_obj_t *label =
//         lv_label_create(btn);

//     lv_label_set_text(
//         label,
//         text
//     );

//     lv_obj_center(label);

//     /*
//      * Group
//      */

//     lv_group_add_obj(
//         group,
//         btn
//     );

//     return btn;
// }



// // #include "menu_button.h"
// // #include "lvgl.h"

// // static lv_group_t *group;

// // lv_obj_t *menu_button_create(
// //     lv_obj_t *parent,
// //     lv_group_t *group,
// //     const char *text,
// //     int x,
// //     int y
// // )
// // {
// //     lv_obj_t *btn = lv_btn_create(parent);

// //     lv_obj_set_pos(
// //         btn,
// //         x,
// //         y
// //     );

// //     // Safe Size
// //     lv_obj_set_size(
// //         btn,
// //         66,
// //         52
// //     );
    
// //     lv_obj_set_style_radius(
// //         btn,
// //         8,
// //         LV_PART_MAIN
// //     );

// //     lv_obj_set_style_outline_width(
// //         btn,
// //         0,
// //         LV_PART_MAIN
// //     );

// //     lv_obj_set_style_border_width(
// //         btn,
// //         0,
// //         LV_PART_MAIN
// //     );

// //     lv_obj_set_style_shadow_width(
// //         btn,
// //         0,
// //         LV_PART_MAIN
// //     );

// //     lv_obj_set_style_pad_all(
// //         btn,
// //         0,
// //         LV_PART_MAIN
// //     );
    
// //     // Normal state
// //     lv_obj_set_style_bg_color(
// //         btn,
// //         lv_color_hex(0x505050),
// //         LV_PART_MAIN | LV_STATE_FOCUSED
// //     );

// //     // Focus state 
// //     lv_obj_set_style_bg_color(
// //         btn,
// //         lv_color_hex(0x505050),
// //         LV_PART_MAIN | LV_STATE_FOCUSED 
// //     );

// //     // Disable Scroll
// //     lv_obj_clear_flag(
// //         btn,
// //         LV_OBJ_FLAG_SCROLLABLE
// //     );

// //     lv_obj_t *label = lv_label_create(btn); // Label

// //     lv_label_set_text(label, text);

// //     lv_obj_center(label);

// //     lv_group_add_obj( group, btn); // group

// //     return btn;
// // }