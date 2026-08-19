idf_component_register(

    SRCS

        "core/ui.c"
        "core/ui_input.c"
        "core/ui_styles.c"
        "core/ui_splash.c"
        "core/ui_event.c"

        "screens/home_screen.c"
        "screens/settings_screen.c"
        "screens/messages_screen.c"
        "screens/battery_screen.c"
        "screens/comm_screen.c"
        "screens/quick_message_screen.c"
        "screens/recipient_screen.c"
        "screens/common/list_screen.c"
        "screens/common/text_editor_screen.c"


        "managers/screen_manager.c"

        "widgets/menu_button.c"

        "services/settings_service.c"
        "services/message_service.c"
        "services/storage_service.c"
        "services/comm_service.c"
        "services/text_editor.c"

    INCLUDE_DIRS
        "include"

    REQUIRES
        lvgl
        display
        input
        app
)

target_add_binary_data(
    ${COMPONENT_LIB}
    "assets/splash.raw"
    BINARY
)