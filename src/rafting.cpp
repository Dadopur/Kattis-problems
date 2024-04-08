
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Line {
    Point start;
    Point end;
};

struct Vec {
    double x;
    double y;
};
double projectivise(Point p, Line l) {
    //get shortest dist from point p to line l
    Vec v1 = Vec{l.end.x - l.start.x, l.end.y - l.start.y};
    Vec v2 = Vec{p.x - l.start.x, p.y - l.start.y};

    double scaler = (v1.x * v2.x + v1.y * v2.y) / (v1.x * v1.x + v1.y * v1.y);
    if(scaler > 1 || scaler < 0) {
        return 0;
    }
    double x_part = (v2.x - (v1.x * scaler));
    double y_part = (v2.y - (v1.y * scaler));
    double dist = sqrt(x_part * x_part + y_part * y_part);
    return dist;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int num_tests;
    cin >> num_tests;

    while(num_tests--) {
        vector<Point> inner_points;
        vector<Line> inner_lines;
        vector<Point> outer_points;
        vector<Line> outer_lines;

        int num_inner_points;
        cin >> num_inner_points;
        
        // Save inner points and lines, start with point 0 outside of loop
        double x, y;
        cin >> x >> y;
        inner_points.push_back(Point{x, y});
        for(int i = 1; i < num_inner_points; i++) {
            cin >> x >> y;
            inner_points.push_back(Point{x, y});
            inner_lines.push_back(Line{inner_points[i-1], inner_points[i]});
        }
        inner_lines.push_back(Line{inner_points[num_inner_points-1], inner_points[0]});

        int num_outer_points;
        cin >> num_outer_points;
        
        // Save outer points and lines, start with point 0 outside of loop
        cin >> x >> y;
        outer_points.push_back(Point{x, y});
        for(int i = 1; i < num_outer_points; i++) {
            cin >> x >> y;
            outer_points.push_back(Point{x, y});
            outer_lines.push_back(Line{outer_points[i-1], outer_points[i]});
        }
        outer_lines.push_back(Line{outer_points[num_outer_points-1], outer_points[0]});

        double shortest_dist = 1000000000;
        // Check shortest dist from inner points to outer lines
        for(Point p : inner_points) {
            for(Line l : outer_lines) {
                if(projectivise(p, l) <= 0) {
                    continue;
                } else {
                    shortest_dist = min(shortest_dist, projectivise(p, l));
                }
            }
        }

        // check shortest dist from outer points to inner lines
        for(Point p : outer_points) {
            for(Line l : inner_lines) {
                if(projectivise(p, l) <= 0) {
                    continue;
                } else {
                    shortest_dist = min(shortest_dist, projectivise(p, l));
                }
            }
        }

        // Check dist from inner points to outer points
        for(Point p : inner_points) {
            for(Point q : outer_points) {
                double dist = sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
                shortest_dist = min(shortest_dist, dist);
            }
        }

        cout << setprecision(8) << (shortest_dist/2) << "\n";
    }
}