#include<bits/stdc++.h>

using namespace std;

class Database
{
private:

    struct  FieldData
    {
        /* data */
        string value;
        long long timestamp;
        long long expiresAt=-1;
    };

    struct Backup{
        long long timestamp;
        unordered_map<string, unordered_map<string,FieldData>> records;
        unordered_map<string, map<string,FieldData>> sortedRecordsPerFields;
    };
    vector<pair<long long, Backup>> backups;
    /* data */
    unordered_map<string, unordered_map<string,FieldData>> records; // key is like emp_id, accid, field is the field for that guy and value is value
    unordered_map<string, map<string,FieldData>> sortedRecordsPerFields;
public:
    Database();
    ~Database();

    bool isExpired(const string &key, const string &field, long long timestamp){
        if(records.find(key)==records.end() || records[key].find(field)==records[key].end()){
            return true;
        }
        if(records[key][field].expiresAt==-1){
            return false;
        }
        if(records[key][field].expiresAt<=timestamp){
            return true;
        }
        return false;
    }
    void setValue(string &key, string &field, string &value) {
        setAt(key,field,value,0);
    }

    void setAt(string &key, string &field, string &value, long long timestamp){
        setAtWithTTL(key,field,value,timestamp,-1);
    }

    void setAtWithTTL(string &key, string &field, string &value, long long timestamp, long long ttl) {
        long long expAt=(ttl==-1)?-1:timestamp+ttl;
        records[key][field]={value,timestamp,expAt};
        sortedRecordsPerFields[key][field]={value,timestamp,expAt};
    }

    optional<string> getValue(string &key, string &field){
        return getAt(key,field,0);

    }

    optional<string> getAt(string &key, string &field, long long timestamp){
        if(records.find(key)==records.end() || records[key].find(field)==records[key].end()){
            return nullopt;
        }
        if(isExpired(key,field,timestamp)){
            return nullopt;
        }
        return records[key][field].value;   

    }

    bool del(string &key,string &field){
        if(records.find(key)==records.end()||records[key].find(field)==records[key].end()){
            return false;
        }
        records[key].erase(field);
        sortedRecordsPerFields[key].erase(field);

        if(records[key].empty()){
            records.erase(key);
            sortedRecordsPerFields.erase(key);
        }
        return true;

    }

    vector<pair<string,string>> scan(string &key, long long timestamp){
        if(records.find(key)== records.end() || records[key].size()==0){
            return {};
        }
        
        vector<pair<string, string>> res;
        for(auto &it:sortedRecordsPerFields[key]){
            if(isExpired(key,it.first,timestamp))
                continue;
            res.push_back(make_pair(it.first,it.second.value));
        }
        return res;
    }

    vector<pair<string, string>> scanByPrefix( const string& key, const string& prefix, long long timestamp){
        if(records.find(key)==records.end() || records[key].size()==0){
            return {};
        }
        vector<pair<string,string>> res;
        for(auto &it:sortedRecordsPerFields[key]){
            if(it.first.starts_with(prefix)){ //it.first.compare(0, prefix.size(), prefix) == 0  or it.first.rfind(prefix,0)==0
                if(isExpired(key,it.first,timestamp))
                    continue;
                res.push_back(make_pair(it.first,it.second.value));
            }
        }
        return res;
    }

    int backup(long long timestamp){
        Backup b;
        b.timestamp=timestamp;
        for(auto &item:records){
            for(auto &field:item.second){
                if(isExpired(item.first,field.first,timestamp)) continue;
                FieldData data = field.second;
                if(data.expiresAt!=-1)
                    data.expiresAt=data.expiresAt-timestamp; //new TTL
                b.records[item.first][field.first]=data;
                b.sortedRecordsPerFields[item.first][field.first]=data;

            }
        }
        backups.push_back(make_pair(timestamp,b));
        return b.records.size();
    }

    void restore(long long timestamp, long long backupTimestamp){
        auto it= upper_bound(backups.begin(), backups.end(),backupTimestamp,[](long long ts, const pair<long long,Backup> &b){
            return ts<b.first;
        });
        if(it==backups.begin()) return;
            --it;
            Backup rest=it->second;
            for(auto &it:rest.records){
                for(auto &fields:it.second){
                    if(fields.second.expiresAt!=-1)
                        fields.second.expiresAt=timestamp+fields.second.expiresAt;
                    
                }
            }
            for(auto &it:rest.sortedRecordsPerFields){
                for(auto &fields:it.second){
                    if(fields.second.expiresAt!=-1)
                        fields.second.expiresAt=timestamp+fields.second.expiresAt;
                    
                }
            }
            records=rest.records;
            sortedRecordsPerFields=rest.sortedRecordsPerFields;

    }
};


int main(){
    cout<<"Hello"<<endl;
}