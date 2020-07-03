#pragma once

#include <stdint.h>
#include "macros.h"

#define DELAY_KBC 20000

#define KBC_IRQ 1

#define ESC_KEY_BREAKCODE 0x81
#define TWO_BYTE 0xE0
#define OUT_BUF 0x60
#define IN_BUF 0x60
#define STAT_REG 0x64
#define KBC_CMD_REG 0x64
#define OUT_BUF_FULL 0x01

#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)
#define OBF BIT(0)
#define IBF BIT(1)
#define AUX BIT(5)

#define READ_CMD 0x20
#define WRITE_CMD 0x60
#define MOUSE_WRITE_CMD 0xD4

#define COMPLETE_BYTE 0
#define INCOMPLETE_TWO_BYTE 1
#define COMPLETE_TWO_BYTE 2

#define W_KEY_MAKECODE 0x11
#define A_KEY_MAKECODE 0x1e
#define S_KEY_MAKECODE 0x1f
#define D_KEY_MAKECODE 0x20
#define Z_KEY_MAKECODE 0x2c
#define X_KEY_MAKECODE 0x2d

#define W_KEY_BREAKCODE 0x91
#define A_KEY_BREAKCODE 0x9e
#define S_KEY_BREAKCODE 0x9f
#define D_KEY_BREAKCODE 0xa0

/**
 * @brief Subscribes the keyboard's interrupts.
 *
 * @param bit_no Address of the bit order in the interrupt mask.
 * @return Returns the bit order of the keyboard in the interrupt mask, or returns -1 if an error is found.
 */
int kbc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes the keyboard's interrupts.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int kbc_unsubscribe_int();

/**
 * @brief Updates a global variable with the byte read from the keyboard.
 *
 */
void(kbc_ih)();

/**
 * @brief Reads the byte from the keyboard, and raises an event to the state machine buffer, if the byte corresponds to one of the game's controls.
 *
 */
void keyboard_int_handler();

/**
 * @brief Assembles the keyboard's make/break codes, depending if they have one byte or two bytes.
 *
 * @return Returns the status of the two byte codes, or returns a successful one byte reading.
 */
int read_keyboard_data();

/**
 * @brief Reads the byte from the output buffer of the keyboard.
 *
 * @return Returns the byte from the output buffer, or a negative value in case of an error.
 */
int read_scan_codes();

/**
 * @brief Writes a command to the KBC.
 *
 * @param type Type of command being written.
 * @param port Port where the command will be written.
 * @return Returns 0 if successful, or a negative value in the case of an error.
 */
int write_command(unsigned int type, unsigned int port);

/**
 * @brief Writes a command to the KBC.
 *
 * @param type Type of command being written.
 * @param cmd_byte Command byte being written.
 * @return Returns 0 if successful, or different values in the case of an error.
 */
unsigned int issue_command(unsigned int type, unsigned int cmd_byte);
