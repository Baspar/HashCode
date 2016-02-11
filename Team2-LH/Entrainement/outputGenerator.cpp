#include <bits/stdc++.h>


int main()
{
    int N,M;
    std::cin >> N >> M;
    std::freopen("logo.out","r",stdin);
    std::freopen("logo.in1","w",stdout);
    std::string line;
    std::vector<std::vector<char> > vecteur(N+1,std::vector<char>(TAILLEMAX,'.'));
    int a,b,c,d;
    while(getline(std::cin,line))
    {
        sscanf(line,"%d %d %d %d\n",&a,&b,&c,&d);
        if(a == c )
        {
            for(int k=b; k<=d; k++)
                vecteur[i][k]='#';
        }
        else if( b == d )
        {
            for(int k=a; k<=c; k++)
                vecteur[i][k]='#';
        }
    }
    std::for_each(vecteur.begin(),vecteur.end(),[](auto&x)
    {
        for_each(x.begin(),x.end(),[](auto&x)
        {
            std::cout << x;
        });
        std::cout << std::endl;
    });
}
