CC    = gcc
FLAGS = -g -DDEBUG -Wall -Wextra -Werror

BIN   = bin/messenger
OBJS  = obj/main.o obj/utils.o obj/client.o obj/server.o

$(BIN): $(OBJS)
	$(info === Linking ===)
	$(CC) -o $@ $^ $(FLAGS)

obj/main.o:   src/main.c
obj/utils.o:  src/utils.c
obj/client.o: src/client.c
obj/server.o: src/server.c

$(OBJS):
	$(info === Compiling $@ ===)
	$(CC) -c -o $@ $^ $(FLAGS)