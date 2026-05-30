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

        "managers/screen_manager.c"

        "widgets/menu_button.c"

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