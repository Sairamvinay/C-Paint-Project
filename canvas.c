#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "canvas.h"


/*THIS FUNCTION CREATES AND RETURNS A NEW CANVAS OBJECT
  @PARAMETERS: NUMBER OF ROWS AND COLUMNS
  @RETURNS : A CANVAS STRUCTURE POINTER
*/
Canvas *canvas_new(int nRows, int nCols) {
    Canvas *canvas;
    char **rows;
    int i;

    canvas =(Canvas*) (malloc(sizeof(Canvas)));
    rows = (char **)malloc(nRows * sizeof(char*));
    for (i=0; i<nRows; i++) {
        rows[i] = (char*) malloc(nCols * sizeof(char));
        memset(rows[i], '*', nCols);  //USED IN PLACE OF LOOP
    }
    
    canvas->nRows = nRows;
    canvas->nCols = nCols;
    canvas->rows = rows;

    return canvas;
}

/*
THIS FUNCTION DELETES THE EXISTING CANVAS
BY FREEING THE MALLOCED MEMORY
@PARAMETERS: CANVAS STRUCTURE POINTER*/

void canvas_free(Canvas *canvas) {
    int i;

    for (i=0; i<canvas->nRows; i++)
        free(canvas->rows[i]);
    free(canvas->rows);
    free(canvas);
}


/*
THIS FUNCTION PRINTS THE CANVAS
@PARAMETER: CANVAS STRUCTURE POINTER
*/
void canvas_print(Canvas *canvas) {
    int i, j;

    for (i=canvas->nRows-1; i>=0; i--) {
        printf("%2d ", i);
        for (j=0; j<canvas->nCols; j++)
            printf(" %c ", canvas->rows[i][j]);
        printf("\n");
    }

    printf("   ");
    for (i=0; i<canvas->nCols; i++)
        printf("%2d ", i);
    printf("\n");
}


/*
THIS FUNCTION RESIZES THE BOARD TO SPECIFIC NUMBER OF ROWS AND COLUMNS
@PARAMETER: CANVAS, NUMBER OF NEW ROWS AND COLUMNS
*/

void canvas_resize(Canvas *canvas, int newRows, int newCols) {
    int i;

    if (newCols != canvas->nCols) {
        for (i=0; i<canvas->nRows; i++) {
            canvas->rows[i] = (char *)realloc(canvas->rows[i], newCols * sizeof(char));
            if (newCols > canvas->nCols)
                memset(canvas->rows[i]+canvas->nCols, '*', newCols-canvas->nCols);
        }
    }

    if (newRows != canvas->nRows) {
        if (newRows < canvas->nRows)
            for (i=newRows; i<canvas->nRows; i++) 
                free(canvas->rows[i]);

        canvas->rows = (char **)realloc(canvas->rows, newRows * sizeof(char*));

        if (newRows > canvas->nRows) {
            for (i=canvas->nRows; i<newRows; i++) {
                canvas->rows[i] = malloc(newCols * sizeof(char));
                memset(canvas->rows[i], '*', newCols);
            }
        }
    }

    canvas->nRows = newRows;
    canvas->nCols = newCols;
}


/*
THIS FUNCTION ADDS A NEW ROW TO THE CANVAS AND UPDATES IT
  @PARAMETER: CANVAS AND THE NUM OF ROW TO CHANGE
*/
void canvas_add_row(Canvas *canvas,int num){
    
    int i;
    (canvas->nRows)++;
    canvas->rows = (char **) realloc(canvas->rows, (canvas->nRows) * sizeof(char *));
    for (i= (canvas->nRows) - 1; i>num;i--){
    
        canvas->rows[i] =canvas->rows[i-1];
        
    }
    
    
    //fill with spaces for the new row
    (canvas->rows)[num] = (char*)malloc(canvas->nCols*sizeof(char));
    memset(canvas->rows[num], '*', canvas->nCols);
    
}



