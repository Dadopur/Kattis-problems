// Do the neg weights but instead of doing bfs, just set the current node that has become smaller true 
// (looped) and do so for all those nodes that become smaller. maybe


/**
 * @file graph_shortest_path.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Program is made to find shortest path between 2 nodes using Floyd Warshall algorithm.
 * The time complexity is O(V^3) because of 3 nested for loops. Memory complexity is O(V^2). 
 * @version 0.1
 * @date 2024-03-03
 */
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <utility>
#include <queue>
#include <map>
#include <numeric>
using namespace std;
static const int INF = numeric_limits<int>::max();

class Node;

/**
 * @brief Edge between two nodes. Only a one way edge with a set cost.
 */
struct Edge {
    // Constructor
    Edge(Node* const node1, Node* const node2, const int cost) : from_node(node1), to_node(node2), edge_cost(cost) {}
    // Member variables
    Node* from_node;
    Node* to_node;
    int edge_cost;
};

/**
 * @brief Node class containing all necessary information for most basic search algorithms.
 */
class Node {
public:
    /**
     * @brief Construct a new Node object.
     * 
     * @param in_index Unique index of node as it is in the graph.
     * @param in_value Initial (start) value of node.
     */
    Node(const int in_index, int in_value, const int num_nodes) : index(in_index), visited(false) {
        distances_to_node = vector<int>(num_nodes, in_value);
        distances_to_node[in_index] = 0;
        no_good = false;
    }
    
    // Getters
    // ================================
    int get_index() const {
        return index;
    }

    bool is_visited() const {
        return visited;
    }

    vector<int> get_distances() {
        return distances_to_node;
    }

    // Setters
    // ================================
    void set_visited(bool const new_visited) {
        visited = new_visited;
    }
    
    void set_distance(int node_index, int new_distance) {
        distances_to_node[node_index] = new_distance;
    }

    void reset_distances(int init_value) {
        for(int i = 0; i < distances_to_node.size(); i++) {
            distances_to_node[0] = init_value;
        }
        distances_to_node[index] = 0;
    }

    void add_neighbour(int i) {
        neighbours.push_back(i);
    }

    vector<int> get_neighbours() {
        return neighbours;
    }

    void set_no_good(bool new_no_good) {
        no_good = new_no_good;
    }

    bool is_no_good() {
        return no_good;
    }

private:
    // Member variables
    const int index;
    bool visited;
    vector<int> distances_to_node;
    vector<int> neighbours;
    bool no_good;
};

/**
 * @brief Class containing everything needed for a graph.
 */
class Graph {
public:
    /**
     * @brief Construct a new Graph object
     * 
     * @param num_nodes Number of nodes to be initialized in the graph.
     * @param init_value Int of the initial values for all nodes.
     */
    Graph(int const num_nodes, int const init_value) {
        for(int i = 0; i < num_nodes; i++) {
            Node* new_node = new Node{i, init_value, num_nodes};
            nodes.push_back(new_node);
        }
    }

    /**
     * @brief Destroy the Graph object
     */
    ~Graph() {
        for(Node* node : nodes) {
            delete node;
        }

        for(Edge* edge : edges) {
            delete edge;
        }
    }

    Node* get_node(int const index) const {
        return nodes[index];
    }

    vector<Node*> get_nodes() {
        return nodes;
    }

    vector<Edge*> get_edges() {
        return edges;
    }

    /**
     * @brief Add new connection between two nodes with a given weight cost.
     *
     * @param node1 Index of first node to be connected.
     * @param node2 Index of second node to be connected.
     * @param cost Path cost for the connection (edge).
     */
    void add_one_way_edge(int const node1, int const node2, int const cost) {
        // Get nodes to be connected
        Node* primary_node = nodes[node1];
        Node* secundary_node = nodes[node2];

        // Make new edge
        Edge* edge = new Edge{primary_node, secundary_node, cost};
        primary_node->add_neighbour(node2);


        // Add new edges to the nodes
        edges.push_back(edge);
    }

    /**
     * @brief Reset all nodes to standard values and resets starting node to provided index.
     */
    void graph_reset(int init_value) {
        for(Node* node : nodes) {
            node->reset_distances(init_value);
            node->set_visited(false);
        }
    }

private:
    vector<Node*> nodes;
    vector<Edge*> edges;
};

/**
 * @brief Find shortest path from given start node to all other nodes using Floyd-Warshall algorithm. 
 * 
 * @param graph Graph with all nodes and edges included. 
 */
