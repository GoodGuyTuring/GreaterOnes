#Parameter für Compiler, Flags, etc.
CC=nasm
CFLAGS=-f elf64

#Übersetze die Assemblerdatei 
#mit NASM in Objektdatei
helloworld-b: helloworld-b.o
	ld $< -o $@
	
helloworld-b.o: helloworld-b.asm
	$(CC) $(CFLAGS) -o $@ $<
	
