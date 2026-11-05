#include<bits/stdc++.h>

using namespace std;

 struct DListNode {
    int val;
    DListNode *next;
    DListNode  *prev;
    DListNode() : val(0), next(nullptr),prev(nullptr) {}
    DListNode(int x) : val(x), next(nullptr),prev(nullptr) {}
    DListNode(int x, DListNode *next) : val(x), next(next) {}
    DListNode(int x, DListNode *prev, DListNode *next) : val(x), prev(prev), next(next) {}
 };

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class LRUCache {
public:
    LRUCache(int capacity) {
        capa=capacity;
        head=nullptr;
        tail=nullptr;
        
    }
    
    int get(int key) {
        if(hash.find(key)!=hash.end()){
            DListNode *tmp=hash[key].second;
            if(tmp==tail){
                return hash[key].first;
            }
            if(tmp->prev!=nullptr)
                tmp->prev->next=tmp->next;
            if(tmp->next!=nullptr)
                tmp->next->prev=tmp->prev;
            if(tmp==head && head->next!=nullptr){
                head=head->next;
            }
            if(capa!=1){
                tail->next=tmp;
                tmp->prev=tail;
                tmp->next=nullptr;
                tail=tail->next;
            }

            // DListNode *thead=head;
            // cerr<<"Post Get: "<<key<<" :";
            // while(thead!=nullptr){
            //     cerr<<" "<<hash[thead->val].first<<"("<<thead->val<<")";
            //     thead=thead->next;
            // }
            // cerr<<endl;
            // cerr<<"Tail key "<<tail->val<<", HEad key"<<head->val<<endl;
            return hash[key].first;
        }
        else{    
            return -1;
        }
        
    }
    
    void put(int key, int value) {
        cerr<<value<<"("<<key<<")"<<endl;
        DListNode *newNode=new DListNode(key);
        if(cSize<capa){
            if(head==nullptr){
                head=newNode;
                tail=newNode;
                hash[key]=make_pair(value,newNode);
                // cerr<<"had nothing "<<hash[key].first<<endl;
                cSize++;
            }else{
                if(hash.find(key)!= hash.end()){
                    ///move to back
                    DListNode *tmp=hash[key].second;
                    // cerr<<"wowowiee key "<<tmp->val<<"value" <<hash[key].first<<endl;
                    if(tmp==tail){
                        // cerr<<"howwwww2"<<endl;
                        hash[tail->val].first=value;
                        return;
                    }
                    if(tmp==head){
                        // cerr<<"should shift"<<endl;
                        head=head->next;
                    }
                    if(tmp->prev!=nullptr){
                        // cerr<<"before "<<tmp->prev->val<<endl;
                        tmp->prev->next=tmp->next;
                    }
                    if(tmp->next!=nullptr)
                        tmp->next->prev=tmp->prev;
                    tail->next=tmp;
                    tmp->prev=tail;
                    tail=tail->next;
                    tmp->next=nullptr;
                    hash[key].first=value;

                }else{
                    // cerr<<"I am here"<<endl;
                    tail->next=newNode;
                    newNode->prev=tail;
                    tail=newNode;
                    hash[key]=make_pair(value,newNode);
                    cSize++;
                }
            }
            
        }else{
            if(hash.find(key)!= hash.end()){
                ///move to back
                DListNode *tmp=hash[key].second;
                // cerr<<"wowowiee key "<<tmp->val<<"value" <<hash[key].first<<endl;
                if(tmp==tail){
                    // cerr<<"howwwww"<<endl;
                    hash[tail->val].first=value;
                    return;
                }
                if(tmp==head){
                    // cerr<<"should shift"<<endl;
                    head=head->next;
                }
                if(tmp->prev!=nullptr){
                    // cerr<<"before "<<tmp->prev->val<<endl;
                    tmp->prev->next=tmp->next;
                }
                if(tmp->next!=nullptr)
                    tmp->next->prev=tmp->prev;
                tail->next=tmp;
                tmp->prev=tail;
                tail=tail->next;
                tmp->next=nullptr;
                hash[key].first=value;

            }else{
                if(capa!=1){
                    hash.erase(head->val);
                    head=head->next;
                    head->prev=nullptr;
                    tail->next=newNode;
                    newNode->prev=tail;
                    tail=newNode;
                    hash[key]=make_pair(value,newNode);
                }else{
                    hash.erase(head->val);
                    head=newNode;
                    tail=newNode;
                    hash[key]=make_pair(value,newNode);
                }
            }
        }
        // cerr<<"Post Put:";
        // DListNode *thead=head;
        // while(thead!=nullptr){
        //     cerr<<" "<<hash[thead->val].first<<"("<<thead->val<<")";
        //     thead=thead->next;
        // }
        // cerr<<endl;
    }

private: 
    int capa;
    int cSize=0;
    DListNode *head=nullptr;
    DListNode *tail=nullptr;
    unordered_map<int,pair<int, DListNode *>> hash;

};

