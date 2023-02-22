CXX = g++

all: hw4

hw4: hw4.o Firework.o Barge.o
	$(CXX) -o hw4 hw4.o Firework.o Barge.o

hw4.o: hw4.sxs220093.cpp Barge.h
	$(CXX) -c hw4.sxs220093.cpp -o hw4.o

Firework.o: Firework.cpp Firework.h
	$(CXX) -c Firework.cpp

Barge.o: Barge.cpp Barge.h
	$(CXX) -c Barge.cpp

clean:
	rm -f *.o
