all:	main

main:	main.o JogoSenha.o
	gcc main.o JogoSenha.o -o main

main.o:	main.c
	gcc -g -c main.c
JogoSenha.o:	JogoSenha.c
	gcc -g -c JogoSenha.c

clean:
	rm -f *.o *~ main
