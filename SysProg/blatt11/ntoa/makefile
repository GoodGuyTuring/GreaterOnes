#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = ntoa.o

#Linker-Regel
ntoa: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

#Compiler-Regeln
ntoa.o: ntoa.c
	$(CC) $(CFLAGS) $^ -c -o $@ 






