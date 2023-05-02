EXECUTABLE = hw6
SOURCES = main.cpp HashTable.cpp
HEADERS = HashTable.h
CXX = g++
CFLAGS = -Wall
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE) : main.o HashTable.o
	$(CXX) main.o HashTable.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CFLAGS) -c HashTable.cpp

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
