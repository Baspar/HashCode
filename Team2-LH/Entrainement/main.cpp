#include <bits/stdc++.h>



int main()
{
#define LIGNE 2
#define COLONNE 1
#define TROU 0
#define CARRE 3

    std::freopen("right_angle.in","r",stdin);
    std::freopen("right_angle.out","w",stdout);
    uint32_t N,M;
    std::string line;
    std::cin >> N >> M;
    std::cin.ignore();
    uint32_t vecteur[N+1][M+1];
    std::pair<std::pair<uint32_t,uint32_t>,std::pair<uint32_t,uint32_t> > scores[N+1][M+1];

    memset(vecteur,0,sizeof(vecteur));

    for(uint32_t i=0; i<N; i++)
    {
        getline(std::cin,line);
        for(uint32_t j=0 ; j<line.size() ; j++)
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
    uint32_t score_ligne[N+1];
    uint32_t score_colonne[M+1];
    uint32_t l,p,r,q=0;
#define  MP(A,B) std::make_pair(A,B)
    for(uint32_t i=0; i<N; i++)
    {
        uint32_t j=0;
        while(j < M)
        {
            if(vecteur[i][j] != 0)
            {
                l=j;
                while(j < M && vecteur[i][j] !=0)
                {
                    j++;
                }
                q++;
                for(uint32_t k=l; k<j; k++)
                {
                    scores[i][k]=MP(MP(j-l+1,LIGNE),MP(i,l));
                }
            }
            else
            {
                scores[i][j]=MP(MP(0,TROU),MP(i,j));
            }
            j++;
        }
    }
    q=0;
    for(uint32_t i=0; i<M; i++)
    {
        uint32_t j=0;
        while(j < N)
        {
            if(vecteur[j][i] != 0)
            {
                l=j;
                while(j < N && vecteur[j][i] !=0)
                {
                    j++;
                }
                uint32_t res = j-l+1;
                uint32_t compteur=0;
                bool modifie=false;
                for(uint32_t k=l; k<=j; k++)
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
                    for(uint32_t k=l; k<=j ; k++)
                    {
                        uint32_t x = scores[k][i].second.second;
                        uint32_t length= scores[k][i].first.first;
                        uint32_t y = scores[k][i].second.first;
                        for(uint32_t u=x; u<x+length; u++)
                        {
                            scores[k][u]= MP(MP(length-1,LIGNE),MP(y,x));
                        }
                    }

                    // Update les y
                    for(uint32_t k=l; k<=j; k++)
                    {
                        scores[k][i]= MP(MP(j-l+1,COLONNE),MP(l,i));
                    }
                }
                //q++;
                //std::cout << "PAINT_LINE "<< i << " " << l << " "<< i << " "<< j << std::endl;
            }
            j++;
        }
    }
    //std::cout << std::endl << q<< std::endl;

    std::vector<std::string> sol;
    bool visited[N+1][M+1];
    memset(visited,false,sizeof(visited));
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(visited[i][j] == false && scores[i][j].first.first > 0)
            {
                int l = scores[i][j].first.first;
                switch(scores[i][j].first.second)
                {
                case(1):
                {
                    auto s="PAINT_LINE "+ std::to_string(i) + " " + std::to_string(j) +" "+ std::to_string(i+l) + " " + std::to_string(j) + "\n";
                    sol.push_back(s);
                    for(int k=i; k<i+l; k++)
                    {
                        visited[k][j]=true;
                    }
                    break;
                }
                case(2) :
                {
                    auto s="PAINT_LINE "+ std::to_string(i) + " " + std::to_string(j) +" "+ std::to_string(i) + " " + std::to_string(j+l) + "\n";
                    sol.push_back(s);
                    for(int k=j; k<j+l; k++)
                    {
                        visited[i][k]=true;
                    }
                    break;
                }
                }
            }
        }
    }
    std::for_each(sol.begin(),sol.end(),[](auto & x)
    {
        std::cout << x;
    });

    return 0;
}

