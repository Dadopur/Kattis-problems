#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

/**
 * @brief Seperates a input string with spaces into a vector.
 *
 * @param str
 * @return vector<string>
 */
vector<string> separate_string (string str) {
    stringstream ss{str};
    // Iterates over ss and puts every word into a vector<string> (through constructor)
    return { istream_iterator<string>{ ss }, istream_iterator<string>{}  };
}


long sum_fenwick(vector<long>fenwick_tree, int index) {
    // Increment index because fenwick starts at index 1 not 0.
    long sum = 0;
    while(index > 0) {
        sum += fenwick_tree[index];
        // Flip the lowest significant 1 to a 0. This acts as going to a lower layer of the tree.
        index -= (index & (-index));
    }
    return sum;
}

vector<long> add_fenwick(vector<long> fenwick_tree, int fenwick_length, int index, int add_value) {
    // Increment index because fenwick starts at index 1 not 0
    index++;
    while(index < fenwick_length) {
        fenwick_tree[index] += add_value;
        // Step to a higher layer that uses sum of position current index.
        index += (index & (-index));
    }
    return fenwick_tree;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string input;
    getline(cin, input);
    vector<string> split_input = separate_string(input);
    string arg1 = split_input[0];
    string arg2 = split_input[1];
    // Fenwick structure start at intiger 1 instead of 0
    int fenwick_length = stoi(arg1) + 1;
    int num_operations = stoi(arg2);

    vector<long> fenwick_tree(fenwick_length+1, 0);
    
    for(int i = 0; i < num_operations; i++) {
        getline(cin, input);
        split_input = separate_string(input);
        // Two cases, one where
        if(split_input[0] == "?") {
            int index = stoi(split_input[1]);
            long sum = sum_fenwick(fenwick_tree, index);
            cout << sum << "\n";

        } else {
            int index = stoi(split_input[1]);
            long add_value = stoi(split_input[2]);
            fenwick_tree = add_fenwick(fenwick_tree, fenwick_length, index, add_value);
        }
    }
}