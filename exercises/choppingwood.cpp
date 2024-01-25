#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <array>
using namespace std;


/**
 * @brief Main function, takes input from terminal and outputs answer to terminal.
 *
 * @return int
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string input;
    getline(cin, input);
    int num_nodes = stoi(input);

    if(num_nodes == 0) {
        cout << "Error" << "\n";
        return;
    }

    vector<int> degree(num_nodes+1);
    vector<int> u(num_nodes+1);


    for(int i = 0; i < num_nodes; i++) {
        getline(cin, input);
        int curr_node = stoi(input);
        degree[curr_node] += 1;
        if(i == num_nodes -1 && curr_node != num_nodes + 1) {
            cout << "Error" << "\n";
            return;
        }
    }

    for(int i = 0; i < num_nodes + 1; i++) {
        if(degree[i] == 0){
            degree[i] -= 1;
            u.push_back(i);
            i = 0;
        }
    }



    return;
}