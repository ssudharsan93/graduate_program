EXECUTABLE1 = test1.exe 
EXECUTABLE2 = test2.exe
EXECUTABLE3 = print.exe
SOURCES = test1.cpp test2.cpp print.cpp printer.cpp
CXX = g++
CFLAGS = -Wall -std=gnu++11
OBJECT1 = test1.o
OBJECT2 = test2.o
OBJECT3 = print.o
OBJECT4 = printer.o


all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE1) : $(OBJECT1)
	$(CXX) $(OBJECT1) -o $(EXECUTABLE1)

$(EXECUTABLE2) : $(OBJECT2)
	$(CXX) $(OBJECT2) -o $(EXECUTABLE2)

$(EXECUTABLE3) : $(OBJECT3) $(OBJECT4)
	$(CXX) $(OBJECT3) $(OBJECT4) -o $(EXECUTABLE3)

test1.o: test1.cpp
	$(CXX) $(CFLAGS) -c test1.cpp

test2.o: test2.cpp
	$(CXX) $(CFLAGS) -c test2.cpp

print.o: print.cpp print.h
	$(CXX) $(CFLAGS) -c print.cpp

printer.o: printer.cpp printer.h
	$(CXX) $(CFLAGS) -c printer.cpp

clean:
	rm -f ${EXECUTABLE1} ${EXECUTABLE2} ${EXECUTABLE3} $(OBJECT1) ${OBJECT2}
