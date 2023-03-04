EXECUTABLE1 = hw2_bst_delete
SOURCES = main.cpp TreeNode.cpp
HEADERS = TreeNode.h
CXX = g++
CFLAGS = -Wall
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE1)

$(EXECUTABLE1) : main.o TreeNode.o
	$(CXX) main.o TreeNode.o -o $(EXECUTABLE1)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

TreeNode.o: TreeNode.cpp TreeNode.h
	$(CXX) $(CFLAGS) -c TreeNode.cpp

clean:
	rm -f ${EXECUTABLE1} $(OBJECTS)
