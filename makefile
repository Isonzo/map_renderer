build:
	g++ src/*.cpp -lraylib -I./include/ -std=c++20 -o mapgen

debug:
	g++ -g src/*.cpp -lraylib -I./include/
