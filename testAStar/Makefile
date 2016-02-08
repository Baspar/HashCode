GPP=g++ --std=c++11
all: Noeud.o AlgoA.o Graphe.o
	$(GPP) main.cpp $^ -o main

%.o: %.cpp
	$(GPP) -c $<

clean:
	rm -f *.o main
