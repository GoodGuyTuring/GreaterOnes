#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall #-fsanitize=address
LDFLAGS = -g -Wall #-fsanitize=address
OBJ = modules/shell.o modules/mystdlib.o modules/mygetline.o modules/myunistd.o modules/mystring.o
HEADERS = syscalls/mystddef.h syscalls/myunistd.h strings/mystring.h

#Linker-Regel
shell: $(OBJ)
	$(CC) $(LDFLAGS) -lm $^ -o $@ 
	rm $(OBJ)

#Compiler-Regeln
modules/myunistd.o: syscalls/myunistd.s $(HEADERS)
	nasm -f elf64 -o $@ $<

modules/mystring.o: strings/mystring.c
	$(CC) $(CFLAGS) -c -o $@ $^ 

modules/mystdlib.o: stdlib/mystdlib.c
	$(CC) $(CFLAGS) -lm -c -o $@ $^

modules/mygetline.o: getline/mygetline.c
	$(CC) $(CFLAGS) -c -o $@ $^

modules/shell.o: shell.c 
	$(CC) $(CFLAGS) $^ -c -o $@











