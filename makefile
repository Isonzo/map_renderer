build:
	g++ src/*.cpp -lraylib -I./include/ -std=c++20

debug:
	g++ -g src/*.cpp -lraylib -I./include/
