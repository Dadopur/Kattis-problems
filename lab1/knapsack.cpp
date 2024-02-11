#include <iostream>
#include <vector>
using namespace std;

struct Item
{
    int weight, value, index;
};

vector<int> knapsack(vector<Item> items, int capacity) {
    int num_items = items.size();

    vector<vector<int>> grid(num_items+1, vector<int>(capacity+1, 0));
    
    // Fill the grid (the sack with all cases)
    for(auto item : items) {
        for(int curr_capacity = 1; curr_capacity <= capacity; curr_capacity++) {
            // Initialize useful variables
            int item_index = item.index;
            int item_value = item.value;
            int item_weight = item.weight;
            int value_of_pos = grid[item_index-1][curr_capacity]; // default value of prev grid same capacity
            
            // Position value should not be 0
            if(curr_capacity >= item_weight) {
                // Update with prev grid value on best path
                int prev_grid_side_value = grid[item_index-1][curr_capacity-item_weight] + item_value;
                //cout << prev_grid_side_value << " " << prev_grid_value << endl;
                if(prev_grid_side_value > value_of_pos){
                    value_of_pos = prev_grid_side_value;
                }
            }
            // Update grid value
            grid[item_index][curr_capacity] = value_of_pos;
        }
    }

    vector<int> items_in_sack;
    int curr_capacity = capacity;

    // Back tracking to find optimal path.
    for(int index = num_items-1; index >= 0; index--) {
        Item item = items[index];
        int weight = item.weight;

        int curr_value = grid[index+1][curr_capacity];
        // Space in sack to add item
        if(curr_capacity >= weight) {
            int next_value_straight = grid[index][curr_capacity];
            // Adding curr item gives more value than not adding
            if(curr_value > next_value_straight) {
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
        for(auto item = items_in_sack.rbegin(); item != items_in_sack.rend(); ++item) {
            cout << *item << " ";
        }
        cout << "\n";
    }
}