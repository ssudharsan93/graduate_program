EXECUTABLE1 = test1.exe 
EXECUTABLE2 = test2.exe
SOURCES = test1.cpp test2.cpp
CXX = g++
CFLAGS = -Wall -std=gnu++11
OBJECT1 = test1.o
OBJECT2 = test2.o

all: $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1) : $(OBJECT1)
	$(CXX) $(OBJECT1) -o $(EXECUTABLE1)

$(EXECUTABLE2) : $(OBJECT2)
	$(CXX) $(OBJECT2) -o $(EXECUTABLE2)

test1.o: test1.cpp
	$(CXX) $(CFLAGS) -c test1.cpp

test2.o: test2.cpp
	$(CXX) $(CFLAGS) -c test2.cpp

clean:
	rm -f ${EXECUTABLE1} ${EXECUTABLE2} $(OBJECT1) ${OBJECT2}
