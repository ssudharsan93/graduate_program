EXECUTABLE1 = test1.exe 
EXECUTABLE2 = test2.exe
EXECUTABLE3 = print_proj2.exe
SERVER = server.exe
CLIENT = client.exe
PRINTER = printer.exe
SOURCES = test1.cpp test2.cpp print_proj2.cpp printer_proj2.cpp server.cpp client.cpp printer.cpp printer.h
CXX = g++
CFLAGS = -Wall -std=gnu++11
OBJECT1 = test1.o
OBJECT2 = test2.o
OBJECT3 = print_proj2.o
OBJECT4 = printer_proj2.o
SERVER_OBJECT = server.o
CLIENT_OBJECT = client.o

all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(SERVER) $(CLIENT) $(PRINTER)

$(EXECUTABLE1) : $(OBJECT1)
	$(CXX) $(OBJECT1) -o $(EXECUTABLE1)

$(EXECUTABLE2) : $(OBJECT2)
	$(CXX) $(OBJECT2) -o $(EXECUTABLE2)

$(EXECUTABLE3) : $(OBJECT3) $(OBJECT4)
	$(CXX) $(OBJECT3) $(OBJECT4) -o $(EXECUTABLE3)

$(SERVER) : server.cpp
	$(CXX) server.cpp -o $(SERVER)

$(CLIENT) : client.cpp
	$(CXX) client.cpp -o $(CLIENT)

$(PRINTER) : printer.cpp printer.h
	$(CXX) printer.cpp -o $(PRINTER)

test1.o: test1.cpp
	$(CXX) $(CFLAGS) -c test1.cpp

test2.o: test2.cpp
	$(CXX) $(CFLAGS) -c test2.cpp

print_proj2.o: print_proj2.cpp print_proj2.h
	$(CXX) $(CFLAGS) -c print_proj2.cpp

printer_proj2.o: printer_proj2.cpp printer_proj2.h
	$(CXX) $(CFLAGS) -c printer_proj2.cpp

clean:
	rm -f $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) $(SERVER) $(CLIENT) $(PRINTER) $(OBJECT1) $(OBJECT2) $(OBJECT3) $(OBJECT4)
