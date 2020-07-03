#pragma once

#include <stdint.h>
#include <lcom/lcf.h>

#define BIOS_SERVICES 0x10
#define SET_VIDEO_MODE 0x4F02
#define INDEX_MODE 0x105
#define RETURN_VBE_INFO 0x4F01

#define STORE_BYTE 0xFF

#define SUCCESS 0
#define MEMORY_ALLOC_FAILED 1
#define BIOS_CALL_FAILED 2
#define VG_INIT_FAILED NULL
#define LM_INIT_FAILED NULL

#define SET_PIXEL_X_ERROR 1
#define SET_PIXEL_Y_ERROR 2
#define SET_PIXEL_ERROR 3
#define RECTANGLE_OFF_SCREEN 4
#define VIDEO_INIT_ERROR 2

/**
 * @brief Returns the memory address of the video buffer.
 *
 * @return Video buffer's memory address.
 */
char *get_buffer();

/**
 * @brief Copies the content of the video buffer to the main screen.
 *
 */
void buffercopy();

/**
 * @brief Gets the information of the requested video mode.
 *
 * @param mode Mode to be used on the information request.
 * @param vbe_info Memory address that contains all the information about the requested mode.
 * @return 0 on success, -1 on failure.
 */
int vbe_get_info(uint16_t mode, vbe_mode_info_t *vbe_info);

/**
 * @brief Frees the buffer's memory.
 *
 * @param buffer Memory address of the buffer to be freed.
 */
void free_mem(char *buffer);

/**
 * @brief Returns the video mode's horizontal resolution.
 *
 * @return Video mode's horizontal resolution.
 */
unsigned get_h_res();

/**
 * @brief Returns the video mode's vertical resolution.
 *
 * @return Video mode's vertical resolution.
 */
unsigned get_v_res();

/**
 * @brief Returns the video mode's bits used per pixel.
 *
 * @return Video mode's bits used per pixel.
 */
unsigned get_bits_per_pixel();

/**
 * @brief Sets minix's video mode to a different one.
 *
 * @param mode Mode to be changed to.
 * @return 0 on success, non-zero otherwise.
 */
int set_video_mode(uint16_t mode);

/**
 * @brief Clears the entire buffer, setting everything to 0.
 *
 */
void clear_buffer();

/**
 * @brief Clears the video buffer, only on the parts of the screen used on combat.
 *
 */
void clear_combat_buffer();

