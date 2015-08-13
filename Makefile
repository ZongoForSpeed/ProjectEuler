CC=g++

CFLAGS=-std=gnu++11 -c -Wall -O3 -lboost_timer -lboost_system -lm

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm

SOURCES=Timer.cpp Arithmetiques.cpp Problemes.cpp Probleme156.cpp Probleme303.cpp Probleme346.cpp Probleme357.cpp Probleme381.cpp Probleme500.cpp Probleme501.cpp Euler.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=Euler

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) 
	
clean:
	rm *.o $(EXECUTABLE)
