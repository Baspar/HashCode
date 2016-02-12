#include <bits/stdc++.h>
#include <algorithm>
#define ui int
#define FICHIER "ex"

/// ---------------------------------------- NON FONCTIONNELLE ---------------------------------------------------/
/// Pour faire avancer le jeu
ui __TOUR__NUMERO__ = 0;
std::vector<std::string > commandes_a_faire;

/// Quelques fonctions du code
/// voir après les classes les autres qui requiert d'avoir défini les classes avant
template<typename T>
inline T distance(const T&a,const T&b,const T&c,const T&d);
void occuperDrone();
void updatePriority();


/// ----------------------------------------------------- Classe ---------------------------------------------/
class Item
{
public:
    Item(ui c,ui p) : code_(c),poids_(p) {};
    inline ui code() const
    {
        return code_;
    }
    inline ui poids() const
    {
        return poids_;
    }

    bool operator==(const Item& rhs)
    {
        return rhs.poids() == poids_ && code_ == rhs.code();
    }

    ui code_;
    ui poids_;
};

class Ordre
{
public:
    Ordre(ui x__,ui y__,ui code) : x_(x__), y_(y__), code_(code)  {};
    Ordre& operator=(const Ordre& rhs)
    {
        x_ = rhs.x();
        y_ = rhs.y();
        code_ = rhs.code();
        poids_ = rhs.poids();
        items = rhs.items;

        return *this;
    }
    bool operator<(const Ordre& )
    {
        return true;
    }
    bool operator==(const Ordre rhs)
    {
        ui j=0;
        if( x_ != rhs.x() || y_ != rhs.y() )
            return false;
        if(items.size() != rhs.items.size())
            return false;
        else
        {
            for(Item i :items)
            {
                if(i == rhs.items.at(j++))
                {
                    continue;
                }
                else return false;
            }
        }
        return true;
    }
    inline ui x() const
    {
        return x_;
    }
    inline ui y() const
    {
        return y_;
    }
    ~Ordre()
    {
        items.erase(items.begin(),items.end());
        items.clear();
    }
    void setPoids() noexcept
    {
        poids_=0;
        for(Item i : items)
        {
            poids_+=i.poids();
        }
    }
    inline ui poids() const
    {
        return poids_;
    }
    inline code() const
    {
        return code_;
    }
    ui x_;
    ui y_;
    ui code_;

    ui poids_;
    std::vector<Item> items;
};

class Warehouse
{
public:
    // Tri completement inutil, juste pour supprimer les doublons
    friend bool operator<(const Warehouse&a,const Warehouse&b )
    {
        return a.code() < b.code();
    }

    Warehouse() : x_(0), y_(0) {};
    Warehouse(ui x,ui y,ui code) : x_(x),y_(y),code_(code) {};
    ~Warehouse()
    {
        items.erase(items.begin(),items.end());
        items.clear();
    };
    bool operator==(const Warehouse& rhs)
    {
        ui j=0;
        if(x_ != rhs.x() || y_ != rhs.y() )
            return false;
        if(items.size() != rhs.items.size())
            return false;
        else
        {
            for(Item &i :items)
            {
                if(i == rhs.items.at(j++))
                {
                    continue;
                }
                else return false;
            }
        }
        return true;
    }

    ui x()const
    {
        return x_;
    }
    Warehouse& operator=(const Warehouse& rhs)
    {
        x_ = rhs.x();
        y_ = rhs.y();
        items = rhs.items;
        return *this;
    }
    ui y() const
    {
        return y_;
    }
    ui code() const
    {
        return code_;
    }
    ui x_;
    ui y_;
    ui code_;
    std::vector<Item> items;
};

class Robot
{
public:
    Robot(int x__,int y__,int charge_,int numero) : numero_(numero), x_(x__), y_(y__), chargeMax_(charge_),
        poidsActuel_(0), occupe_(false), nbreTourUtilise_(0), ordreCharge_(0,0,0) , tempsLivraison_(0) {};

