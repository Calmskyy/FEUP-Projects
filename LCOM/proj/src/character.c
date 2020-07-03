#include "character.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "video_gr.h"

Character *create_character(BitmapImage *image, int x, int y, int health) {

	Character *chara = (Character *) malloc(sizeof(Character));

  if (chara == NULL)
    return CHARACTER_ERROR;

  Sprite *sp = create_sprite(image, x, y);

  if (sp == NULL) {
    free(chara);
    return SPRITE_ERROR;
  }

  chara->hp = health;
  chara->turn = 1;

  chara->sprite = sp;
  if (chara->sprite == NULL) {
    free(chara);
    return CHARACTER_ERROR;
  }

  return chara;
}

void destroy_character(Character *chara) {
  if (chara == NULL)
    return;

  if (chara->sprite)
    destroy_sprite(chara->sprite);

  free(chara);
  chara = NULL;
}

void update_character(Character *chara, int xmove, int ymove, int health, unsigned int turn, unsigned int which) {
  if (chara == NULL)
    return;

  chara->hp += health;
  chara->turn += turn;
  if (chara->hp < 0)
    chara->hp = 0;

  if (which == 0) {
    chara->sprite->x += xmove;
    if (chara->sprite->x < 380)
      chara->sprite->x = 380;
    if (chara->sprite->x + chara->sprite->bitmap->width > 772)
      chara->sprite->x = 772 - chara->sprite->bitmap->width;

    chara->sprite->y += ymove;
    if (chara->sprite->y < 364)
      chara->sprite->y = 364;
    if (chara->sprite->y + chara->sprite->bitmap->height > 660)
      chara->sprite->y = 660 - chara->sprite->bitmap->height;
  }

  if (which == 1) {
    chara->sprite->x += xmove;
    if (chara->sprite->x < 0)
      chara->sprite->x = 0;
    if (chara->sprite->x + chara->sprite->bitmap->width > 1152)
      chara->sprite->x = 1152 - chara->sprite->bitmap->width;

    chara->sprite->y += ymove;
    if (chara->sprite->y < 0)
      chara->sprite->y = 0;
    if (chara->sprite->y + chara->sprite->bitmap->height > 864)
      chara->sprite->y = 864 - chara->sprite->bitmap->height;
  }

  if (which == 2) {
    chara->sprite->x += xmove;
    if (chara->sprite->x < 20)
      chara->sprite->x = 20;
    if (chara->sprite->x + chara->sprite->bitmap->width > 1152)
      chara->sprite->x = 1152 - chara->sprite->bitmap->width;
  }
}

int draw_character(Character *chara) {
  if (chara == NULL)
    return NULL_SPRITE;

  if (draw_sprite(chara->sprite) == CHARACTER_COLLISION)
    return CHARACTER_COLLISION;
  else
    return NO_CHARACTER_COLLISION;
}
