```c
/******************************************************************************
 *
 * FILE:
 *      reminder_state.h
 *
 * DESCRIPTION:
 *      Reminder lifecycle state management for the e-PA firmware.
 *
 * PURPOSE:
 *      Defines and manages the runtime state of reminders.
 *
 *      The Reminder State module is responsible for maintaining the
 *      lifecycle of a reminder from creation through completion.
 *
 *      This module centralizes reminder state transitions and prevents
 *      individual runtime modules from implementing independent state
 *      logic.
 *
 * RESPONSIBILITIES:
 *      - Maintain reminder lifecycle state
 *      - Validate state transitions
 *      - Provide state query services
 *      - Track reminder lifecycle progress
 *      - Enforce state ownership rules
 *
 * ARCHITECTURAL ROLE:
 *      Application Layer
 *
 * DESIGN PATTERNS:
 *      - Explicit Finite State Machine (FSM)
 *      - State Ownership Pattern
 *
 * COLLABORATORS:
 *      - reminder_runtime
 *      - reminder_scheduler
 *      - snooze_manager
 *      - audio_playback
 *
 * OWNERSHIP RULES:
 *      - Reminder State owns reminder lifecycle information.
 *      - Other modules may query state.
 *      - State transitions should occur through this module.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed maximum reminder count.
 *
 * TESTING CONSIDERATIONS:
 *      - Valid transitions
 *      - Invalid transitions
 *      - State persistence
 *      - Boundary conditions
 *      - Unknown reminder identifiers
 *
 ******************************************************************************/

#ifndef REMINDER_STATE_H
#define REMINDER_STATE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define REMINDER_STATE_MAX_REMINDERS      (32U)

/******************************************************************************
 * TYPES
 ******************************************************************************/

/*
 * Unique reminder identifier.
 *
 * Actual implementation may evolve later.
 */
typedef uint32_t reminder_id_t;

/******************************************************************************
 * REMINDER LIFECYCLE STATES
 *
 * State model derived from Event Model and CRC analysis.
 ******************************************************************************/

typedef enum
{
    REMINDER_STATE_IDLE = 0,

    /*
     * Reminder exists but is not yet active.
     */
    REMINDER_STATE_SCHEDULED,

    /*
     * Reminder currently active.
     */
    REMINDER_STATE_ACTIVE,

    /*
     * Reminder temporarily deferred.
     */
    REMINDER_STATE_SNOOZED,

    /*
     * Reminder finished successfully.
     */
    REMINDER_STATE_COMPLETED,

    /*
     * Reminder timed out or expired.
     */
    REMINDER_STATE_EXPIRED,

    /*
     * Reminder cancelled.
     */
    REMINDER_STATE_CANCELLED

} reminder_state_t;

/******************************************************************************
 * TRANSITION RESULT
 ******************************************************************************/

typedef enum
{
    REMINDER_TRANSITION_OK = 0,

    REMINDER_TRANSITION_INVALID_ID,

    REMINDER_TRANSITION_INVALID_STATE,

    REMINDER_TRANSITION_TABLE_FULL

} reminder_transition_result_t;

/******************************************************************************
 * REMINDER STATE ENTRY
 *
 * Internal representation concept.
 *
 * Final implementation may vary.
 ******************************************************************************/

typedef struct
{
    reminder_id_t      reminder_id;

    reminder_state_t   state;

    uint32_t           timestamp;

} reminder_state_entry_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize reminder state database.
 */
void reminder_state_init(void);

/******************************************************************************
 * REMINDER REGISTRATION
 ******************************************************************************/

/**
 * Register a reminder with state management.
 *
 * Initial state:
 *      REMINDER_STATE_SCHEDULED
 */
bool reminder_state_register(reminder_id_t reminder_id);

/**
 * Remove reminder from state management.
 */
bool reminder_state_unregister(reminder_id_t reminder_id);

/******************************************************************************
 * STATE TRANSITIONS
 ******************************************************************************/

/**
 * Request state transition.
 *
 * Module validates transition legality.
 */
reminder_transition_result_t reminder_state_transition(
    reminder_id_t reminder_id,
    reminder_state_t new_state);

/******************************************************************************
 * STATE QUERIES
 ******************************************************************************/

/**
 * Retrieve current reminder state.
 */
reminder_state_t reminder_state_get(
    reminder_id_t reminder_id);

/**
 * Check if reminder exists.
 */
bool reminder_state_exists(
    reminder_id_t reminder_id);

/******************************************************************************
 * STATE HELPERS
 ******************************************************************************/

/**
 * Returns true if reminder is active.
 */
bool reminder_state_is_active(
    reminder_id_t reminder_id);

/**
 * Returns true if reminder is complete.
 */
bool reminder_state_is_complete(
    reminder_id_t reminder_id);

/**
 * Returns true if reminder is snoozed.
 */
bool reminder_state_is_snoozed(
    reminder_id_t reminder_id);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Number of reminders currently tracked.
 */
uint16_t reminder_state_count(void);

/**
 * Number of invalid transition attempts.
 */
uint32_t reminder_state_invalid_transition_count(void);

/******************************************************************************
 * REFERENCE STATE TRANSITION MODEL
 *
 * SCHEDULED
 *      ->
 * ACTIVE
 *
 * ACTIVE
 *      ->
 * SNOOZED
 *
 * SNOOZED
 *      ->
 * ACTIVE
 *
 * ACTIVE
 *      ->
 * COMPLETED
 *
 * ACTIVE
 *      ->
 * EXPIRED
 *
 * Any State
 *      ->
 * CANCELLED
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* REMINDER_STATE_H */
```
