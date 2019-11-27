#Parameter für Compiler, Flags, etc.
CC=nasm
CFLAGS=-f elf64
HEADERS=mystddef.h myunistd.h 
OBJECTS=myunistd.o

#Übersetze die Assemblerdatei 
#mit NASM in Objektdatei	
myunistd.o: myunistd.s $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

	
