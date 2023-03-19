EXECUTABLE1 = test1.exe 
EXECUTABLE2 = test2.exe
EXECUTABLE3 = print_proj2.exe
SOURCES = test1.cpp test2.cpp print_proj2.cpp printer_proj2.cpp
CXX = g++
CFLAGS = -Wall -std=gnu++11
OBJECT1 = test1.o
OBJECT2 = test2.o
OBJECT3 = print_proj2.o
OBJECT4 = printer_proj2.o


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

print_proj2.o: print_proj2.cpp print_proj2.h
	$(CXX) $(CFLAGS) -c print_proj2.cpp

printer_proj2.o: printer_proj2.cpp printer_proj2.h
	$(CXX) $(CFLAGS) -c printer_proj2.cpp

clean:
	rm -f $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(OBJECT1) $(OBJECT2) $(OBJECT3) $(OBJECT4)
