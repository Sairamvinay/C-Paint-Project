#ifndef DRAW_H
#define DRAW_H

#include "canvas.h"
#define FIND_MAX(num1,num2) (num1) > (num2) ? (num1) : (num2)
#define FIND_MIN(num1,num2) (num1) < (num2) ? (num1) : (num2)
bool canvas_draw(Canvas *canvas, int y1, int x1, int y2, int x2);
void horz_draw(Canvas *canvas, int row, int start_col, int end_col);
void vert_draw(Canvas *canvas, int col, int start_row, int end_row);
void diag_draw(Canvas *canvas, int y1, int x1, int y2, int x2, int slope);
bool is_full(char letter);
void fill_char(char *to_fill,char filler);

#endif

