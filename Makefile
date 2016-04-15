COMPILER=clang

WARNINGS=-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors

CPPFLAGS=-std=gnu++11 -c -O3 -DNDEBUG -DBOOST_UBLAS_NDEBUG $(WARNINGS) -I.

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm -lgmpxx -lgmp -lstdc++

SOURCES=timer.cpp premiers.cpp graphe.cpp $(wildcard probleme*.cpp) $(wildcard probleme0xx/*.cpp) $(wildcard probleme1xx/*.cpp)

TEST_SOURCES=test.cpp $(wildcard test/*.cpp)

INCLUDES=$(wildcard *.h)

OBJECTS=$(SOURCES:.cpp=.o)

TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

all: $(SOURCES) Euler Test

Euler: $(OBJECTS) euler.o
	$(COMPILER) $(OBJECTS) euler.o -o $@ $(LDFLAGS)
	
Test: $(OBJECTS) $(TEST_OBJECTS)
	$(COMPILER) $(OBJECTS) $(TEST_OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp $(INCLUDES)
	$(COMPILER) $< -o $@ $(CPPFLAGS)
		
clean:
	rm $(OBJECTS) $(TEST_OBJECTS) Euler Test
