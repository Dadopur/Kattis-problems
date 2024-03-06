#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <utility>
using namespace std;
int unvisited = -2;

void traverse_grid(vector<vector<int>>& world_map, int x_start, int y_start) {

    int start_steps = -1;
    // x, y, steps
    queue<tuple<int, int, int>> q;
    q.push({x_start, y_start, start_steps});

    while (!q.empty()) {
        tuple<int, int, int> front = q.front();
        int x = get<0>(front);
        int y = get<1>(front);
        int prev_steps = get<2>(front);
        q.pop();

        // cout << "FROM INDEX: " << from_index << endl; 
        int curr_pos = world_map[y][x];
        // cout << "CURR POS IS: " << curr_pos << " "<< x << " " << y<< endl;
        // Base case, we hit a wall, go back.
        if(curr_pos != unvisited) {
            continue;
        }
        int steps = prev_steps + 1;
        world_map[y][x] = steps; 
        // cout << "Steps: "<< steps << endl;

        // vector<pair<int, int>> next_steps;

        int x_right_2 = x+2;
        int x_left_2 = x-2;
        int y_up_2 = y-2;
        int y_down_2 = y+2;

        int x_right_1 = x+1;
        int x_left_1 = x-1;
        int y_up_1 = y-1;
        int y_down_1 = y+1;

        // RIGHT
        if(x_right_2 < 8) {
            // UP
            if(y_up_1 >= 0) {
                if (world_map[y_up_1][x_right_2] == unvisited) q.push({x_right_2, y_up_1, steps});
            }

            // DOWN
            if(y_down_1 < 8) {
                if (world_map[y_down_1][x_right_2] == unvisited) q.push({x_right_2, y_down_1, steps});
            }
        }

        // LEFT
        if(x_left_2 >= 0) {
            // UP
            if(y_up_1 >= 0) {
                if (world_map[y_up_1][x_left_2] == unvisited) q.push({x_left_2, y_up_1, steps});
            }

            // DOWN
            if(y_down_1 < 8) {
                if (world_map[y_down_1][x_left_2] == unvisited) q.push({x_left_2, y_down_1, steps});
            }
        }

        // UP
        if(y_up_2 >= 0) {
            // RIGHT
            if(x_right_1 < 8) {
                if (world_map[y_up_2][x_right_1] == unvisited) q.push({x_right_1, y_up_2, steps});
            }

            // LEFT
            if(x_left_1 >= 0) {
                if (world_map[y_up_2][x_left_1] == unvisited) q.push({x_left_1, y_up_2, steps});
            }
        }

        // DOWN
        if(y_down_2 < 8) {
            // RIGHT
            if(x_right_1 < 8) {
                if (world_map[y_down_2][x_right_1] == unvisited) q.push({x_right_1, y_down_2, steps});
            }

            // LEFT
            if(x_left_1 >= 0) {
                if (world_map[y_down_2][x_left_1] == unvisited) q.push({x_left_1, y_down_2, steps});
            }
        }
        

        // cout << "BOUT TO SET SAIL, X: "<< x << " Y: " << y  << endl;

        // Set current place to visited to avoid loops.
        // for(auto i : world_map) {
        //     for(auto j : i) {
        //         cout << j << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "\n";
    }
    // cout << "here" << endl;

    // for(auto i : world_map) {
    //     for(auto j : i) {
    //         cout << j << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "\n";

    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int rounds;
    cin >> rounds;
    for(int round = 0; round < rounds; round++) {
        vector<vector<int>> world_map(8, vector<int>(8, unvisited));
        string start_position;
        cin >> start_position;
        int start_x, start_y;
        start_x = (int) start_position[0] - 97;
        start_y = abs(start_position[1] - '8');

        //cout << start_x << " " << start_y << endl;
        traverse_grid(world_map, start_x, start_y);

        int highest_number_steps;
        for(auto i : world_map) {
            for(auto j : i) {
                highest_number_steps = max(highest_number_steps, j);
            }
        }
        
        vector<pair<int, int>> hiding_places;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(world_map[i][j] == highest_number_steps) {
                    hiding_places.push_back({j, i});
                }
            }
        }
        cout << highest_number_steps << " ";
        int x;
        int y;
        for(auto place : hiding_places) {
            x = place.first;
            y = place.second;

            cout << char(x+97) << char(abs(y - '8')) << " ";
        }
        cout << "\n";
    }

}