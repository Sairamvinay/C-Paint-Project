#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

/*THIS FUNCTION IS USED TO CHECK THE VALIDITY OF THE INTEGERS
@PARAMETERS: THE INTEGER TO CHECK, NUMBER OF ARGUMENT READ AND THE NAME OF THE ARGUMENT
@RETURNS BOOL IF CORRECT ARGS THEN TRUE ELSE FALSE
*/
bool check_valid_int(int integer,int num_args_read,char *arg_name){
    
    if (num_args_read == 0){
        printf("The number of %s is not an integer.\n",arg_name);
        return false;
    }
    
    
    else if (integer < 1){
        printf("The number of %s is less than 1.\n",arg_name);
        return false;
    }
    return true;
}     
                

/*THIS FUNCTION IS USED TO CHECK COMMAND LINE ARGUMENTS
@PARAMETERS: THE NUMBER OF COMMANDS LINE ARGUMENTS AND THE LIST OF ARGUMENTS AS AN ARRAY OF STRINGS
THE NUMBER OF ROWS AND COLUMNS(AS POINTERS)
*/
void check_args(int argc,char **argv,int *num_rows,int *num_cols){

    if (argc == 3){
        int num_args_read;
        num_args_read = sscanf(argv[1],"%d",&(*num_rows));
        if (!check_valid_int(*num_rows,num_args_read,"rows")){
            printf("Making default board of 10 X 10.\n");
            *num_rows = 10;
            *num_cols = 10;
            return;
        }
            
        
        num_args_read = sscanf(argv[2],"%d",&(*num_cols));
        if (!check_valid_int(*num_cols,num_args_read,"columns")){
            printf("Making default board of 10 X 10.\n");
            *num_rows = 10;
            *num_cols = 10;
            return;
        }
    }
    
    else if (argc == 1){
        
        *num_rows = 10;
        *num_cols = 10;
    }
    
    else{
        
        printf("Wrong number of command line arguements entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]\n");
        *num_rows = 10;
        *num_cols = 10;
        printf("Making default board of 10 X 10.\n");
    }
}
