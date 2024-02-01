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
void update_fenwick(long fenwick_tree[], int fenwick_length, int index, long add_value) {
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
    long fenwick_tree[list_length+1];// = {1};
    // Compute operations for each line
    for(int i = 0; i < list_length; i++) {
        cin >> input;
        int number = stoi(input);
        indexes[number] = i;
        // Set all element to 1 in tree
        fenwick_tree[i] = 1;
    }

    fenwick_tree[list_length] = 1;
    fenwick_tree[list_length + 1] = 1;


    // Get word length for each of the stuff
    int iteration = 0;
    while(iteration < list_length) {
        int swaps = 0;
        if(iteration % 2 == 0) {
            // Add 1 because fenwick start from 1
            int index = iteration + 1;
            update_fenwick(fenwick_tree, list_length, index, -1);
            swaps = sum_fenwick(fenwick_tree, index);
        } else {
            int index = list_length + 2 - iteration;
            update_fenwick(fenwick_tree, list_length, index, -1);
            swaps = sum_fenwick(fenwick_tree, index) - sum_fenwick(fenwick_tree, list_length);
        }
        cout << swaps << "\n";
        iteration++;
        // Set index i to 0 and count up (up) or down (up-down)
        // Maybe do a while loop instead, 1 N, 2 N-1, 3, N-2
    }
}