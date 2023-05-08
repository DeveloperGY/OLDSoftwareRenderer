make: build run

build:
	g++ src/*.cpp -o bin/exe -Wall -Wextra -Werror -Ilibs -Llibs -lm3 -ltermDisplay

run:
	./bin/exe