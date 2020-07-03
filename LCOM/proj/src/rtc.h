#pragma once

#include <stdint.h>

#define BIT(n) (0x01 << (n))

#define RTC_IRQ 8

#define ADDRESS_REG 0x70
#define DATA_REG 0x71
#define REGISTER_A 0x0A
#define REGISTER_B 0x0B
#define REGISTER_C 0x0C
#define HOUR_ADDRESS 0x04

#define RATE_SET_BYTE 0x0F
#define INTERRUPT_ENABLE_BIT BIT(6)
#define INTERRUPT_DISABLE_BYTE 0xbf
#define PERIODIC_INTERRUPT_BIT BIT(6)

#define RTC_SUCCESS 0
#define RTC_ERROR 1
#define ENABLE_INTERRUPT 2
#define DISABLE_INTERRUPT 3
#define SET_INTERRUPT_RATE 4

/**
 * @brief Subscribes the RTC's interrupts.
 *
 * @param bit_no Address of the bit order in the interrupt mask.
 * @return Bit order of the RTC in the interrupt mask, -1 if an error is found.
 */
int rtc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes the RTC's interrupts.
 *
 * @return 0 on success, -1 on failure.
 */
int rtc_unsubscribe_int();

/**
 * @brief Writes the address that will be written/read from on the RTC's address register.
 *
 * @param reg Address that we want to access.
 * @return 0 on success, -1 on failure.
 */
int rtc_write_address(uint8_t reg);

/**
 * @brief Reads the data from one of the RTC's registers.
 *
 * @param reg Address that we want to access.
 * @param regcontent Memory address that will be filled with the RTC's data.
 * @return 0 on success, -1 on failure.
 */
int read_rtc_data(uint8_t reg, uint8_t *regcontent);

/**
 * @brief Issues a command to the RTC.
 *
 * @param command Command to be issued.
 * @return 0 on success, -1 on failure.
 */
int rtc_command(int command);

/**
 * @brief Reads the current hour value on the RTC's hour address.
 *
 * @param time Memory address to be filled with the current hour.
 * @return 0 on success, -1 on failure.
 */
int rtc_get_time(uint8_t *time);

/**
 * @brief Reads the data from the RTC's periodic interrupt register, and raises an event to the state machine buffer to update the game's time.
 *
 */
void rtc_int_handler();
