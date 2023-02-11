build:
<<<<<<< HEAD
	g++ src/*.cpp -lraylib -I./include/ -std=c++20 -o mapviz -O2
=======
	g++ src/*.cpp -lraylib -I./include/ -std=c++20 -o mapviz
>>>>>>> aac0c2cba39f4f3baf6f462d10ffc5a32fc9ae39

debug:
	g++ -g src/*.cpp -lraylib -I./include/ -std=c++20
