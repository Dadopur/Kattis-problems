/**
 * @file union-find.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Problem solved is disjoint sets with the union-find problem. This is a problem where
 * unions can be made between disjoint sets and two elements can be compared to see if they are 
 * in the same union. These operations are done in amortized time complexity O(log(N)) through
 * path compression and merging on size. 
 * @version 0.1
 * @date 2024-02-14
 */

// Imports
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Recursive find of root node for a integer in a collection of (disjoint) sets.
 * 
 * @param parents Vector of all parents for each element in the collection of (disjoint) sets.
 * @param a Integer which root is to be found.
 * @return int of root node for element a.
 */
int find_root(vector<int> parents, int a) {
    if(parents[a] == a) {
        // Root has itself as parent
        return a;
    } else {
        // Find the root for parent of a to be used in path compression 
        int root = find_root(parents, parents[a]);
        parents[a] = root;
        return root;
    }
}

/**
 * @brief Check if a and b are in the same union.
 * 
 * @param parents Vector of all parents for each element in the collection of (disjoint) sets.
 * @param a Integer of first element to be compared with b.
 * @param b Integer of secound element to be compared with a.
 * @return true if a and b are in same union,
 * @return false otherwise.
 */
bool find(vector<int> parents, int a, int b) {
    // Same root means same union
    if(find_root(parents, a) == find_root(parents, b)){
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Merge two unions (of a and b) if possible.
 * 
 * @param parents Vector of all parents for each element in the collection of (disjoint) sets.
 * @param union_sizes Vector of all union sizes. 
 * @param a Integer (element) which root union is to be merged with root union of b.
 * @param b Integer (element) whoch root union is to be merged with root union of a.
 */
void merge_unions(vector<int> parents, vector<int> union_sizes, int a, int b) {
    // Fint root nodes
    int root_a = find_root(parents, a);
    int root_b = find_root(parents, b);

    // Same union - do nothing
    if(root_a == root_b){
        return;
    }

    // Get union sizes
    int size_a = union_sizes[root_a];
    int size_b = union_sizes[root_b];

    // Merge smaller union into larger one -> less path compression later
    if(size_a >= size_b) {
        parents[root_b] = root_a;
        union_sizes[root_a] += size_b;
    } else {
        parents[root_a] = root_b;
        union_sizes[root_b] += size_a;
    }
}

/**
 * @brief Main function executing union-find operations on a set of numbers given in the terminal.
 * 
 * @return int 
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<int> parents(N);
    vector<int> union_sizes(N, 1);
    for(int operation = 0; operation < Q; Q++) {
        char op;
        int first_num, second_num;
        cin >> op >> first_num >> second_num;
        if (op == '?') {
            bool same_union = find(parents, first_num, second_num);
            if(same_union){
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        } else {
            merge_unions(parents, union_sizes, first_num, second_num);
        }
    }
}