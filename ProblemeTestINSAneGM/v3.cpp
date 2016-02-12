#include <iostream>
#include <vector>

using namespace std;
vector<vector <char> > image;
vector<vector <char> > image2;
int L, C;

void ERASE_CELL(int x, int y){
    image2[x][y]='.';
    cout << "ERASE_CELL "<< x <<" " << y << endl;
}

void PAINT_SQUARE(int x, int y, int S){
    //a effacer
    vector<pair<int ,int> > efface;
    for(int i=x-S; i<=x+S; i++)
        for(int j=y-S; j<=y+S; j++){
            image2[i][j]='#';
            if(image[i][j]=='.')
                efface.push_back(make_pair(i,j));
        }    
    cout << "PAINT_SQUARE " << x << " " << y << " "<< S << endl;
    for(int i=0; i<efface.size();i++)
        ERASE_CELL(efface[i].first, efface[i].second);
}

void PAINT_ROW(int x, int y, int l){
    for(int i=y;i<=y+l;i++)
        image2[x][i]='#';
    cout << "PAINT_LINE " << x << " " << y << " "<< x<< " " << y+l << endl;
}


void PAINT_COLUMN(int x, int y, int l){
    for(int i=x;i<=x+l;i++)
        image2[i][y]='#';
    cout << "PAINT_LINE " << x << " " << y << " "<< x+l << " " << y << endl;
}


float TEST_SQUARE(int x, int y, int S){
    //cout << "test square" << S << endl;
    float out=0;
    //Nombre de case qu'on efface
    int compteur=0;
    if( (x-S>-1) && (x+S<L) && (y-S>-1) && (y+S<C) ){
        for(int i=x-S; i<=x+S; i++)
            for(int j=y-S; j<=y+S; j++){
                if(image[i][j]=='#'){
                    if(image2[i][j]!='#')
                        out++;
                } 
                else {//si la case est un point on la compte comme a effacer
                    compteur++;
                }    
        }
        //on limite a S le nombre d'erreur
        if(compteur<(S+1))
            return out;
        else
            return -1;
    }
    else
        return -1;
}


float TEST_ROW(int x, int y, int l){
    float out=0;
    if(y+l<C && (y==0 || image[x][y-1]=='.') ){
        for(int i=y;i<=y+l;i++){
            if(image[x][i]=='#'){
                if(image2[x][i]!='#')
                    out++;
            } else
                return -1;
        }
        return out;
    }
    else
        return -1;
}


float TEST_COLUMN(int x, int y, int l){
    float out=0;
    if(x+l<L){
        for(int i=x;i<=x+l;i++){
            if(image[i][y]=='#'){
                if(image2[i][y]!='#')
                    out++;
            } else
                return -1;
        }
        return out;
    }
    else
        return -1;
}


bool estFini(){
    for(int i=0; i<L; i++){
        for(int j=0; j<C; j++){
            if(  image[i][j]!=image2[i][j]){
                return false;
            }    
        }
    }

    return true;
}




int main(){
    cin >> L >> C;
    image.resize(L);
    image2.resize(L);
    for(int i=0;i<L;i++){
        image[i].resize(C);
        image2[i].resize(C);
    }
    for(int i=0; i<L; i++){
        string line;
        cin >> line;
        for(int j=0; j<C; j++){
            char c=line[j];
            image[i][j]=c;
            image2[i][j]='.';
        }
    }

    while(!estFini() ){
        int x, y, p;
        float max=0;
        char type;
        for(int i=0; i<L; i++){
            for(int j=0; j<C; j++){

                int s;

                for(s=0; TEST_SQUARE(i, j, s)!=-1;s++);
                if(TEST_SQUARE(i, j, s-1)>max){
                    max=TEST_SQUARE(i, j, s-1);
                    type='S';
                    x=i;
                    y=j;
                    p=s-1;
                }


                for(s=1; TEST_COLUMN(i, j, s)!=-1;s++);
                if(TEST_COLUMN(i, j, s-1)>max){
                    max=TEST_COLUMN(i, j, s-1);
                    type='C';
                    x=i;
                    y=j;
                    p=s-1;
                }

                for(s=1; TEST_ROW(i, j, s)!=-1;s++);
                if(TEST_ROW(i, j, s-1)>max){
                    max=TEST_ROW(i, j, s-1);
                    type='R';
                    x=i;
                    y=j;
                    p=s-1;
                }


            }
        }

        switch(type){
            case 'C': PAINT_COLUMN(x, y, p);
                      break;
            case 'R': PAINT_ROW(x, y, p);
                      break;
            case 'S': PAINT_SQUARE(x, y, p);
                      break;
        }
        
    }
}