    Robot& operator=(const Robot& r)
    {
        x_=r.x();
        y_ = r.y();
        poidsActuel_ = r.poidsActuel();
        chargeMax_ = r.chargeMax();
        return *this;
    }
    bool operator==(const Robot& r)
    {
        if(r.numero() == this->numero_)
            return true;
        return false;
    }
    ~Robot()
    {
        items.erase(items.begin(),items.end());
        items.clear();
    }
    void ChargeOrdre(const Ordre& o,const ui timeloading)
    {
        occupe_ = true ;
        nbreTourUtilise_ = __TOUR__NUMERO__ + timeloading + distance(x_,y_,o.x(),o.y());
        ordreCharge_ = o;
        std::cerr << "robot "<< numero_ << " prend en charge " << o.code_ << " jusqu'au " << nbreTourUtilise_ << " tours"<<std::endl;
    }
    inline ui nbreTourUtilise() const
    {
        return nbreTourUtilise_;
    }
    inline ui x() const
    {
        return x_;
    }
    inline ui numero() const
    {
        return numero_;
    }
    inline bool occupe() const
    {
        return occupe_;
    }
    inline ui y() const
    {
        return y_;
    }
    inline ui chargeMax() const
    {
        return chargeMax_;
    }
    inline ui poidsActuel() const
    {
        return poidsActuel_;
    }
    inline ui tempsLivraison() const
    {
        return tempsLivraison_;
    }
    ui numero_;
    ui x_;
    ui y_;
    ui chargeMax_;
    ui poidsActuel_;
    bool occupe_;
    ui nbreTourUtilise_;
    Ordre ordreCharge_;
    ui tempsLivraison_;
    std::vector<Item> items;
};


/// ----------------------------------------------------- ~~~~~~~~~~ ---------------------------------------------------/

/// ----------------------------------------------------- Variable Globale ---------------------------------------------/

/// Variable utilisant les classes dessus
Robot robotEnAction(-1,-1,0,-1);
inline void  updateRobotenaction(const ui& x,const ui&y,const ui& num)
{
    robotEnAction=Robot(x,y,0,num);
}
inline void  updateRobotenaction(const Robot& r)
{
    robotEnAction=r;
}

std::vector<Warehouse> getWarehouseDisponible(Item);

/// La priority queue des ordres
#define paire std::pair<Ordre&,std::vector<Warehouse> >

/// Comparateur d'ordre qui trie dans la priority queue
auto comp = [](const paire &a,const paire &b )
{
    //std::cerr << "Tri de la priority_queue" <<std::endl;
    if(robotEnAction.x() == -1 && robotEnAction.y() == -1)       /// Il y a une erreur , retourne aléatoire
        return (rand() % 1 == 1);
    Ordre o1 = a.first;
    Ordre o2 = b.first;
    if(a.second.size() > b.second.size())                                   /// Heuristique: visiter deux warehouses toujours plus couteux que un
        return false;
    ui d1=std::numeric_limits<ui>::max(),d2=std::numeric_limits<ui>::max();
    /// Recherche du warehouse le plus pret
    /// Comparer distance drone en action et warehouse
    Warehouse buffWa(-1,-1,-1);
    for(Warehouse w : a.second)
    {
        if(d1 >= distance(robotEnAction.x(),robotEnAction.y() , w.x(),w.y()))
        {
            d1 = distance(robotEnAction.x(),robotEnAction.y() , w.x(),w.y());
            buffWa = w;
        }
    }
    if(buffWa.x() == -1 && buffWa.y() == -1)
    {
        std::cerr << "YA UNE ERREUR";
    }
    else
        for(Warehouse w : a.second)
        {
            if(w == buffWa)
            {
                continue;
            }
            else
            {
                /// Si on a plusieurs warehouses a visiter, pas gérer encore (toujours un warehouse)
                d1+= distance(buffWa.x(),buffWa.y(),w.x(),w.y());
                buffWa = w;
            }
        }

    buffWa = Warehouse(-1,-1,-1);
    for(Warehouse w : b.second)
    {

        if(d2 >= distance(robotEnAction.x(),robotEnAction.y() , w.x(),w.y()))
        {
            d2 =distance(robotEnAction.x(),robotEnAction.y() , w.x(),w.y());
            buffWa = w;
        }
    }
    if(buffWa.x() == -1 && buffWa.y() == -1)
    {
        std::cerr << "YA UNE ERREUR";
    }
    else
        for(Warehouse w : b.second)
        {
            if(w == buffWa)
            {
                continue;
            }
            else
            {
                d2+= distance(buffWa.x(),buffWa.y(),w.x(),w.y());
                buffWa = w;
            }
        }
    return d1 < d2;
};

