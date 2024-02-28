
// Imports
#include <iostream>
#include <vector>
#include <numeric>
#include <set>
using namespace std;

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


pair<int, vector<pair<int, int>>> kruskals(set<pair<int, pair<int, int>>>& edges, int num_nodes) {
 // @return pair<int, vector<pair<int, int>>>: total_tree_cost, edges in tree. Vector will be length 1 with (-1, -1) if no tree is made.

    // Initialize parent nodes and sizes of disjoint unions
    vector<int> parents(num_nodes);
    iota(parents.begin(), parents.end(), 0);
    vector<int> union_sizes(num_nodes, 1);

    vector<pair<int, int>> connections_made;
    int total_path_cost = 0;
    while(!edges.empty()) {
        pair<int, pair<int, int>> new_edge = *edges.begin();
        edges.erase(new_edge);
        int first_node = (new_edge.second).first;
        int second_node = (new_edge.second).second;
        int cost = new_edge.first;
        //not in set, check both from and to index
        if(!find(parents, first_node, second_node)) {
            // add to set (both of the nodes), add cost to total_path_cost
            merge_unions(parents, union_sizes, first_node, second_node);
            connections_made.push_back({first_node, second_node});
            total_path_cost += cost;
        }
    }

    // Check if all nodes are in the same set (all nodes connected)
    int root = find_root(parents, 0);
    if(union_sizes[root] != num_nodes) {
        return {-1, vector<pair<int, int>>(1, {-1, -1})};
    }
    
    return {total_path_cost, connections_made};
}


/**
 * @brief 
 * 
 * @return int 
 */
int main() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);

    int num_nodes, num_edges;
    std::cin >> num_nodes >> num_edges;
    while(!(num_nodes == 0 && num_edges == 0)) {

        // Init edges, set of edges: cost, (from - to)
        set<pair<int, pair<int, int>>> edges;
        int node1, node2, cost;
        for(int i = 0; i < num_edges; i++) {
            std::cin >> node1 >> node2 >> cost;
            edges.insert({cost, {node1, node2}});
        }
        
        // Output from kruskals
        int total_cost;
        vector<pair<int, int>> connections;
        pair<int, vector<pair<int, int>>> result_from_kruskal = kruskals(edges, num_nodes);
        
        // Ending prints
        total_cost = result_from_kruskal.first;
        connections = result_from_kruskal.second;
        if(connections[0].first == -1) {
            // All nodes not connected
            cout << "Impossible\n";
        } else {
            cout << total_cost << "\n";
            for(pair<int, int> edge : connections) {
                cout << edge.first << " " << edge.second << "\n";
            }
        }
        std::cin >> num_nodes >> num_edges;
    }
}