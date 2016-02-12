#ifndef ALGOA_HPP
#define ALGOA_HPP

#include <iostream>
#include <vector>
#include "Noeud.hpp"
#include <queue>

using namespace std;

class AlgoA{
    private:
        vector<Noeud*> listerFermee;
        vector<Noeud*> solution;
        Noeud* depart;
        Noeud* arrivee;
        priority_queue<pair<Noeud,int> > listeOuverte;
        void updateListeFermee();
        void updateListeOuverte(Noeud* noeud);
        float distanceArrivee(Noeud* n);
    public:
       priority_queue<pair<Noeud,int> >  getListeOuverte();
       void setListeOuverte(priority_queue<pair<Noeud,int> > listeOuverte);
	   vector<Noeud*> getListeFermee();
	   void setListeFermee(vector<Noeud*> listeFermee);
	   vector<Noeud*> getSolution();
	   void setSolution(vector<Noeud*> solution);
	   Noeud* getDepart();
	   void setDepart(Noeud* depart);
	   Noeud* getArrivee();
	   void setArrivee(Noeud* arrivee);	
	   AlgoA(Noeud* noeudDepart, Noeud* noeudArrivee);
       void resolution();
};
#endif
