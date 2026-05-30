

// #include "comm_screen.h"

// #include "screen_manager.h"
// #include "ui_input.h"

// #include "lvgl.h"


// static comm_screen_t g_comm;
// static lv_group_t *group;

// /*
//  * Event Handler
//  */

// void comm_screen_handle_event(
//     ui_event_t *event
// )
// {
//     switch(event->type)
//     {
//         default:
//             break;
//     }
// }



// /*
//  * Lifecycle
//  */

// void comm_screen_destroy(void)
// {
// }

// void comm_screen_on_enter(void)
// {
// }

// void comm_screen_on_exit(void)
// {
// }

// void comm_screen_update(
//     uint32_t dt_ms
// )
// {
// }



// /*
//  * Back Button
//  */

// static void back_event_cb(
//     lv_event_t *e
// )
// {
//     lv_event_code_t code =
//         lv_event_get_code(e);

//     if(code == LV_EVENT_CLICKED)
//     {
//         screen_manager_load(
//             SCREEN_HOME
//         );
//     }
// }



// /*
//  * Screen Create
//  */

// void comm_screen_create(void)
// {
//     lv_obj_t *screen =
//         lv_screen_active();



//     /*
//      * Background
//      */

//     lv_obj_set_style_bg_color(
//         screen,
//         lv_color_black(),
//         0
//     );



//     /*
//      * Group
//      */

//     group =
//         lv_group_create();

//     /*
//      * Title
//      */

//     lv_obj_t *title =
//         lv_label_create(screen);

//     lv_label_set_text(
//         title,
//         "Communication"
//     );

//     lv_obj_align(
//         title,
//         LV_ALIGN_TOP_MID,
//         0,
//         8
//     );



//     /*
//      * Connected Devices
//      */

//     lv_obj_t *devices =
//         lv_label_create(screen);

//     lv_label_set_text(
//         devices,
//         "Connected Devices: 2"
//     );

//     lv_obj_align(
//         devices,
//         LV_ALIGN_TOP_LEFT,
//         10,
//         40
//     );



//     /*
//      * Device List
//      */

//     lv_obj_t *dev1 =
//         lv_label_create(screen);

//     lv_label_set_text(
//         dev1,
//         "- DEVICE_A"
//     );

//     lv_obj_align(
//         dev1,
//         LV_ALIGN_TOP_LEFT,
//         20,
//         65
//     );



//     lv_obj_t *dev2 =
//         lv_label_create(screen);

//     lv_label_set_text(
//         dev2,
//         "- DEVICE_B"
//     );

//     lv_obj_align(
//         dev2,
//         LV_ALIGN_TOP_LEFT,
//         20,
//         85
//     );



//     /*
//      * Back Button
//      */

//     lv_obj_t *btn_back =
//         lv_btn_create(screen);

//     lv_obj_set_size(
//         btn_back,
//         70,
//         28
//     );

//     lv_obj_align(
//         btn_back,
//         LV_ALIGN_BOTTOM_MID,
//         0,
//         -10
//     );



//     lv_obj_t *label_back =
//         lv_label_create(btn_back);

//     lv_label_set_text(
//         label_back,
//         "Back"
//     );

//     lv_obj_center(
//         label_back
//     );



//     lv_obj_add_event_cb(
//         btn_back,
//         back_event_cb,
//         LV_EVENT_CLICKED,
//         NULL
//     );



//     /*
//      * Group
//      */

//     lv_group_add_obj(
//         group,
//         btn_back
//     );



//     /*
//      * Input
//      */

//     ui_input_set_group(
//         group
//     );



//     lv_group_focus_obj(
//         btn_back
//     );
// }

// static void comm_screen_refresh(void)
// {
//     app_state_t *state =
//         app_state_get();

//     char buffer[64];



//     /*
//      * Status
//      */

//     switch(state->comm_state)
//     {
//         case COMM_STATE_IDLE:

//             lv_label_set_text(
//                 g_comm.status,
//                 "No Devices"
//             );

//             break;



//         case COMM_STATE_SCANNING:

//             lv_label_set_text(
//                 g_comm.status,
//                 "Scanning..."
//             );

//             break;



//         case COMM_STATE_DEVICE_LIST:

//             snprintf(
//                 buffer,
//                 sizeof(buffer),
//                 "Devices Found: %d",
//                 state->device_count
//             );

//             lv_label_set_text(
//                 g_comm.status,
//                 buffer
//             );

//             break;



//         case COMM_STATE_PAIRING:

//             lv_label_set_text(
//                 g_comm.status,
//                 "Pairing..."
//             );

//             break;



//         case COMM_STATE_RESULT:

//             lv_label_set_text(
//                 g_comm.status,

//                 state->pairing_success ?
//                 "Pairing Success" :
//                 "Pairing Failed"
//             );

//             break;
//     }



//     /*
//      * Device Labels
//      */

//     for(int i = 0; i < MAX_DEVICES; i++)
//     {
//         if(i < state->device_count)
//         {
//             snprintf(
//                 buffer,
//                 sizeof(buffer),
//                 "%s [%s]",

//                 state->devices[i].name,

//                 state->devices[i].paired ?
//                 "P" :
//                 "-"
//             );

//             lv_label_set_text(
//                 g_comm.device_labels[i],
//                 buffer
//             );

//             lv_obj_clear_flag(
//                 g_comm.device_labels[i],
//                 LV_OBJ_FLAG_HIDDEN
//             );
//         }
//         else
//         {
//             lv_obj_add_flag(
//                 g_comm.device_labels[i],
//                 LV_OBJ_FLAG_HIDDEN
//             );
//         }
//     }
// }