/**
 * @file graph_shortest_path.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 */
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class Node;

struct Edge {
    // Constructor
    Edge(Node* const node, const int cost) : connection_node(node), edge_cost(cost) {}
    // Member variables
    const Node* connection_node;
    const int edge_cost;
};

class Node {
    public:
        // Constructor
        Node(const int in_index, int in_value) : index(in_index), value(in_value), visited(false) {}
        // Destructor
        ~Node(){
            for(auto edge : edges){
                delete edge;
            }
        }
        // Getters
        // ================================
        int get_index() const {
            return index;
        }

        int get_value() const {
            return value;
        }

        bool is_visited() const {
            return visited;
        }

        vector<Edge*> get_edges() const {
            return edges;
        }

        Edge* get_edge(int const edge_index) const {
            return edges[edge_index];
        }

        // Setters
        // ================================
        void set_value(int const new_value) {
            value = new_value;
        }

        void set_visited(bool const new_visited) {
            visited = new_visited;
        }

        void add_edge(Edge* const new_edge) {
            edges.push_back(new_edge);
        }

    private:
        // Member variables
        const int index;
        int value;
        bool visited;
        vector<Edge*> edges;
};

class Graph {
    public:
        ~Graph() {
            for(Node* node : nodes) {
                delete node;
            }
        }

        Node* get_node(int const index) const {
            return nodes[index];
        }

    private:
        vector<Node*> nodes;
};

bool node_value_compare(pair<int, int> node1, pair<int, int> node2) {
    return (get<1>(node1) < get<1>(node2));
}

vector<pair<int, int>> dijkstra(vector<Node*>& graph, int start_node_index) {

    Node* start_node = graph[start_node_index];
    start_node->set_value(0);

    // Add all node pointers to the set comparing them on distance, dont forget to remove and re-add nodes with updated value


    // Pair of (prev_index, curr_value)
    vector<pair<int, int>> table(graph.size(), {0, numeric_limits<int>::max()});
    vector<int> visited_nodes;

    Node* start_node = graph[start_node_index];
    table[start_node_index].second = 0;

    // Go through all edges in start node and update next node_index (value = edge_cost + curr_value)
    // Add curr node index to visited nodes, go to next node in
    // dont go back and update/ check already visited nodes.

    // Use a set, the we need to have a tuple/ 3 long array cuz index will change.
    vector<pair<int, int>>::iterator next_node = min_element(table.begin(), table.end(), node_value_compare);

    return table;
}

/**
 * @brief Adds a new connection between two nodes with a given weight cost.
 *
 * @param nodes Vector of all nodes in the graph.
 * @param node1 Index of first node to be connected.
 * @param node2 Index of second node to be connected.
 * @param cost Path cost for the connection (edge).
 */
void add_edge(vector<Node*>& graph, int node1, int node2, int cost) {
    // Get nodes to be connected
    Node* primary_node = graph[node1];
    Node* secundary_node = graph[node2];

    // Make new edges
    Edge* edge1 = new Edge{primary_node, cost};
    Edge* edge2 = new Edge{secundary_node, cost};

    // Add new edges to the nodes
    primary_node->add_edge(edge1);
    secundary_node->add_edge(edge2);
}

/**
 * @brief Initializes nodes with corresponding index.
 *
 * @param nodes Vector of length N (number of nodes) to be initialized with nodes pointers.
 */
void init_nodes(vector<Node*>& graph, int init_value) {
    for(int i = 0; i < graph.size(); i++) {
        graph[i] = new Node{i, init_value};
    }
}

/**
 * @brief Main function that takes inputs and outputs to the consol.
 * Finds the shortest (lowest cost) path to a given node in a given graph.
 *
 * @return int
 */
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, q, s;
    while((cin >> n >> m >> q >> s) && !(n==0 && m==0 && q==0 && s==0)) {
        vector<Node*> graph(n);
        init_nodes(graph, numeric_limits<int>::max());

        int node1, node2, weight;
        for(int i = 0; i < m; i++) {
            cin >> node1 >> node2 >> weight;
            add_edge(graph, node1, node2, weight);
        }

    }
}