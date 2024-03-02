build:
	gcc -o tema3 tema3-functii.c main.c
clean:
	rm -f tema3
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3