EXECUTABLE1 = hw2_bst_delete
SOURCES = main.cpp BinarySearchTree.cpp
HEADERS = BinarySearchTree.h
CXX = g++
CFLAGS = -Wall
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1) : hw1_bubble_sort.o ListNode.o
	$(CXX) hw1_bubble_sort.o ListNode.o -o $(EXECUTABLE1)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h
	$(CXX) $(CFLAGS) -c BinarySearchTree.cpp

clean:
	rm -f ${EXECUTABLE1} ${EXECUTABLE2} $(OBJECTS)
