/******************************************************************************
 *
 * FILE:
 *      rtc_manager.h
 *
 * DESCRIPTION:
 *      Real-Time Clock (RTC) management service.
 *
 * PURPOSE:
 *      Provides a centralized time management service for the e-PA
 *      firmware.
 *
 *      The RTC Manager owns current system time, time synchronization
 *      status, time validity, and time-related services required by
 *      reminder scheduling and synchronization workflows.
 *
 * RESPONSIBILITIES:
 *      - Maintain current date and time
 *      - Provide time query services
 *      - Manage time synchronization status
 *      - Detect invalid time conditions
 *      - Support offline time keeping
 *      - Support time updates from external sources
 *
 * ARCHITECTURAL ROLE:
 *      Shared Services Layer
 *
 * DESIGN PATTERNS:
 *      - Time Service Pattern
 *      - Single Source of Truth Pattern
 *
 * COLLABORATORS:
 *      - reminder_scheduler
 *      - schedule_sync
 *      - wifi_manager
 *      - event_dispatcher
 *      - rtc_platform
 *
 * OWNERSHIP RULES:
 *      - Owns current system time.
 *      - Owns time validity status.
 *      - Owns synchronization status.
 *      - Other modules consume time information.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Single active system time instance.
 *
 * TESTING CONSIDERATIONS:
 *      - Time updates
 *      - RTC rollover
 *      - Power restoration
 *      - Invalid time detection
 *      - Synchronization handling
 *      - Leap year handling
 *
 ******************************************************************************/

#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * DATE TIME
 ******************************************************************************/

typedef struct
{
    uint16_t year;

    uint8_t month;

    uint8_t day;

    uint8_t hour;

    uint8_t minute;

    uint8_t second;

} rtc_datetime_t;

/******************************************************************************
 * TIME STATUS
 ******************************************************************************/

typedef enum
{
    RTC_TIME_INVALID = 0,

    RTC_TIME_VALID,

    RTC_TIME_SYNCHRONIZED

} rtc_time_status_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize RTC manager.
 */
void rtc_manager_init(void);

/******************************************************************************
 * TIME ACCESS
 ******************************************************************************/

/**
 * Get current date and time.
 */
bool rtc_manager_get_time(
    rtc_datetime_t *datetime);

/**
 * Set current date and time.
 */
bool rtc_manager_set_time(
    const rtc_datetime_t *datetime);

/******************************************************************************
 * TIME STATUS
 ******************************************************************************/

/**
 * Returns current time validity status.
 */
rtc_time_status_t rtc_manager_status(void);

/**
 * Returns true if current time is valid.
 */
bool rtc_manager_time_valid(void);

/**
 * Returns true if time has been synchronized.
 */
bool rtc_manager_time_synchronized(void);

/******************************************************************************
 * SYNCHRONIZATION CONTROL
 ******************************************************************************/

/**
 * Mark time synchronized.
 */
void rtc_manager_mark_synchronized(void);

/**
 * Mark time invalid.
 */
void rtc_manager_mark_invalid(void);

/******************************************************************************
 * TIME UTILITIES
 ******************************************************************************/

/**
 * Compare two date/time values.
 *
 * Returns:
 *      <0 if time_a < time_b
 *       0 if equal
 *      >0 if time_a > time_b
 */
int32_t rtc_manager_compare(
    const rtc_datetime_t *time_a,
    const rtc_datetime_t *time_b);

/**
 * Convert datetime to epoch seconds.
 */
uint32_t rtc_manager_to_epoch(
    const rtc_datetime_t *datetime);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Number of time updates.
 */
uint32_t rtc_manager_update_count(void);

/**
 * Number of synchronization events.
 */
uint32_t rtc_manager_sync_count(void);

/**
 * Number of invalid time detections.
 */
uint32_t rtc_manager_invalid_time_count(void);

/******************************************************************************
 * REFERENCE WORKFLOW
 *
 * System Startup
 *      ->
 * Load RTC Time
 *
 * Time Valid
 *      ->
 * Scheduler Enabled
 *
 * Cloud Time Sync
 *      ->
 * Update RTC
 *
 * RTC Manager
 *      ->
 * TIME_SYNC_COMPLETED
 *
 * Time Lost
 *      ->
 * TIME_INVALID
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* RTC_MANAGER_H */
