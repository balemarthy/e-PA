/******************************************************************************
 *
 * FILE:
 *      configuration_manager.h
 *
 * DESCRIPTION:
 *      System configuration management service for the e-PA firmware.
 *
 * PURPOSE:
 *      Provides centralized management of configurable system parameters.
 *
 *      The Configuration Manager owns device configuration data,
 *      configuration persistence, configuration validation, and
 *      configuration version management.
 *
 * RESPONSIBILITIES:
 *      - Load configuration
 *      - Save configuration
 *      - Validate configuration
 *      - Manage configuration defaults
 *      - Manage configuration versioning
 *      - Provide configuration access services
 *
 * ARCHITECTURAL ROLE:
 *      Shared Services Layer
 *
 * DESIGN PATTERNS:
 *      - Configuration Service Pattern
 *      - Singleton Ownership Pattern
 *
 * COLLABORATORS:
 *      - storage_service
 *      - schedule_sync
 *      - wifi_manager
 *      - fault_monitor
 *
 * OWNERSHIP RULES:
 *      - Owns device configuration.
 *      - Owns configuration validation.
 *      - Owns configuration persistence.
 *      - Other modules consume configuration.
 *
 * MEMORY STRATEGY:
 *      - Static allocation only.
 *      - Single active configuration instance.
 *
 * TESTING CONSIDERATIONS:
 *      - Default configuration loading
 *      - Configuration persistence
 *      - Invalid configuration recovery
 *      - Version mismatch handling
 *      - Factory reset behavior
 *
 ******************************************************************************/

#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 * CONFIGURATION VERSION
 ******************************************************************************/

#define CONFIGURATION_VERSION      (1U)

/******************************************************************************
 * DEVICE CONFIGURATION
 ******************************************************************************/

typedef struct
{
    uint32_t configuration_version;

    bool audio_enabled;

    uint8_t volume_level;

    uint16_t default_snooze_minutes;

    bool auto_sync_enabled;

    uint32_t sync_interval_minutes;

} device_configuration_t;

/******************************************************************************
 * CONFIGURATION RESULT
 ******************************************************************************/

typedef enum
{
    CONFIGURATION_RESULT_OK = 0,

    CONFIGURATION_RESULT_INVALID,

    CONFIGURATION_RESULT_STORAGE_FAILURE,

    CONFIGURATION_RESULT_VERSION_MISMATCH

} configuration_result_t;

/******************************************************************************
 * MODULE INITIALIZATION
 ******************************************************************************/

/**
 * Initialize configuration manager.
 */
void configuration_manager_init(void);

/******************************************************************************
 * CONFIGURATION CONTROL
 ******************************************************************************/

/**
 * Load configuration from persistent storage.
 */
configuration_result_t configuration_load(void);

/**
 * Save configuration to persistent storage.
 */
configuration_result_t configuration_save(void);

/**
 * Restore factory defaults.
 */
configuration_result_t configuration_reset_defaults(void);

/******************************************************************************
 * CONFIGURATION ACCESS
 ******************************************************************************/

/**
 * Get active configuration.
 */
const device_configuration_t* configuration_get(void);

/**
 * Update active configuration.
 */
configuration_result_t configuration_set(
    const device_configuration_t *configuration);

/******************************************************************************
 * CONFIGURATION VALIDATION
 ******************************************************************************/

/**
 * Validate configuration structure.
 */
bool configuration_validate(
    const device_configuration_t *configuration);

/******************************************************************************
 * DIAGNOSTICS
 ******************************************************************************/

/**
 * Configuration load count.
 */
uint32_t configuration_load_count(void);

/**
 * Configuration save count.
 */
uint32_t configuration_save_count(void);

/**
 * Configuration validation failure count.
 */
uint32_t configuration_validation_failure_count(void);

/******************************************************************************
 * REFERENCE CONFIGURATION ITEMS
 *
 * Audio
 *      - volume level
 *      - enable/disable
 *
 * Snooze
 *      - default duration
 *
 * Synchronization
 *      - auto sync enable
 *      - sync interval
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* CONFIGURATION_MANAGER_H */
