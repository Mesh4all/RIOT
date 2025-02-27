/*
 * Copyright (C) 2022 Gunar Schorcht
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_esp32
 * @{
 *
 * @file
 * @brief       SDK configuration used by ESP-IDF for all ESP32x SoC variants (families)
 *
 * The SDK configuration can be partially overridden by application-specific
 * board configuration.
 *
 * @author      Gunar Schorcht <gunar@schorcht.net>
 */

#ifndef SDKCONFIG_H
#define SDKCONFIG_H

/*
 * The SoC capability definitions are often included indirectly in the
 * ESP-IDF files, although all ESP-IDF files require them. Since not all
 * ESP-IDF header files are included in RIOT, the SoC capability definitions
 * are unknown if they are only indirectly included. Therefore, the SoC
 * capabilities are included in this file and are thus available to all
 * ESP-IDF files. This avoids to update vendor code.
 */
#include "soc/soc_caps.h"

/**
 * @brief   SDK version number
 *
 * Determined with `git describe --tags` in `$ESP32_SDK_DIR`
 */
#if !defined(IDF_VER)
#include "esp_idf_ver.h"
#endif

#ifndef DOXYGEN

/**
 * Default console configuration
 *
 * STDIO_UART_BAUDRATE is used as CONFIG_CONSOLE_UART_BAUDRATE and
 * can be overridden by an application specific configuration.
 */
#define CONFIG_CONSOLE_UART_NUM 0
#define CONFIG_ESP_CONSOLE_UART_NUM     CONFIG_CONSOLE_UART_NUM

#ifndef CONFIG_CONSOLE_UART_BAUDRATE
#define CONFIG_CONSOLE_UART_BAUDRATE    STDIO_UART_BAUDRATE
#endif

/**
 * Log output configuration (DO NOT CHANGE)
 */
#ifndef CONFIG_LOG_DEFAULT_LEVEL
#define CONFIG_LOG_DEFAULT_LEVEL    LOG_LEVEL
#endif
#define CONFIG_LOG_MAXIMUM_LEVEL    LOG_LEVEL

/**
 * System specific configuration (DO NOT CHANGE)
 */
#ifdef MODULE_NEWLIB_NANO
#define CONFIG_NEWLIB_NANO_FORMAT               1
#endif

#define CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_4     1
#define CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE      32
#define CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE 2560

#define CONFIG_ESP_TIME_FUNCS_USE_ESP_TIMER     1
#define CONFIG_ESP_TIMER_TASK_STACK_SIZE        3584
#define CONFIG_ESP_TIMER_INTERRUPT_LEVEL        1
#define CONFIG_TIMER_TASK_STACK_SIZE            CONFIG_ESP_TIMER_TASK_STACK_SIZE

#define CONFIG_APP_BUILD_TYPE_APP_2NDBOOT       1
#define CONFIG_APP_BUILD_GENERATE_BINARIES      1
#define CONFIG_APP_BUILD_BOOTLOADER             1
#define CONFIG_APP_BUILD_USE_FLASH_SECTIONS     1

#define CONFIG_PARTITION_TABLE_CUSTOM_FILENAME  "partitions.csv"
#define CONFIG_PARTITION_TABLE_FILENAME         "partitions_singleapp.csv"
#define CONFIG_PARTITION_TABLE_SINGLE_APP       1
#define CONFIG_PARTITION_TABLE_OFFSET           0x8000

/**
 * Bluetooth configuration (DO NOT CHANGE)
 */
#define CONFIG_BT_ENABLED                       0
#define CONFIG_BT_RESERVE_DRAM                  0

/**
 * SPI RAM configuration (DO NOT CHANGE)
 */
#ifdef  MODULE_ESP_SPI_RAM
#define CONFIG_SPIRAM_TYPE_AUTO                 1
#define CONFIG_SPIRAM_SIZE                      -1
#define CONFIG_SPIRAM_SPEED_40M                 1
#define CONFIG_SPIRAM                           1
#define CONFIG_SPIRAM_BOOT_INIT                 1
#define CONFIG_SPIRAM_USE_MALLOC                0   /* using malloc requires QStaticQueue */
#define CONFIG_SPIRAM_MEMTEST                   1
#define CONFIG_SPIRAM_MALLOC_ALWAYSINTERNAL     16384
#define CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL   32768
#endif

/**
 * SPI Flash driver configuration (DO NOT CHANGE)
 */
