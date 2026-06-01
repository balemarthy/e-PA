/******************************************************************************
 *
 * FILE:
 *      snooze_manager.h
 *
 * DESCRIPTION:
 *      Snooze coordination and deferred reminder activation service.
 *
 * PURPOSE:
 *      Manages temporary deferral of active reminders.
 *
 *      The Snooze Manager is responsible for tracking snoozed reminders,
 *      managing snooze timers, and restoring reminders when snooze periods
 *      expire.
 *
 * RESPONSIBILITIES:
 *      - Accept snooze requests
 *      - Create snooze timers
 *      - Track snoozed reminders
 *      - Restore reminders after snooze expiration
 *      - Coordinate snooze lifecycle
 *
 * ARCHITECTURAL ROLE:
 *      Application Layer
 *
 * DESIGN PATTERNS:
 *      - Deferred Execution Pattern
 *      - Timer Coordination Pattern
 *
 * COLLABORATORS:
 *      - reminder_runtime
 *      - reminder_state
 *      - timer_service
 *      - event_dispatcher
 *
 * OWNERSHIP RULES:
 *      - Owns snooze timing information.
 *      - Owns snoozed reminder tracking.
 *      - Does not own reminder lifecycle state.
 *      - Does not own reminder playback behavior.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed snooze capacity.
 *
 * TESTING CONSIDERATIONS:
 *      - Snooze creation
 *      - Snooze expiration
 *      - Multiple snoozed reminders
 *      - Snooze cancellation
 *      - Timer expiration behavior
 *      - Invalid reminder identifiers
 *
 ******************************************************************************/

#ifndef SNOOZE_MANAGER_H
#define SNOOZE_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define SNOOZE_MANAGER_MAX_ENTRIES      (16U)

#define SNOOZE_DEFAULT_DURATION_MIN     (5U)

/******************************************************************************
 * TYPES
 ******************************************************************************/

typedef uint32_t reminder_id_t;

/******************************************************************************
 * SNOOZE RESULT
 ******************************************************************************/

typedef enum
{
    SNOOZE_RESULT_OK = 0,

    SNOOZE_RESULT_INVALID_ID,

    SNOOZE_RESULT_ALREADY_SNOOZED,

    SNOOZE_RESULT_TABLE_FULL,

    SNOOZE_RESULT_INVALID_DURATION

} snooze_result_t;

/******************************************************************************
 * SNOOZE ENTRY
 ******************************************************************************/

typedef struct
{
    reminder_id_t reminder_id;

    uint32_t duration_ms;

    uint32_t expiration_tick;

} snooze_entry_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize snooze manager.
 */
void snooze_manager_init(void);

/******************************************************************************
 * SNOOZE CONTROL
 ******************************************************************************/

/**
 * Snooze reminder using default duration.
 */
snooze_result_t snooze_manager_request(
    reminder_id_t reminder_id);

/**
 * Snooze reminder using specified duration.
 */
snooze_result_t snooze_manager_request_duration(
    reminder_id_t reminder_id,
    uint32_t duration_ms);

/**
 * Cancel snooze operation.
 */
bool snooze_manager_cancel(
    reminder_id_t reminder_id);

/******************************************************************************
 * SNOOZE QUERIES
 ******************************************************************************/

/**
 * Returns true if reminder is snoozed.
 */
bool snooze_manager_is_snoozed(
    reminder_id_t reminder_id);

/**
 * Remaining snooze time.
 *
 * Returns:
 *      Remaining milliseconds.
 */
uint32_t snooze_manager_remaining_time(
    reminder_id_t reminder_id);

/**
 * Number of active snoozes.
 */
uint16_t snooze_manager_active_count(void);

/******************************************************************************
 * RUNTIME PROCESSING
 ******************************************************************************/

/**
 * Runtime processing function.
 *
 * Evaluates snooze expiration.
 */
void snooze_manager_process(void);

/******************************************************************************
 * EVENT HANDLING
 ******************************************************************************/

/**
 * Event dispatcher callback.
 */
void snooze_manager_event_handler(
    const void *event);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Total snooze requests processed.
 */
uint32_t snooze_manager_request_count(void);

/**
 * Total snooze expirations.
 */
uint32_t snooze_manager_expiration_count(void);

/**
 * Total snooze cancellations.
 */
uint32_t snooze_manager_cancel_count(void);

/**
 * Total snooze failures.
 */
uint32_t snooze_manager_failure_count(void);

/******************************************************************************
 * REFERENCE WORKFLOW
 *
 * Reminder Active
 *      ->
 * User Presses Snooze
 *
 * Snooze Manager
 *      ->
 * Create Snooze Timer
 *
 * Reminder State
 *      ->
 * SNOOZED
 *
 * Snooze Timer Expires
 *      ->
 * Generate SNOOZE_EXPIRED
 *
 * Reminder Runtime
 *      ->
 * Reactivate Reminder
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SNOOZE_MANAGER_H */
