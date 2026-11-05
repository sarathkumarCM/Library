#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        bool searchMatrix(vector<vector<int>>& matrix, int target) {
            int r=matrix.size();
            vector<int> firstCol;
            for(auto &row: matrix){
                if(row.size()<1)
                    return false;
                firstCol.push_back(row[0]);
            }
            int rn=lower_bound(firstCol.begin(),firstCol.end(),target)-firstCol.begin();
            int rnu=upper_bound(firstCol.begin(),firstCol.end(),target)-firstCol.begin();
            if(rn!=rnu){
                return true; // found element in col itself
            }
            if(rn>0)
                rn--;
            int itmIdx=lower_bound(matrix[rn].begin(),matrix[rn].end(),target)-matrix[rn].begin();
            int itmIdxU=upper_bound(matrix[rn].begin(),matrix[rn].end(),target)-matrix[rn].begin();
            if(itmIdx!=itmIdxU){
                return true;
            }
            return false;
        }
    };


int main() {
    int m,n;
    cin>>m>>n;
    //vector<vector<int>>mat ={{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    //vector<vector<int>>mat ={{1,3}};
    vector<vector<int>>mat ={{1}};
    Solution s;
    cout<<s.searchMatrix(mat,0);

}
