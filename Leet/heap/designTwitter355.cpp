#include <bits/stdc++.h>
using namespace std;

struct Tweet{
    int uid;
    int tid;
    int tcnum;
    bool operator <(const Tweet &other) const {
        return tcnum<other.tcnum;
    }
    Tweet() : uid(0), tid(0){}
    Tweet(int uuid,int utid, int utcnum): uid(uuid),tid(utid),tcnum(utcnum){}
};
struct User{
    int id;
    priority_queue<Tweet> pq;
    list<int> followers;
};


class Twitter2 {
public:
    Twitter2() {
        tc=0;
    }
    
    void postTweet(int userId, int tweetId) {
        //add to mine and followers
        ++tc;
        Tweet t(userId,tweetId,tc);
        allTweets.push(t);
        cout<<"Top "<<allTweets.top().tid<<endl;
    }
    
    vector<int> getNewsFeed(int userId) {
        //get top 10
        int i=0;
        vector<int> ans;
        priority_queue<Tweet> cp(allTweets);
        while((!cp.empty()) &&(i<MAX_TWEET)){
            Tweet t=cp.top();
            if(userId==t.uid){
                ans.push_back(t.tid);
                i++;
            }
            else if(followd_user.find(userId)!=followd_user.end()){
                if(followd_user[userId][t.uid]==true){
                    ans.push_back(t.tid);
                    i++;
                }
            }
            cp.pop();
        }
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        //add user to friend
        //followd_user[followerId]=[followeeId=; //follower follows followee;
        if(followd_user.find(followerId)==followd_user.end()){
            followd_user[followerId]=vector<bool>(501,false);
        }
        followd_user[followerId][followeeId]=true;
        
    }
    
    void unfollow(int followerId, int followeeId) {
        //remove all tweets of friend from my feed;
        if(followd_user.find(followerId)!=followd_user.end()){
            followd_user[followerId][followeeId]=false;
        }
        
    }

    int MAX_TWEET=10;
    unordered_map<int,vector<bool>> followd_user;
    priority_queue<Tweet> allTweets;
    int tc=0;
};

struct Tweet{
    int uid;
    int tid;
    int tcnum;
    bool operator <(const Tweet &other) const {
        return tcnum<other.tcnum;
    }
    Tweet() : uid(0), tid(0){}
    Tweet(int uuid,int utid, int utcnum): uid(uuid),tid(utid),tcnum(utcnum){}
};
struct User{
    int id;
    priority_queue<Tweet> pq;
    list<int> followers;
};

class Twitter {
public:
    Twitter() {
        tc=0;
    }
    
    void postTweet(int userId, int tweetId) {
        //add to mine and followers
        ++tc;
        Tweet t(userId,tweetId,tc);
        all_users[userId].pq.push(t);
        cout<<"there are "<<followd_user[userId].size()<<" followers for "<<userId<<endl;
        for(auto &it:followd_user){
            for(auto &it2: it.second){
                cout<<" meh "<<it2<<" "<<it.first<<endl;
                if(it2==userId){
                    all_users[it.first].pq.push(t);
                    cout<<" pushing tweet from "<<userId<< " to "<<it.first<<endl;
                }
            }
        }
    }
    
    vector<int> getNewsFeed(int userId) {
        //get top 10
        int i=0;
        vector<int> ans;
        priority_queue<Tweet> cp=all_users[userId].pq;
         while((!cp.empty()) &&(i<MAX_TWEET)){
            Tweet t=cp.top();
            ans.push_back(t.tid);
            i++;
            cp.pop();
        }
        
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        //add user to friend
        //followd_user[followerId]=[followeeId=; //follower follows followee;
        if(find(followd_user[followerId].begin(),followd_user[followerId].end(),followeeId)!=followd_user[followerId].end()){
            return;
        }
        followd_user[followerId].push_back(followeeId);
        cout<<"Followed "<<followerId<<" with size "<<followd_user[followerId].size()<<endl;
        priority_queue<Tweet> temp=all_users[followeeId].pq;
        int k=0;//only 10
        //cout<<followerId<<" follows1 "<<followeeId<<endl;
        while((!temp.empty()) && (k<10)){
            Tweet t=temp.top();
            //cout<<followerId<<" follows "<<followeeId<<endl;
            if(t.uid==followeeId){
                k++;
                all_users[followerId].pq.push(t);
            }
            temp.pop();
        }
        
    }
    
    void unfollow(int followerId, int followeeId) {
        //remove all tweets of friend from my feed;
        if(followd_user.find(followerId)!=followd_user.end()){
            auto& vec = followd_user[followerId];
            vec.erase(
            remove(vec.begin(), vec.end(),followeeId),
            vec.end()
            );
            User &u=all_users[followerId];
            priority_queue<Tweet> pqt;
            while(!u.pq.empty()){
                if(u.pq.top().uid!=followeeId){
                    pqt.push(u.pq.top());
                }
                u.pq.pop();
            }
            u.pq=pqt;

        }
        
    }

    int MAX_TWEET=10;
    unordered_map<int,vector<int>> followd_user;
    unordered_map<int,User> all_users;
    int tc=0;
}; // better 



//others
class Twitter {
public:
    struct Tweet {
        int tweetId;
        int timestamp;
        Tweet(int tweetId, int timestamp): tweetId(tweetId), timestamp(timestamp) {}
    };

    int time;
    unordered_map<int, unordered_set<int>> followMap;
    unordered_map<int, vector<pair<int, int>>> tweetMap;

    Twitter() {
        time = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweetMap[userId].push_back({time++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<pair<int, int>> feed = tweetMap[userId];
        for (int followeeId : followMap[userId]) {
            feed.insert(feed.end(), tweetMap[followeeId].begin(),
                                    tweetMap[followeeId].end());
        }
        sort(feed.begin(), feed.end(), [](auto &a, auto &b) {
            return a.first > b.first;
        });
        vector<int> res;
        for (int i = 0; i < min(10, (int)feed.size()); ++i) {
            res.push_back(feed[i].second);
        }
        return res;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            followMap[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        followMap[followerId].erase(followeeId);
    }
};


//-- best
class Twitter {
public:
    unordered_map<int,unordered_map<int,bool>> follower; 
    unordered_map<int,vector<pair<int,int>>> tweets; // userId -> time, tweetId
    int time;
    Twitter() {
        time=0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time, tweetId});
        time++;
    }
    
    vector<int> getNewsFeed(int userId) {
        priority_queue<pair<int,int>> pq; //time, tweetId

        for(int i=0;i<tweets[userId].size();i++)
        {
            pq.push(tweets[userId][i]);
        }

        for(auto x: follower[userId])
        {
            if(x.second==false)
                continue;
            
            for(int i=0;i<tweets[x.first].size();i++)
            {
                pq.push(tweets[x.first][i]);
            }
        }

        vector<int> op;
        while(pq.size()!=0 && op.size()<10)
        {
            op.push_back(pq.top().second);
            pq.pop();
        }

        return op;
    }
    
    void follow(int followerId, int followeeId) {
        follower[followerId][followeeId]=true;
    }
    
    void unfollow(int followerId, int followeeId) {
        follower[followerId][followeeId]=false;
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

 int main(){

 }