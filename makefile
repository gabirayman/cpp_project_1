# gabi.rayman@gmail.com
CXX=clang++
CXXFLAGS=-std=c++2a

Main: main.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) main.o Graph.o Algorithms.o -o Main
	./Main

test: test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) test.o Graph.o Algorithms.o -o test
	./test

main.o: main.cpp Graph.hpp Algorithms.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp Graph.hpp Algorithms.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp
	$(CXX) $(CXXFLAGS) -c Algorithms.cpp

valgrind: Main
	valgrind ./Main

clean:
	rm -f *.o Main test
