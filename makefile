FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow
LIBRARIES = -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_ttf

build:
	g++ pong.cpp -o pong $(FLAGS) $(LIBRARIES)

san:
	g++ pong.cpp -o pong $(FLAGS) $(LIBRARIES) -fsanitize=address -fsanitize=undefined 

debug:
	g++ pong.cpp -o pong -g $(FLAGS) $(LIBRARIES)

release:
	g++ pong.cpp -o pong -O3 $(FLAGS) $(LIBRARIES)

run: build
	./pong

clean:
	rm pong