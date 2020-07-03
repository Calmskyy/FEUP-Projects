#include "button.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Button *create_button(BitmapImage *def, BitmapImage *hover, int x, int y) {

  Button *but = (Button *) malloc(sizeof(Button));

  if (but == NULL)
    return BUTTON_ERROR;

  Sprite *sp = create_sprite(def, x, y);

  if (sp == NULL) {
    free(but);
    but = NULL;
    return SPRITE_ERROR;
  }

  but->hover = false;
  but->defaultimage = sp->bitmap->image;
  but->hoverimage = hover->image;

  but->sprite = sp;
  if (but->sprite == NULL) {
    free(but);
    but = NULL;
    return BUTTON_ERROR;
  }
  if (but->defaultimage == NULL) {
    free(but);
    but = NULL;
    return BUTTON_ERROR;
  }
  if (but->hoverimage == NULL) {
    free(but);
    but = NULL;
    return BUTTON_ERROR;
  }

  return but;
}

void destroy_button(Button *but) {
  if (but == NULL)
    return;

  if (but->sprite->bitmap->image == but->hoverimage && but->hoverimage != NULL)
    if (but->defaultimage != NULL) {
      free(but->defaultimage);
      but->defaultimage = NULL;
    }

  if (but->sprite->bitmap->image == but->defaultimage && but->defaultimage != NULL)
    if (but->hoverimage != NULL) {
      free(but->hoverimage);
      but->hoverimage = NULL;
    }

  if (but->sprite)
    destroy_sprite(but->sprite);

  free(but);
  but = NULL;
}

void update_button(Button *but, bool hover) {
  if (but == NULL)
    return;

  if (hover == true) {
    but->hover = true;
    but->sprite->bitmap->image = but->hoverimage;
  }
  else if (hover == false) {
    but->hover = false;
    but->sprite->bitmap->image = but->defaultimage;
  }
}

void draw_button(Button *but) {
  if (but == NULL)
    return;

  draw_sprite(but->sprite);
}
