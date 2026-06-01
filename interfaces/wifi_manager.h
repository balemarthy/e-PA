******************************************************************************
 *
 * FILE:
 *      wifi_manager.h
 *
 * DESCRIPTION:
 *      Wi-Fi connectivity management module for the e-PA firmware.
 *
 * PURPOSE:
 *      Manages wireless network connectivity and provides a stable
 *      communication interface to upper runtime modules.
 *
 *      The Wi-Fi Manager owns network connection establishment,
 *      reconnection handling, connection monitoring, and network
 *      status reporting.
 *
 * RESPONSIBILITIES:
 *      - Establish Wi-Fi connection
 *      - Disconnect from Wi-Fi
 *      - Monitor connection health
 *      - Perform automatic reconnection
 *      - Report connectivity events
 *      - Expose network status
 *
 * ARCHITECTURAL ROLE:
 *      Connectivity Layer
 *
 * DESIGN PATTERNS:
 *      - Connection Manager Pattern
 *      - Explicit State Machine Pattern
 *
 * COLLABORATORS:
 *      - schedule_sync
 *      - connectivity_monitor
 *      - led_indicator
 *      - event_dispatcher
 *      - wifi_platform
 *
 * OWNERSHIP RULES:
 *      - Owns Wi-Fi connection state.
 *      - Owns reconnection policy.
 *      - Does not own cloud synchronization.
 *      - Does not own application behavior.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - No dynamic memory allocation.
 *
 * TESTING CONSIDERATIONS:
 *      - Initial connection
 *      - Connection loss
 *      - Reconnection
 *      - Invalid credentials
 *      - Repeated failures
 *      - Connectivity restoration
 *
 ******************************************************************************/

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define WIFI_MANAGER_MAX_SSID_LENGTH         (32U)
#define WIFI_MANAGER_MAX_PASSWORD_LENGTH     (64U)

/******************************************************************************
 * WIFI STATE MACHINE
 ******************************************************************************/

typedef enum
{
    WIFI_STATE_DISCONNECTED = 0,

    WIFI_STATE_CONNECTING,

    WIFI_STATE_CONNECTED,

    WIFI_STATE_RECONNECTING,

    WIFI_STATE_ERROR

} wifi_state_t;

/******************************************************************************
 * WIFI CREDENTIALS
 ******************************************************************************/

typedef struct
{
    char ssid[WIFI_MANAGER_MAX_SSID_LENGTH];

    char password[WIFI_MANAGER_MAX_PASSWORD_LENGTH];

} wifi_credentials_t;

/******************************************************************************
 * CONNECTION RESULT
 ******************************************************************************/

typedef enum
{
    WIFI_RESULT_OK = 0,

    WIFI_RESULT_INVALID_CREDENTIALS,

    WIFI_RESULT_CONNECTION_FAILED,

    WIFI_RESULT_ALREADY_CONNECTED,

    WIFI_RESULT_INTERNAL_ERROR

} wifi_result_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize Wi-Fi manager.
 */
void wifi_manager_init(void);

/******************************************************************************
 * CONNECTION MANAGEMENT
 ******************************************************************************/

/**
 * Configure Wi-Fi credentials.
 */
bool wifi_manager_set_credentials(
    const wifi_credentials_t *credentials);

/**
 * Connect to configured network.
 */
wifi_result_t wifi_manager_connect(void);

/**
 * Disconnect from network.
 */
bool wifi_manager_disconnect(void);

/******************************************************************************
 * STATUS QUERIES
 ******************************************************************************/

/**
 * Get current Wi-Fi state.
 */
wifi_state_t wifi_manager_get_state(void);

/**
 * Returns true if connected.
 */
bool wifi_manager_is_connected(void);

/**
 * Returns current RSSI.
 *
 * Units:
 *      dBm
 */
int32_t wifi_manager_rssi(void);

/******************************************************************************
 * RUNTIME PROCESSING
 ******************************************************************************/

/**
 * Runtime processing function.
 *
 * Handles:
 *      - reconnect logic
 *      - health monitoring
 *      - timeout handling
 */
void wifi_manager_process(void);

/******************************************************************************
 * EVENT HANDLING
 ******************************************************************************/

/**
 * Event dispatcher callback.
 */
void wifi_manager_event_handler(
    const void *event);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Successful connections.
 */
uint32_t wifi_manager_connection_count(void);

/**
 * Disconnections detected.
 */
uint32_t wifi_manager_disconnect_count(void);

/**
 * Reconnection attempts.
 */
uint32_t wifi_manager_reconnect_count(void);

/**
 * Connection failures.
 */
uint32_t wifi_manager_failure_count(void);

/******************************************************************************
 * REFERENCE STATE MODEL
 *
 * DISCONNECTED
 *      ->
 * CONNECTING
 *
 * CONNECTING
 *      ->
 * CONNECTED
 *
 * CONNECTED
 *      ->
 * DISCONNECTED
 *
 * CONNECTED
 *      ->
 * RECONNECTING
 *
 * RECONNECTING
 *      ->
 * CONNECTED
 *
 * RECONNECTING
 *      ->
 * ERROR
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* WIFI_MANAGER_H */
