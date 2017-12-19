CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

PROG = minpriority
$(PROG) :  main.o minpriority.o
	$(CXX) $(LDFLAGS) main.o  minpriority.o  -o  $(PROG)

main.o: main.cpp minpriority.h
	$(CXX) $(CXXFLAGS) main.cpp

minpriority.o: minpriority.cpp minpriority.h 
	$(CXX) $(CXXFLAGS) minpriority.cpp

clean:
	rm -f core $(PROG) *.o
