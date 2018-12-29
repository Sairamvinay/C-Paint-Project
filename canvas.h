#ifndef CANVAS_H
#define CANVAS_H

#include <stdbool.h>

typedef struct Canvas_ {
    int nRows;
    int nCols;
    char **rows;
} Canvas;

Canvas *canvas_new(int nRows, int nColumns);
void canvas_free(Canvas *canvas);
void canvas_print(Canvas *canvas);
void canvas_resize(Canvas *canvas, int newRows, int newCols);
void canvas_add_row(Canvas *canvas,int num);
void canvas_add_col(Canvas *canvas,int num);
void canvas_del_row(Canvas *canvas,int num);
void canvas_del_col(Canvas *canvas, int num);
bool canvas_load(Canvas *canvas, char *filename);
bool canvas_save(Canvas *canvas, char *filename);
void canvas_erase(Canvas *canvas, int row, int col);
#endif
