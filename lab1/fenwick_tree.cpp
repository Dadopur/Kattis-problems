/**
 * @file fenwick_tree.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Takes in operations and executes them on a fenwick tree.
 * @version 0.1
 * @date 2024-02-01
 *
 * A fenwick tree is a array/list of length N that can be represented as a tree.
 * It is done by combining the sum of different parts of the array and storing them in
 * indexes of powers of 2. The first part is to pair up elements of index 2^0,
 * meaning 1-2, 3-4, 5-6 and so on get paird up. This means that 2 has sum of 1 and 2, 4 has sum om 3 and 4,
 * but 1,3,5 has thier own value. Then indexes 2^1: 2-4, 6-8 and so on.
 * This goes on till the 2^M where M is the biggest power of 2 in N.
 *
 * This property gives it the ability to sum up values up to index i with complexity O(Nlog(N)).
 * It also has complexity of O(Nlog(N)) when changing a value in the tree.
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;


/**
 * @brief Sums all elements up to index index. Has time complexity O(Nlog(N)).
 *
 * @param index
 * @return long
 */
long sum_fenwick(long fenwick_tree[], int index) {
    long sum = 0;
    // Sum tills we cannot sum anymore (smalles bigroup summed)
    while(index > 0) {
        sum += (fenwick_tree)[index];
        // Flip the lowest significant 1 to a 0. This acts as going to a lower layer of the tree.
        index -= (index & (-index));
    }
    return sum;
}

/**
 * @brief Updates the fenwick tree by adding a value to position index. Has time complexity O(Nlog(N)).
 *
 * @param fenwick_tree
 * @param fenwick_length
 * @param index
 * @param add_value
 * @return void
 */
void update_fenwick(long fenwick_tree[], int fenwick_length, int index, int add_value) {
    // Increment index because fenwick starts at index 1 not 0
    index++;
    // Stop when we have gone to the highest layer of the tree (cannot be longer than actual length)
    while(index < fenwick_length) {
        (fenwick_tree)[index] += add_value;
        // Step to a higher layer that uses sum of position current index.
        index += (index & (-index));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string input;
    // Get first input (N, Q) were N is length of fenwick vector and Q numer of operations
    cin >> input;
    // Fenwick structure start at intiger 1 instead of 0
    int fenwick_length = stoi(input) + 1;
    cin >> input;
    int num_operations = stoi(input);

    // Initiate all elements to 0
    long fenwick_tree[fenwick_length] = {0};

    // Compute operations for each line
    for(int i = 0; i < num_operations; i++) {
        cin >> input;
        // Sum operation is used
        if(input == "?") {
            // Get input parameter
            cin >> input;
            int index = stoi(input);
            // Get sum up to index index
            long sum = sum_fenwick(fenwick_tree, index);
            // Print to terminal
            cout << sum << "\n";
        // Update vector by addinga integer
        } else {
            // Get input parameters
            cin >> input;
            int index = stoi(input);
            cin >> input;
            long add_value = stoi(input);
            // Update the tree
            update_fenwick(fenwick_tree, fenwick_length, index, add_value);
        }
    }
}