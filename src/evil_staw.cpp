#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int test_cases;
    cin >> test_cases;
    for(int test = 0; test < test_cases; test++) {
        string s;
        cin >> s;
        unordered_map<char, int> freq;
        for(char c : s) {
            freq[c]++;
        }
        int odd_count = 0;
        for(auto it = freq.begin(); it != freq.end(); it++) {
            if(it->second % 2 != 0) {
                odd_count++;
            }
        }
        if(odd_count > 1) {
            cout << "Impossible\n";
            continue;
        }

        int left_fixed = 0;
        int right_fixed = s.size() - 1;
        int num_swaps = 0;
        vector<char> word(s.begin(), s.end());

        while(left_fixed < right_fixed) {
            int right_pointer = right_fixed;
            while(word[right_pointer] != word[left_fixed]) {
                right_pointer--;
            }
            if(right_pointer == left_fixed) {
                char temp = word[right_pointer];
                word[right_pointer] = word[right_pointer + 1];
                word[right_pointer + 1] = temp;
                num_swaps++;
                continue;
            }
            while(right_pointer < right_fixed) {
                char temp = word[right_pointer];
                word[right_pointer] = word[right_pointer + 1];
                word[right_pointer + 1] = temp;
                num_swaps++;
                right_pointer++;
            }
            right_fixed--;
            left_fixed++;
        }
        cout << num_swaps << "\n";
    }
}