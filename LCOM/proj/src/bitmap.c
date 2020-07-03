#include "bitmap.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BitmapImage *load_bitmap_file(const char *file) {
  FILE *filePtr;                     //our file pointer
  BitmapFileHeader bitmapFileHeader; //our bitmap file header
  BitmapInfoHeader bitmapInfoHeader; //our bitmap info header
  unsigned char *data;               //store image data
  long int width;                    //store width
  long int height;                   // store height

  //open filename in read binary mode
  filePtr = fopen(file, "rb");
  if (filePtr == NULL) {
    return FILE_ERROR;
  }

  //read the bitmap file header
  fread(&bitmapFileHeader, sizeof(BitmapFileHeader), 1, filePtr);

  //verify that this is a bmp file by check bitmap id
  if (bitmapFileHeader.type != BITMAP_ID) {
    fclose(filePtr);
    printf("file is not a bitmap.\n");
    return FILE_ERROR;
  }

  //read the bitmap info header
  fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

  //move file point to the begging of bitmap data
  fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

  //allocate enough memory for the bitmap image data
  data = (unsigned char *) malloc(bitmapInfoHeader.SizeImage);

  //verify memory allocation
  if (!data) {
    free(data);
    fclose(filePtr);
    printf("memory allocation error.\n");
    return IMAGE_ERROR;
  }
  //read in the bitmap image data
  fread(data, bitmapInfoHeader.SizeImage, 1, filePtr);
  //make sure bitmap image data was read
  if (data == NULL) {
    fclose(filePtr);
    return IMAGE_ERROR;
  }

  width = bitmapInfoHeader.width;
  height = bitmapInfoHeader.height;

  fclose(filePtr);
  BitmapImage *image = (BitmapImage *) malloc(sizeof(BitmapImage));
  if (image == NULL)
    return IMAGE_ERROR;
  image->image = data;
  image->width = width;
  image->height = height;
  return image;
}

Sprite *create_sprite(BitmapImage *image, int x, int y) {

  Sprite *sp = (Sprite *) malloc(sizeof(Sprite));

  if (sp == NULL)
    return SPRITE_ERROR;

  if (image == NULL) {
    free(sp);
    sp = NULL;
    return SPRITE_ERROR;
  }

  sp->bitmap = image;
  sp->x = x;
  sp->y = y;
  return sp;
}

void destroy_sprite(Sprite *sp) {
  if (sp == NULL)
    return;

  if (sp->bitmap != NULL)
    if (sp->bitmap->image != NULL) {
      free(sp->bitmap->image);
      sp->bitmap->image = NULL;
    }

  if (sp->bitmap != NULL) {
    free(sp->bitmap);
    sp->bitmap = NULL;
  }

  free(sp);
  sp = NULL;
}

int draw_sprite(Sprite *sp) {
  if (sp == NULL)
    return NULL_SPRITE;

  unsigned hres = get_h_res();
  unsigned vres = get_v_res();
  char *buffer = get_buffer();

  int x = sp->x;
  int ylimit = sp->y;
  int y = sp->y + sp->bitmap->height;
  int xlimit = sp->x + sp->bitmap->width;
  int count = 0;
  int collision_found = 0;

  uint8_t *bufferposition;
  unsigned char *imageposition;

  for (; y > ylimit; y--) {
    for (; x < xlimit; x++) {
      if (x >= (int) hres)
        continue;
      if (y >= (int) vres)
        continue;
      if (x < 0)
        continue;
      if (y < 0)
        continue;
      bufferposition = (uint8_t*) buffer;
      bufferposition = bufferposition + x * 4 + y * hres * 4;

      imageposition = sp->bitmap->image + count * 4;
      if (*imageposition == 0x00 && *(imageposition + 1) == 0x00 && *(imageposition + 2) == 0x00 && *(imageposition + 3) == 0x00) {
        count++;
        continue;
      }
      if (*bufferposition != 0x00 || *(bufferposition + 1) != 0x00 || *(bufferposition + 2) != 0x00 || *(bufferposition + 3) != 0x00)
        collision_found = 1;
      if (*bufferposition == 0x99 && *(bufferposition + 1) == 0x99 && *(bufferposition + 2) == 0xa5)
        collision_found = 0;

      memcpy(bufferposition, imageposition, 4);
      count++;
    }
    x = sp->x;
  }

  if (collision_found == 1)
    return CHARACTER_COLLISION;
  else
    return NO_CHARACTER_COLLISION;
}

void move_sprite(Sprite *sp, int xmove, int ymove) {
  if (sp == NULL)
    return;

  sp->x = sp->x + xmove;
  sp->y = sp->y + ymove;
}

int get_width(Sprite *sp) {
  int width = sp->bitmap->width;
  return width;
}

int get_height(Sprite *sp) {
  int height = sp->bitmap->height;
  return height;
}
