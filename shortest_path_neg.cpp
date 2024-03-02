/**
 * @file graph_shortest_path.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Program is made to find the shortest path between two nodes using Bellman-Fords algorithm.
 * The time complexity for Bellmans is O(E*V) where E is number of edges and V
 * is number of nodes. This is because all E edges are checked V-1 times, then all edges are checked
 * again, then all nodes are updated. O(E*(V-1) + E + V) = O(E*V).
 * @version 0.1
 * @date 2024-03-02
 *
 */
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <utility>
#include <set>
using namespace std;
int const INF = numeric_limits<int>::max();

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
        Node(const int in_index, int in_value) : index(in_index), value(in_value), visited(false) {}
        
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
 * @brief 
 * 
 */
class Graph {
    public:
        /**
         * @brief Construct a new Graph object
         * 
         * @param num_nodes Number of nodes to be initialized in the graph.
         * @param init_value Int of the initial values for all nodes.
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
        // root_node->set_value(numeric_limits<int>::min());
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

    int num_nodes, num_edges, queries, start_node_index;
    while((cin >> num_nodes >> num_edges >> queries >> start_node_index) 
        && !(num_nodes==0 && num_edges==0 && queries==0 && start_node_index==0)) {

        // Make graph and connect edges
        Graph graph = Graph(num_nodes, INF, start_node_index);
        int node1, node2, weight;
        for(int i = 0; i < num_edges; i++) {
            cin >> node1 >> node2 >> weight;
            graph.add_one_way_edge(node1, node2, weight);
        }

        bellman(graph, start_node_index);

        /* 
        Code to print path from start node to given index:
        
        int path_to_index = 2;

        vector<Node*> test = graph.get_path(path_to_index);
        for(Node* node : test) {
            cout << node->get_index() << " ";
        }cout << endl;
        */


        // Prints
        int query;
        for(int k = 0; k < queries; k++) {
            cin >> query;
            Node* q_node = graph.get_node(query);
            int value = q_node->get_value();

            if(value == INF) {
                std::cout << "Impossible" << "\n";
            } else if(q_node->get_value() == -INF) {
                std::cout << "-Infinity" << "\n";
            }else {
                std::cout << q_node->get_value() << "\n";
            }
        }
    }
}