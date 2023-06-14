EXECUTABLE = hw5
SOURCES = main.cpp DirectedGraph.cpp DirectedEdge.cpp Vertex.cpp
CXX = g++
CFLAGS = -Wall -std=gnu++11 
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE) : main.o DirectedGraph.o DirectedEdge.o Vertex.o
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

DirectedGraph.o: DirectedGraph.cpp DirectedGraph.h
	$(CXX) $(CFLAGS) -c DirectedGraph.cpp

DirectedEdge.o: DirectedEdge.cpp DirectedEdge.h
	$(CXX) $(CFLAGS) -c DirectedEdge.cpp

Vertex.o: Vertex.cpp Vertex.h
	$(CXX) $(CFLAGS) -c Vertex.cpp

clean:
	rm -f ${EXECUTABLE} $(OBJECTS)

clnobj:
	rm -f $(OBJECTS)
