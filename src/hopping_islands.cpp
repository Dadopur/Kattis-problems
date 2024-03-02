#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <cmath>
#include <string>
using namespace std;

struct Bridge_position {
    double x_pos, y_pos;
};


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

double euclidean_dist(double x1, double x2, double y1, double y2) {
    return sqrt(pow(abs(x1-x2), 2) + pow(abs(y1-y2), 2));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int num_cases;
    cin >> num_cases;
    for(int num_case = 0; num_case < num_cases; num_case++) {
        int islands;
        cin >> islands;
        vector<Bridge_position> bridge_positions(islands);

        for(int island = 0; island < islands; island++) {
            string x_pos_s, y_pos_s;
            cin >> x_pos_s >> y_pos_s;
            double x_pos = stod(x_pos_s);
            double y_pos = stod(y_pos_s);
            bridge_positions[island] = Bridge_position{x_pos, y_pos};
        }
        vector<int> parents(islands);
        std::iota(parents.begin(), parents.end(), 0);
        vector<int> union_sizes(islands, 1);

        // set of edges: cost, (from - to)
        set<pair<double, pair<int, int>>> edges;
        for(int from_index = 0; from_index < islands; from_index++) {
            int to_index = 1+from_index;
            while(to_index < islands) {
                Bridge_position island1 = bridge_positions[from_index];
                Bridge_position island2 = bridge_positions[to_index];
                double cost = euclidean_dist(island1.x_pos, island2.x_pos, island1.y_pos, island2.y_pos);
                edges.insert({cost, {from_index, to_index}});
                to_index++;
            }
        }
        double total_path_cost = 0;
        while(!edges.empty()) {
            pair<double, pair<int, int>> new_edge = *edges.begin();
            edges.erase(new_edge);
            int first_node = (new_edge.second).first;
            int second_node = (new_edge.second).second;
            double cost = new_edge.first;
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