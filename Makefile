CC=g++

CFLAGS=-std=gnu++11 -c -Wall -O3 -lboost_timer -lboost_system -lm -lgmpxx -lgmp

LDFLAGS=-L/usr/local/boost/lib -lboost_timer -lboost_system -lm -lgmpxx -lgmp

SOURCES=Timer.cpp Arithmetiques.cpp Probleme001.cpp Probleme002.cpp Probleme003.cpp Probleme004.cpp Probleme005.cpp Probleme006.cpp Probleme007.cpp Probleme008.cpp Probleme009.cpp Probleme010.cpp Probleme011.cpp Probleme012.cpp Probleme013.cpp Probleme014.cpp Probleme015.cpp Probleme016.cpp Probleme017.cpp Probleme018.cpp Probleme019.cpp Probleme020.cpp Probleme021.cpp Probleme022.cpp Probleme023.cpp Probleme024.cpp Probleme025.cpp Probleme026.cpp Probleme027.cpp Probleme028.cpp Probleme029.cpp Probleme030.cpp Probleme156.cpp Probleme303.cpp Probleme346.cpp Probleme357.cpp Probleme381.cpp Probleme500.cpp Probleme501.cpp Euler.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=Euler

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) 
	
clean:
	rm *.o $(EXECUTABLE)
