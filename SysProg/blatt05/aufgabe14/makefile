#Parameter für Compiler, Flags, etc.
CC=nasm
CFLAGS=-f elf64

#Übersetze die Assemblerdatei 
#mit NASM in Objektdatei

matrix: m_add.o matrix.c
	clang -o $@ $^
	
m_add.o: m_add.asm print.asm
	$(CC) $(CFLAGS) -o $@ $<
	
