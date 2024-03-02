
#include <iostream>
#include <vector>
using namespace std;

int find_gold(vector<vector<char>>& world_map, int x, int y ) {


    char curr_pos = world_map[y][x];
    // Base case, we hit a wall, go back.
    if(curr_pos == '#' || curr_pos == 'V') {
        return 0;
    }

    int gold_amout = 0;

    if(curr_pos == 'G') {
        gold_amout++;
    }

    char down_pos = world_map[y+1][x];
    char up_pos = world_map[y-1][x];
    char right_pos = world_map[y][x+1];
    char left_pos = world_map[y][x-1];

    // Set current place to visited to avoid loops.
    world_map[y][x] = 'V';

    // Feeling draft, trap somewhere so go back.
    if(down_pos == 'T' || up_pos == 'T' || right_pos == 'T' || left_pos == 'T') {
        return gold_amout;
    }

    int gold_down = find_gold(world_map, x, y+1);
    int gold_up = find_gold(world_map, x, y-1);
    int gold_right = find_gold(world_map, x+1, y);
    int gold_left = find_gold(world_map, x-1, y);

    // for(auto i : world_map) {
    //     for(auto j : i) {
    //         cout << j;
    //     }
    //     cout << endl;
    // }
    // cout << "\n";

    return gold_amout + gold_down + gold_up + gold_right + gold_left;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int w, h;
    cin >> w >> h;

    vector<vector<char>> world_map(h, vector<char>(w));
    string s;
    int start_y, start_x;
    for(int i = 0; i < h; i++) {
        cin >> s;
        for(int c = 0; c < w; c++) {
            world_map[i][c] = s[c];
            if(s[c] == 'P') {
                start_x = c;
                start_y = i;
            }
        }
    }
    cout << find_gold(world_map, start_x, start_y);
}