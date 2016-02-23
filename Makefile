COMPILER=clang

WARNINGS=-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors

CPPFLAGS=-std=gnu++11 -c -O3 -DNDEBUG -DBOOST_UBLAS_NDEBUG $(WARNINGS)	

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm -lgmpxx -lgmp -lstdc++

SOURCES=timer.cpp premiers.cpp graphe.cpp $(wildcard probleme*.cpp) euler.cpp

INCLUDES=$(wildcard *.h)

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) Euler

Euler: $(OBJECTS) 
	$(COMPILER) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o: $(INCLUDES)
	$(COMPILER) $< -o $@ $(CPPFLAGS) 
	
clean:
	rm *.o Euler
