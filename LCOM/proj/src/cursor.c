#include "cursor.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cursor *create_cursor(BitmapImage *image, int x, int y) {

  Cursor *curs = (Cursor *) malloc(sizeof(Cursor));

  if (curs == NULL)
    return CURSOR_ERROR;

  Sprite *sp = create_sprite(image, x, y);

  if (sp == NULL) {
    free(curs);
    curs = NULL;
    return SPRITE_ERROR;
  }

  curs->lb = false;

  curs->sprite = sp;
  if (curs->sprite == NULL) {
    free(curs);
    curs = NULL;
    return CURSOR_ERROR;
  }

  return curs;
}

void destroy_cursor(Cursor *curs) {
  if (curs == NULL)
    return;

  if (curs->sprite)
    destroy_sprite(curs->sprite);

  free(curs);
  curs = NULL;
}

void update_cursor(Cursor *curs, int xmove, int ymove, bool click) {
  if (curs == NULL)
    return;

  if (click == true)
    curs->lb = true;
  else if (click == false)
    curs->lb = false;
  curs->sprite->x += xmove;

  if (curs->sprite->x < 0)
    curs->sprite->x = 0;
  unsigned int rightpos = curs->sprite->x + curs->sprite->bitmap->width;
  if (rightpos > get_h_res())
    curs->sprite->x = get_h_res() - curs->sprite->bitmap->width;

  curs->sprite->y += ymove;
  if (curs->sprite->y < 0)
    curs->sprite->y = 0;

  unsigned int downpos = curs->sprite->y + curs->sprite->bitmap->height;
  if (downpos > get_v_res())
    curs->sprite->y = get_v_res() - curs->sprite->bitmap->height;
}

void draw_cursor(Cursor *curs) {
  if (curs == NULL)
    return;

  draw_sprite(curs->sprite);
}
