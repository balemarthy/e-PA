/******************************************************************************
 *
 * FILE:
 *      fault_monitor.h
 *
 * DESCRIPTION:
 *      Runtime fault detection and supervision module.
 *
 * PURPOSE:
 *      Provides centralized fault detection, fault registration,
 *      fault reporting, and recovery coordination for the e-PA firmware.
 *
 *      The Fault Monitor acts as the primary health monitoring
 *      subsystem and provides visibility into runtime failures.
 *
 * RESPONSIBILITIES:
 *      - Register faults
 *      - Track active faults
 *      - Clear faults
 *      - Generate fault events
 *      - Coordinate recovery workflows
 *      - Provide diagnostic information
 *
 * ARCHITECTURAL ROLE:
 *      Runtime Infrastructure Layer
 *
 * DESIGN PATTERNS:
 *      - Fault Manager Pattern
 *      - Health Monitor Pattern
 *
 * COLLABORATORS:
 *      - event_dispatcher
 *      - wifi_manager
 *      - schedule_sync
 *      - audio_playback
 *      - storage_service
 *      - configuration_manager
 *      - watchdog_supervisor
 *
 * OWNERSHIP RULES:
 *      - Owns fault registry.
 *      - Owns fault state tracking.
 *      - Owns fault reporting.
 *      - Does not own subsystem recovery logic.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed fault table.
 *
 * TESTING CONSIDERATIONS:
 *      - Fault registration
 *      - Duplicate fault detection
 *      - Fault clearing
 *      - Multiple simultaneous faults
 *      - Recovery reporting
 *      - Fault overflow handling
 *
 ******************************************************************************/

#ifndef FAULT_MONITOR_H
#define FAULT_MONITOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define FAULT_MONITOR_MAX_FAULTS      (16U)

/******************************************************************************
 * FAULT IDENTIFIERS
 ******************************************************************************/

typedef enum
{
    FAULT_NONE = 0,

    FAULT_WIFI_CONNECTION,

    FAULT_SYNC_FAILURE,

    FAULT_STORAGE_FAILURE,

    FAULT_AUDIO_PLAYBACK,

    FAULT_CONFIGURATION,

    FAULT_WATCHDOG_TIMEOUT,

    FAULT_MEMORY_EXHAUSTION,

    FAULT_INTERNAL_ERROR,

    FAULT_COUNT

} fault_id_t;

/******************************************************************************
 * FAULT SEVERITY
 ******************************************************************************/

typedef enum
{
    FAULT_SEVERITY_INFO = 0,

    FAULT_SEVERITY_WARNING,

    FAULT_SEVERITY_ERROR,

    FAULT_SEVERITY_CRITICAL

} fault_severity_t;

/******************************************************************************
 * FAULT RECORD
 ******************************************************************************/

typedef struct
{
    fault_id_t fault_id;

    fault_severity_t severity;

    uint32_t timestamp;

    uint32_t occurrence_count;

    bool active;

} fault_record_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize fault monitor.
 */
void fault_monitor_init(void);

/******************************************************************************
 * FAULT REGISTRATION
 ******************************************************************************/

/**
 * Register fault occurrence.
 */
bool fault_monitor_report(
    fault_id_t fault_id,
    fault_severity_t severity);

/**
 * Clear active fault.
 */
bool fault_monitor_clear(
    fault_id_t fault_id);

/******************************************************************************
 * FAULT QUERIES
 ******************************************************************************/

/**
 * Check if fault is active.
 */
bool fault_monitor_is_active(
    fault_id_t fault_id);

/**
 * Get fault record.
 */
const fault_record_t* fault_monitor_get(
    fault_id_t fault_id);

/**
 * Returns true if any fault active.
 */
bool fault_monitor_has_active_faults(void);

/******************************************************************************
 * RECOVERY COORDINATION
 ******************************************************************************/

/**
 * Mark recovery started.
 */
bool fault_monitor_recovery_started(
    fault_id_t fault_id);

/**
 * Mark recovery completed.
 */
bool fault_monitor_recovery_completed(
    fault_id_t fault_id);

/******************************************************************************
 * EVENT HANDLING
 ******************************************************************************/

/**
 * Event dispatcher callback.
 */
void fault_monitor_event_handler(
    const void *event);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Active fault count.
 */
uint16_t fault_monitor_active_count(void);

/**
 * Total faults detected.
 */
uint32_t fault_monitor_total_faults(void);

/**
 * Total recoveries completed.
 */
uint32_t fault_monitor_recovery_count(void);

/**
 * Fault overflow count.
 */
uint32_t fault_monitor_overflow_count(void);

/******************************************************************************
 * REFERENCE WORKFLOW
 *
 * Subsystem Failure
 *      ->
 * FAULT_DETECTED
 *
 * Fault Monitor
 *      ->
 * Register Fault
 *
 * Fault Monitor
 *      ->
 * Generate Fault Event
 *
 * Recovery Successful
 *      ->
 * FAULT_CLEARED
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* FAULT_MONITOR_H */
