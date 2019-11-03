#Parameter für Compiler, Flags, etc.
CC=nasm
CFLAGS=-f elf64

#Übersetze die Assemblerdatei 
#mit NASM in Objektdatei
helloworld-c: helloworld-c.o
	ld $< -o $@
	
helloworld-c.o: helloworld-c.asm
	$(CC) $(CFLAGS) -o $@ $<
	
