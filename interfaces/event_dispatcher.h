/******************************************************************************
 *
 * FILE:
 *      event_dispatcher.h
 *
 * DESCRIPTION:
 *      Central runtime event routing infrastructure for the e-PA firmware.
 *
 * PURPOSE:
 *      Provides decoupled communication between runtime modules using
 *      semantic events.
 *
 *      The Event Dispatcher is the heart of the event-driven runtime
 *      architecture selected for the e-PA system.
 *
 * RESPONSIBILITIES:
 *      - Maintain runtime event queue
 *      - Accept events from producers
 *      - Route events to consumers
 *      - Preserve event ordering
 *      - Decouple producers from consumers
 *      - Support deferred event processing
 *
 * ARCHITECTURAL ROLE:
 *      Runtime Infrastructure Layer
 *
 * DESIGN PATTERNS:
 *      - Event Dispatcher Pattern
 *      - Reactor Pattern
 *
 * COLLABORATORS:
 *      - timer_service
 *      - reminder_runtime
 *      - reminder_scheduler
 *      - snooze_manager
 *      - audio_playback
 *      - wifi_manager
 *      - fault_monitor
 *
 * EVENTS OWNED:
 *      All system-level semantic events.
 *
 * OWNERSHIP RULES:
 *      - Modules publish events.
 *      - Modules subscribe to events.
 *      - Modules must not directly invoke behavior in unrelated modules
 *        when an event-driven interaction is appropriate.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - No dynamic memory allocation.
 *
 * CONCURRENCY STRATEGY:
 *      - Single-threaded cooperative runtime.
 *      - ISR-safe event posting permitted.
 *      - Event processing occurs in runtime context.
 *
 * TESTING CONSIDERATIONS:
 *      - Event queue overflow
 *      - Event ordering
 *      - Subscriber registration
 *      - Event routing correctness
 *      - Invalid event handling
 *      - Queue wraparound behavior
 *
 ******************************************************************************/

#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define EVENT_DISPATCHER_MAX_SUBSCRIBERS      (8U)
#define EVENT_DISPATCHER_QUEUE_DEPTH          (32U)

/******************************************************************************
 * EVENT IDENTIFIERS
 *
 * NOTE:
 * These are semantic system events discovered during the Event Modeling stage.
 ******************************************************************************/

typedef enum
{
    EVENT_NONE = 0,

    /* Reminder Events */
    EVENT_REMINDER_DUE,
    EVENT_REMINDER_EXPIRED,
    EVENT_REMINDER_COMPLETED,

    /* Snooze Events */
    EVENT_USER_SNOOZE_REQUESTED,
    EVENT_SNOOZE_EXPIRED,

    /* Playback Events */
    EVENT_PLAYBACK_STARTED,
    EVENT_PLAYBACK_COMPLETED,
    EVENT_PLAYBACK_FAILED,

    /* Connectivity Events */
    EVENT_WIFI_CONNECTED,
    EVENT_WIFI_DISCONNECTED,
    EVENT_CONNECTIVITY_LOST,
    EVENT_CONNECTIVITY_RESTORED,

    /* Synchronization Events */
    EVENT_SYNC_STARTED,
    EVENT_SYNC_COMPLETED,
    EVENT_SYNC_FAILED,

    /* Time Events */
    EVENT_TIME_SYNC_COMPLETED,
    EVENT_TIME_SYNC_FAILED,

    /* Fault Events */
    EVENT_FAULT_DETECTED,
    EVENT_FAULT_CLEARED,

    EVENT_RECOVERY_STARTED,
    EVENT_RECOVERY_COMPLETED,

    EVENT_WATCHDOG_TIMEOUT,

    EVENT_COUNT

} event_id_t;

/******************************************************************************
 * EVENT PRIORITY
 *
 * Future enhancement.
 * May be ignored in MVP implementation.
 ******************************************************************************/

typedef enum
{
    EVENT_PRIORITY_LOW = 0,
    EVENT_PRIORITY_NORMAL,
    EVENT_PRIORITY_HIGH

} event_priority_t;

/******************************************************************************
 * EVENT DATA
 *
 * Generic event payload.
 *
 * Payload ownership remains with publisher.
 ******************************************************************************/

typedef struct
{
    event_id_t event_id;

    void *context;

} event_t;

/******************************************************************************
 * EVENT HANDLER
 ******************************************************************************/

typedef void (*event_handler_t)(const event_t *event);

/******************************************************************************
 * INITIALIZATION
 ******************************************************************************/

/**
 * Initialize event dispatcher infrastructure.
 */
void event_dispatcher_init(void);

/******************************************************************************
 * PUBLISHING
 ******************************************************************************/

/**
 * Publish an event to the runtime event queue.
 *
 * Returns:
 *      true  - event accepted
 *      false - queue full or invalid event
 */
bool event_publish(const event_t *event);

/**
 * Publish event from ISR context.
 *
 * Implementation may defer processing.
 */
bool event_publish_from_isr(const event_t *event);

/******************************************************************************
 * SUBSCRIPTION MANAGEMENT
 ******************************************************************************/

/**
 * Register handler for a specific event.
 */
bool event_subscribe(event_id_t event_id,
                     event_handler_t handler);

/**
 * Remove event subscription.
 */
bool event_unsubscribe(event_id_t event_id,
                       event_handler_t handler);

/******************************************************************************
 * PROCESSING
 ******************************************************************************/

/**
 * Process pending runtime events.
 *
 * Intended to be called from:
 *
 *      main runtime loop
 *
 * or
 *
 *      cooperative scheduler
 */
void event_dispatcher_process(void);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Returns number of pending events.
 */
uint16_t event_dispatcher_pending_count(void);

/**
 * Returns queue overflow count.
 */
uint32_t event_dispatcher_overflow_count(void);

/******************************************************************************
 * FUTURE EXTENSIONS
 *
 * Candidate future enhancements:
 *
 *      Event prioritization
 *      Event filtering
 *      Event tracing
 *      Event statistics
 *      Multi-subscriber routing
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* EVENT_DISPATCHER_H */
