build:
	g++ src/*.cpp -lraylib -I./include/

debug:
	g++ -g src/*.cpp -lraylib -I./include/
