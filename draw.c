#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "draw.h"
#include <math.h>

/*
THIS FUNCTION CHECKS WHETHER THE GIVEN CHARACTER IS FILLED OR NOT
@PARAMETER: THE LETTER OR CHARACTER TO CHECK
@RETURNS:A BOOL VALUE OF WHETHER THE LETTER IS A SPACE(*) OR NOT
*/
bool is_full(char letter){
    
    return (letter != '*');
}

/*
THIS FUNCTION FILLS THE CHARACTER TO_FILL WITH FILLER OR '+'
IF THE CHARACTER IS FILLED OR NOT RESPECTIVELY
@PARAMETERS: POINTER TO CHAR TO_FILL AND THE FILLER CHARACTER
*/
void fill_char(char *to_fill,char filler){
    
             
    if (is_full(*to_fill)){
        
        if ((*to_fill)!= filler){
                
            (*to_fill) = '+';
        }
    }
        
    else {
            
        (*to_fill) = filler;
    }
}    
    

/*
THIS FUNCTION DRAWS THE CANVAS AND CALLS THE SPECIFIC DRAWS FOR THE SPECIFIC CONDITION
@PARAMETERS: CANVAS, THE COORDINATES OF THE STARTING POINT (Y1,X1) AND THEN THE ENDING POINT (Y2,X2)
@RETURNS: BOOL VALUE TO CHECK WHETHER THE DRAWING IS POSSIBLE OR NOT
*/
bool canvas_draw(Canvas *canvas, int y1, int x1, int y2, int x2) {
    double slope;

    if (y1 == y2)
        horz_draw(canvas, y1, x1, x2);
        
    
    else if (x1 == x2)
        vert_draw(canvas, x1, y1, y2);
    
    else {
        
        slope = ((double) (y2 - y1)) / (x2 - x1);
        if (fabs(slope - 1) < 0.0001)
            diag_draw(canvas, y1, x1, y2, x2, 1);
        else if (fabs(slope + 1) < 0.0001)
            diag_draw(canvas, y1, x1, y2, x2, -1);
        else
            return false;
    }

    return true;
}


/* 
THIS FUNCTION DRAWS A HORIZONTAL LINE FROM START_COL TO END_COL FOR
THE ROW
@PARAMETERS: CANVAS, ROW, START_COL AND THE END COL
*/
void horz_draw(Canvas *canvas,int row, int start_col, int end_col){
    
    int min = FIND_MIN(start_col,end_col);
    int max = FIND_MAX(start_col,end_col);
    int i;
    for (i=min;i<=max;i++){
       fill_char(&(canvas->rows[row][i]),'-');
   }
}
    

/*
THIS FUNCTION DRAWS A VERTICAL LINE FROM START ROW TO END ROW 
AT THE COLUMN
@PARAMETERS: CANVAS, THE COLUMN, START_ROW AND THE END_ROW
*/    
void vert_draw(Canvas *canvas, int col, int start_row, int end_row){
    
    int min = FIND_MIN(start_row,end_row);
    int max = FIND_MAX(start_row,end_row);
    int i;
    for (i=min;i<=max;i++){
       fill_char(&(canvas->rows[i][col]),'|');
    }
}


/*
THIS FUNCTION DRAWS THE DIAGONAL LINE FROM STARTING COORDINATES(Y1,X1) TO ENDING COORDINATES
(Y2,X2) BASED ON THE SLOPE
@PARAMETERS: CANVAS, STARTING COORDINATES(Y1,X1),ENDING COORDINATES(Y2,X2),SLOPE
*/
void diag_draw(Canvas *canvas, int y1, int x1, int y2, int x2, int slope) {
    int temp, x, y; //X AND Y ARE ITERATING VARIABLES
    char draw_char;

    if (x1 > x2) {
        temp = x2;
        x2 = x1;
        x1 = temp;

        temp = y2;
        y2 = y1;
        y1 = temp;
    }

    x = x1;
    y = y1;
    draw_char = (slope == 1) ? '/' : '\\';    //1 FOR LEFT TO RIGHT DIAGONAL AND -1 FOR RIGHT TO LEFT DIAGONAL

    while (x <= x2) {
        
        fill_char(&(canvas->rows[y][x]),draw_char);
        x++;
        y += slope;
    }
}
