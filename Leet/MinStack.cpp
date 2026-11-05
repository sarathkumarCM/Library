#include "bits/stdc++.h"
using namespace std;

class MinStack {
private: 
    stack<int> st;
    stack<int> prefMin;
    int mini;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        st.push(val);
        if(prefMin.size()==0){
            prefMin.push(val);
        }else{
            int tmin=prefMin.top();
            prefMin.push(min(val,tmin));
        }
    }
    
    void pop() {
        st.pop();
        prefMin.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return prefMin.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

//Best??-- a normal vector with pair pair can do

class MinStack {
public:
    MinStack() : stack() {}

    void push(int val) {
        int currMin = stack.size() == 0
                          ? val
                          : min(val, stack.at(stack.size() - 1).second);
        stack.push_back({val, currMin});
    }

    void pop() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }

    int top() {
        if (!stack.empty()) {
            return stack.at(stack.size() - 1).first;
        }
        return -1;
    }

    int getMin() { return stack.at(stack.size() - 1).second; }

private:
    vector<pair<int, int>> stack;
};