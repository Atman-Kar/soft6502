CC=gcc 

CFLAGS= -Wall -Wextra -pedantic -ggdb
CFLAGS_TEST= -Wall -Wextra -pedantic 

CSOURCE= $(wildcard src/*.c)
CSOURCE_TEST= $(filter-out src/main.c, $(CSOURCE))
CSOURCE_TEST+= $(wildcard test/*.c)

INC_TEST = -I src/ -I test/ 

build:
	@$(CC) $(CFLAGS) $(CSOURCE) -o main 

clean:
	@rm -f main utest

utest:
	@gcc -o utest $(CSOURCE_TEST) $(INC_TEST)
	@./utest