/// La priority
std::vector<paire> prioritequeue;
//std::priority_queue<paire > prioritequeue;
/// Update stock
void updateUtil(Robot&r,paire&);
bool updateWarehouse(Robot&r,paire &p,bool modifie);

void bougerDrone();
/// Variable globale contenant les listes d'objets
std::vector<Item> items;
std::vector<Warehouse> warehouses;
std::vector<Robot> robots;
std::vector<Ordre> orders;


/// Calcul de distance
template<typename T>
inline
T distance(const T& a,const T& b,const T& c,const T& d)
{
    return ceil(pow(abs(c-a),2) + pow(abs(d-b),2));
}


///---> fonctionnelle
void updatePriority()
{
    /// Pour tous les ordres
    for(Ordre &o : orders)
    {
        std::vector<Warehouse> warehouse;
        /// Je récupere les warehouses qui contiennent les items
        for(Item &i : o.items)
        {
            //std::cout << " "<<x<<" ";
            if(i.poids() > 0)
            {
                std::vector<Warehouse> buff = getWarehouseDisponible(i);
                /// je les mets dans un set pour éviter les doublons
                for(Warehouse &www : buff)
                    warehouse.push_back(www);
            }
        }

        /// que je remets dans un vector parce que fuck les set
        // std::vector<Warehouse> warehouse1;
        // std::copy(warehouse.begin(), warehouse.end(), std::back_inserter(warehouse1));
        std::sort(warehouse.begin(),warehouse.end());
        std::unique(warehouse.begin(),warehouse.end());
        /// puis je trie les warehouses par rapport a la distance a l'ordre
        std::sort(warehouse.begin(),warehouse.end(),[=](const Warehouse& a,const Warehouse& b)
        {
            int dA = distance(o.x(),o.y(),a.x(),a.y());
            int dB = distance(o.x(),o.y(),b.x(),b.y());
            return dA < dB;
        });

        /// J'append a la priority queue...
        bool n_trouve = false;
        while( !n_trouve )
        {
            for(Warehouse &w : warehouse)
            {
                bool suffisant=true;

                /// Si un warehouse contient tous les items
                for(Item &i : o.items)
                {
                    if(static_cast<uint32_t>(i.code()) < w.items.size() && w.items.at(i.code()).poids() >= i.poids())
                    {
                        continue;
                    }
                    else suffisant=false;
                }
                if(suffisant == true)
                {
                    n_trouve = true;
                    std::vector<Warehouse *> ww = {w};
                    prioritequeue.push_back(paire(o,ww));
                    break; // J'ai trouvé mon warehouse
                }
            }
            /// Si je ne peux pas récupérer en un warehouse, alors je ne sers pas l'order
            if(n_trouve == false)
            {
                std::cerr << "La commande " << o.code_ <<" ne sera pas charge" << std::endl;
                n_trouve =true;
            }

        }
    }
    //std::cerr << prioritequeue.size();
    std::sort(prioritequeue.begin(),prioritequeue.end(),comp);
}

