#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = server.o

#Linker-Regel
server: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ 

#Compiler-Regeln
server.o: server.c
	$(CC) $(CFLAGS) $^ -c -o $@ 







