CC=g++
CFLAGS=-std=c++11 -c -Wall -O3 -lboost_timer -lboost_system -lm
LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm
SOURCES=Timer.cpp Bezout.cpp Premiers.cpp Probleme171.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Euler

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) 
	
clean:
	rm *.o $(EXECUTABLE)