void occuperDrone()
{
    bool encoreEnLivraison = true;

    while(!prioritequeue.empty() || encoreEnLivraison)
    {
        __TOUR__NUMERO__++;
        //  std::cerr << "TOUR N'" << __TOUR__NUMERO__<< std::endl;
        bougerDrone();
        for(Robot &r : robots)
        {
            if(r.occupe() == false && !prioritequeue.empty())
            {
                std::cerr << "Le robot " << r.numero() << " n'est pas occupe"<<std::endl;
                updateRobotenaction(r);
                paire p = prioritequeue.at(0);

                /// Si il y a une douille de disponibilité, alors il faut refaire la priority en entier

                if(updateWarehouse(r,p,false) == false)
                {
                    std::cerr << "Il faut mettre a jour la priorityqueue"<<std::endl;
                    prioritequeue.clear();
                    updatePriority();
                }
                if(r.chargeMax_ >= p.first.poids())      /// Si le poids est supérieur a la charge max
                {
                    std::cerr << "La derniere commande est "<< p.first.code()<< std::endl;
                    if(updateWarehouse(r,p,false) == true)
                        updateUtil(r,p);
                }
                else
                {
                    /// gérer les différents allez retour pour un order
                }
                prioritequeue.erase(prioritequeue.begin());
                std::sort(prioritequeue.begin(),prioritequeue.end(),comp);
                if(prioritequeue.empty())
                    break;
            }
        }
        bool u =false;
        for(Robot &r :robots)
        {
            if(r.occupe() == true)
            {
                u=true;
                //   std::cerr << r.numero() << " est encore occuper"<<std::endl;
            }
        }
        if(u == true)
            encoreEnLivraison = true;
        else
            encoreEnLivraison = false;
    }
}

bool
updateWarehouse(Robot& r, paire &p,bool modifie)
{
    int c=0;

    /// met a jour les warehouses
    for(Item &i: p.first.items)
    {
        bool trouve=false;
        for(Warehouse &w : p.second)
        {
            /// Si c'est le warehouse qui contient l'item
            if(w.items.at(i.code()).poids() >= i.poids())
            {
                trouve=true;
                if(modifie == true)
                {
                    c++;
                    // Load
                    std::string s = std::to_string(r.numero())+" L "+std::to_string(w.code())
                                    +" "+std::to_string(i.code())+" "+std::to_string(i.poids());
                    commandes_a_faire.push_back(s);
                    // Update
                    w.items.at(i.code()).poids_-=i.poids();
                }
                // Updaye le robot

                break;
            }
        }
        if(trouve == false)
            return false;
    }
    if(modifie)
    {
        auto x = std::find(robots.begin(),robots.end(),r);
        if(x != robots.end())
        {
            x->ChargeOrdre(p.first,c);  /// update robot de charge c, et d'ordre o

        }
    }

    return true;
}

/// Update les drones
/// Update liste des ordres
void updateUtil(Robot &r,paire &p)
{
    updateWarehouse(r,p,true);

    ///met a jour les robots


    /// remove de la liste des orders
    std::vector<Ordre>::iterator x = std::find(orders.begin(),orders.end(),p.first);
    if(x != orders.end())
    {
        orders.erase(std::remove(orders.begin(), orders.end(), *x), orders.end());
        std::cerr << x->code()<< " a été pris en charge par le robot " << r.numero()<<std::endl;
    }

    /// Enregistrement
}


