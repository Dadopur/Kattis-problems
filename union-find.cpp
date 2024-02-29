/**
 * @file union-find.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Problem solved is disjoint sets with the union-find problem. This is a problem where
 * unions can be made between disjoint sets and two elements can be compared to see if they are 
 * in the same union. These operations are done in amortized time complexity O(a(log(N))) which is practicly
 * constant amortized time. This is done through path compression and merging based on union size. 
 * @version 0.1
 * @date 2024-02-14
 */

// Imports
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class UnionFind {
public:

    /**
     * @brief Construct a new Union Find object
     * 
     * @param N number of unions at start
     */
    UnionFind(int const N) {
        // Initialize parent nodes and sizes of disjoint unions
        parents = vector<int>(N);
        iota(parents.begin(), parents.end(), 0);
        union_sizes = vector<int>(N, 1);
    }

    /**
     * @brief Recursive find of root node for a integer in a collection of (disjoint) sets.
     * 
     * @param a Integer which root is to be found.
     * @return int of root node for element a.
     */
    int find_root(int a) {
        if(parents[a] == a) {
            // Root has itself as parent
            return a;
        } else {
            // Find the root for parent of a to be used in path compression 
            int root = find_root(parents[a]);
            parents[a] = root;
            return root;
        }
    }

    /**
     * @brief Check if a and b are in the same union.
     * 
     * @param a Integer of first element to be compared with b.
     * @param b Integer of secound element to be compared with a.
     * @return true if a and b are in same union,
     * @return false otherwise.
     */
    bool same(int a, int b) {
        // Same root means same union
        return (find_root(a) == find_root(b));
    }

    /**
     * @brief Merge two unions (of a and b) if possible.
     * 
     * @param a Integer (element) which root union is to be merged with root union of b.
     * @param b Integer (element) whoch root union is to be merged with root union of a.
     */
    void merge_unions(int a, int b) {
        // Fint root nodes
        int root_a = find_root(a);
        int root_b = find_root(b);

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
private:
    // Vector of all parents for each element in the collection of (disjoint) sets.
    vector<int> parents;
    vector<int> union_sizes;
};

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
    
    UnionFind union_find(N);
    
    for(int operation = 0; operation < Q; operation++) {
        char op;
        int first_num, second_num;
        cin >> op >> first_num >> second_num;
        if (op == '?') {
            bool same_union = union_find.same(first_num, second_num);
            if(same_union){
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        } else {
            union_find.merge_unions(first_num, second_num);
        }
    }
}