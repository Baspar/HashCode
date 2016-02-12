#include <bits/stdc++.h>


int main()
{
    int N,M;
    std::cin >> N >> M;
    std::freopen("learn_and_teach.out","r",stdin);
    std::freopen("learn_and_teach.in1","w",stdout);
    std::string line;
    char buff[30];
    std::vector<std::vector<char> > vecteur(N+2,std::vector<char>(M+2,'.'));
    int a,b,c,d;
    getline(std::cin, line);
    while(getline(std::cin,line))
    {
       // sscanf(line.c_str(),"%s %d %d %d %d\n",buff,&a,&b,&c,&d);
        std::cout << a << b<< c << d<<std::endl;
        if(a == c )
        {
            for(int k=b; k<=d; k++)
                vecteur[a][k]='#';
        }
        else if( b == d )
        {
            for(int k=a; k<=c; k++)
                vecteur[k][b]='#';
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
