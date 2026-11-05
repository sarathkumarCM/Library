#include<bits/stdc++.h>

using namespace std;
class TimeMap {
    public:
    unordered_map<string,vector<pair<int,string>>> aData;
        TimeMap() {
            
        }
        
        void set(string key, string value, int timestamp) {
            aData[key].emplace_back(timestamp,value);
        }
        
        string get(string key, int timestamp) {
            vector<pair<int,string>> &item=aData[key];
                if(item.size()==0){
                    return "";
                }
                int beg=0,end=item.size()-1;
                if(timestamp<item[0].first){
                    return "";
                }
                while(beg<=end){
                    int mid=beg+(end-beg)/2;
                    if(item[mid].first==timestamp){
                        return item[mid].second;
                    }
                    if(item[mid].first<timestamp){
                        beg=mid+1;
                    }else{
                        end=mid-1;
                    }
                }
                if(beg!=0)
                    beg--;
                return item[beg].second;
        }
        // use of custom upper bound
        string get(string key, int timestamp, int a) {
            auto it = upper_bound(aData[key].begin(), end(aData[key]), pair<int, string>(timestamp, ""), [](
                const pair<int, string>& a, const pair<int, string>& b) { return a.first < b.first; })-aData[key].begin();
                    if(it==0)return "";
                    return aData[key][it-1].second;
            }
    };
    

    class TimeMap {
        public:
            unordered_map<string,vector<pair<int,string>>> aData;
            TimeMap() {
                
            }
            
            void set(string key, string value, int timestamp) {
                aData[key].emplace_back(timestamp,value);
            }
            
            string get(string key, int timestamp) {
                vector<pair<int,string>> item=aData[key];
                    // if(item.size()==0){
                    //     return "";
                    // }
                    int beg=0,end=item.size()-1;
                    string val="";
                    // if(timestamp<item[0].first){
                    //     return "";
                    // }
                    while(beg<=end){
                        int mid=beg+(end-beg)/2;
                        if(item[mid].first<=timestamp){
                            val=item[mid].second;
                            beg=mid+1;
                        }else{
                            end=mid-1;
                        }
                    }
                    return val;
            }
        };
        
        /**
         * Your TimeMap object will be instantiated and called as such:
         * TimeMap* obj = new TimeMap();
         * obj->set(key,value,timestamp);
         * string param_2 = obj->get(key,timestamp);
         */

int main(){


}