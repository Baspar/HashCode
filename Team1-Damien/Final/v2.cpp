#include <iostream>
#include <map>
#include <vector>
#include <math.h>

using namespace std;

int nbDrone, nbWarehouse, nbTour, poidsMax;
int R,C;

int nbProd;
int nbOrder;

vector<int> poidsProd;


class Warehouse{
    public:
        int x;
        int y;
        int id;
        bool isActif;
        vector<int> produits;
		Warehouse(){}
        Warehouse(int a, int b, int c){
            isActif=true;
            id=a;
            x=b;
            y=c;
        }
        void addProd(int qtite){
            produits.push_back(qtite);
        }
};
vector<Warehouse> warehouses;

class Order{
    public:
        int x;
        int y;
        int id;
        vector<int> produits;
		Order(){
		}
        Order(int a, int b, int c){
            id=a;
            x=b;
            y=c;
        }
        void addProd(int x){
            produits.push_back(x);
        }
		bool estFini(){
			for(int i=0; i<produits.size(); i++){
				if(produits[i]!=0)	
					return false;
				}
		}
		vector<Warehouse> trouverUtile(){
			vector<Warehouse> v;
			for(int i=0; i<warehouses.size();i++){
				bool b=false;
				for(int j=0; (j<nbProd) && !b ; j++){
					if( (produits[j]!=0)&&(warehouses[i].produits[j]!=0) ){
						v.push_back(warehouses[i]);
						b=true;
					}
				}
			}
			return v;
		}
};
class Drone{
    public:
        int id;
        int dispo;
        int x;
        int y;
        vector<int> charge;
        Drone(){};
        Drone(int i){
            id=i;
            x=0;
            y=0;
            dispo=0;
        }
};

vector<map<int, int> > whereIsProduct;

vector<Order> orders;

map<int, Drone> droneDispo;
map<int, Drone> droneOccupe;

void lecture(){
    cin >> R >> C >> nbDrone >> nbTour >> poidsMax;

    for(int i=0; i<nbDrone; i++)
        droneDispo[i]=Drone(i);


    cin >> nbProd;
    whereIsProduct.resize(nbProd);
    for(int i=0; i<nbProd; i++){
        int tmp;
        cin >> tmp;
        poidsProd.push_back(tmp);
    }

    cin >> nbWarehouse;
    for(int i=0; i<nbWarehouse; i++){
        int x,y;
        cin >> x >> y;
        warehouses.push_back(Warehouse(i, x, y));
        for(int j=0; j<nbProd; j++){
            int qtiteProd;
            cin >> qtiteProd;
            warehouses[i].addProd(qtiteProd);
            whereIsProduct[j][i]=qtiteProd;
        }
    }

    cin >> nbOrder;
    for(int i=0; i<nbOrder; i++){
        int x, y;
        cin >> x >> y;
        orders.push_back(Order(i, x, y));

        int nbItem;
        cin >> nbItem;
        for(int j=0; j<nbItem; j++){
            int numProd;
            cin >> numProd;
            orders[i].addProd(numProd);
        }
    }
}
bool estFini(){
	for(int i=0; i<orders.size(); i++)
	if(!orders[i].estFini())
		return false;
}
float distance(int x, int y, int x2, int y2){
	return (sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2) ));

}
void load (int numeroDrone, int quantiteProduit, int numeroProduit, int numeroWarehouse){
    //noter qu'on a pris tant de produit dans l'entrepot
	

    cout << numeroDrone << " L " << numeroWarehouse << " " << numeroProduit  << " " << quantiteProduit  << endl; 
}


void deliver (int numeroDrone, int numeroCustomer, int quantiteProduit, int numeroProduit){
    //noter qu'on a commencer tel commande


    cout << numeroDrone << " D " << numeroCustomer << " "<< numeroProduit << " " << quantiteProduit<< endl; 
}

int main(){

    lecture();

	while(!estFini()){
		//cout << "ok" << endl;
		if( (droneDispo.size()!=0) && !estFini() ){
			//		cout << "ok" << endl;
			float min=10000000;
			Drone droneActif;
			Order commandeActif;
			Warehouse entrepotActif;
			for(int i=0; i<orders.size();i++){
		//cout << "ok" << endl;
				vector<Warehouse> v=orders[i].trouverUtile();
	//	cout << "ok" << endl;
				for(int j=0; j<v.size();j++){
		//						cout << "ok" << endl;
						float sigma;
						cout << droneDispo.size() << endl;
						for(pair<int, Drone> p : droneDispo){
			//						cout << "ok" << endl;
	//	cout << orders[i].x << endl;
	//	cout << p.second.x << endl;
	//	cout << v.size();
	//			cout << "ok" << endl;
							sigma=distance(orders[i].x, orders[i].y, p.second.x, p.second.y) +distance(orders[i].x, orders[i].y, v[j].x, v[j].y);
//		cout << "ok" << endl;
							if( sigma<min) {
								min=sigma;
										//cout << "ok" << endl;
								droneActif=p.second;
	//	cout << "ok1" << endl;
								commandeActif=orders[i];
		//cout << "ok2" << endl;
								entrepotActif=v[j];
	//	cout << "ok3" << endl;
							}
	//	cout << "ok" << endl;
						}
	//	cout << "ok" << endl;
						int capaciteMax;
						vector <pair <int , int > > chargement;
						chargement.clear();
						for(int k=0; k< nbProd; k++){
							bool b=true;
							while(b){
								int nbProd=0;
								if( (commandeActif.produits[k]>0) && (entrepotActif.produits[k]>0 ) && (poidsProd[k]<capaciteMax) ){
									nbProd++;
									commandeActif.produits[k]--;
									entrepotActif.produits[k]--;
									capaciteMax-=poidsProd[k];
								}
								else b=false;
							}
							//		cout << "ok" << endl;
					//		load(droneActif.id, nbProd, k, entrepotActif.id);
							chargement.push_back(make_pair(nbProd, k));
						}
					//	for(int k=0; k<chargement.size(); k++)
						//	deliver(droneActif.id, commandeActif.id, chargement[k].first, chargement[k].second);
						
						droneActif.dispo=ceil(sigma);
						droneDispo.erase(droneActif.id);
						droneOccupe[droneActif.id]=droneActif;
				}

			}
		}
		for (pair<int, Drone> p : droneOccupe){
			p.second.dispo--;
			if(p.second.dispo==0){
				droneOccupe.erase(p.second.id);
				droneDispo[p.second.id]= p.second;
			}
		}
	}
}
