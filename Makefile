snake: 	snake.h snake.cpp main.cpp
	g++ -lncurses -o snake snake.cpp main.cpp		
clean:
	@rm -rf *.o *~ *.dSYM
	@echo Made clean.
love:
	@echo Not war.
