#include<bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
    MedianFinder() {
        maxh=priority_queue<int>();
        minh=priority_queue<int,vector<int>,greater<int>>();
    }
    
    void addNum(int num) {
        if(maxh.empty() || num<=maxh.top()){
            maxh.push(num);
        }else{
            minh.push(num);
        }
        while((int)minh.size()-(int)maxh.size()>1){
            int tp=minh.top();
            minh.pop();
            maxh.push(tp);
        }
        while((int)maxh.size()-(int)minh.size()>1){
            int tp=maxh.top();
            maxh.pop();
            minh.push(tp);
        }
        
    }
    
    double findMedian() {   
        if(minh.size()>maxh.size()){
            return minh.top();
        }else if(maxh.size()>minh.size()){
            return maxh.top();
        }else{
            return ((double)(minh.top()*1.0+maxh.top())/2); 
        }
    }
    priority_queue<int> maxh;
    priority_queue<int,vector<int>,greater<int>> minh;
};


//Best

class MedianFinder {
private:
    priority_queue<int> left;
    priority_queue<int,vector<int>,greater<int>> right;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
       if (left.empty() || num <= left.top())
    left.push(num);
else
    right.push(num);

if (left.size() > right.size() + 1) {
    right.push(left.top());
    left.pop();
}
else if (right.size() > left.size()) {
    left.push(right.top());
    right.pop();
}

    }
    
    double findMedian() {
        if (left.size()==right.size()){
            return (left.top()+right.top())/2.0;
        }
        return left.top();
    }
};

int main(){

}