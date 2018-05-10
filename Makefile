CC=g++
CFLAGS= -I. -std=c++14 -O3 -DNDEBUG -g0 -Wall
LDFLAGS = -g0

all: project5

project5: main.o PSO.o Problem.o Particle.o
	$(CC) $(LDFLAGS) -o project5 main.o PSO.o Problem.o Particle.o

Particle.o: Particle.cpp Particle.h
	$(CC) -c -o Particle.o Particle.cpp $(CFLAGS)

PSO.o: PSO.cpp PSO.h particle.h
	$(CC) -c -o PSO.o PSO.cpp $(CFLAGS)

Problem.o: Problem.cpp Problem.h PSO.h
	$(CC) -c -o Problem.o Problem.cpp $(CFLAGS)

main.o: main.cpp problem.h PSO.h
	$(CC) -c -o main.o main.cpp $(CFLAGS)

clean:
	rm -f *.o project5 *.csv *.png

CleanAll: clean
	rm -rf problems experiments *.gif
