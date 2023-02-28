EXECUTABLE1 = test1.exe 
EXECUTABLE2 = test2.exe
EXECUTABLE3 = test3.exe
SOURCES = test1.cpp test2.cpp test3.cpp test4.cpp
CXX = g++
CFLAGS = -Wall -std=gnu++11
OBJECT1 = test1.o
OBJECT2 = test2.o
OBJECT3 = test3.o
OBJECT4 = test4.o


all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE1) : $(OBJECT1)
	$(CXX) $(OBJECT1) -o $(EXECUTABLE1)

$(EXECUTABLE2) : $(OBJECT2)
	$(CXX) $(OBJECT2) -o $(EXECUTABLE2)

$(EXECUTABLE3) : $(OBJECT3) $(OBJECT4)
	$(CXX) $(OBJECT3) -o $(EXECUTABLE3)

test1.o: test1.cpp
	$(CXX) $(CFLAGS) -c test1.cpp

test2.o: test2.cpp
	$(CXX) $(CFLAGS) -c test2.cpp

test3.o: test3.cpp test3.h
	$(CXX) $(CFLAGS) -c test3.cpp

test4.o: test4.cpp test.h
	$(CXX) $(CFLAGS) -c test4.cpp

clean:
	rm -f ${EXECUTABLE1} ${EXECUTABLE2} $(OBJECT1) ${OBJECT2}
