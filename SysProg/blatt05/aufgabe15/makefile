#Parameter für Compiler, Flags, etc.
CC=nasm
CFLAGS=-f elf64

#Übersetze die Assemblerdatei 
#mit NASM in Objektdatei

#-soname glibc linkt mit GLIBC
ausgabe: ausgabe.o
	clang $< -o $@ 
	
ausgabe.o: ausgabe.asm
	$(CC) $(CFLAGS) -o $@ $< 