vector<vector<int>> floyd(Graph& graph, int num_nodes) {
    // Reset graph to be sure it's a clean search
    //graph.graph_reset(INF);
    vector<vector<int>> grid(num_nodes, vector<int>(num_nodes, INF));
    for(Edge* edge : graph.get_edges()) {
        Node* from_node = edge->from_node;
        Node* to_node = edge->to_node;
        int to_node_index = to_node->get_index();
        int from_node_index = from_node->get_index();
        int edge_cost = edge->edge_cost;
        //int old_distance_1 = from_node->get_distances()[to_node_index];
        //int old_distance_2 = to_node->get_distances()[from_node_index];
        int old_distance_1 = grid[from_node_index][to_node_index];
        
        // A better path was found in direct connections
        if(edge_cost < old_distance_1) {
            //from_node->set_distance(to_node_index, edge_cost);
            grid[from_node_index][to_node_index] = edge_cost;
        }
    }

    vector<int> distances_k;
    vector<int> distances_i;
    Node* node_i;
    int a;
    int b;
    int c;
    // Find shortest paths
    for(int k = 0; k < num_nodes; k++) {
        //distances_k = graph.get_node(k)->get_distances();
        // distances_k = grid[k][j];
        for(int i = 0; i < num_nodes; i++) {
            //node_i = graph.get_node(i);
            //distances_i = node_i->get_distances();
            for(int j = 0; j < num_nodes; j++) {
                a = grid[k][j];
                // int a = distances_k[j];
                b = grid[i][k];
                //b = distances_i[k];
                c = grid[i][j];
                // c = distances_i[j];
                if(c > a + b && a != INF && b != INF) {
                    //node_i->set_distance(j, a + b);
                    grid[i][j] = a + b;
                }
            }
        }
    }
    return grid;
}


class UnionFind {
public:

    /**
     * @brief Construct a new Union Find object
     * 
     * @param N number of unions at start
     */
    UnionFind(int const N) {
        // Initialize parent nodes and sizes of disjoint unions
        parents = vector<int>(N);
        iota(parents.begin(), parents.end(), 0);
        union_sizes = vector<int>(N, 1);
    }

    /**
     * @brief Recursive find of root node for a integer in a collection of (disjoint) sets.
     * 
     * @param a Integer which root is to be found.
     * @return int of root node for element a.
     */
    int find_root(int a) {
        if(parents[a] == a) {
            // Root has itself as parent
            return a;
        } else {
            // Find the root for parent of a to be used in path compression 
            int root = find_root(parents[a]);
            parents[a] = root;
            return root;
        }
    }

    /**
     * @brief Check if a and b are in the same union.
     * 
     * @param a Integer of first element to be compared with b.
     * @param b Integer of secound element to be compared with a.
     * @return true if a and b are in same union,
     * @return false otherwise.
     */
    bool same(int a, int b) {
        // Same root means same union
        return (find_root(a) == find_root(b));
    }

    /**
     * @brief Merge two unions (of a and b) if possible.
     * 
     * @param a Integer (element) which root union is to be merged with root union of b.
     * @param b Integer (element) whoch root union is to be merged with root union of a.
     */
    void merge_unions(int a, int b) {
        // Fint root nodes
        int root_a = find_root(a);
        int root_b = find_root(b);

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
    // Vector of all parents for each element in the collection of (disjoint) sets.
    vector<int> parents;
    vector<int> union_sizes;
};
/**
 * @brief Main function that takes inputs and outputs to the consol.
 * Finds the shortest (lowest cost) path to a given node in a given graph (neg edges ok).
 *
 * @return int
 */
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);

    
    int num_flights;
    cin >> num_flights;
    map<string, int> city_indexes;
    vector<pair<int, int>> flights;
    for(int edge = 0; edge < num_flights; edge++) {
        string first, second;
        cin >> first >> second;
        if(city_indexes.find(first) == city_indexes.end()) {
            city_indexes[first] = city_indexes.size();
        }
        if(city_indexes.find(second) == city_indexes.end()) {
            city_indexes[second] = city_indexes.size();
        }
        int city1 = city_indexes[first];
        int city2 = city_indexes[second];
        flights.push_back({city1, city2});
    }

    int num_nodes = city_indexes.size();
    Graph graph = Graph(num_nodes, INF);
    for(pair<int, int> flight : flights) {
        graph.add_one_way_edge(flight.first, flight.second, 1);
    }
    vector<vector<int>> grid = floyd(graph, num_nodes);

    UnionFind union_find = UnionFind(num_nodes);
    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < num_nodes; j++) {
            if(grid[i][j] != INF && grid[j][i] != INF) {
                union_find.merge_unions(i, j);
            }
        }
    }
    string test_city;
    while(cin >> test_city) {
        int city_index = city_indexes[test_city];
        int root = union_find.find_root(city_index);
        int size = union_find.union_sizes[root];
        if(size <= 2) {
            cout << test_city << " trapped" << "\n";
        } else {
            cout << test_city << " safe" << "\n";
        }
    }

}