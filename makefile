all:
	gcc lscommand.c -o ls
	gcc catcommand.c -o cat
	gcc datecommand.c -o date
	gcc mkdircommand.c -o mkdir
	gcc rmcommand.c -o rm
	gcc -lpthread question1.c
	./a.out
remove:
	rm ls
	rm rm
	rm cat
	rm mkdir
	rm date
