#include "canvas.h"
#include "commands.h"

/*
THIS PROJECT IS COMPLETED BY BOTH OF US NAMELY
IAN SCOTT AND SAIRAMVINAY VIJAYARAGHAVAN AS A GROUP
*/

int main(int argc,char **argv){

    int num_rows=1,num_cols=1;
    check_args(argc, argv,&num_rows,&num_cols);
    Canvas *canvas = canvas_new(num_rows,num_cols);
    keep_commanding(canvas);
    canvas_free(canvas);
    return 0;
}
