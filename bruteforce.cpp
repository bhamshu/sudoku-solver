//This is totally independent of the rest of the project

#include<bits/stdc++.h>
using namespace std;
#define watchv(v) cout << (#v) << " is: ["; for(auto itr = v.begin(); itr!=v.end();itr++){cout<<*itr<<", ";}cout<<(v.empty()?"":"\b\b")<<"] \n"
//the following two are for vector of vectors and like.
#define watchvunnamed(v) cout << "["; for(auto itt = v.begin(); itt!=v.end();itt++){cout<<*itt<<", ";} cout<<(v.empty()?"":"\b\b")<<"]"
#define watchvv(v) cout << (#v) << " is: ["; for(auto itr = v.begin(); itr!=v.end();itr++){watchvunnamed((*itr)); cout<<", ";} cout<<(v.empty()?"":"\b\b")<<"] \n"

/***************************************************************************************************************************/
/***************************************************************************************************************************/

#define f(x) x<=2?1:(x<=5?4:7)

bool allowed(int I, int J, char r, vector<vector<char>> &ret){
    for(int i = 0; i<9; i++){
        if(i!=I && ret[i][J]==r) return false;
    }
    for(int j = 0; j<9; j++){
        if(j!=J && ret[I][j]==r) return false;
    }
    int IR = f(I), JR=f(J);
    for(int i = -1; i<=1; i++){
        for(int j = -1; j<=1; j++){
            if(IR+i==I && JR+j==J) continue;
            if(ret[IR+i][JR+j]==r) return false;
        }
    }
    return true;
}

bool solve(vector<vector<char>> &ret){
    for(int I=0; I<9; I++){ vector<char> &i = ret[I];
        for(int J=0; J<9; J++){ char j = i[J];
            if(j=='.'){
                bool none = true;
                for(char r = '1'; r<='9'; r++){
                    if(allowed(I, J, r, ret)){
                        none = false;
                        ret[I][J] = r;
                        if(solve(ret))return true;
                        else{ret[I][J]='.'; none = true;}
                    }
                }
                if(none) return false;
            }
            if(I==8 && J==8)return true;
        }
    }
}
void solveSudoku(vector<vector<char> > &A) {
    solve(A);
}

int main(){
    vector<vector<char> > v={{'5', '3', '4', '6', '7', '8', '9', '1', '2'}, {'6', '7', '2', '1', '9', '5', '3', '4', '8'}, {'1', '9', '8', '3', '4', '2', '5', '6', '7'}, {'8', '5', '9', '7', '6', '1', '4', '2', '3'}, {'4', '2', '6', '8', '5', '3', '7', '9', '1'}, {'7', '1', '3', '9', '2', '4', '8', '5', '6'}, {'9', '6', '1', '5', '3', '7', '2', '8', '4'}, {'2', '8', '7', '4', '1', '9', '6', '3', '5'}, {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};
    solveSudoku(v);
    watchvv(v);
    return 0;
}
