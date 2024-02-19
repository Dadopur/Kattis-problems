#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Node {
    int value; 
    // Maybe change to pair instead of 2 seperate vectors
    vector<Node*> connections;
    vector<int> edge_costs;
};





void add_node(vector<Node*>& nodes, int node1, int node2, int weight) {
    // Add nodes if not initialized
    if(nodes[node1] == nullptr) {
        nodes[node1] = new Node{numeric_limits<int>::max()};
    }

    if(nodes[node2] == nullptr) {
        nodes[node2] = new Node{numeric_limits<int>::max()};
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

        for(int i = 0; i < n; i++){
            Node* a = nodes[i];
            cout << a << endl;
            if(a != nullptr) {
                cout <<"size: " << a ->connections.size() << " ";
                cout << "value: " << a->value << " ";
            }
            cout << endl;
        }
    }
}