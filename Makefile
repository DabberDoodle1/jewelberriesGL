all: all.o
	g++ main.o glad.o shaders.o -ldl -lglfw -o main && mv *.o {} && ./main

all.o: main.cpp src/glad.c src/shaders.cpp
	g++ -c main.cpp src/glad.c src/shaders.cpp

clean:
	rm *.o main
