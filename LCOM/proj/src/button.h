#pragma once

#include <stdbool.h>
#include "bitmap.h"

#define BUTTON_ERROR NULL

#define COLLISION 0
#define NO_COLLISION 1
#define BUTTON_CLICK 2

typedef struct {
  unsigned char *defaultimage;
  unsigned char *hoverimage;
  Sprite *sprite;
  bool hover;
} Button;

/**
 * @brief Creates a button object.
 *
 * @param def Default button image (when not being hovered).
 * @param hover Hovered button image (when being hovered).
 * @param x Sprite's starting x position.
 * @param y Sprite's starting y position.
 * @return Returns the button object created.
 */
Button *create_button(BitmapImage *def, BitmapImage *hover, int x, int y);

/**
 * @brief Destroys a button.
 *
 * @param but Button to be destroyed.
 */
void destroy_button(Button *but);

/**
 * @brief Updates a button's hover status, changing the image if they were on the opposite status before.
 *
 * @param but Button to be updated.
 * @param hover Hover value detected.
 */
void update_button(Button *but, bool hover);

/**
 * @brief Draws a button on the screen.
 *
 * @param but Button to be drawn.
 */
void draw_button(Button *but);

