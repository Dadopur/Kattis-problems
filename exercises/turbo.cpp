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
    // Fenwick structure
    int list_length = stoi(input);

    int indexes[list_length-1];

    // Initiate all elements to 0
    long fenwick_tree[list_length] = {1};

    // Compute operations for each line
    for(int i = 0; i < list_length; i++) {
        cin >> input;
        int number = stoi(input);
        indexes[number] = i
    }

    // Get word length for each of the stuff
    for(int i = 0; i < list_length; i++) {
        int index = 1; //index switches, 1, N, 2, N-1, 3, N-2 ...
        update_fenwick(fenwick_tree, list_length, , )

        // Set index i to 0 and count up (up) or down (up-down)
        // Maybe do a while loop instead, 1 N, 2 N-1, 3, N-2
    }
}