#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
using namespace std;

struct Node {
    int index;
    // Maybe change to pair instead of 2 seperate vectors
    vector<Node*> connections;
    vector<int> edge_costs;
};

bool node_value_compare(pair<int, int> node1, pair<int, int> node2) {
    return (get<1>(node1) < get<1>(node2));
}

vector<pair<int, int>> dijkstra(vector<Node*>& nodes, int start_node_index) {
    // Pair of (prev_index, curr_value) 
    vector<pair<int, int>> table(nodes.size(), {0, numeric_limits<int>::max()});
    vector<int> visited_nodes;

    Node* start_node = nodes[start_node_index];
    table[start_node_index].second = 0;

    // Go through all edges in start node and update next node_index (value = edge_cost + curr_value)
    // Add curr node index to visited nodes, go to next node in 
    // dont go back and update/ check already visited nodes.

    // Use a set, the we need to have a tuple/ 3 long array cuz index will change.
    vector<pair<int, int>>::iterator next_node = min_element(table.begin(), table.end(), node_value_compare);

    return table;
} 

void add_node(vector<Node*>& nodes, int node1, int node2, int weight) {
    // Add nodes if not initialized
    if(nodes[node1] == nullptr) {
        nodes[node1] = new Node{node1};
    }

    if(nodes[node2] == nullptr) {
        nodes[node2] = new Node{node2};
    }

    // Add connections and edge costs
    Node* primary_node = nodes[node1];
    Node* secundary_node = nodes[node2];
    
    primary_node->connections.push_back(secundary_node);
    secundary_node->connections.push_back(primary_node);

    primary_node->edge_costs.push_back(weight);
    secundary_node->edge_costs.push_back(weight);
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, q, s;
    while((cin >> n >> m >> q >> s) && !(n==0 && m==0 && q==0 && s==0)) {
        vector<Node*> nodes(n, nullptr);
        int node1, node2, weight;
        for(int i = 0; i < m; i++) {
            cin >> node1 >> node2 >> weight;
            add_node(nodes, node1, node2, weight); 
        }

    }
}