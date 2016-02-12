#ifndef NOEUD_HPP
#define NOEUD_HPP

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Noeud{
    protected:
         string id;
         float g,h,f;
	     Noeud* pere;
	public:
	    virtual vector<Noeud*> successeurs()=0;
        Noeud* getPere();
        void setPere(Noeud* pere);
	    float getG();
	    void setG(float g);
	    float getH();
	    void setH(float h);
	    float getF();
	    void setF(float f);
	    string getId();
	    void setId(string id);
};
#endif
