CXX      = /usr/sup/bin/clang++
CXXFLAGS = --std=c++11 -Wshadow -Wall -Wextra -g3

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

findpath: main.o Location.o Graph.o Driver.o
	$(CXX) -o $@ $^ 
	
test: Location.o Graph.o testGraph.cpp
	$(CXX) -o $@ $^ 

Graph.o: Graph.cpp Graph.h locationStruct.h
clean: 
	rm -f rt findpath *.o

