/******************************************************************************
 *
 * FILE:
 *      cloud_interface.h
 *
 * DESCRIPTION:
 *      Cloud communication abstraction layer for the e-PA firmware.
 *
 * PURPOSE:
 *      Provides a clean architectural boundary between application
 *      services and cloud communication mechanisms.
 *
 *      This module abstracts transport protocols, HTTP clients,
 *      payload exchange mechanisms, authentication methods, and
 *      cloud endpoint interactions from the rest of the system.
 *
 *      Application modules should never directly access networking
 *      stacks or protocol implementations.
 *
 * RESPONSIBILITIES:
 *      - Download reminder schedules
 *      - Upload device status
 *      - Upload diagnostics
 *      - Manage cloud requests
 *      - Abstract cloud communication
 *      - Report cloud communication status
 *
 * ARCHITECTURAL ROLE:
 *      Infrastructure Boundary Layer
 *
 * DESIGN PATTERNS:
 *      - Facade Pattern
 *      - Gateway Pattern
 *      - Adapter Pattern
 *
 * COLLABORATORS:
 *      - schedule_sync
 *      - wifi_manager
 *      - configuration_manager
 *      - fault_monitor
 *      - event_dispatcher
 *
 * OWNERSHIP RULES:
 *      - Owns cloud communication abstraction.
 *      - Owns request execution.
 *      - Does not own business rules.
 *      - Does not own reminder processing.
 *      - Does not own scheduling logic.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed communication buffers.
 *
 * TESTING CONSIDERATIONS:
 *      - Successful download
 *      - Communication timeout
 *      - Invalid payload
 *      - Authentication failure
 *      - Network loss
 *      - Server unavailable
 *
 ******************************************************************************/

#ifndef CLOUD_INTERFACE_H
#define CLOUD_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define CLOUD_MAX_URL_LENGTH          (128U)
#define CLOUD_MAX_PAYLOAD_SIZE        (4096U)

/******************************************************************************
 * CLOUD RESULT
 ******************************************************************************/

typedef enum
{
    CLOUD_RESULT_OK = 0,

    CLOUD_RESULT_TIMEOUT,

    CLOUD_RESULT_NETWORK_ERROR,

    CLOUD_RESULT_AUTHENTICATION_ERROR,

    CLOUD_RESULT_SERVER_ERROR,

    CLOUD_RESULT_INVALID_RESPONSE,

    CLOUD_RESULT_INTERNAL_ERROR

} cloud_result_t;

/******************************************************************************
 * REQUEST TYPES
 ******************************************************************************/

typedef enum
{
    CLOUD_REQUEST_SCHEDULE_DOWNLOAD = 0,

    CLOUD_REQUEST_DEVICE_STATUS,

    CLOUD_REQUEST_DIAGNOSTICS

} cloud_request_type_t;

/******************************************************************************
 * RESPONSE
 ******************************************************************************/

typedef struct
{
    cloud_result_t result;

    uint32_t response_length;

    uint16_t http_status;

} cloud_response_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize cloud interface.
 */
void cloud_interface_init(void);

/******************************************************************************
 * SCHEDULE OPERATIONS
 ******************************************************************************/

/**
 * Download reminder schedule payload.
 *
 * Payload buffer supplied by caller.
 */
cloud_result_t cloud_download_schedule(
    uint8_t *payload_buffer,
    uint32_t buffer_size,
    uint32_t *actual_size);

/******************************************************************************
 * DEVICE STATUS OPERATIONS
 ******************************************************************************/

/**
 * Upload device status.
 */
cloud_result_t cloud_upload_status(
    const uint8_t *payload,
    uint32_t payload_length);

/**
 * Upload diagnostic payload.
 */
cloud_result_t cloud_upload_diagnostics(
    const uint8_t *payload,
    uint32_t payload_length);

/******************************************************************************
 * STATUS QUERIES
 ******************************************************************************/

/**
 * Returns true if cloud service reachable.
 */
bool cloud_interface_available(void);

/**
 * Returns most recent cloud result.
 */
cloud_result_t cloud_interface_last_result(void);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Successful requests.
 */
uint32_t cloud_interface_success_count(void);

/**
 * Failed requests.
 */
uint32_t cloud_interface_failure_count(void);

/**
 * Timeout count.
 */
uint32_t cloud_interface_timeout_count(void);

/**
 * Authentication failures.
 */
uint32_t cloud_interface_auth_failure_count(void);

/******************************************************************************
 * REFERENCE WORKFLOW
 *
 * schedule_sync
 *      ->
 * cloud_download_schedule()
 *
 * cloud_interface
 *      ->
 * HTTP Request
 *
 * cloud_interface
 *      ->
 * Receive JSON Payload
 *
 * schedule_sync
 *      ->
 * Validate Payload
 *
 * reminder_scheduler
 *      ->
 * Update Schedule Repository
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* CLOUD_INTERFACE_H */
