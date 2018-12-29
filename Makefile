paint.out: main.o scanf_verify.o draw.o canvas.o commandline.o commands.o
	gcc -g -std=c11 -Wall -Werror main.o scanf_verify.o commandline.o commands.o canvas.o draw.o -o paint.out -lm

main.o: main.c canvas.h commands.h
	gcc -g -std=c11 -Wall -Werror -c main.c -o main.o

scanf_verify.o:  scanf_verify.c scanf_verify.h
	gcc -g -std=c11 -Wall -Werror -c -o $@ $<

canvas.o: canvas.c canvas.h
	gcc -g -std=c11 -Wall -Werror -c -o $@ $<

commandline.o: commandline.c commands.h
	gcc -g -std=c11 -Wall -Werror -c -o $@ $<

commands.o: commands.c draw.h commands.h scanf_verify.h
	gcc -g -std=c11 -Wall -Werror -c -o $@ $<

draw.o: draw.c draw.h canvas.h
	gcc -g -std=c11 -Wall -Werror -c -o $@ $< 

clean:
	rm -f *.o *.out
