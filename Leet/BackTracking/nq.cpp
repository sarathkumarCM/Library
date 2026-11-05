#include<bits/stdc++.h>
using namespace std;
vector<int> row(8,0);
int a,b,lineCounter;

bool place(int r, int c){
    for(int prev=0;prev<c;prev++){
        if(row[prev]==r || (abs(c-prev) ==abs(row[prev]-r))){
            return false;
        }
    }
    return true;
}

void backTrack(int c){
    if(c==8){
        printf("%2d    %d",++lineCounter,row[0]+1);
        for(int i=1;i<8;i++){
            printf(" %d",row[i]+1);
        }
        printf("\n");
    }
    for(int r=0;r<8;r++){
        if(place(r,c)){
            row[c]=r;
            backTrack(c+1);
        }
    }
}

int main(){
    cin>>a>>b; a--;b--;
    printf("SOLN    COLM");
    printf("#    1 2 3 4 5 6 7 8\n\n");
    backTrack(0);
    return 0;
}