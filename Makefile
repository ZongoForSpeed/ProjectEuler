COMPILER=clang

WARNINGS=-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors

CPPFLAGS=-std=gnu++11 -c -O3 -DNDEBUG -DBOOST_UBLAS_NDEBUG $(WARNINGS)	

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm -lgmpxx -lgmp -lstdc++

SOURCES=timer.cpp premiers.cpp graphe.cpp $(wildcard probleme*.cpp)

INCLUDES=$(wildcard *.h)

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) Euler Test

Euler: $(OBJECTS) euler.o
	$(COMPILER) $(OBJECTS) euler.o -o $@ $(LDFLAGS)
	
Test: $(OBJECTS) test.o
	$(COMPILER) $(OBJECTS) test.o -o $@ $(LDFLAGS)

.cpp.o: $(INCLUDES)
	$(COMPILER) $< -o $@ $(CPPFLAGS) 

#euler.o: euler.cpp
#	$(COMPILER) $< -o $@ $(CPPFLAGS) 
	
#test.o: test.cpp
#	$(COMPILER) $< -o $@ $(CPPFLAGS) 
	
clean:
	rm *.o Euler
