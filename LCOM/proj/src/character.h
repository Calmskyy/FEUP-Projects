#pragma once

#include <stdbool.h>
#include "bitmap.h"

#define CHARACTER_ERROR NULL

typedef struct {
  Sprite *sprite;
  int hp;
  unsigned int turn;
} Character;

/**
 * @brief Creates a character object.
 *
 * @param image Character's image.
 * @param x Sprite's starting x position.
 * @param y Sprite's starting y position.
 * @param health Character's starting health value.
 * @return Returns the character object created.
 */
Character *create_character(BitmapImage *image, int x, int y, int health);

/**
 * @brief Destroys a character.
 *
 * @param chara Character to be destroyed.
 */
void destroy_character(Character *chara);

/**
 * @brief Updates a character's position, health, turn, which go through different checks depending on the last parameter.
 *
 * @param chara Character to be updated.
 * @param xmove Character's movement across the x axis.
 * @param ymove Character's movement across the y axis.
 * @param health Character's health increment.
 * @param turn Character's turn increment.
 * @param which Used to set different character limits depending on the movable area.
 */
void update_character(Character *chara, int xmove, int ymove, int health, unsigned int turn, unsigned int which);

/**
 * @brief Draws a character on the screen.
 *
 * @param chara Character to be drawn.
 */
int draw_character(Character *chara);

