FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow
LIBRARIES = -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_ttf

run:
	g++ pong.cpp -o pong $(FLAGS) $(LIBRARIES)
	./pong

san:
	g++ pong.cpp -o pong -g $(FLAGS) $(LIBRARIES) -fsanitize=address -fsanitize=undefined 
	./pong

debug:
	g++ pong.cpp -o pong -g $(FLAGS) $(LIBRARIES)

fast:
	g++ pong.cpp -o pong -O3 $(FLAGS) $(LIBRARIES)
	./pong

clean:
	rm pong