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
#include <numeric>
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
    //graph.get_node(2)->set_value(10);

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
 * @brief Main function that takes inputs and outputs to the consol.
 * Finds the shortest (lowest cost) path to a given node in a given graph.
 *
 * @return int
 */
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);

    int num_rounds;
    cin >> num_rounds;
    for(int r = 0; r < num_rounds; r++) {
        int w, h;
        cin >> w >> h;
        cin.ignore();

        vector<int> alien_node_indexes;


        vector<vector<pair<int, char>>> world_map(h, vector<pair<int, char>>(w));
        string s;
        int counting_index = 0;
        int start_index;
        for(int i = 0; i < h; i++) {
            getline(cin, s);
            for(int c = 0; c < w; c++) {
                world_map[i][c].second = s[c];
                world_map[i][c].first = counting_index;
                if (s[c] == 'A') {
                    alien_node_indexes.push_back(counting_index);
                }
                else if(s[c] == 'S') {
                    start_index = counting_index;
                }
                counting_index++;
            }
        }

        // TESTING
        for(auto baba : world_map) {
            for(auto jaja : baba) {
                cout << jaja.second;
            }
            cout << endl;
        }

        cout << "START INDEX " << start_index << endl;
        Graph graph_map = Graph(w*h, numeric_limits<int>::max());

        for(int y = 1; y < h-1; y++) {
            cout << endl;
            for(int x = 1; x < w-1; x++) {
                char curr_char = world_map[y][x].second;
                cout << curr_char;
                int curr_index = world_map[y][x].first;
                // do normal nodes
                if(curr_char == '#') {
                    continue;
                }

                char up_char = world_map[y-1][x].second;
                char up_index = world_map[y-1][x].first;
                char down_char = world_map[y+1][x].second;
                char down_index = world_map[y+1][x].first;
                char left_char = world_map[y][x-1].second;
                char left_index = world_map[y-1][x-1].first;
                char right_char = world_map[y][x+1].second;
                char right_index = world_map[y-1][x+1].first;

                if(up_char != '#') {
                    graph_map.add_one_way_edge(curr_index, up_index, 1);
                }
                if(down_char != '#') {
                    graph_map.add_one_way_edge(curr_index, down_index, 1);
                }
                if(left_char != '#') {
                    graph_map.add_one_way_edge(curr_index, left_index, 1);
                }
                if(right_char != '#') {
                    graph_map.add_one_way_edge(curr_index, right_index, 1);
                }

            }
        }

        dijkstra(graph_map, start_index);

        for(Node* node : graph_map.get_nodes()) {
            cout << "node index: " << node->get_index() << " " << node->get_value() << endl;
        }
        //cout << endl;

        // Start value fist at start, reset, then first A, next A osv.
        int distances_length = alien_node_indexes.size()+1;

        //vector<vector<int>> dist_to_aliens(distances_length, vector<int>(distances_length, -1));


        // Kruskals
        vector<int> parents(distances_length);
        iota(parents.begin(), parents.end(), 0);
        vector<int> union_sizes(distances_length, 1);

        // set of edges: cost, (from - to)
        set<pair<int, pair<int, int>>> edges;
        for(int from_index = -1; from_index < distances_length; from_index++) {
            int to_index = from_index +1;
            if(from_index == -1) {
                dijkstra(graph_map, start_index);
            } else {
                graph_map.graph_reset();
                dijkstra(graph_map, alien_node_indexes[from_index]);
            }
            while(to_index < distances_length) {
                //int cost = dist_to_aliens[from_index][to_index];
                int cost = graph_map.get_node(alien_node_indexes[to_index])->get_value();
                edges.insert({cost, {from_index+1, to_index+1}});
                //cout << cost << endl;
                to_index++;
            }
        }
        cout << "NUM EDGES: " << edges.size();
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
