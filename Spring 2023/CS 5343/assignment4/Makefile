EXECUTABLE = hw4
SOURCES = main.cpp Graph.cpp Edge.cpp Vertex.cpp
CXX = g++
CFLAGS = -Wall -std=gnu++11
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE) : main.o Graph.o Edge.o Vertex.o
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CFLAGS) -c Graph.cpp

Edge.o: Edge.cpp Edge.h
	$(CXX) $(CFLAGS) -c Edge.cpp

Vertex.o: Vertex.cpp Vertex.h
	$(CXX) $(CFLAGS) -c Vertex.cpp

clean:
	rm -f ${EXECUTABLE} $(OBJECTS)
