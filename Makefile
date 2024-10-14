all:
	g++ -Iinclude/SDL2 -Iinclude/imgui -Llib -o main src/*.cpp imgui/*.cpp -lmingw32 -lSDL2main -lSDL2