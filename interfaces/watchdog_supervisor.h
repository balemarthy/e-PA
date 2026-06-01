/******************************************************************************
 *
 * FILE:
 *      watchdog_supervisor.h
 *
 * DESCRIPTION:
 *      System watchdog supervision and health monitoring coordinator.
 *
 * PURPOSE:
 *      Provides a centralized mechanism for detecting runtime stalls,
 *      task starvation, and software lockups.
 *
 *      The Watchdog Supervisor is responsible for monitoring critical
 *      runtime components and ensuring the system remains responsive.
 *
 *      Unlike the hardware watchdog itself, this module owns the
 *      software supervision policy.
 *
 * RESPONSIBILITIES:
 *      - Monitor system health
 *      - Supervise critical runtime modules
 *      - Detect execution stalls
 *      - Detect missed heartbeats
 *      - Feed hardware watchdog when system healthy
 *      - Trigger fault reporting on failures
 *      - Coordinate recovery escalation
 *
 * ARCHITECTURAL ROLE:
 *      Runtime Infrastructure Layer
 *
 * DESIGN PATTERNS:
 *      - Watchdog Pattern
 *      - Heartbeat Supervision Pattern
 *      - Health Monitor Pattern
 *
 * COLLABORATORS:
 *      - fault_monitor
 *      - event_dispatcher
 *      - timer_service
 *      - reminder_runtime
 *      - wifi_manager
 *      - schedule_sync
 *
 * OWNERSHIP RULES:
 *      - Owns supervision policy.
 *      - Owns heartbeat tracking.
 *      - Owns watchdog feeding decisions.
 *      - Does not own subsystem recovery.
 *      - Does not own hardware watchdog implementation.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed supervision table.
 *
 * TESTING CONSIDERATIONS:
 *      - Heartbeat timeout detection
 *      - False positive prevention
 *      - Multiple subsystem supervision
 *      - Watchdog feed behavior
 *      - Fault escalation
 *      - Recovery coordination
 *
 ******************************************************************************/

#ifndef WATCHDOG_SUPERVISOR_H
#define WATCHDOG_SUPERVISOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define WATCHDOG_MAX_SUPERVISED_MODULES      (16U)

/******************************************************************************
 * SUPERVISED MODULES
 ******************************************************************************/

typedef enum
{
    WATCHDOG_MODULE_RUNTIME = 0,

    WATCHDOG_MODULE_SCHEDULER,

    WATCHDOG_MODULE_WIFI,

    WATCHDOG_MODULE_SYNC,

    WATCHDOG_MODULE_AUDIO,

    WATCHDOG_MODULE_STORAGE,

    WATCHDOG_MODULE_COUNT

} watchdog_module_id_t;

/******************************************************************************
 * SUPERVISION STATUS
 ******************************************************************************/

typedef enum
{
    WATCHDOG_STATUS_HEALTHY = 0,

    WATCHDOG_STATUS_WARNING,

    WATCHDOG_STATUS_TIMEOUT,

    WATCHDOG_STATUS_FAULT

} watchdog_status_t;

/******************************************************************************
 * HEARTBEAT CONFIGURATION
 ******************************************************************************/

typedef struct
{
    watchdog_module_id_t module_id;

    uint32_t timeout_ms;

} watchdog_registration_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize watchdog supervisor.
 */
void watchdog_supervisor_init(void);

/******************************************************************************
 * SUPERVISION MANAGEMENT
 ******************************************************************************/

/**
 * Register supervised module.
 */
bool watchdog_supervisor_register(
    const watchdog_registration_t *registration);

/**
 * Remove supervised module.
 */
bool watchdog_supervisor_unregister(
    watchdog_module_id_t module_id);

/******************************************************************************
 * HEARTBEAT INTERFACE
 ******************************************************************************/

/**
 * Report module heartbeat.
 *
 * Expected to be called periodically
 * by supervised modules.
 */
bool watchdog_supervisor_kick(
    watchdog_module_id_t module_id);

/******************************************************************************
 * STATUS QUERIES
 ******************************************************************************/

/**
 * Get module supervision status.
 */
watchdog_status_t watchdog_supervisor_status(
    watchdog_module_id_t module_id);

/**
 * Returns true if entire system healthy.
 */
bool watchdog_supervisor_system_healthy(void);

/******************************************************************************
 * PROCESSING
 ******************************************************************************/

/**
 * Runtime supervision processing.
 *
 * Responsibilities:
 *      - Evaluate heartbeat deadlines
 *      - Detect stalled modules
 *      - Generate watchdog faults
 *      - Feed hardware watchdog
 */
void watchdog_supervisor_process(void);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Number of watchdog feeds.
 */
uint32_t watchdog_supervisor_feed_count(void);

/**
 * Number of timeout detections.
 */
uint32_t watchdog_supervisor_timeout_count(void);

/**
 * Number of supervision failures.
 */
uint32_t watchdog_supervisor_failure_count(void);

/******************************************************************************
 * REFERENCE WORKFLOW
 *
 * Runtime Module
 *      ->
 * Heartbeat
 *
 * Watchdog Supervisor
 *      ->
 * Track Activity
 *
 * All Modules Healthy
 *      ->
 * Feed Hardware Watchdog
 *
 * Missing Heartbeat
 *      ->
 * FAULT_DETECTED
 *
 * Recovery Failure
 *      ->
 * Watchdog Reset
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* WATCHDOG_SUPERVISOR_H */
