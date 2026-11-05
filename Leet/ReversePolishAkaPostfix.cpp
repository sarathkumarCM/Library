
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> operands;
        for(auto &it: tokens){
            if(it==" "){
                continue;
            }
            cerr<<"it "<<it<<endl;
            if(it=="+"|| it=="-" || it =="/" || it=="*"){
                //pop 2 elemements
                int val1=operands.top();
                operands.pop();
                int val2= operands.top();
                operands.pop();
                int result=0;
                if(it=="/"){
                    result=val2/val1;
                }else if(it=="*"){
                    result=val1*val2;
                }else if(it=="+"){
                    result=val1+val2;
                }else if(it=="-"){
                    result=val2-val1;
                }

                //push result back
                operands.push(result);
            }else{
                operands.push(stoi(it));
            }
        }
        return operands.top();
    }
};

//best

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    stack<long> stack;
    const unordered_map<string, function<long(long, long)>> op{
        {"+", std::plus<long>()},
        {"-", std::minus<long>()},
        {"*", std::multiplies<long>()},
        {"/", std::divides<long>()}};

    for (const string& token : tokens)
      if (op.contains(token)) {
        const long b = stack.top();
        stack.pop();
        const long a = stack.top();
        stack.pop();
        stack.push(op.at(token)(a, b));
      } else {
        stack.push(stoi(token));
      }

    return stack.top();
  }
};

int main(){

    int n;
    cin>>n;
    vector<string> tokens(n);
    Solution s;
    int res=s.evalRPN(tokens);
    cout<<res<<endl;
    return 0;
}