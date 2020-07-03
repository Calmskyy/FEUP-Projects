#include "bitmap.h"
#include <stdbool.h>

#define CURSOR_ERROR NULL

typedef struct {
  bool lb;
  Sprite* sprite;
}Cursor;

/**
 * @brief Creates a cursor object.
 *
 * @param image Image content to be used on the cursor.
 * @param x Cursor's starting x position.
 * @param y Cursor's starting y position.
 * @return Returns the cursor object created.
 */
Cursor *create_cursor(BitmapImage *image, int x, int y);

/**
 * @brief Destroys a cursor.
 *
 * @param curs Cursor to be destroyed.
 */
void destroy_cursor(Cursor *curs);

/**
 * @brief Updates a cursor's position, and left click held flag.
 *
 * @param curs Cursor to be updated.
 * @param xmove Cursor's movement across the x axis.
 * @param ymove Cursor's movement across the y axis.
 * @param click Left click's current value.
 */
void update_cursor(Cursor *curs, int xmove, int ymove, bool click);

/**
 * @brief Draws a cursor on the screen.
 *
 * @param curs Cursor to be drawn.
 */
void draw_cursor(Cursor *curs); 

