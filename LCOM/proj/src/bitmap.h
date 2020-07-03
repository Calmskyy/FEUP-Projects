#pragma once

#include <stdint.h>

#define BITMAP_ID 0x4D42
#define FILE_ERROR NULL
#define IMAGE_ERROR NULL
#define SPRITE_ERROR NULL
#define CHARACTER_COLLISION 1
#define NO_CHARACTER_COLLISION 0
#define NULL_SPRITE 2

#pragma pack(push, 1)

typedef struct {
  uint16_t type;      //specifies the file type
  uint32_t size;      //specifies the size in bytes of the bitmap file
  uint16_t reserved1; //reserved; must be 0
  uint16_t reserved2; //reserved; must be 0
  uint32_t offset;    //species the offset in bytes from the bitmapfileheader to the bitmap bits
} BitmapFileHeader;

#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  uint32_t size;            //specifies the number of bytes required by the struct
  long int width;           //specifies width in pixels
  long int height;          //species height in pixels
  uint16_t planes;          //specifies the number of color planes, must be 1
  uint16_t bitCount;        //specifies the number of bit per pixel
  uint32_t bitCompression;  //spcifies the type of compression
  uint32_t SizeImage;       //size of image in bytes
  long int XPixelsPerMeter; //number of pixels per meter in x axis
  long int YPixelsPerMeter; //number of pixels per meter in y axis
  uint32_t ColorUsed;       //number of colors used by th ebitmap
  uint32_t ColorImportant;  //number of colors that are important
} BitmapInfoHeader;

#pragma pack(pop)

typedef struct {
  long int width, height;
  unsigned char *image;
} BitmapImage;

typedef struct {
  int x, y;
  BitmapImage *bitmap;
} Sprite;


/**
 * @brief Creates a sprite object.
 *
 * @param image Image content to be used on the sprite.
 * @param x Sprite's starting x position.
 * @param y Sprite's starting y position.
 * @return Returns the sprite object created.
 */
Sprite *create_sprite(BitmapImage *image, int x, int y);

/**
 * @brief Displaces a sprite on the screen.
 *
 * @param sp Sprite to be moved.
 * @param xmove Sprite's movement across the x axis.
 * @param ymove Sprite's movement across the y axis.
 */
void move_sprite(Sprite *sp, int xmove, int ymove);

/**
 * @brief Destroys a sprite.
 *
 * @param sp Sprite to be destroyed.
 */
void destroy_sprite(Sprite *sp);

/**
 * @brief Draws a sprite on the screen.
 *
 * @param sp Sprite to be drawn.
 * @return For enemy attacks, returns a flag to determine if the player is in a collision that damages them.
 */
int draw_sprite(Sprite *sp);

/**
 * @brief Loads a bitmap file to be used on the game.
 *
 * @param file File path of the image.
 * @return Returns the relevant image content.
 */
BitmapImage *load_bitmap_file(const char *file);
