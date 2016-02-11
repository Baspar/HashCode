#include <iostream>

using namespace std;

int main(){
    int L, C;
    cin >> L >> C;
    for(int i=0; i<L; i++){
        string line;
        cin >> line;
        for(int j=0; j<C; j++){
            char c=line[j];
            if(c=='#')
                cout << "PAINT_SQUARE " << i << " " << j << " " << 0 << endl;
        }
    }
}
