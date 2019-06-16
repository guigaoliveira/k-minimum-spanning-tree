all: main

main: main.cpp 
	g++ -std=c++17 -O3 main.cpp min_heap.hpp graph.cpp disjoint_set.cpp util.cpp -o main.out

clean:
	rm *.o output.out