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

    int list_length = stoi(input);
    
    vector<int> indexes(list_length);
    
    long fenwick_tree[list_length+1] = {0};
    // Compute operations for each line
    for(int i = 0; i < list_length; i++) {
        cin >> input;
        int number = stoi(input);
        // Add what number has what index, where every element represents each number (shifted by -1)
        indexes[number-1] = i;
        // Set all element to 1 in tree
        update_fenwick(fenwick_tree,list_length +1, i ,1);
    }
    int iteration = 0; // Iteration to know if even or odd
    int k = 0; // keep track what number we are on, also used for odd (N-k).
    while(iteration < list_length) {
        int swaps = 0;
        // Even
        if(iteration % 2 == 0) {
            int index = indexes[k]; // Get what index current number has
            // Update that current pos has been visited and shifted down.
            update_fenwick(fenwick_tree, list_length+1, index, -1);
            // Get how many shifts it takes to do down all the way. (number of elements down)
            swaps = sum_fenwick(fenwick_tree, index);
            k++;

        // Odd
        } else {
            int index = indexes[list_length - k]; // get what index current number has
            // Update that current pos has been visited and shifted up.
            update_fenwick(fenwick_tree, list_length+1, index, -1);
            // How many shift up do go all the way up.
            swaps = sum_fenwick(fenwick_tree, list_length) - sum_fenwick(fenwick_tree, index);
        }
        cout << swaps << "\n";
        iteration++;
    }
}