#include "draw.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "scanf_verify.h"

/*
THIS FUNCTION PRINTS THE LIST OF COMMANDS WHENEVER HELP (h) COMMAND IS PRESSED
*/
void print_help()
{
    printf("Commands:\n");
    printf("Help: h\n");
    printf("Quit: q\n"); 
    printf("Draw line: w row_start col_start row_end col_end\n");
    printf("Resize: r num_rows num_cols\n");
    printf("Add row or column: a [r | c] pos\n");
    printf("Delete row or column: d [r | c] pos\n");
    printf("Erase: e row col\n");
    printf("Save: s file_name\n");
    printf("Load: l file_name\n");

}


/*
THIS FUNCTION KEEPS PROMPTING FOR THE COMMANDS TILL Q IS ENTERED
@PARAMETERS :THE CANVAS STRUCTURE POINTER
*/
void keep_commanding(Canvas *canvas){
    char command = '\0';
    int start_row,start_col,end_row,end_col;
    int row,col;
    int num_rows,num_cols;
    int num;
    char dim;
    char file_name[128];
    while (true){
        canvas_print(canvas);
        printf("Enter your command: ");
        scanf(" %c",&command);
        command = tolower(command);
        switch(command){
            
            case 'q': 
                if (!correct_input(true)){
                  printf("Unrecognized command. Type h for help.\n");
                  continue;
                }
                
                return;
            
            case 'h':
                if (!correct_input(true)){
                  printf("Unrecognized command. Type h for help.\n");
                  continue;
                }
                
                printf("\n");
                print_help();
                printf("\n");
                break;
           
            
            case 'w':
                
                
                if (!scanf_verify(" %d %d %d %d",&start_row,&start_col,&end_row,&end_col)){
                    printf("Improper draw command.\n");
                    continue;
                }
                
                if (start_row< 0 || (start_row >= (canvas->nRows))){
                     printf("Improper draw command.\n");
                     continue;
                }
                
                  
                if (start_col < 0 || (start_col >= (canvas->nCols))){
                     printf("Improper draw command.\n");
                     continue;
                }
                
                  
                if (end_row< 0 || (end_row >= (canvas->nRows))){
                     printf("Improper draw command.\n");
                     continue;
                }
                
                  
                if (end_col< 0 || (end_col >= (canvas->nCols))){
                     printf("Improper draw command.\n");
                     continue;
                }
                
                  
                
                if (!canvas_draw(canvas,start_row,start_col,end_row,end_col)){
                    
                    printf("Cannot draw the line as it is not straight.\n");                    
                }
                
                break;
            
            
            case 'e':
                
                
                if (!scanf_verify(" %d %d",&row,&col) || (row<0) || (col <0)){
                    
                    printf("Improper erase command.\n");
                    continue;
                }
                
                if ((row >= canvas->nRows) || (col >= canvas->nCols)){
                    
                    printf("Improper erase command.\n");
                    continue;
                }
                    
                canvas_erase(canvas, row, col); 
                break;
                
           
           case 'r':
               
               
               if ((!scanf_verify(" %d %d",&num_rows,&num_cols)) || (num_rows < 1) || (num_cols < 1)){
                   
                   printf("Improper resize command.\n");
                   continue;
               }
               
         
               canvas_resize(canvas,num_rows,num_cols);
               break;
           
           
           case 'a':
               
               
               if ((!scanf_verify(" %c %d",&dim,&num))){
                   printf("Improper add command.\n");
                   continue;
               }
               
              else{
                   
                   dim = tolower(dim);
                   if (dim == 'r'){
                       
                       
                       if ((num < 0) || (num > (canvas->nRows + 1))){
                          printf("Improper add command.\n");
                          continue;
                       }
                       
                       canvas_add_row(canvas,num);
                   }
                   
                   else if (dim == 'c'){
                       
                       
                       if ((num < 0) ||(num > (canvas->nCols + 1))){
                          printf("Improper add command.\n");
                          continue;
                       }
                       canvas_add_col(canvas,num);
                   }
                   
                   else{
                       
                       printf("Improper add command.\n");
                       continue;
                   }
              }
              
              break;
                              
          
          case 'd':
              
               
               if ((!scanf_verify(" %c %d",&dim,&num))){
                   printf("Improper delete command.\n");
                   continue;
               }
               
              else{
                   
                   dim = tolower(dim);
                   if (dim == 'r'){
                       
                       
                       if ((num >= (canvas->nRows)) || (num < 0)){
                          printf("Improper delete command.\n");
                          continue;
                       }
                       
                       canvas_del_row(canvas,num);
                   }
                   
                   else if (dim == 'c'){
                       
                       
                       if ((num >= (canvas->nCols)) || (num < 0)){
                          printf("Improper delete command.\n");
                          continue;
                       }
                       canvas_del_col(canvas,num);
                   }
                   
                   else{
                       
                       printf("Improper delete command.\n");
                       continue;
                   }
              }
              
              break;
                              
                            
        
        case 's':
            
            
            if (!scanf_verify(" %s",file_name) || (!canvas_save(canvas,file_name))){
                
                printf("Improper save command or file could not be created.\n");
                
            }
            
            break;
       
       case 'l':
           
            if (!scanf_verify(" %s",file_name) || (!canvas_load(canvas,file_name))){
                

                printf("Failed to open file: %s\n", file_name);
                
            }
            
            break;
       

      default:
          correct_input(true); // Reads input up to newline
          printf("Unrecognized command. Type h for help.\n");
          break;
   }
 }
}
        
