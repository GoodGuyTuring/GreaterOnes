#Parameter für Compiler, Flags, etc.
CC=nasm
CFLAGS=-f elf64

#Übersetze die Assemblerdatei 
#mit NASM in Objektdatei
helloworld-a: helloworld-a.o
	ld helloworld-a.o -o helloworld-a
	
helloworld-a.o: helloworld-a.asm
	$(CC) $(CFLAGS) -o $@ $<
	