/*
THIS FUNCTION ADDS A NEW COLUMN TO THE CANVAS AND UPDATES IT
  @PARAMETER: CANVAS AND THE NUM OF COLUMN TO CHANGE
*/
void canvas_add_col(Canvas *canvas,int num){
    
    (canvas->nCols)++;
    
    int i,j;
    for (i=0;i<(canvas->nRows);i++){
        
        (canvas->rows)[i] = (char *) realloc((canvas->rows)[i], (canvas->nCols) * sizeof(char));
    }
    
    for (i=0;i<(canvas->nRows);i++){
        
        for (j=(canvas->nCols) - 1; j>num ;j--){
            
            (canvas->rows)[i][j] = (canvas->rows)[i][j-1];
        }
        
        (canvas->rows)[i][j] = '*';
   }
   
}
 

/*
THIS FUNCTION DELETES A ROW TO THE CANVAS AND UPDATES IT
  @PARAMETER: CANVAS AND THE NUM OF ROW TO CHANGE
*/
void canvas_del_row(Canvas *canvas,int num){
    
    int i;
    for (i=num;i<(canvas->nRows) - 1;i++){
        
        (canvas->rows)[i] = (canvas->rows)[i+1];
    }
    
    (canvas->nRows)--;
    (canvas->rows) = (char **) realloc((canvas->rows),(canvas->nRows) * sizeof(char *));
    
}


/*
*
THIS FUNCTION DELETES A COLUMN TO THE CANVAS AND UPDATES IT
  @PARAMETER: CANVAS AND THE NUM OF COLUMN TO CHANGE
*/
void canvas_del_col(Canvas *canvas, int num){

    int i,j;
    for (i=0;i<(canvas->nRows);i++){
        
        
        for (j=num;j<(canvas->nCols) - 1;j++){
            
            (canvas->rows)[i][j] = (canvas->rows)[i][j+1];
        }
        
        (canvas->rows)[i] = (char *)realloc((canvas->rows)[i],((canvas->nCols) - 1) * sizeof(char));
        
    }
    
    (canvas->nCols)--;
}


/*
THIS FUNCTION SAVES THE EXISTING CANVAS ONTO THE GIVEN FILE
@PARAMETERS: CANVAS AND THE FILENAME
@RETURNS: A BOOL TO ENSURE THAT THE DATA IS WRITTEN ONTO THE FILE
*/
bool canvas_save(Canvas *canvas, char *filename) {
    FILE *file;
    int i;

    file = fopen(filename, "w");
    if (file == NULL)
        return false;

    fwrite(&canvas->nRows, sizeof(int), 1, file);
    fwrite(&canvas->nCols, sizeof(int), 1, file);

    for (i=0; i<canvas->nRows; i++)
        fwrite(canvas->rows[i], sizeof(char), canvas->nCols, file);

    fclose(file);

    return true;
}


/*
THIS FUNCTION LOADS THE CANVAS FROM THE GIVEN FILE AND ALSO FREE THE EXISITING CANVAS
@PARAMETERS: CANVAS AND THE FILENAME
@RETURNS: A BOOL TO ENSURE THAT THE DATA IS READ FROM THE FILE
*/
bool canvas_load(Canvas *canvas, char *filename) {
    FILE *file;
    int i;

    file = fopen(filename, "r");
    if (file == NULL)
        return false;

    // Free existing canvas
    for (i=0; i<canvas->nRows; i++)
        free(canvas->rows[i]);
    free(canvas->rows);

    fread(&canvas->nRows, sizeof(int), 1, file);
    fread(&canvas->nCols, sizeof(int), 1, file);

    canvas->rows = malloc(canvas->nRows * sizeof(char*));
    for (i=0; i<canvas->nRows; i++) {
        canvas->rows[i] = malloc(canvas->nCols * sizeof(char));
        fread(canvas->rows[i], sizeof(char), canvas->nCols, file);
    }

    fclose(file);

    return true;
}


/*
THIS FUNCTION ERASES THE GIVEN POSITION'S VALUE
@PARAMETERS: CANVAS,THE ROW AND COLUMN POSITION TO ERASE
*/
void canvas_erase(Canvas *canvas, int row, int col){
    
    (canvas->rows)[row][col]= '*';
}
