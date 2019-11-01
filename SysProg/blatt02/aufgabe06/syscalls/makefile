CC=nasm
CFLAGS=-f elf64
HEADERS=mystddef.h myunistd.h 
OBJECTS=myunistd.o
ASM=myunistd.s

# zu o-Datei kompilieren	
$(OBJECTS): $(ASM) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

	
