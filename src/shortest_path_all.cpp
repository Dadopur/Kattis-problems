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

private:
    // Member variables
    const int index;
    bool visited;
    vector<int> distances_to_node;
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
void floyd(Graph& graph) {
    // Reset graph to be sure it's a clean search
    graph.graph_reset(INF);

    for(Edge* edge : graph.get_edges()) {
        Node* from_node = edge->from_node;
        Node* to_node = edge->to_node;
        int to_node_index = to_node->get_index();
        int edge_cost = edge->edge_cost;
        int old_distance = from_node->get_distances()[to_node_index];
        
        // A better path was found in direct connections
        if(edge_cost < old_distance) {
            from_node->set_distance(to_node_index, edge_cost);
        }
    }

    int num_nodes = graph.get_nodes().size();
    vector<int> distances_k;
    vector<int> distances_i;
    Node* node_i;

    // Find shortest paths
    for(int k = 0; k < num_nodes; k++) {
        distances_k = graph.get_node(k)->get_distances();
        for(int i = 0; i < num_nodes; i++) {
            node_i = graph.get_node(i);
            distances_i = node_i->get_distances();
            for(int j = 0; j < num_nodes; j++) {
                int a = distances_k[j];
                int b = distances_i[k];
                int c = distances_i[j];
                if(c > a + b && a != INF && b != INF) {
                    node_i->set_distance(j, a + b);
                }
            }
        }
    } 

    // Find negative cycles and set to -INF (one more round, better results => neg cycle)
    for(int k = 0; k < num_nodes; k++) {
        distances_k = graph.get_node(k)->get_distances();
        for(int i = 0; i < num_nodes; i++) {
            node_i = graph.get_node(i);
            distances_i = node_i->get_distances();
            for(int j = 0; j < num_nodes; j++) {
                int a = distances_k[j];
                int b = distances_i[k];
                int c = distances_k[k];
                if(c < 0 && a != INF && b != INF) {
                    node_i->set_distance(j, -INF);
                }
            }
        }
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
    std::cout.tie(NULL);

    int num_nodes, num_edges, queries;
    while((cin >> num_nodes >> num_edges >> queries) 
        && !(num_nodes==0 && num_edges==0 && queries==0)) {

        // Make graph and connect edges
        Graph graph = Graph(num_nodes, INF);
        int node1, node2, weight;
        for(int i = 0; i < num_edges; i++) {
            cin >> node1 >> node2 >> weight;
            graph.add_one_way_edge(node1, node2, weight);
        }

        floyd(graph);

        // Prints
        int start_node_index;
        int end_node_index;
        for(int k = 0; k < queries; k++) {
            cin >> start_node_index >> end_node_index;

            Node* node1 = graph.get_node(start_node_index);
            Node* node2 = graph.get_node(end_node_index);
            int value = node1->get_distances()[end_node_index];

            if(value == INF) {
                std::cout << "Impossible" << "\n";
            } else if(value == -INF) {
                std::cout << "-Infinity" << "\n";
            }else {
                std::cout << value << "\n";
            }
        }
        cout << "\n";
    }
}