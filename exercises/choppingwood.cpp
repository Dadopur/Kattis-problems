#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <array>
#include <set>
using namespace std;


/**
 * @brief Main function, takes input from terminal and outputs answer to terminal.
 * Takes a V list and tries to compute the U list.
 *
 * @return int
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string input;
    getline(cin, input);
    int num_nodes = stoi(input);

    // No input got
    if(num_nodes == 0) {
        cout << "Error" << "\n";
        return 0;
    }

    // Make basic lists
    vector<int> degree(num_nodes+1);
    vector<int> v(num_nodes);

    // Take out numbers from terminal and put them in degree and v.
    for(int i = 0; i < num_nodes; i++) {
        getline(cin, input);
        int curr_node = stoi(input);

        // We have a bigger input than should exist
        if(curr_node > (num_nodes + 1)) {
            cout << "Error" << "\n";
            return 0;
        }

        // Add to v
        v[i] = curr_node;

        // Add to degrees (-1 for index starts at 0)
        int deg_index = curr_node - 1;
        degree[deg_index] += 1;

    }

    // Last element in the input stream is not the biggest node.
    if(v[v.size()-1] != (num_nodes + 1)) {
        cout << "Error" << "\n";
        return 0;
    }

    // Insert leaves (nodes that have degree 0)
    set<int> leaves; // Set sorts leaves, smallest leaf first
    for(unsigned i = 0; i < degree.size(); i ++) {
        if(degree[i] == 0){
            leaves.insert(i);
        }
    }

    // Make the u list
    int k = 0;
    while(leaves.size() != 0 && k < num_nodes) {
        // Take top (smalles) leaf and remove it from leaves
        int top_leaf = *leaves.begin();
        leaves.erase(top_leaf);

        // Print smallest leaf
        cout << to_string(top_leaf + 1) << "\n";
        // Get new degree
        int upd_deg = degree[v[k]-1] - 1;
        // Update leaves if needed
        if(upd_deg == 0) {
            leaves.insert(v[k]-1);
        }
        // Update degree list
        degree[v[k]-1] = upd_deg;
        k++;
    }
    return 0 ;
}