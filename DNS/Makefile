CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=dns.cpp dns.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dns.exe


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)