#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "Noeud.hpp"

using namespace std;

class Graphe{
   public: 
    float distance(Noeud* noeud1, Noeud* noeud2);
};
#endif
