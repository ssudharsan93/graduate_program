EXECUTABLE1 = hw3
SOURCES = main.cpp
CXX = g++
CFLAGS = -Wall
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE1)

$(EXECUTABLE1) : main.o
	$(CXX) main.o -o $(EXECUTABLE1)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

clean:
	rm -f ${EXECUTABLE1} $(OBJECTS)
