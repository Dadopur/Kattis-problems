#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

struct Item
{
    int weight, value;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int capacity;
    int num_items;
    while(cin >> capacity >> num_items) {
        int value;
        int weight;
        vector<Item> items(num_items);
        for(int i = 0; i < num_items; i++) {
            cin >> value >> weight;
            Item t{ weight, value };
            items.push_back(t);
        }
    }
}