#define CONFIG_SPI_FLASH_ROM_DRIVER_PATCH           1
#define CONFIG_SPI_FLASH_USE_LEGACY_IMPL            1
#define CONFIG_SPI_FLASH_DANGEROUS_WRITE_ABORTS     1
#define CONFIG_SPI_FLASH_YIELD_DURING_ERASE         1
#define CONFIG_SPI_FLASH_ERASE_YIELD_DURATION_MS    20
#define CONFIG_SPI_FLASH_ERASE_YIELD_TICKS          1
#define CONFIG_SPI_FLASH_WRITE_CHUNK_SIZE           8192
#define CONFIG_SPI_FLASH_SUPPORT_ISSI_CHIP          1
#define CONFIG_SPI_FLASH_SUPPORT_MXIC_CHIP          1
#define CONFIG_SPI_FLASH_SUPPORT_GD_CHIP            1
#define CONFIG_SPI_FLASH_SUPPORT_WINBOND_CHIP       1

/**
 * Ethernet driver configuration (DO NOT CHANGE)
 */
#ifdef MODULE_ESP_ETH
#define CONFIG_ETH_ENABLED                      1
#endif

/**
 * Serial flasher config (defined by CFLAGS, only sanity check here)
 */
#if !defined(CONFIG_FLASHMODE_DOUT) && \
    !defined(CONFIG_FLASHMODE_DIO) && \
    !defined(CONFIG_FLASHMODE_QOUT) && \
    !defined(CONFIG_FLASHMODE_QIO)
#error "Flash mode not configured"
#endif

/**
 * Wi-Fi driver configuration (DO NOT CHANGE)
 */
#ifdef MODULE_ESP_WIFI_ANY
#define CONFIG_ESP32_WIFI_ENABLED               1
#define CONFIG_ESP32_WIFI_STATIC_RX_BUFFER_NUM  10
#define CONFIG_ESP32_WIFI_DYNAMIC_RX_BUFFER_NUM 32
#define CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER     1
#define CONFIG_ESP32_WIFI_TX_BUFFER_TYPE        1
#define CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER_NUM 32
#define CONFIG_ESP32_WIFI_CACHE_TX_BUFFER_NUM   32  /* required when CONFIG_SPIRAM_USE_MALLOC=0 */
#define CONFIG_ESP32_WIFI_AMPDU_TX_ENABLED      1
#define CONFIG_ESP32_WIFI_TX_BA_WIN             6
#define CONFIG_ESP32_WIFI_AMPDU_RX_ENABLED      1
#define CONFIG_ESP32_WIFI_RX_BA_WIN             6
#ifdef MODULE_ESP_IDF_NVS_ENABLED
#define CONFIG_ESP32_WIFI_NVS_ENABLED           1
#endif
#define CONFIG_ESP32_WIFI_TASK_PINNED_TO_CORE_0 1
#define CONFIG_ESP32_WIFI_SOFTAP_BEACON_MAX_LEN 752
#define CONFIG_ESP32_WIFI_MGMT_SBUF_NUM         32
#define CONFIG_ESP32_WIFI_IRAM_OPT              1
#define CONFIG_ESP32_WIFI_RX_IRAM_OPT           1
#define CONFIG_ESP32_WIFI_ENABLE_WPA3_SAE       1
#if defined(MODULE_ESP_WIFI_AP) || defined(MODULE_ESP_NOW)
#define CONFIG_ESP_WIFI_SOFTAP_SUPPORT          1
#endif
#endif

/**
 * PHY configuration
 */
#if MODULE_ESP_IDF_NVS_ENABLED
#define CONFIG_ESP_PHY_CALIBRATION_AND_DATA_STORAGE     1
#endif

#define CONFIG_ESP_PHY_MAX_TX_POWER                     20
#define CONFIG_ESP_PHY_MAX_WIFI_TX_POWER                20

#define CONFIG_ESP32_PHY_CALIBRATION_AND_DATA_STORAGE   CONFIG_ESP_PHY_CALIBRATION_AND_DATA_STORAGE
#define CONFIG_ESP32_PHY_MAX_WIFI_TX_POWER              CONFIG_ESP_PHY_MAX_WIFI_TX_POWER

#endif /* DOXYGEN */

/**
 * @brief   Include ESP32x family specific SDK configuration
 */
#if defined(CPU_FAM_ESP32)
#include "sdkconfig_esp32.h"
#elif defined(CPU_FAM_ESP32C3)
#include "sdkconfig_esp32c3.h"
#else
#error "ESP32x family implementation missing"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* SDKCONFIG_H */
/** @} */
