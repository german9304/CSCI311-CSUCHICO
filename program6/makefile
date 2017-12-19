CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

mstapp: graph.o minpriority.o mstapp.o
	$(CXX) $(LDFLAGS) graph.o minpriority.o mstapp.o -o mstapp

graph.o: graph.cpp graph.h minpriority.h
	$(CXX) $(CXXFLAGS) graph.cpp

minpriority.o: minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp

mstapp.o: mstapp.cpp mstapp.h graph.h
	$(CXX) $(CXXFLAGS) mstapp.cpp

clean:
	rm *o mstapp
