
#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <queue>
#include <tuple>
using namespace std;

void find_aliens(map<pair<int, int>, int> alien_indexes, vector<vector<char>>& world_map, 
    const vector<vector<char>> orig_world_map, vector<vector<int>>& dist_to_aliens, int x_start, int y_start, int start_steps, int from_index ) {


    queue<tuple<int, int, int>> q;
    q.push({x_start, y_start, start_steps});

    while (!q.empty()) {
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int prev_steps = get<2>(q.front());
        q.pop();

        // cout << "FROM INDEX: " << from_index << endl; 
        char curr_pos = world_map[y][x];
        // Base case, we hit a wall, go back.
        if(curr_pos == '#' || curr_pos == 'V') {
            //cout << "INSIDE WALL " << from_index << endl;
            continue;
        }

        //cout << "hello" << endl;
        int steps = prev_steps + 1;

        if(curr_pos == 'A' && (y_start != y || x_start != x)) {
            //cout << "Found A! " << from_index << endl;
            world_map[y][x] = 'V';
            int curr_alien_index = alien_indexes[{x, y}];

            //int dist_1 = dist_to_aliens[from_index][curr_alien_index];
            //if(steps < dist_1) {
            dist_to_aliens[from_index][curr_alien_index] = steps;
            dist_to_aliens[curr_alien_index][from_index] = steps;
            //}

            if(from_index != 0){
                //cout << "WHY ARE WE HERE SO FAST " << from_index << endl;
                continue;
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
                find_aliens(alien_indexes, new_map, orig_world_map, dist_to_aliens, x, y, -1, curr_alien_index);
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

        if (world_map[y + 1][x] != 'V') q.push({x, y + 1, steps});
        if (world_map[y - 1][x] != 'V') q.push({x, y - 1, steps});
        if (world_map[y][x + 1] != 'V') q.push({x + 1, y, steps});
        if (world_map[y][x - 1] != 'V') q.push({x - 1, y, steps});
    }

}

/**
 * @brief Recursive find of root node for a integer in a collection of (disjoint) sets.
 * 
 * @param parents Vector of all parents for each element in the collection of (disjoint) sets.
 * @param a Integer which root is to be found.
 * @return int of root node for element a.
 */
int find_root(vector<int>& parents, int a) {
    if(parents[a] == a) {
        // Root has itself as parent
        return a;
    } else {
        // Find the root for parent of a to be used in path compression 
        int root = find_root(parents, parents[a]);
        parents[a] = root;
        return root;
    }
}

/**
 * @brief Check if a and b are in the same union.
 * 
 * @param parents Vector of all parents for each element in the collection of (disjoint) sets.
 * @param a Integer of first element to be compared with b.
 * @param b Integer of secound element to be compared with a.
 * @return true if a and b are in same union,
 * @return false otherwise.
 */
bool find(vector<int>& parents, int a, int b) {
    // Same root means same union
    if(find_root(parents, a) == find_root(parents, b)){
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Merge two unions (of a and b) if possible.
 * 
 * @param parents Vector of all parents for each element in the collection of (disjoint) sets.
 * @param union_sizes Vector of all union sizes. 
 * @param a Integer (element) which root union is to be merged with root union of b.
 * @param b Integer (element) whoch root union is to be merged with root union of a.
 */
void merge_unions(vector<int>& parents, vector<int>& union_sizes, int a, int b) {
    // Fint root nodes
    int root_a = find_root(parents, a);
    int root_b = find_root(parents, b);

    // Same union - do nothing
    if(root_a == root_b){
        return;
    }

    // Get union sizes
    int size_a = union_sizes[root_a];
    int size_b = union_sizes[root_b];

    // Merge smaller union into larger one -> less path compression later
    if(size_a >= size_b) {
        parents[root_b] = root_a;
        union_sizes[root_a] += size_b;
    } else {
        parents[root_a] = root_b;
        union_sizes[root_b] += size_a;
    }
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
        vector<vector<int>> dist_from_alien_to_alien(alien_index, vector<int>(alien_index, 1000000));

        find_aliens(alien_indexes, world_map, world_map, dist_from_alien_to_alien, start_x, start_y, -1, 0);

        // Do kruskalls
        // for(auto& jj : alien_indexes) {
        //      cout << "first: " << (jj.first).first << " " << (jj.first).second << " sec " << jj.second<< endl;
        // }
        // cout << "\n";
        // for(auto hej : dist_from_alien_to_alien) {
        //     for(auto bajs : hej) {
        //         cout << bajs << " ";
        //     }
        //     cout << endl;
        // }

        vector<int> parents(alien_index);
        std::iota(parents.begin(), parents.end(), 0);
        vector<int> union_sizes(alien_index, 1);

        // set of edges: cost, (from - to)
        set<pair<int, pair<int, int>>> edges;
        for(int from_index = 0; from_index < alien_index; from_index++) {
            int to_index = 1+from_index;
            while(to_index < alien_index) {
                int cost = dist_from_alien_to_alien[from_index][to_index];
                edges.insert({cost, {from_index, to_index}});
                //cout << cost << endl;
                to_index++;
            }
        }
        int total_path_cost = 0;
        while(!edges.empty()) {
            pair<int, pair<int, int>> new_edge = *edges.begin();
            edges.erase(new_edge);
            int first_node = (new_edge.second).first;
            int second_node = (new_edge.second).second;
            int cost = new_edge.first;
            //not in set, check both from and to index
            if(!find(parents, first_node, second_node)) {
                total_path_cost += cost;
                merge_unions(parents, union_sizes, first_node, second_node);
                // add to set (both of the nodes), add cost to total_path_cost
            }
        }
        cout << total_path_cost << endl;
    }
}