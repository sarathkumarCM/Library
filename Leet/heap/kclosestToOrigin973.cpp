#include<bits/stdc++.h>

using namespace std;

struct Point{
    pair<int,int> pt;
    int sq;
};
bool cmp(Point &pt1, Point &pt2){
        return pt1.sq<pt2.sq;
}
struct Compare{
    bool operator()(Point &pt1, Point &pt2){
        return pt1.sq>pt2.sq;
    }
};

class Solution {
public:
   
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> ans;
        for(auto &it:points){
            Point p1;
            p1.pt=make_pair(it[0],it[1]);
            p1.sq=(it[0]*it[0])+(it[1]*it[1]);
            pq.push(p1);

        }

        int ik=0;
        while((!pq.empty())&&(ik<k)){
            Point tp=pq.top();
            vector<int> pps;
            pps.push_back(tp.pt.first);
            pps.push_back(tp.pt.second);
            ans.push_back(pps);
            pq.pop();
            ik++;
        }
        return ans;
    }
    //priority_queue<Point,vector<Point>,bool(*)(Point&, Point&)> pq(cmp);
    priority_queue<Point,vector<Point>,Compare> pq;
};

//best
#include <vector>
#include <algorithm>

using namespace std;

static const int _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n = points.size();
        // Используем структуру для компактного хранения данных
        struct PointDist {
            int dist;
            int id;
            // Оператор для быстрого сравнения
            bool operator<(const PointDist& other) const {
                return dist < other.dist;
            }
        };

        vector<PointDist> dists(n);
        for (int i = 0; i < n; ++i) {
            // Считаем квадрат расстояния (без sqrt)
            dists[i] = {points[i][0] * points[i][0] + points[i][1] * points[i][1], i};
        }

        // nth_element на плоской структуре работает в разы быстрее,
        // чем на тяжелых vector<vector<int>>
        nth_element(dists.begin(), dists.begin() + k, dists.end());

        vector<vector<int>> result;
        result.reserve(k);
        for (int i = 0; i < k; ++i) {
            result.push_back(std::move(points[dists[i].id]));
        }

        return result;
    }
};


//lol
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        nth_element(points.begin(), points.begin() + k, points.end(),
                    [](const vector<int>& a, const vector<int>& b) {
                        return (a[0] * a[0] + a[1] * a[1]) <
                               (b[0] * b[0] + b[1] * b[1]);
                    });
        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};
int main(){

}