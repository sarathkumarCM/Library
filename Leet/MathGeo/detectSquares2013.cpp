#include<bits/stdc++.h>
using namespace std;

class DetectSquares {

public:
    // alt long long key = 1LL * x * 1000000 + y;
    struct pair_hash {
        size_t operator()(const pair<int,int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
    unordered_map<pair<int,int>,int,pair_hash> ptFreq;
    DetectSquares() {
        ptFreq.clear();
    }
    
    void add(vector<int> point) {
        ptFreq[{point[0],point[1]}]++;
    }
    
    int count(vector<int> point) {
        //pfreq of points *
        int x=point[0],y=point[1];
        int ans=0;
        for(auto &it:ptFreq){
            auto [dx, dy] = it.first;
            if(abs(x-dx)==abs(y-dy) && dx!=x){
                //forms diagonal;
                auto p1 = ptFreq.find({x, dy});
                auto p2 = ptFreq.find({dx, y});

                if (p1 != ptFreq.end() && p2 != ptFreq.end()) {
                    ans += it.second * p1->second * p2->second;
                }
            }
        }
        return ans;
        
    }

};


/*

 x1 y1.          x2 y1


 x1 y2           x2 y2


*/

//best
#include <vector>
#include <unordered_map>

using namespace std;

static const int _ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class DetectSquares {
    // Хеш-карта: ключ — упакованная координата (x << 10 | y), значение — количество
    unordered_map<int, int> counts;
    // Группировка: для каждого X храним список его Y-координат
    unordered_map<int, vector<int>> x_to_ys;

public:
    DetectSquares() {}

    void add(vector<int> point) {
        int x = point[0], y = point[1];
        int key = (x << 10) | y;
        
        // Если это первая точка с таким X и Y, добавляем Y в список иксов
        if (counts[key] == 0) {
            x_to_ys[x].push_back(y);
        }
        counts[key]++;
    }

    int count(vector<int> point) {
        int x1 = point[0], y1 = point[1];
        int ans = 0;

        // Если для этого X вообще нет точек, выходим сразу
        if (x_to_ys.find(x1) == x_to_ys.end()) return 0;

        // Перебираем только те Y, которые реально существуют при данном X
        for (int y2 : x_to_ys[x1]) {
            if (y2 == y1) continue;

            int side = abs(y1 - y2);

            // Проверяем квадрат справа
            int x_right = x1 + side;
            if (x_right <= 1000) {
                // Ищем точки (x_right, y1) и (x_right, y2)
                int q1 = getCount(x_right, y1);
                int q2 = getCount(x_right, y2);
                if (q1 > 0 && q2 > 0) {
                    ans += counts[(x1 << 10) | y2] * q1 * q2;
                }
            }

            // Проверяем квадрат слева
            int x_left = x1 - side;
            if (x_left >= 0) {
                int q1 = getCount(x_left, y1);
                int q2 = getCount(x_left, y2);
                if (q1 > 0 && q2 > 0) {
                    ans += counts[(x1 << 10) | y2] * q1 * q2;
                }
            }
        }

        return ans;
    }

private:
    // Быстрая вспомогательная функция для получения количества точек
    inline int getCount(int x, int y) {
        int key = (x << 10) | y;
        auto it = counts.find(key);
        return (it != counts.end()) ? it->second : 0;
    }
};

//Another
class DetectSquares {
public:
    std::unordered_map<int, std::unordered_map<int, int>> squaresMap;
    DetectSquares() {
    }
    
    void add(vector<int> point) {
        squaresMap[point[0]][point[1]]++;
    }
    
    int count(vector<int> point) {
        int x1 = point[0];
        int y1 = point[1];
        int finalcount = 0;
        for(const auto& [y2, count]: squaresMap[point[0]]){
            int sLength = y2 - y1;
            if(sLength == 0){continue;}
            int leftPoint = x1-sLength;
            int rightPoint = x1+sLength;
            int leftSqCount = squaresMap[x1][y2]*squaresMap[leftPoint][y2]*squaresMap[leftPoint][y1];
            int rightSqCount = squaresMap[x1][y2]*squaresMap[rightPoint][y2]*squaresMap[rightPoint][y1];
            finalcount += leftSqCount;
            finalcount += rightSqCount;
        }
        return finalcount;
    }
};


//Another
class DetectSquares {
    map<pair<int,int>,int>pointFreq;
    unordered_map<int,set<int>>cols;
public:
    DetectSquares() {
        
    }
    
    void add(vector<int> point) {
        pointFreq[{point[0],point[1]}]++;
        cols[point[1]].insert(point[0]);
    }
    
    int count(vector<int> point) {
        int r1 = point[0], c1 = point[1];
        int ans=0;
        for(int r2 : cols[c1]) {
            int len = abs(r2-r1);
            if(len==0)continue;
            int c2 = c1-len;
            if(pointFreq.count({r2,c2}) and pointFreq.count({r1,c2})) {
                ans+=(pointFreq[{r2,c1}]*pointFreq[{r2,c2}]*pointFreq[{r1,c2}]);
            }
            c2 = c1+len;
            if(pointFreq.count({r2,c2}) and pointFreq.count({r1,c2})) {
                ans+=(pointFreq[{r2,c1}]*pointFreq[{r2,c2}]*pointFreq[{r1,c2}]);
            }
        }
        return ans;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */