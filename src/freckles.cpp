
/**
 * @file minimal_spanning_tree.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Find minimal spanning tree using kruskals algorithm (unsing union search).
 * @version 0.1
 * @date 2024-02-28
 */
// Imports
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
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

/**
 * @brief Find if edge1 is in lexicographic order compared with edge2. (Comparitor).
 * 
 * @param edge1 to be compared to edge2
 * @param edge2 to be compared with edge1
 * @return true if edge1 is "smaller" than edge2 in lexicographic order 
 * @return false otherwise
 */
bool compare_lexicographic(pair<int, int> edge1, pair<int, int> edge2) {
    // First node is smaller
    if(edge1.first < edge2.first) {
        return true;
    }
    
    // Same node, look at secound node
    if (edge1.first == edge2.first) {
        if(edge1.second < edge2.second) {
            return true;
        }
    }

    // Base case, edge2 is samller
    return false;
}

/**
 * @brief Find what edges make minimal spanning tree (least cost) if any exist and its cost, 
 * using a set of edges and kruskals algorithm. 
 * 
 * @param edges Edges in given graph.
 * @param num_nodes Number of nodes in the graph.
 * @return pair<int, vector<pair<int, int>>>: total_tree_cost, edges in tree (lexicographic order). 
 * Vector will be length 1 with (-1, -1) if no tree is made.
 */
pair<double, vector<pair<int, int>>> kruskals(vector<pair<double, pair<int, int>>>& edges, int num_nodes) {

    // Initialize parent nodes and sizes of disjoint unions
    vector<int> parents(num_nodes);
    iota(parents.begin(), parents.end(), 0);
    vector<int> union_sizes(num_nodes, 1);

    vector<pair<int, int>> connections_made;
    double total_path_cost = 0;
    int curr_index = 0;
    while(curr_index < edges.size()) {
        pair<double, pair<int, int>> new_edge = edges[curr_index];
        //edges.erase(new_edge);
        int first_node = (new_edge.second).first;
        int second_node = (new_edge.second).second;
        double cost = new_edge.first;
        //not in set, check both from and to index
        if(!find(parents, first_node, second_node)) {
            // add to set (both of the nodes), add cost to total_path_cost
            merge_unions(parents, union_sizes, first_node, second_node);
            if(first_node < second_node) {
                connections_made.push_back({first_node, second_node});
            } else {
                connections_made.push_back({second_node, first_node});
            }
            total_path_cost += cost;
        }
        curr_index++;
    }

    // Check if all nodes are in the same set (all nodes connected)
    int root = find_root(parents, 0);
    if(union_sizes[root] != num_nodes) {
        return {-1, vector<pair<int, int>>(1, {-1, -1})};
    }
    
    // Sort in lexicographic order
    sort(connections_made.begin(), connections_made.end(), compare_lexicographic);
    return {total_path_cost, connections_made};
}

double pythagoras(pair<double, double> node1, pair<double, double> node2) {
    return sqrt(pow(node1.first - node2.first, 2) + pow(node1.second - node2.second, 2));
}


/**
 * @brief Execute program (minimal spanning tree) and takes inputs/ outputs from console.
 * 
 * @return int 
 */
int main() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);

    int rounds;
    cin >> rounds;
    for(int round = 0; round < rounds; round++) {
        if(round != 0) {
            cout << "\n";
        }
        int num_nodes;
        cin >> num_nodes;
        vector<pair<double, double>> nodes(num_nodes);
        for(int node = 0; node < num_nodes; node++) {
            double x_pos, y_pos;
            cin >> x_pos >> y_pos;
            nodes[node] = {x_pos, y_pos};
        }
        // Init edges, set of edges: cost, (from - to)
        vector<pair<double, pair<int, int>>> edges;
        for(int column = 0; column < num_nodes; column++) {
            int row = column+1;
            while(row < num_nodes) {
                if(column == row) {
                    continue;
                }
                double dist = pythagoras(nodes[column], nodes[row]);
                //cout << dist << endl;
                edges.push_back({dist, {column, row}});
                row++;
            }
        }
        sort(edges.begin(), edges.end());
        // Output from kruskals
        double total_cost = 0;
        vector<pair<int, int>> connections;
        pair<double, vector<pair<int, int>>> result_from_kruskal = kruskals(edges, num_nodes);
        //cout << "it broke" << endl;
        // Ending prints
        total_cost = result_from_kruskal.first;
        cout << std::fixed << setprecision(2) << total_cost << "\n";
    }
}