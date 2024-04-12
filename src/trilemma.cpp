#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

bool is_triange(pair<int,int> a, pair<int,int> b, pair<int,int> c) {
    if((a == b) || (b == c) || (a == c)) {
        return false;
    }

    if((b.second - a.second) * (c.first - b.first) == (c.second - b.second) * (b.first - a.first)) {
        return false;
    }

    return true;
}

string get_angle(vector<int> lengths) {
    if(lengths[0] + lengths[1] == lengths[2]) {
        return "right";
    } else if(lengths[0] + lengths[1] > lengths[2]) {
        return "acute";
    } else {
        return "obtuse";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int test_cases;
    cin >> test_cases;
    for(int test = 0; test < test_cases; test++) {
        int x, y;
        vector<pair<int, int>> points;
        for(int i = 0; i < 3; i++) {
            cin >> x >> y;
            points.push_back({x, y});
        }
        
        if(!is_triange(points[0], points[1], points[2])) {
            cout << "Case #" << (test +1) << ": not a triangle\n";
            continue;
        }

        vector<int> lengths;    
        lengths.push_back(pow(points[0].first - points[1].first, 2) + pow(points[0].second - points[1].second, 2));
        lengths.push_back(pow(points[1].first - points[2].first, 2) + pow(points[1].second - points[2].second, 2));
        lengths.push_back(pow(points[0].first - points[2].first, 2) + pow(points[0].second - points[2].second, 2));

        sort(lengths.begin(), lengths.end());

        string angle = get_angle(lengths);
        string triangle_type = "scalene";

        if(lengths[0] == lengths[1] || lengths[1] == lengths[2] || lengths[0] == lengths[2]) {
            triangle_type = "isosceles";
        }

        cout << "Case #" << (test + 1) << ": " << triangle_type << " " << angle << " triangle\n";
    }
}