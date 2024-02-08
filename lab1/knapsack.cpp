#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

struct Item
{
    int weight, value, index;
};

vector<int> knapsack(vector<Item> items, int capacity) {
    int num_items = items.size();

    vector<vector<int>> grid(num_items+1, vector<int>(capacity, 0));
    
    // Fill the grid (the sack with all cases)
    for(auto item : items) {
        for(int curr_capacity = 1; curr_capacity <= capacity; curr_capacity++) {
            // Initialize useful variables
            int value_of_pos = 0; // default value 0
            int item_index = item.index;
            int item_value = item.value;
            int item_weight = item.weight;

            cout <<"index "<< item_index << "value " << item_value << "weight " << item_weight << endl;
            // Position value should not be 0
            if(curr_capacity >= item_weight) {
                // Update with prev grid value on best path
                int prev_grid_side_value = grid[item_index-1][capacity-item_weight];
                int prev_grid_value = grid[item_index-1][capacity];
                cout << "FETT GAY" << endl;
                if(prev_grid_side_value > prev_grid_value){
                    value_of_pos = item_value + prev_grid_side_value;
                } else {
                    value_of_pos = prev_grid_value;
                }
            }
            cout << "val " << value_of_pos<< endl;
            // Update grid value
            grid[item_index][curr_capacity] = value_of_pos;
        }
    }
    
    for(auto i : grid){
        for(int l : i) {
            cout << l << endl;
        }
    }

    vector<int> items_in_sack;
    int curr_capacity = capacity;
    // Back tracking to find optimal path.
    for(int index = num_items; index > 0; index--) {
        Item item = items[index-1];
        int weight = item.weight;

        int curr_value = grid[index][curr_capacity];
        //cout << "HERE "<<weight<<" "<<index << endl;
        if(curr_capacity >= weight) {
            int next_value_side = grid[index-1][curr_capacity-weight];
            int next_value_straight = grid[index-1][curr_capacity];

            if(next_value_side > next_value_straight) {
                curr_capacity -= weight;
                items_in_sack.push_back(index);
            }
        }
    }
    return items_in_sack;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int capacity;
    int num_items;
    while(cin >> capacity >> num_items) {
        int value;
        int weight;
        vector<Item> items;
        for(int i = 0; i < num_items; i++) {
            cin >> value >> weight;
            // Make item with its specific values, index +1 for right index
            Item t{ weight, value, i + 1 };
            items.push_back(t);
        }
        vector<int> items_in_sack = knapsack(items, capacity);
        cout << items_in_sack.size() << "\n";
        for(int item : items_in_sack) {
            cout << item << "\n";
        }
    }
}