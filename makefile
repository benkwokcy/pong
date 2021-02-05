FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow
LIBRARIES = -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_ttf
MAIN = source/*.cpp

run:
	g++ $(MAIN) -o pong $(FLAGS) $(LIBRARIES)
	./pong

san:
	g++ $(MAIN) -o pong -g $(FLAGS) $(LIBRARIES) -fsanitize=address -fsanitize=undefined 
	./pong

debug:
	g++ $(MAIN) -o pong -g $(FLAGS) $(LIBRARIES)

fast:
	g++ $(MAIN) -o pong -O3 $(FLAGS) $(LIBRARIES)
	./pong

clean:
	rm pong