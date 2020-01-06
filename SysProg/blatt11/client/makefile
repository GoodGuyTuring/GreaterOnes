#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = client.o

#Linker-Regel
client: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ -lm 

#Compiler-Regeln
client.o: client.c
	$(CC) $(CFLAGS) $^ -c -o $@ 








