/******************************************************************************
 *
 * FILE:
 *      schedule_sync.h
 *
 * DESCRIPTION:
 *      Reminder schedule synchronization manager.
 *
 * PURPOSE:
 *      Synchronizes reminder schedules between the cloud service and
 *      the local reminder repository.
 *
 *      This module is responsible for downloading reminder data,
 *      validating received payloads, updating local schedules, and
 *      coordinating synchronization status reporting.
 *
 * RESPONSIBILITIES:
 *      - Request schedule updates
 *      - Download reminder schedules
 *      - Parse schedule payloads
 *      - Validate schedule data
 *      - Update local reminder repository
 *      - Report synchronization status
 *
 * ARCHITECTURAL ROLE:
 *      Connectivity Layer
 *
 * DESIGN PATTERNS:
 *      - Synchronization Manager Pattern
 *      - Repository Update Pattern
 *
 * COLLABORATORS:
 *      - wifi_manager
 *      - reminder_scheduler
 *      - reminder_state
 *      - configuration_manager
 *      - storage_service
 *      - event_dispatcher
 *
 * OWNERSHIP RULES:
 *      - Owns synchronization workflow.
 *      - Owns payload validation.
 *      - Does not own reminder scheduling.
 *      - Does not own reminder lifecycle state.
 *      - Does not own Wi-Fi connectivity.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed synchronization buffer sizes.
 *
 * TESTING CONSIDERATIONS:
 *      - Successful synchronization
 *      - Invalid payload handling
 *      - Network loss during sync
 *      - Duplicate reminders
 *      - Repository update failures
 *      - Large payload handling
 *
 ******************************************************************************/

#ifndef SCHEDULE_SYNC_H
#define SCHEDULE_SYNC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define SCHEDULE_SYNC_MAX_PAYLOAD_SIZE      (4096U)

/******************************************************************************
 * SYNC STATE
 ******************************************************************************/

typedef enum
{
    SYNC_STATE_IDLE = 0,

    SYNC_STATE_REQUESTING,

    SYNC_STATE_DOWNLOADING,

    SYNC_STATE_VALIDATING,

    SYNC_STATE_UPDATING,

    SYNC_STATE_COMPLETED,

    SYNC_STATE_FAILED

} sync_state_t;

/******************************************************************************
 * SYNC RESULT
 ******************************************************************************/

typedef enum
{
    SYNC_RESULT_OK = 0,

    SYNC_RESULT_NETWORK_ERROR,

    SYNC_RESULT_INVALID_PAYLOAD,

    SYNC_RESULT_STORAGE_ERROR,

    SYNC_RESULT_TIMEOUT,

    SYNC_RESULT_INTERNAL_ERROR

} sync_result_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize synchronization manager.
 */
void schedule_sync_init(void);

/******************************************************************************
 * SYNCHRONIZATION CONTROL
 ******************************************************************************/

/**
 * Start synchronization cycle.
 */
bool schedule_sync_start(void);

/**
 * Cancel active synchronization.
 */
bool schedule_sync_cancel(void);

/******************************************************************************
 * STATUS QUERIES
 ******************************************************************************/

/**
 * Get synchronization state.
 */
sync_state_t schedule_sync_get_state(void);

/**
 * Returns true if synchronization is active.
 */
bool schedule_sync_is_active(void);

/**
 * Returns true if last synchronization succeeded.
 */
bool schedule_sync_last_successful(void);

/******************************************************************************
 * RUNTIME PROCESSING
 ******************************************************************************/

/**
 * Runtime processing function.
 *
 * Handles:
 *      - synchronization workflow
 *      - payload processing
 *      - repository updates
 *      - timeout handling
 */
void schedule_sync_process(void);

/******************************************************************************
 * EVENT HANDLING
 ******************************************************************************/

/**
 * Event dispatcher callback.
 */
void schedule_sync_event_handler(
    const void *event);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Successful synchronizations.
 */
uint32_t schedule_sync_success_count(void);

/**
 * Failed synchronizations.
 */
uint32_t schedule_sync_failure_count(void);

/**
 * Payload validation failures.
 */
uint32_t schedule_sync_validation_failure_count(void);

/**
 * Repository update failures.
 */
uint32_t schedule_sync_repository_failure_count(void);

/******************************************************************************
 * REFERENCE WORKFLOW
 *
 * WIFI_CONNECTED
 *      ->
 * Start Sync
 *
 * Request Schedule Payload
 *      ->
 * Download Payload
 *
 * Validate Payload
 *      ->
 * Update Repository
 *
 * Update Scheduler
 *      ->
 * SYNC_COMPLETED
 *
 * OR
 *
 * SYNC_FAILED
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SCHEDULE_SYNC_H */
