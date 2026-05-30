idf_component_register(
    SRCS
        "input.c"
        "keyboard.c"

    INCLUDE_DIRS
        "include"

    REQUIRES
        driver
        freertos
        esp_timer
)