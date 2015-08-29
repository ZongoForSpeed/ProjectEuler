CPPFLAGS=-std=gnu++11 -c -Wall -O3 -lboost_timer -lboost_system -lm -lgmpxx -lgmp

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm -lgmpxx -lgmp

SOURCES=Timer.cpp Arithmetiques.cpp $(wildcard Probleme*.cpp) Euler.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) Euler

Euler: $(OBJECTS) 
	g++ $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o: Arithmetiques.h Timer.h
	g++ $< -o $@ $(CPPFLAGS) 
	
clean:
	rm *.o Euler
