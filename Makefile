snake: 	snake.h snake.cpp main.cpp
	g++ -lncurses -o snake snake.cpp main.cpp		
line:	line.cpp
	g++ -Wall -o line line.cpp

sc:     sc.c
	gcc -Wall -g -o sc sc.c	

ss:	ss.c
	gcc -Wall -g -o	ss ss.c

base:	base.c
	gcc -Wall -g -o	base base.c

little: little.c
	gcc -Wall -g -o little little.c

big: 	little.c
	gcc -Wall -g -o big little.c

todo: 	todo.c
	gcc -Wall -g -o	todo todo.c
clean:
	@rm -rf *.o *~ *.dSYM
	@echo Made clean.
love:
	@echo Not war.