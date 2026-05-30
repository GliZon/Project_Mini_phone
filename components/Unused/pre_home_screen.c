
// void home_screen_create(void)
// {
//     lv_obj_clean(lv_screen_active());

//     // LVGL setups
//     lv_obj_t *screen = lv_screen_active();
    
//     lv_obj_set_style_bg_color(
//         screen,
//         lv_color_black(),
//         0
//     );

//     lv_obj_set_style_bg_opa(
//         screen,
//         LV_OPA_COVER,
//         0
//     );

//     group = lv_group_create();

//     menu_button_create(
//         screen,
//         group,
//         "BTRY",
//         5,
//         5
//     );

//     menu_button_create(
//         screen,
//         group,
//         "COMM",
//         85,
//         5
//     );

//     menu_button_create(
//         screen,
//         group,
//         "SETNG",
//         5,
//         70
//     );

//     menu_button_create(
//         screen,
//         group,
//         "MSG",
//         85,
//         70
//     );


//     //app_state
//     app_state_t *state = app_state_get();

//     char info[32];

//     snprintf(
//         info,
//         sizeof(info),
//         "%s [%s] %d%%",
//         state->device_name,
//         device_type_to_string(
//             state->device_type
//         ),
//         state->battery_percent
//     );

//     lv_label_set_text(title, info);

//     lv_obj_align(
//         title,
//         LV_ALIGN_TOP_MID,
//         0,
//         2
//     );


//     ui_input_set_group(group);

//     lv_group_focus_next(group);
// }


// lv_obj_t *menu_button_create(
//     lv_obj_t *parent,
//     lv_group_t *group,
//     const char *text,
//     int x,
//     int y
// )
// {
//     // =========================
//     // BUTTON CREATE
//     // =========================

//     lv_obj_t *btn =
//         lv_btn_create(parent);

//     lv_obj_set_pos(
//         btn,
//         x,
//         y
//     );

//     // =========================
//     // SAFE SIZE
//     // =========================

//     lv_obj_set_size(
//         btn,
//         66,
//         52
//     );

//     // =========================
//     // REMOVE ALL FANCY EFFECTS
//     // =========================

//     lv_obj_set_style_radius(
//         btn,
//         1,
//         1
//     );

//     // lv_obj_set_style_border_width(
//     //     btn,
//     //     0,
//     //     0
//     // );

//     // lv_obj_set_style_outline_width(
//     //     btn,
//     //     0,
//     //     0
//     // );
//     lv_obj_set_style_outline_width(
//         btn,
//         0,
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     ); //No issue

//     lv_obj_set_style_border_width(
//         btn,
//         0,
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     ); // No issue

//     // lv_obj_set_style_shadow_width(
//     //     btn,
//     //     0,
//     //     0
//     // );
//     lv_obj_set_style_shadow_width(
//         btn,
//         0,
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     );

//     lv_obj_set_style_pad_all(
//         btn,
//         0,
//         0
//     );

//     // =========================
//     // NORMAL STATE
//     // =========================

//     // lv_obj_set_style_bg_color(
//     //     btn,
//     //     lv_color_hex(0x202020),
//     //     LV_PART_MAIN | LV_STATE_DEFAULT
//     // );
//     lv_obj_set_style_bg_color(
//         btn,
//         lv_color_hex(0x505050),
//         LV_PART_MAIN | LV_STATE_FOCUSED
//     );

//     // =========================
//     // FOCUSED STATE
//     // =========================

//     lv_obj_set_style_bg_color(
//         btn,
//         lv_color_hex(0x505050),
//         LV_PART_MAIN | LV_STATE_FOCUSED 
//     );

//     // =========================
//     // DISABLE SCROLL
//     // =========================

//     lv_obj_clear_flag(
//         btn,
//         LV_OBJ_FLAG_SCROLLABLE
//     );

//     // =========================
//     // LABEL
//     // =========================

//     lv_obj_t *label =
//         lv_label_create(btn);

//     lv_label_set_text(
//         label,
//         text
//     );

//     lv_obj_center(label);

//     // =========================
//     // GROUP
//     // =========================

//     lv_group_add_obj(
//         group,
//         btn
//     );

//     return btn;
// }




//NEXY


// #include "home_screen.h"
// #include "ui_input.h"
// #include "ui_event.h"
// #include "lvgl.h"
// #include "app_state.h"
// #include <stdio.h>
// #include "menu_button.h"
// #include "screen_manager.h"


// static home_screen_t g_home;

// // Even Handler
// void home_screen_handle_event(
//     ui_event_t *event
// )
// {
//     switch(event->type)
//     {
//         case UI_EVENT_MENU_BUTTON:

//             switch(event->menu_button_id)
//             {
//                 case MENU_BUTTON_BATTERY:

//                     screen_manager_load(
//                         SCREEN_BATTERY
//                     );

//                     break;

//                 case MENU_BUTTON_COMM:

//                     screen_manager_load(
//                         SCREEN_COMM
//                     );

//                     break;

//                 case MENU_BUTTON_SETTINGS:

//                     screen_manager_load(
//                         SCREEN_SETTINGS
//                     );

//                     break;

//                 case MENU_BUTTON_MESSAGES:

//                     screen_manager_load(
//                         SCREEN_MESSAGES
//                     );

//                     break;
//             }

//             break;

//         default:
//             break;
//     }
// }

// void home_screen_create(void)
// {
//     lv_obj_clean(lv_screen_active());

//     lv_obj_t *screen =
//         lv_screen_active();

//     app_state_t *state =
//         app_state_get();

//     /*
//      * Screen background
//      */

//     lv_obj_set_style_bg_color(
//         screen,
//         lv_color_black(),
//         0
//     );

//     lv_obj_set_style_bg_opa(
//         screen,
//         LV_OPA_COVER,
//         0
//     );

//     /*
//      * Group
//      */

//     g_home.group =
//         lv_group_create();

//     /*
//      * Top info label
//      */

//     g_home.title =
//         lv_label_create(screen);

//     char info[32];

//     snprintf(
//         info,
//         sizeof(info),
//         "%s [%s]", //%d%%
//         state->device_name,
//         device_type_to_string(state->device_type)
//     );
//         // state->battery_percent
//     // );

//     lv_label_set_text(
//         g_home.title,
//         info
//     );

//     lv_obj_align(
//         g_home.title,
//         LV_ALIGN_TOP_MID,
//         0,
//         2
//     );

//     /*
//      * Buttons
//      */
//     g_home.btn_battery = menu_button_create(
//         screen,
//         g_home.group,

//         MENU_BUTTON_BATTERY,

//         "100%",
//         "Battery",
//         5,
//         22
//     );

//     g_home.btn_comm =
//         menu_button_create(
//             screen,
//             g_home.group,
//             MENU_BUTTON_COMM,
//             "D|2", "COM",
//             85,
//             22
//         );

//     g_home.btn_settings =
//         menu_button_create(
//             screen,
//             g_home.group,
//             MENU_BUTTON_SETTINGS,
//             "", "SETNG",
//             5,
//             78
//         );

//     g_home.btn_messages =
//         menu_button_create(
//             screen,
//             g_home.group,
//             MENU_BUTTON_MESSAGES,
//             "","MSG",
//             85,
//             78
//         );

//     /*
//      * Input
//      */

//     ui_input_set_group(
//         g_home.group
//     );

//     lv_group_focus_obj(
//         g_home.btn_battery
//     );
// }

