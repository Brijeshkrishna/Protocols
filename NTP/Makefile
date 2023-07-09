CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=ntp.cpp ntp.hpp
OBJECTS=ntp.o
EXECUTABLE=ntp.exe


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)