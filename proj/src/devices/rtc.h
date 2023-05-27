/**
 * @file
 * @brief Real-Time Clock (RTC) functions
 *
 * This file contains functions related to the Real-Time Clock (RTC).
 */

#ifndef __RTC_H
#define __RTC_H

#include <lcom/lcf.h>
#include <stdint.h>

// Macros

#define IRQ_RTC 8
#define REGISTER_INPUT 0x70 /**< Address of the RTC register to be accessed */
#define REGISTER_OUTPUT 0x71 /**< Transfer data to/from the RTC's register accessed */

// REGISTERS
#define SECONDS 0
#define SECONDS_ALARM 1
#define MINUTES 2
#define MINUTES_ALARM 3
#define HOURS 4
#define HOURS_ALARM 5
#define DAY_OF_WEEK 6
#define DAY 7
#define MONTH 8
#define YEAR 9

// REGISTER A
#define REGISTER_A 10
#define UPDATING BIT(7)

// REGISTER B
#define REGISTER_B 11
#define BINARY BIT(2)
#define FORMAT_TIME BIT(1)

// REGISTER C
#define REGISTER_C 12

// REGISTER D
#define REGISTER_D 13

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week_day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} time_display;

/** Structure to store the current time information used in the Game */
time_display time_info;


/**
 * @brief Subscribe to RTC interrupts
 *
 * Subscribes to RTC interrupts using the specified bit number.
 *
 * @param bit_rtc Pointer to the memory location where the bit number will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int rtc_subscribe_interrupts(uint8_t *bit_rtc);

/**
 * @brief Unsubscribe from RTC interrupts
 *
 * Unsubscribes from RTC interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise
 */
int rtc_unsubcribe_interrupts();

/**
 * @brief Read data from RTC register
 *
 * Reads data from the RTC's register using the specified command.
 *
 * @param cmd The command to be sent to the RTC register
 * @param output Pointer to the memory location where the read data will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int rtc_output(uint8_t cmd, uint8_t *output);

/**
 * @brief Check if RTC is updating
 *
 * Checks if the RTC is currently updating.
 *
 * @return Return 0 if RTC is not updating, non-zero otherwise
 */
int is_updating_rtc();

/**
 * @brief Convert value to binary representation
 *
 * Converts the given value to its binary representation.
 *
 * @param value Pointer to the value to be converted
 */
void convert_binary(uint8_t *value);

/**
 * @brief Update time display structure
 *
 * Updates the time display structure with the current time values from the RTC.
 *
 * @param time_info Pointer to the time display structure to be updated
 * @return Return 0 upon success, non-zero otherwise
 */
int update_time_display(time_display *time_info);

/**
 * @brief Get hours value from time display structure
 *
 * Retrieves the hours value from the time display structure.
 *
 * @param time_info The time display structure
 * @return The hours value
 */
int getHours(time_display time_info);

/**
 * @brief Get minutes value from time display structure
 *
 * Retrieves the minutes value from the time display structure.
 *
 * @param time_info The time display structure
 * @return The minutes value
 */
int getMinutes(time_display time_info);

/**
 * @brief Get seconds value from time display structure
 *
 * Retrieves the seconds value from the time display structure.
 *
 * @param time_info The time display structure
 * @return The seconds value
 */
int getSeconds(time_display time_info);

#endif
