#ifndef APP_STATE_H
#define APP_STATE_H

#include <stdint.h>
#include <stdbool.h>

#define DEVICE_NAME_LEN    32
#define MAX_DEVICES        5



/*
 * Device Type
 */

typedef enum
{
    DEVICE_TYPE_D,
    DEVICE_TYPE_G,
    DEVICE_TYPE_C

} device_type_t;



/*
 * Message Mode
 */

typedef enum
{
    MESSAGE_MODE_NONE,
    MESSAGE_MODE_INSTANT,
    MESSAGE_MODE_WRITE

} message_mode_t;



/*
 * Comm State
 */

typedef enum
{
    COMM_STATE_IDLE,
    COMM_STATE_SCANNING,
    COMM_STATE_DEVICE_LIST,
    COMM_STATE_PAIRING,
    COMM_STATE_RESULT

} comm_state_t;



/*
 * Device Info
 */

typedef struct
{
    char name[DEVICE_NAME_LEN];

    bool paired;

} device_info_t;



/*
 * App State
 */
typedef struct
{
    char device_name[DEVICE_NAME_LEN];
    device_type_t device_type;

    bool first_boot;

    uint8_t battery_percent;

    uint32_t runtime_seconds;

    bool charging;


    /*Messaging*/
    message_mode_t message_mode;
    
    /*
     * Communication
     */
    comm_state_t comm_state;
    device_info_t devices[MAX_DEVICES];
    uint8_t device_count;
    uint8_t selected_device;
    bool pairing_success;

} app_state_t;



void app_state_init(void);

app_state_t *app_state_get(void);

const char *device_type_to_string(
    device_type_t type
);

const char *message_mode_to_string(
    message_mode_t mode
);

#endif