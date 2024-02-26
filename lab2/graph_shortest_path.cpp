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
#include <utility>
#include <set>
using namespace std;

class Node;

struct Edge {
    // Constructor
    Edge(Node* const node, const int cost) : connection_node(node), edge_cost(cost) {}
    // Member variables
    Node* connection_node;
    int edge_cost;
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

class Graph {
    public:
        /**
         * @brief Construct a new Graph object
         * 
         * @param num_nodes Number of nodes to be initialized in the graph.
         * @param init_value Int of the initial values for all nodes.
         */
        Graph(int const num_nodes, int const init_value){
            for(int i = 0; i < num_nodes; i++) {
                nodes.push_back(new Node{i, init_value});
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

        /**
         * @brief Adds a new connection between two nodes with a given weight cost.
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
            Edge* edge = new Edge{secundary_node, cost};

            // Add new edges to the nodes
            primary_node->add_edge(edge);
        }

        void graph_reset() {
            for(Node* node : nodes) {
                node->set_prev_node(nullptr);
                node->set_value(numeric_limits<int>::max());
                node->set_visited(false);
            }
        }

    private:
        vector<Node*> nodes;
};

void dijkstra(Graph& graph, int start_node_index) {

    Node* start_node = graph.get_node(start_node_index);
    start_node->set_value(0);

    set<pair<int, Node*>> prio_queue;
    prio_queue.insert({start_node->get_value(), start_node});

    pair<int, Node*> curr_cost_node;
    while(!prio_queue.empty()) {
        curr_cost_node = *prio_queue.begin();
        prio_queue.erase(curr_cost_node);

        Node* curr_node = curr_cost_node.second;

        if(curr_node->is_visited()) {
            continue;
        } else {
            curr_node->set_visited(true);
        }

        for(Edge* edge : curr_node->get_edges()) {
            Node* edge_node = edge->connection_node; 
            int cost = edge->edge_cost;

            if(edge_node->is_visited()) {
                continue;
            }

            int curr_value = edge_node->get_value();
            int upd_value = curr_node->get_value() + cost;
            if(upd_value < curr_value) {
                edge_node->set_value(upd_value);
                edge_node->set_prev_node(curr_node);
                prio_queue.insert({upd_value, edge_node});
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

    int n, m, q, s;
    while((cin >> n >> m >> q >> s) && !(n==0 && m==0 && q==0 && s==0)) {
        Graph graph = Graph(n, numeric_limits<int>::max());

        // Make edges
        int node1, node2, weight;
        for(int i = 0; i < m; i++) {
            cin >> node1 >> node2 >> weight;
            graph.add_one_way_edge(node1, node2, weight);
        }

        dijkstra(graph, s);

        // Prints
        int query;
        for(int k = 0; k < q; k++) {
            cin >> query;
            Node* q_node = graph.get_node(query);
            int value = q_node->get_value();
            if(value == numeric_limits<int>::max()) {
                std::cout << "Impossible" << "\n";
            }else {
                std::cout << q_node->get_value() << "\n";
            }
        }
    }
}