build:
	g++ src/*.cpp -lraylib -I./include/ -std=c++20 -o mapviz -O2

debug:
	g++ -g src/*.cpp -lraylib -I./include/ -std=c++20
