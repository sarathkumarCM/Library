#include<bits/stdc++.h>

using namespace std;

class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) {
            stack<pair<int,int>> pm,nm;
            pm.push(make_pair(0,heights[0]));
            int sz=heights.size();
            vector<int> prm(sz,-1),nxm(sz,sz);
            for(int i=1;i<sz;i++){
                if(pm.empty()){
                    pm.push(make_pair(i,heights[i]));
                    continue;
                }
                while(!pm.empty() && pm.top().second>heights[i]){
                    //prm[pm.top().first]=heights[i];
                    pm.pop();
                }
                if(!pm.empty()){
                    prm[i]=pm.top().first;
                }

                pm.push(make_pair(i,heights[i]));
            }

            for(int i=0;i<sz;i++){
                // if(nm.empty()){
                //     nm.push(make_pair(i,heights[i]));
                //     continue;
                // }
                while(!nm.empty() && nm.top().second>heights[i]){
                    nxm[nm.top().first]=i;
                    nm.pop();
                }
                // if(nm.empty()){
                //     nxm[i]=-1;
                // }else{
                //     nxm[i]=nm.top().first;
                // }

                nm.push(make_pair(i,heights[i]));
            }

            cerr<<"Previous min"<<endl;
            for(auto &i: prm){
                cerr<<i <<" ";
            }
            cerr<<endl;
            cerr<<"Next min"<<endl;
            for(auto &i: nxm){
                cerr<<i <<" ";
            }
            cerr<<endl;

            int maxArea = 0;

            // Calculate the area for each Histogram bar
            for (int i = 0; i < sz; ++i) {
                int width = nxm[i] - prm[i] - 1; 
                int area = heights[i] * width;          
                maxArea = max(maxArea, area);        
            }
            
            return maxArea;


            // do op
            int reslt=-1;
            for(int i=0;i<sz;i++){
                if(heights[i]>reslt){
                    reslt=heights[i];
                }
                int minLeft=-1;
                if(prm[i]==-1){
                    //calc till left
                    int tt=heights[i]*(i+1);
                    if(tt>reslt){
                        reslt=tt;
                    }
                    minLeft=i;
                }else{
                    minLeft=prm[i];
                    int tt=min(heights[i],heights[minLeft])*((i-minLeft+1)<=0?1:(i-minLeft+1));
                    cerr<<"wew "<<heights[i]<<" minleft "<<heights[minLeft]<<endl;
                    if(tt>reslt){
                        reslt=tt;
                    }
                }
                
                int minRight=-1;
                if(nxm[i]==-1){
                    int tt=heights[i]*(sz-i);
                    if(tt>reslt){
                        reslt=tt;
                    }
                    minRight=i;
                }else{
                    minRight=nxm[i];
                    int tt=min(heights[i],heights[minRight])*((i-minRight+1)<=0?1:(i-minRight+1));
                    if(tt>reslt){
                        reslt=tt;
                    }
                }

                cerr<<"MinRight: "<<minRight<<" , MinLeft: "<<minLeft<<endl;
                if(minLeft==minRight){
                    int tr=heights[i]*sz;
                    if(tr>reslt){
                        reslt=tr;
                    }
                }
        
                int diff=minRight==minLeft?1:(minRight-minLeft+1);
                cerr<<"Diff : "<<diff<<endl;
                int elem=min(heights[minRight],heights[minLeft]);
                cerr<<"Heights[minRight]: "<<heights[minRight]<<" , heights[minLeft]: "<<heights[minLeft]<<endl;
                cerr<<"Temp res: "<<diff*elem<<endl;
                cerr<<endl<<endl;
                int tres=diff*elem;
                if(tres>reslt)
                    reslt=tres;

                if(minLeft==i){
                    int elem=min(heights[minRight],heights[0]);
                    int tt= elem* (minRight+1);
                    if(tt>reslt){
                        reslt=tt;
                    }

                }
                if(minRight==i){
                    int elem=min(heights[minLeft],heights[sz-1]);
                    int tt= elem* (sz-minLeft);
                    if(tt>reslt){
                        reslt=tt;
                    } 
                }
            }

            return reslt;
        }
    };

int main(){
    Solution s;
    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it: inp){
        cin>>it;
    }
    cout<<s.largestRectangleArea(inp);
    return 0;
}