int main(){

    int n;
    cin>>n;
    vector<string> action(n);
    for(auto &it:action)
        cin>>it;

    LRUCache *lruObj;
    for(auto &it:action){
        if(it=="LRUCache"){
            int cap;
            cin>>cap;
            lruObj=new LRUCache(cap);
        }else if (it=="put"){
            int k,v;
            cin>>k>>v;
            lruObj->put(k,v);
        }
        else if (it=="get") {
            int k;
            cin>>k;
            int v=lruObj->get(k);
            cout<<v<<" ";
        }
    }
}


//best
class LRUCache {
private:
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int cap;
    unordered_map<int, Node*> mp;
    Node* head;
    Node* tail;

    void addNode(Node* node) { // insert after head
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToFront(Node* node) {
        removeNode(node);
        addNode(node);
    }

    void removeLRU() {
        Node* lru = tail->prev;
        removeNode(lru);
        mp.erase(lru->key);
        delete lru;
    }

public:
    LRUCache(int capacity) {
        cap = capacity;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (mp.find(key) == mp.end())
            return -1;

        Node* node = mp[key];
        moveToFront(node);
        return node->value;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            node->value = value;
            moveToFront(node);
        } else {
            if (mp.size() == cap) {
                removeLRU();
            }
            Node* node = new Node(key, value);
            mp[key] = node;
            addNode(node);
        }
    }
};
auto init = atexit([]() { ofstream("display_runtime.txt") << "0"; });

//wtf

auto init_io = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();
class LRUCache {
public:
    inline static int M[10001];
    inline static int16_t L[10002][2];
    int cap, size = 0;
    const int NONE = 10001;
    int head = NONE, tail = NONE;
    
    LRUCache(int capacity) : cap(capacity) {
        memset(M, 0xff, sizeof M);
    }
    
    inline void erase(int key) {
        const int pre = L[key][0];
        const int nxt = L[key][1];
        L[pre][1] = nxt;
        L[nxt][0] = pre;
        if (head == key) head = nxt;
        if (tail == key) tail = pre;
    }
    
    inline void push_front(int key) {
        L[key][0] = NONE;
        L[key][1] = head;
        L[head][0] = key;
        head = key;
        if (tail == NONE)
            tail = key;
    }
    
    inline int pop_back() {
        int ret = tail;
        tail = L[tail][0];
        L[tail][1] = NONE;
        if (tail == NONE)
            head = NONE;
        return ret;
    }
    
    inline int get(int key) {
        if (M[key] == -1) return -1;
        erase(key);
        push_front(key);
        return M[key];
    }
    
    inline void put(int key, int value) {
        if (M[key] != -1) {
            erase(key);
        } else {
            if (size == cap) {
                int poped = pop_back();
                M[poped] = -1;
                size -= 1;
            }
            size += 1;
        }
        push_front(key);
        M[key] = value;
    }
};

#include <unistd.h>
static char buf[20000000];

static inline int mgetchar() {
    static int pos = 0;
    pos++;
    return buf[pos-1] == '\0' ? EOF : buf[pos-1];
}

static inline int getmethod() {
    // while (getchar() != '"');
    int c = mgetchar();
    while (mgetchar() != '"');
    return c;
}

static inline int getinput(vector<int>& ret) {
    int c;
    while((c = mgetchar()) != EOF && c != '[');
    while ((c = mgetchar()) != EOF) {
        if (c == '"')
            ret.push_back(getmethod());
        else if (c == ']')
            return 1;
    }
    return 0;
}

static inline int getone() {
    while(mgetchar() != '[');
    int ans = 0, c;
    while((c = mgetchar()) != ']') {
        if (isdigit(c))
            ans = ans * 10 + c - '0';
    }
    return ans;
}

static inline pair<int,int> gettwo() {
    while(mgetchar() != '[');
    pair<int,int> ans;
    int c;
    while((c = mgetchar()) != ',') {
        if (isdigit(c))
            ans.first = ans.first * 10 + c - '0';
    }
    while((c = mgetchar()) != ']') {
        if (isdigit(c))
            ans.second = ans.second * 10 + c - '0';
    }
    return ans;
}

static inline void getpara(FILE *fp, vector<int>& funcs) {
    while(mgetchar() != '[');
    fprintf(fp, "[");
    LRUCache lru(getone());
    for (int i = 0; i < funcs.size(); i++) {
        auto f = funcs[i];
        if (f == 'L') {
            fprintf(fp, "null");
        } else if (f == 'g') {
            int v = lru.get(getone());
            fprintf(fp, "%d", v);
        } else {
            pair<int,int> v = gettwo();
            lru.put(v.first, v.second);
            fprintf(fp, "null");
        }
        if (i + 1 < funcs.size())
            fprintf(fp, ",");
    }
    while(mgetchar() != ']');
    fprintf(fp, "]\n");
}

[[noreturn]] __attribute__((constructor)) void mymain() {
    int n = read(0, buf, 20000000);
    buf[n] = '\0';

    FILE *fp = fopen("user.out", "w");
    vector<int> funcs;
    while (getinput(funcs)) {
        getpara(fp, funcs);
        funcs.clear();
    }
    fclose(fp);
    exit(0);
}