/******************************************************************************
 *
 * FILE:
 *      storage_service.h
 *
 * DESCRIPTION:
 *      Persistent storage service for the e-PA firmware.
 *
 * PURPOSE:
 *      Provides a centralized abstraction for non-volatile data storage.
 *
 *      The Storage Service hides underlying storage implementation details
 *      and provides a consistent interface for saving and retrieving
 *      configuration, reminder schedules, synchronization metadata,
 *      and runtime settings.
 *
 * RESPONSIBILITIES:
 *      - Store persistent data
 *      - Retrieve persistent data
 *      - Delete stored data
 *      - Validate stored records
 *      - Abstract storage implementation
 *      - Report storage errors
 *
 * ARCHITECTURAL ROLE:
 *      Shared Services Layer
 *
 * DESIGN PATTERNS:
 *      - Storage Abstraction Pattern
 *      - Repository Support Pattern
 *
 * COLLABORATORS:
 *      - configuration_manager
 *      - schedule_sync
 *      - reminder_scheduler
 *      - fault_monitor
 *      - platform_storage_driver
 *
 * OWNERSHIP RULES:
 *      - Owns persistent storage access.
 *      - Owns storage error reporting.
 *      - Does not own business data.
 *      - Does not own application behavior.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Fixed-size storage records for MVP.
 *
 * TESTING CONSIDERATIONS:
 *      - Read operations
 *      - Write operations
 *      - Record deletion
 *      - Storage corruption
 *      - Storage full conditions
 *      - Invalid key handling
 *
 ******************************************************************************/

#ifndef STORAGE_SERVICE_H
#define STORAGE_SERVICE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION
 ******************************************************************************/

#define STORAGE_KEY_MAX_LENGTH        (32U)
#define STORAGE_MAX_RECORD_SIZE       (512U)

/******************************************************************************
 * STORAGE RESULT
 ******************************************************************************/

typedef enum
{
    STORAGE_RESULT_OK = 0,

    STORAGE_RESULT_NOT_FOUND,

    STORAGE_RESULT_FULL,

    STORAGE_RESULT_INVALID_KEY,

    STORAGE_RESULT_INVALID_DATA,

    STORAGE_RESULT_IO_ERROR

} storage_result_t;

/******************************************************************************
 * STORAGE KEY
 ******************************************************************************/

typedef struct
{
    char key[STORAGE_KEY_MAX_LENGTH];

} storage_key_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize storage service.
 */
void storage_service_init(void);

/******************************************************************************
 * DATA OPERATIONS
 ******************************************************************************/

/**
 * Write data record.
 */
storage_result_t storage_write(
    const char *key,
    const void *data,
    uint32_t length);

/**
 * Read data record.
 */
storage_result_t storage_read(
    const char *key,
    void *buffer,
    uint32_t buffer_size,
    uint32_t *actual_length);

/**
 * Delete data record.
 */
storage_result_t storage_delete(
    const char *key);

/**
 * Check if record exists.
 */
bool storage_exists(
    const char *key);

/******************************************************************************
 * STORAGE MANAGEMENT
 ******************************************************************************/

/**
 * Erase all records.
 */
storage_result_t storage_format(void);

/**
 * Get available storage space.
 */
uint32_t storage_available_space(void);

/**
 * Get used storage space.
 */
uint32_t storage_used_space(void);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Total write operations.
 */
uint32_t storage_write_count(void);

/**
 * Total read operations.
 */
uint32_t storage_read_count(void);

/**
 * Total storage failures.
 */
uint32_t storage_failure_count(void);

/******************************************************************************
 * REFERENCE STORAGE USERS
 *
 * configuration_manager
 *      ->
 * device configuration
 *
 * schedule_sync
 *      ->
 * sync metadata
 *
 * reminder_scheduler
 *      ->
 * reminder repository
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* STORAGE_SERVICE_H */
