build/ml: *.c
	gcc -o build/ml *.c -std=c99 -Wall -Wextra -Wpedantic
