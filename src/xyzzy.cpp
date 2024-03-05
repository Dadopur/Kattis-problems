/**
 * @file graph_shortest_path.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Program is made to find the shortest path between two nodes using Bellman-Fords algorithm.
 * The time complexity for Bellmans is O(E*V) where E is number of edges and V
 * is number of nodes. This is because all E edges are checked V-1 times, then all edges are checked
 * again, then all nodes are updated. O(E*(V-1) + E + V) = O(E*V).
 * @version 0.1
 * @date 2024-03-03
 *
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
    Node(const int in_index, const int in_value) : index(in_index), value(in_value), visited(false) {}
    
    /**
     * @brief Destroy the Node object.
     */
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

    Node* get_prev_node() {
        return prev_node;
    }
    // Setters
    // ================================
    void set_value(int const new_value) {
        value = new_value;
    }

    void set_visited(bool const new_visited) {
        visited = new_visited;
    }

    void add_edge(Edge* new_edge) {
        edges.push_back(new_edge);
    }
    
    void set_prev_node(Node* new_pre) {
        prev_node = new_pre;
    }

private:
    // Member variables
    const int index;
    int value;
    bool visited;
    Node* prev_node;
    vector<Edge*> edges;
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
     * @param start_index Index of starting node.
     */
    Graph(int const num_nodes, int const init_value, int const start_index) : start_index(start_index) {
        for(int i = 0; i < num_nodes; i++) {
            Node* new_node = new Node{i, init_value};
            nodes.push_back(new_node);
            new_node->set_prev_node(nullptr);
        }
    }

    /**
     * @brief Destroy the Graph object
     */
    ~Graph() {
        for(Node* node : nodes) {
            delete node;
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

    int get_start_index() {
        return start_index;
    }


    /**
     * @brief Get path from start node to given end node if it exists. 
     * 
     * @param end_node_index Index of node to get path to.
     * @return vector<Node*> with all visited nodes to the end node, (empty if not reached or error).
     */
    vector<Node*> get_path(int end_node_index) {
        vector<Node*> return_path;

        // Given index is out of range (no node of that index) -> return no path
        if(end_node_index >= get_nodes().size()) {
            return return_path;
        }
        
        Node* end_node = get_node(end_node_index);
        Node* start_node = get_node(get_start_index());
        Node* current_prev = end_node->get_prev_node();

        // Only add end node if it has been visited (has a path to start)
        if(end_node->is_visited()) {
            return_path.push_back(end_node);
        }
        
        // Follow path back to start
        while(current_prev != nullptr) {
            return_path.push_back(current_prev);
            current_prev = current_prev->get_prev_node();
        }
        // Reverse to have list in right order: start node -> end node.
        reverse(return_path.begin(), return_path.end());
        return return_path;
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
        primary_node->add_edge(edge);
        edges.push_back(edge);
    }

    /**
     * @brief Reset all nodes to standard values and resets starting node to provided index.
     */
    void graph_reset(int new_start_index, int init_value) {
        for(Node* node : nodes) {
            node->set_prev_node(nullptr);
            node->set_value(init_value);
            node->set_visited(false);
        }
        start_index = new_start_index;
    }

private:
    vector<Node*> nodes;
    vector<Edge*> edges;
    int start_index;
};

/**
 * @brief Find shortest path from given start node to all other nodes using Bellman-Ford algorithm. 
 * 
 * @param graph Graph with all nodes and edges included. 
 * @param start_node_index Index of staring node.
 */
void bellman(Graph& graph, int start_node_index) {
    // Reset graph to be sure it's a clean search
    graph.graph_reset(start_node_index, INF);

    Node* start_node = graph.get_node(start_node_index);
    start_node->set_value(0);

    // Relaxation (num_nodes - 1) times
    for(int round = 0; round < graph.get_nodes().size()-1; round++) {
        for(Edge* edge : graph.get_edges()) {
            Node* from_node = edge->from_node;
            Node* to_node = edge->to_node;

            int from_node_value = from_node->get_value();
            int to_node_value = to_node->get_value();
            int edge_cost = edge->edge_cost;

            // Update only in current node has been visited before (is not INF)
            if((from_node_value != INF) && (from_node_value + edge_cost < to_node_value)) {
                to_node->set_value(from_node_value + edge_cost);
                to_node->set_prev_node(from_node);
            }
        }
    }

    // Find neg cycles
    vector<Node*> negative_cycle_nodes;
    for(Edge* edge : graph.get_edges()) {
        Node* from_node = edge->from_node;
        Node* to_node = edge->to_node;

        int from_node_value = from_node->get_value();
        int to_node_value = to_node->get_value();
        int edge_cost = edge->edge_cost;

        // neg cycle found, find all connected nodes
        if((from_node_value != INF) && (from_node_value + edge_cost < to_node_value)) {
            to_node->set_value(from_node_value + edge_cost);
            negative_cycle_nodes.push_back(to_node);
        }
    }

    // Set all nodes connected to neg cycle to -inf
    int index = 0;
    while(index < negative_cycle_nodes.size()) {
        Node* root_node = negative_cycle_nodes[index];
        root_node->set_value(-INF);
        root_node->set_visited(true);
        for(Edge* edge : root_node->get_edges()) {
            Node* neighbour_node = edge->to_node;
            if(neighbour_node->is_visited()) {
                continue;
            }
            negative_cycle_nodes.push_back(neighbour_node);
        }
        ++index;
    }
}

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

    int rooms;
    cin >> rooms;
    while(cin >> rooms && rooms != -1) {
        Graph graph = Graph(rooms, INF, 0);
        int energy;
        int room_connections;
        int next_room;
        vector<int> room_energies;
        vector<vector<int>> connected_rooms;
        for(int room = 0; room < rooms; room++) {
            cin >> energy >> room_connections;
            room_energies[room] = -energy;
            for(int connection = 0; connection < room_connections; connection++) {
                cin >> next_room;
                connected_rooms[room].push_back(next_room);
            }
        }

        for(int node = 0; node < rooms; node++) {
            vector<int> connections = connected_rooms[node];
            for(int i : connections) {
                int next_room_energy = room_energies[i];
                graph.add_one_way_edge(node, i, next_room_energy);
            }
        }

        bellman(graph, 0);
        int value = graph.get_node(rooms-1)->get_value();
        if(value == INF || value != -INF || value < 0) {
            cout << "hopeless\n";
        } else {
            cout << "winnable\n";
        }

    }

        /* 
        Code to print path from start node to given index:
        
        int path_to_index = 2;

        vector<Node*> test = graph.get_path(path_to_index);
        for(Node* node : test) {
            cout << node->get_index() << " ";
        }cout << endl;
        */
}