#include <bits/stdc++.h>


int main()
{
#define LIGNE 2
#define COLONNE 1
#define TROU 0
#define CARRE 3

    std::freopen("ex.in","r",stdin);
    std::freopen("ex.out","w",stdout);
    int32_t N,M;
    std::string line;
    std::cin >> N >> M;
    std::cin.ignore();
    const int TAILLEMAX = 1000;
    std::vector<std::vector<int32_t> > vecteur(N+1,std::vector<int32_t>(TAILLEMAX,0));
    //  int32_t vecteur[N+1][TAILLEMAX];
#define PAIR std::pair<std::pair<int32_t,int32_t>,std::pair<int32_t,int32_t> >
    std::vector<std::vector<PAIR > > scores(N+1,std::vector<PAIR >(TAILLEMAX));
    //   PAIR scores[N+1][M+1];
#define  MP(A,B) std::make_pair(A,B)
    for(int32_t i=0; i<N; i++)
    {
        getline(std::cin,line);
        for(int32_t j=0 ; j < M ; j++)
        {
            if(line.at(j) == '.')
                vecteur[i][j] = 0;
            else if(line.at(j) == '#')
            {
                if(i != 0)
                {

                    vecteur[i][j]+=vecteur[i-1][j]+1;
                }
                else
                {
                    vecteur[i][j]=1;
                }
            }
        }
    }
    for(int32_t i=0; i<N; i++)
    {
        for(int32_t j=0; j<M; j++)
        {
            scores[i][j]= MP(MP(-1,TROU),MP(i,j));
        }
    }
    int32_t l;
    for(int32_t i=0; i<N; i++)
    {
        for(int32_t j=0; j<M; j++)
        {
            if(vecteur[i][j] != 0)
            {
                l=j;
                while(j+1 < M && vecteur[i][j+1] !=0)
                {
                    j++;
                }
                for(int32_t k=l; k<=j; k++)
                {
                    scores[i][k]=MP(MP(j-l+1,LIGNE),MP(i,l));
                }
            }
            else
            {
                scores[i][j]=MP(MP(0,TROU),MP(i,j));
            }
        }
    }
    for(int32_t i=0; i<M; i++)
    {
        for(int32_t j=0; j<N; j++)
        {
            if(vecteur[j][i] != 0)
            {
                l=j;
                while(j+1 < N && vecteur[j+1][i] !=0)
                {
                    j++;
                }
                int32_t res = j-l;
                int32_t compteur=0;
                bool modifie=false;
                for(int32_t k=l; k<=j; k++)
                {
                    if(res >= scores[k][i].first.first)
                        compteur++;
                }
                if(compteur >= static_cast<double>(res*3/4))
                {
                    modifie =true;
                }

                // On passe aux colonnes
                if(modifie)
                {
                    // Update les x
                    for(int32_t k=l; k<=j ; k++)
                    {
                        int32_t x = scores[k][i].second.first;
                        int32_t length= scores[k][i].first.first;
                        int32_t y = scores[k][i].second.second;
                        for(int32_t u=y; u<y+length; u++)
                        {
                            if(length-1 >= 0)
                                scores[x][u]= MP(MP(length-1,LIGNE),MP(x,y));
                            else
                                scores[x][u]= MP(MP(0,TROU),MP(x,y));

                        }
                    }

                    // Update les y
                    for(int32_t k=l; k<=j; k++)
                    {
                        scores[k][i]= MP(MP(j-l+1,COLONNE),MP(l,i));
                    }
                }
            }
        }
    }

    std::vector<std::string> sol;
    std::vector<std::vector<bool> > visited(N,std::vector<bool>(M,false));

    for(int32_t i=0; i<N; i++)
    {
        for(int32_t j=0; j<M; j++)
        {
            if(visited[i][j] == false )
            {
                int32_t l = scores[i][j].first.first;
                int32_t x = scores[i][j].second.first;
                int32_t y = scores[i][j].second.second;

                switch(scores[i][j].first.second)
                {
                case(1):
                {
                    auto s="PAINT_LINE "+ std::to_string(x) + " " + std::to_string(y) +" "+ std::to_string(x+l-1) + " " + std::to_string(y) + "\n";
                    sol.push_back(s);
                    for(int32_t k=x; k<=x+l; k++)
                    {
                        visited[k][y]=true;
                    }
                    break;
                }
                case(2) :
                {
                    auto s="PAINT_LINE "+ std::to_string(x) + " " + std::to_string(y) +" "+ std::to_string(x) + " " + std::to_string(y+l-1) + "\n";
                    sol.push_back(s);
                    for(int32_t k=y; k<=y+l; k++)
                    {
                        visited[x][k]=true;
                    }
                    break;
                }
                }
            }
        }
    }
    std::cout << sol.size() << std::endl;
    std::for_each(sol.begin(),sol.end(),[](auto & x)
    {
        std::cout << x;
    });
#undef TROU
#undef COLONNE
#undef CARRE
#undef LIGNE
    return 0;
}

