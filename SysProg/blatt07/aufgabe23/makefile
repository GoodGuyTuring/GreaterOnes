#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = shell.o mystdlib.o mygetline.o myunistd.o

#Linker-Regel
shell: $(OBJ)
	$(CC) $(LDFLAGS) -lm $^ -o $@ 

#Compiler-Regeln
shell.o: shell.c
	$(CC) $(CFLAGS) $^ -c -o $@ 

mystdlib.o: mystdlib.c
	$(CC) $(CFLAGS) -lm -c -o $@ $^

mygetline.o: mygetline.c
	$(CC) $(CFLAGS) -c -o $@ $^








