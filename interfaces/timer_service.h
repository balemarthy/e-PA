/******************************************************************************
 *
 * FILE:
 *      timer_service.h
 *
 * DESCRIPTION:
 *      Central software timer management service for the e-PA firmware.
 *
 * PURPOSE:
 *      Provides deterministic timer functionality for runtime modules.
 *
 *      The Timer Service abstracts software timing operations and enables
 *      deferred execution without exposing implementation-specific timing
 *      mechanisms to application modules.
 *
 * RESPONSIBILITIES:
 *      - Create software timers
 *      - Stop software timers
 *      - Monitor timer expiration
 *      - Generate timeout callbacks
 *      - Support deferred execution
 *      - Support one-shot timers
 *      - Support periodic timers
 *
 * ARCHITECTURAL ROLE:
 *      Shared Services Layer
 *
 * DESIGN PATTERNS:
 *      - Timer Service Pattern
 *      - Deferred Execution Pattern
 *
 * COLLABORATORS:
 *      - reminder_scheduler
 *      - snooze_manager
 *      - wifi_manager
 *      - watchdog_supervisor
 *      - event_dispatcher
 *
 * OWNERSHIP RULES:
 *      - Timer Service owns timer lifecycle.
 *      - Clients own timer usage semantics.
 *      - Clients must not directly manipulate internal timer state.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - No dynamic memory allocation.
 *
 * TIMING MODEL:
 *      - Millisecond resolution.
 *      - Cooperative runtime.
 *      - Deterministic execution.
 *
 * TESTING CONSIDERATIONS:
 *      - Timer expiration accuracy
 *      - Simultaneous timer expiration
 *      - Timer cancellation
 *      - Timer restart behavior
 *      - Periodic timer operation
 *      - Timer table exhaustion
 *
 ******************************************************************************/

#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define TIMER_SERVICE_MAX_TIMERS      (16U)

/******************************************************************************
 * TIMER IDENTIFIER
 ******************************************************************************/

typedef uint16_t timer_id_t;

#define TIMER_INVALID_ID              ((timer_id_t)0xFFFFU)

/******************************************************************************
 * TIMER TYPE
 ******************************************************************************/

typedef enum
{
    TIMER_TYPE_ONE_SHOT = 0,
    TIMER_TYPE_PERIODIC

} timer_type_t;

/******************************************************************************
 * TIMER CALLBACK
 *
 * Called when timer expires.
 ******************************************************************************/

typedef void (*timer_callback_t)(timer_id_t timer_id,
                                 void *context);

/******************************************************************************
 * TIMER CONFIGURATION
 ******************************************************************************/

typedef struct
{
    uint32_t            period_ms;

    timer_type_t        type;

    timer_callback_t    callback;

    void               *context;

} timer_config_t;

/******************************************************************************
 * SERVICE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize timer service.
 */
void timer_service_init(void);

/******************************************************************************
 * TIMER CREATION
 ******************************************************************************/

/**
 * Create and start a timer.
 *
 * Returns:
 *      Valid timer identifier
 *      TIMER_INVALID_ID on failure
 */
timer_id_t timer_start(const timer_config_t *config);

/**
 * Stop timer.
 */
bool timer_stop(timer_id_t timer_id);

/**
 * Restart timer.
 */
bool timer_restart(timer_id_t timer_id);

/**
 * Change timer period.
 */
bool timer_set_period(timer_id_t timer_id,
                      uint32_t period_ms);

/******************************************************************************
 * TIMER STATE
 ******************************************************************************/

/**
 * Returns true if timer is active.
 */
bool timer_is_active(timer_id_t timer_id);

/**
 * Returns remaining time.
 *
 * Returns:
 *      Remaining time in milliseconds.
 */
uint32_t timer_remaining_time(timer_id_t timer_id);

/******************************************************************************
 * PROCESSING
 ******************************************************************************/

/**
 * Runtime processing function.
 *
 * Called periodically from:
 *
 *      main loop
 *
 * or
 *
 *      cooperative scheduler
 */
void timer_service_process(void);

/******************************************************************************
 * SYSTEM TICK INTERFACE
 *
 * Platform layer supplies tick updates.
 ******************************************************************************/

/**
 * Notify timer service of elapsed system tick.
 *
 * Typically called from:
 *
 *      SysTick ISR
 *
 * or
 *
 *      platform timing driver
 */
void timer_service_tick(void);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Number of active timers.
 */
uint16_t timer_service_active_count(void);

/**
 * Number of timer allocation failures.
 */
uint32_t timer_service_allocation_failures(void);

/******************************************************************************
 * FUTURE ENHANCEMENTS
 *
 * Candidate future enhancements:
 *
 *      Timer groups
 *      Timer priorities
 *      Timer statistics
 *      Event-based timer expiration
 *      Timer wheel implementation
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* TIMER_SERVICE_H */
