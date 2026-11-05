#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int sz=temperatures.size();
        stack<int> mStack;
        vector<int> indices(sz,0);
        for(int i=0;i<sz;i++){
            cerr<<"Current item "<<temperatures[i]<<endl;
            if(!mStack.empty() && mStack.top()<temperatures[i]){
                vector<int> temp;
                cerr<<"Popped : "<<temp.size()<<" Items: ";
                while(!mStack.empty()&& mStack.top()<temperatures[i]){
                    cerr<<mStack.top()<<" ";
                    temp.push_back(mStack.top());
                    mStack.pop();
                }
                cerr<<endl;
                mStack.push(temperatures[i]);
                int cnt=1;
                cerr<<"Pushed :";
                //for(int j=0;j<temp.size();j++){
                for(int j=temp.size()-1;j>=0;j--){
                    cerr<<temp[j]<<" ";
                    mStack.push(temp[j]);
                    if(indices[j]==0){
                        cerr<<" Im making the current item of "<<j<<" as cnt "<<cnt<<endl;
                        indices[j]=cnt;
                    }
                    cnt++;
                }
                cerr<<endl;
            }else{
                mStack.push(temperatures[i]);
                indices[i]=0;
            }
        }
        return indices;
    }

    vector<int> dailyTemperatures(vector<int>& temperatures,int a) {
        int sz=temperatures.size();
        stack<pair<int,int>> mStack;
        vector<int> indices(sz,0);
        for(int i=0;i<sz;i++){
            cerr<<"Current item "<<temperatures[i]<<endl;
            if(!mStack.empty() && mStack.top().first<temperatures[i]){
                cerr<<"This item needs a correction Pop and push"<<temperatures[i]<<endl;
                vector<pair<int,int>> temp;
                while(!mStack.empty()&& mStack.top().first<temperatures[i]){
                    //cerr<<mStack.top()<<" ";
                    temp.push_back(mStack.top());
                    mStack.pop();
                }
                cerr<<"Temp stack has :"<<temp.size()<<endl;
                mStack.push(make_pair(temperatures[i],i)); //add the current item;
                //pop stuff and set index
                for(int j=temp.size()-1;j>=0;j--){
                    mStack.push(temp[j]);
                    if(indices[j]==0){
                        cerr<<" Im making the current item of "<<j<<" as cnt "<<i-temp[j].second<<endl;
                        cerr<<"\t\t i is: "<<i<<", j is :"<<j<<endl;
                        indices[i]=i-temp[j].second;
                    }
                }
            }
            else{
                mStack.push(make_pair(temperatures[i],i));
                indices[i]=0;
            }
        }
        return indices;
    }
};

int main(){

    int n;
    cin>>n;
    vector<int> inp(n);
    for(auto &it:inp){
        cin>>it;
    }
    Solution s;
    auto a=s.dailyTemperatures(inp,1);
    for(auto &it: a){
        cout<<it<<" ";
    }
    cout<<endl;
    return 0;
}

//

//73 74 75 71 69 72 76 73

