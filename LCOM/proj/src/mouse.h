#pragma once

#include <stdint.h>
#include "macros.h"
#include <stdbool.h>

#define MOUSE_IRQ 12

#define ENABLE_DATA 0xF4
#define DISABLE_DATA 0xF5
#define REMOTE_MODE 0xF0
#define STREAM_MODE 0xEA
#define READ_DATA 0xEB

#define PS2_ACK 0xFA
#define PS2_NACK 0xFE
#define PS2_ERROR 0xFC

#define LB BIT(0)
#define RB BIT(1)
#define MB BIT(2)
#define MOUSETEST BIT(3)
#define XSIGN BIT(4)
#define YSIGN BIT(5)
#define XOVF BIT(6)
#define YOVF BIT(7)

#define PACKET_READY 0
#define PACKET_NOT_READY 1
#define PACKET_OUT_OF_SYNC 2

/**
 * @brief Subscribes the mouse's interrupts.
 *
 * @param bit_no Address of the bit order in the interrupt mask.
 * @return Returns the bit order of the mouse in the interrupt mask, or returns -1 if an error is found.
 */
int mouse_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes the mouse's interrupts.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int mouse_unsubscribe_int();

/**
 * @brief Updates a global variable with the byte read from the mouse, and raises an event to the state machine buffer if a mouse packet is complete.
 *
 */
void(mouse_ih)();

/**
 * @brief Writes a mouse command to the KBC.
 *
 * @param cmd_args Arguments of the command being written.
 * @return Returns 0 if successful, or different values in the case of an error.
 */
int mouse_command(unsigned int cmd_args);

/**
 * @brief Reads the mouse bytes and assembles the mouse packet (consisting of three bytes).
 *
 * @return Returns 0 if successful, or different values if the packet is not ready yet/out of sync.
 */
int read_mouse_data();

/**
 * @brief Reads the mouse acknowledge byte, returned after writing a command.
 *
 * @return Returns the mouse acknowledge byte, or different value in the case of an error.
 */
unsigned int read_mouse_ack();

/**
 * @brief Returns the first byte of the mouse packet.
 *
 * @return First mouse packet byte.
 */
uint8_t get_byte1();

/**
 * @brief Returns the second byte of the mouse packet.
 *
 * @return Second mouse packet byte.
 */
uint8_t get_byte2();

/**
 * @brief Returns the third byte of the mouse packet.
 *
 * @return Third mouse packet byte.
 */
uint8_t get_byte3();
