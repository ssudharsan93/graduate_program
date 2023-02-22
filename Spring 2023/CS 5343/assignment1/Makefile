EXECUTABLE1 = hw1_bubble_sort
EXECUTABLE2 = hw1_ternary_search
SOURCES = hw1_bubble_sort.cpp hw1_ternary_search.cpp ListNode.cpp
HEADERS = ListNode.h
CXX = g++
CFLAGS = -Wall
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1) : hw1_bubble_sort.o ListNode.o
	$(CXX) hw1_bubble_sort.o ListNode.o -o $(EXECUTABLE1)

$(EXECUTABLE2) : hw1_ternary_search.o
	$(CXX) hw1_ternary_search.o -o $(EXECUTABLE2)

hw1_bubble_sort.o: hw1_bubble_sort.cpp
	$(CXX) $(CFLAGS) -c hw1_bubble_sort.cpp

ListNode.o: ListNode.cpp ListNode.h
	$(CXX) $(CFLAGS) -c ListNode.cpp

hw1_ternary_search.o: hw1_ternary_search.cpp
	$(CXX) $(CFLAGS) -c hw1_ternary_search.cpp

clean:
	rm -f ${EXECUTABLE1} ${EXECUTABLE2} $(OBJECTS)