/// Gere l'avancement des drones
void bougerDrone()
{
    for(Robot &r : robots)
    {
        if(r.occupe() == false)
        {
            if(__TOUR__NUMERO__ > r.nbreTourUtilise())     /// Pour update
            {
                // std::cerr << "Le robot "<<r.numero()<<" a livré";
                r.nbreTourUtilise_= __TOUR__NUMERO__;
            }
        }
        else if(r.occupe() == true)
        {
            if(r.tempsLivraison()-1 > 0)
            {
                r.tempsLivraison_--;
                r.nbreTourUtilise_++;
                break;
            }

            if(r.nbreTourUtilise() > __TOUR__NUMERO__)
            {

            }
            else if( r.nbreTourUtilise() == __TOUR__NUMERO__)
            {
                /// Délivré la commande
                r.tempsLivraison_ = 0;
                for(Item i : r.ordreCharge_.items)
                {
                    if(i.poids() > 0)
                    {
                        std::string s = std::to_string(r.numero())+" D "+std::to_string(r.ordreCharge_.code())
                                        +" "+std::to_string(i.code())+" "+std::to_string(i.poids());
                        commandes_a_faire.push_back(s);
                        r.tempsLivraison_++;                  /// Un tour par livraison
                    }
                }
                std::cerr << "Le robot" << r.numero() << " n'est plus occupe: encore "<< r.tempsLivraison()<< std::endl;
                r.ordreCharge_ = Ordre(0,0,0);
            }
            else if(r.tempsLivraison() - 1 == 0)
            {
                std::cerr << "Le robot " << r.numero()<< " a livré" << std::endl;
                r.tempsLivraison_ =0;
                r.occupe_=false;
                r.nbreTourUtilise_++;
            }
        }
    }
}

/**
    Renvoit la liste des warehouses qui ont cette item en bonne quantite
**/
std::vector<Warehouse> getWarehouseDisponible(Item i)
{
    std::vector<Warehouse> warehouse;
    for(const Warehouse &x : warehouses)
    {
        if(x.items.at(i.code()).poids() >= i.poids())
        {
            warehouse.push_back(x);
        }
    }
    return warehouse;
}

int main()
{
    srand(time(NULL));
    // std::string in = std::string(FICHIER+".in"), out = FICHIER+".out";
    std::freopen("ex.in","r",stdin);
    std::freopen("ex.out","w",stdout);
    ui N,M,nbRobots,nbTours,nbItem,poidsMax,nbCommandes;

    std::cin >> N >> M >> nbRobots >> nbTours >> poidsMax;
    //std::cout << N << M << nbRobots << nbTours << poidsMax;
    //std::cin.ignore();
    int a,b,c;
    // poids objet
    std::cin >> nbItem;
    //std::cin.ignore();

    for(int i=0; i<nbItem; i++)
    {
        std::cin >> b;
        Item p(i,b);
        items.push_back(p);
    }


    /// coordonnées warehouse
    std::cin >> a;
    for(int i=0; i<a; i++)
    {
        std::cin >> b >> c;
        int pos = b;
        Warehouse w(b,c,i);
        for(int j=0; j<nbItem; j++)
        {
            std::cin >> b;
            Item p(i,b);
            w.items.push_back(p);
        }
        if(i == 0)
            updateRobotenaction(pos,c,i);
        warehouses.push_back(w);
    }

    std::cin >> nbCommandes;

    for(int i=0; i<nbCommandes; i++)
    {
        std::cin >> a >> b;
        Ordre o(a,b,i);

        for(int j=0 ; j < nbItem ; j++)
        {
            Item p(j,0);
            o.items.push_back(p);
        }
        std::cin >> a;
        for(int j=0; j<a; j++)
        {
            std::cin >> b;
            o.items[b].poids_++;
        }

        /// Poids max de la commande
        o.setPoids();
        orders.push_back(o);
    }

    for(int i=0; i<nbRobots; i++)
    {
        Robot r(warehouses.at(0).x(),warehouses.at(0).y(),poidsMax,i);
        robots.push_back(r);
    }

    updatePriority();
    occuperDrone();

    std::cout << commandes_a_faire.size() << std::endl;
    for(std::string s : commandes_a_faire)
    {
        std::cout << s << std::endl;
    }
#undef ui
#undef paire
    return 0;
}
