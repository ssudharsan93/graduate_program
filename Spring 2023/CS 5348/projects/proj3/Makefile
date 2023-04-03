COMPUTER = computer.exe
PRINTER = printer.exe
SOURCES = computer.cpp memory.cpp load.cpp shell.cpp cpu.cpp scheduler.cpp print.cpp
HEADERS = computer.h memory.h load.h shell.h cpu.h scheduler.h print.h
CXX = g++
CFLAGS = -pthread -g -Wall -std=gnu++11
OBJECTS = $(SOURCES:.cpp=.o)

all: $(COMPUTER) $(PRINTER)

$(COMPUTER) : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(COMPUTER)

$(PRINTER) : printer.o
	$(CXX) $(CFLAGS) printer.o -o $(PRINTER)

computer.o: computer.cpp computer.h
	$(CXX) $(CFLAGS) -c computer.cpp

memory.o: memory.cpp memory.h
	$(CXX) $(CFLAGS) -c memory.cpp

load.o: load.cpp load.h
	$(CXX) $(CFLAGS) -c load.cpp

shell.o: shell.cpp shell.h
	$(CXX) $(CFLAGS) -c shell.cpp

cpu.o: cpu.cpp cpu.h
		$(CXX) $(CFLAGS) -c cpu.cpp

scheduler.o: scheduler.cpp scheduler.h
		$(CXX) $(CFLAGS) -c scheduler.cpp

print.o: print.cpp print.h
		$(CXX) $(CFLAGS) -c print.cpp

printer.o: printer.cpp printer.h
		$(CXX) $(CFLAGS) -c printer.cpp

clean:
	rm -f ${EXECUTABLE} $(OBJECTS)
