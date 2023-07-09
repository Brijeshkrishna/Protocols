CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=icmp.cpp icmp.hpp
OBJECTS=icmp.o
EXECUTABLE=icmp.exe


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)