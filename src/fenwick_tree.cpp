/**
 * @file fenwick_tree.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Takes in operations and executes them on a fenwick tree.
 * @version 0.1
 * @date 2024-02-01
 *
 * A fenwick tree is a array/list of length N that can be represented as a tree and used
 * for its fast updates and summations.
 * It is done by combining the sum of different parts of the array and storing them in
 * indexes of powers of 2. The first part is to pair up elements of index 2^0,
 * meaning 1-2, 3-4, 5-6 and so on get paird up. This means that 2 has sum of 1 and 2, 4 has sum om 3 and 4,
 * but 1,3,5 has thier own value. Then indexes 2^1: 2-4, 6-8 and so on.
 * This goes on till the 2^M where M is the biggest power of 2 in N.
 *
 * This property gives it the ability to sum up values up to index i with complexity O(log(N)).
 * It also has complexity of O(Nlog()) when changing a value in the tree. This is because the array is
 * divided in group of 2 down to the last layer. The problem also uses memory as big as input array O(N).
 * 
 * 
 * TODO: Add support for input of a vector and make a fenwick tree in constructor.
 */

#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
public:
    /**
     * @brief Construct a new Fenwick Tree object
     * 
     * @param fenwick_length length of fenwicktree.
     */
    FenwickTree(const int fenwick_length) {
        // Fenwick structure start at intiger 1 instead of 0
        fenwick_tree = vector<long>(fenwick_length + 1, 0);
    }

    /**
     * @brief Sum all elements up to index index. Has time complexity O(Nlog(N)).
     *
     * @param index Index to be upped up to.
     * @return long that is summation of all values up till index.
     */
    long sum_fenwick(int index) {
        long sum = 0;
        // Sum tills we cannot sum anymore (smalles bigroup summed)
        while(index > 0) {
            sum += fenwick_tree[index];
            // Flip the lowest significant 1 to a 0. This acts as going to a lower layer of the tree.
            index -= (index & (-index));
        }
        return sum;
    }

    /**
     * @brief Sum all elements in a given range. 
     * 
     * @param index1 Start of interval. 
     * @param index2 End of interval.
     * @return long sum of interval. Gives value of index if index1 = index2.
     */
    long ranged_sum(int index1, int index2) {
        // Give index of given index
        if(index1 = index2) {
            return sum_fenwick(index1) - sum_fenwick(index1 - 1);
        }

        return (sum_fenwick(index2) - sum_fenwick(index1));
        
    }

    /**
     * @brief Update the fenwick tree by adding a value to position index. Has time complexity O(Nlog(N)).
     *
     * @param index Index that is to be updated.
     * @param add_value Value that is to be added on in position Index.
     * @return void
     */
    void update_fenwick(int index, int add_value) {
        // Increment index because fenwick starts at index 1 not 0
        index++;
        // Stop when we have gone to the highest layer of the tree (cannot be longer than actual length)
        while(index < fenwick_tree.size()) {
            fenwick_tree[index] += add_value;
            // Step to a higher layer that uses sum of position current index.
            index += (index & (-index));
        }
    }

private:
    vector<long> fenwick_tree;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Get first input (N, Q) were N is length of fenwick vector and Q numer of operations
    int fenwick_length;
    int num_operations;
    cin >> fenwick_length >> num_operations;

    // Initiate the fenwick tree
    FenwickTree fenwick_tree(fenwick_length);

    // Variables used for inputs
    string operation;
    int index;
    long add_value;

    // Compute operations for each line
    for(int i = 0; i < num_operations; i++) {
        cin >> operation;
        // Sum operation is used
        if(operation == "?") {
            cin >> index;
            long sum = fenwick_tree.sum_fenwick(index);
            cout << sum << "\n";
        // Update vector by addinga integer
        } else {
            cin >> index >> add_value;
            fenwick_tree.update_fenwick(index, add_value);
        }
    }
}