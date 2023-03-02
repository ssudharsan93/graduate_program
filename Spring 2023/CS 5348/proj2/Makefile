EXECUTABLE = computer.exe
SOURCES = computer.cpp memory.cpp load.cpp shell.cpp cpu.cpp scheduler.cpp
HEADERS = computer.h memory.h load.h shell.h cpu.h scheduler.h
CXX = g++
CFLAGS = -g -Wall -std=gnu++11
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

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

clean:
	rm -f ${EXECUTABLE} $(OBJECTS)
