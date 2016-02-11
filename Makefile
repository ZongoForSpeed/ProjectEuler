COMPILER=clang

CPPFLAGS=-std=gnu++11 -c -Wall -O3 -DNDEBUG -DBOOST_UBLAS_NDEBUG

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm -lgmpxx -lgmp -lstdc++

SOURCES=Timer.cpp Arithmetiques.cpp Graphe.cpp $(wildcard Probleme*.cpp) Euler.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) Euler

Euler: $(OBJECTS) 
	$(COMPILER) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o: Arithmetiques.h Timer.h
	$(COMPILER) $< -o $@ $(CPPFLAGS) 
	
clean:
	rm *.o Euler
