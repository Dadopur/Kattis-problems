
#include <iostream>
#include <vector>
#include <map>
using namespace std;

void find_aliens(map<pair<int, int>, int> alien_indexes, vector<vector<char>>& world_map, 
    const vector<vector<char>> orig_world_map, vector<vector<int>>& dist_to_aliens, int x, int y, int steps, int from_index ) {

    // cout << "FROM INDEX: " << from_index << endl; 
    char curr_pos = world_map[y][x];
    // Base case, we hit a wall, go back.
    if(curr_pos == '#' || curr_pos == 'V') {
        //cout << "INSIDE WALL" << endl;
        return;
    }

    //cout << "hello" << endl;
    steps++;

    if(curr_pos == 'A') {
        //cout << "Found A!" << endl;
        world_map[y][x] = 'V';
        int curr_alien_index = alien_indexes[{x, y}];

        dist_to_aliens[from_index][curr_alien_index] = steps;
        dist_to_aliens[curr_alien_index][from_index] = steps;
        if(from_index != 0){
            return;
        } else {

            // for(auto hej : dist_to_aliens) {
            //     for(auto bajs : hej) {
            //         cout << bajs << " ";
            //     }
            //     cout << endl;
            // }
            // cout << "\n";
            // for(auto i : world_map) {
            //     for(auto j : i) {
            //         cout << j;
            //     }
            //     cout << endl;
            // }
            // cout << "\n";
            vector<vector<char>> new_map = orig_world_map;
            find_aliens(alien_indexes, new_map, orig_world_map, dist_to_aliens, x, y+1, 0, curr_alien_index);
            find_aliens(alien_indexes, new_map, orig_world_map, dist_to_aliens, x, y-1, 0, curr_alien_index);
            find_aliens(alien_indexes, new_map, orig_world_map, dist_to_aliens, x+1, y, 0, curr_alien_index);
            find_aliens(alien_indexes, new_map, orig_world_map, dist_to_aliens, x-1, y, 0, curr_alien_index);
            return;
        }
        // alien found. Take out where index for current alien and check if already found by the same from_index, stop. 
        // Otherwise reset steps to 0 and continue to find other aliens with a new from_index (index of current alien).
        // Do till whole tabel is full (should be done auto)
        // Do kruskals maybe to find optimal connection path.
    }

    // cout << "BOUT TO SET SAIL, X: "<< x << " Y: " << y  << endl;

    // Set current place to visited to avoid loops.
    // for(auto i : world_map) {
    //     for(auto j : i) {
    //         cout << j;
    //     }
    //     cout << endl;
    // }
    // cout << "\n";
    world_map[y][x] = 'V';

    find_aliens(alien_indexes, world_map, orig_world_map, dist_to_aliens, x, y+1, steps, from_index);
    find_aliens(alien_indexes, world_map, orig_world_map, dist_to_aliens, x, y-1, steps, from_index);
    find_aliens(alien_indexes, world_map, orig_world_map, dist_to_aliens, x+1, y, steps, from_index);
    find_aliens(alien_indexes, world_map, orig_world_map, dist_to_aliens, x-1, y, steps, from_index);

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int rounds;
    cin >> rounds;

    for(int r = 0; r < rounds; r++) {
        int w, h;
        cin >> w >> h;
        cin.ignore();

        vector<vector<char>> world_map(h, vector<char>(w));
        map<pair<int, int>, int> alien_indexes;


        string s;
        int start_y, start_x;
        int alien_index = 1;

        for(int i = 0; i < h; i++) {
            getline(cin, s);
            for(int c = 0; c < w; c++) {
                world_map[i][c] = s[c];
                if(s[c] == 'S') {
                    start_x = c;
                    start_y = i;
                }else if (s[c] == 'A') {
                    alien_indexes[{c, i}] = alien_index;
                    alien_index++;
                }
            }
        }

        // for(auto baba : world_map) {
        //     for(auto jaja : baba) {
        //         cout << jaja;
        //     }
        //     cout << endl;
        // }
        // inklusive start
        vector<vector<int>> dist_from_alien_to_alien(alien_index, vector<int>(alien_index, 0));

        find_aliens(alien_indexes, world_map, world_map, dist_from_alien_to_alien, start_x, start_y, -1, 0);

        // Do kruskalls
        for(auto& jj : alien_indexes) {
             cout << "first: " << (jj.first).first << " " << (jj.first).second << " sec " << jj.second<< endl;
        }
        cout << "\n";
        for(auto hej : dist_from_alien_to_alien) {
            for(auto bajs : hej) {
                cout << bajs << " ";
            }
            cout << endl;
        }
    }
}