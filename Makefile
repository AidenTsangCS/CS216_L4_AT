CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

run: main
	./main

clean:
	rm -f main
