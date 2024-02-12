#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<vector<int>> FLIP_OUTCOMES = {
        vector<int>{1, 2, 4},
        vector<int>{0, 3, 5},
        vector<int>{0, 3, 6},
        vector<int>{1, 2, 7},
        vector<int>{0, 5, 6},
        vector<int>{1, 4, 7},
        vector<int>{2, 4, 7},
        vector<int>{3, 5, 6}
    };
    int rounds;
    cin >> rounds;
    // How many test cases/ rounds will go down.
    for(int i = 0; i < rounds; i++) {
        int priests;
        cin >> priests;
        // Initiate all grid values to 0 at first
        vector<vector<int>> stone_outputs(priests, vector<int>(8, 0));
        vector<int> temp;
        for(int n = 0; n < 8; n++) {
            temp.push_back(n);
        }
        stone_outputs.push_back(temp);

        vector<vector<int>> choices;
        // One priest at a time.
        for(int priest = 0; priest < priests; priest++) {
            vector<int> temp_choice(8,0);
            // Get the priests prefered answers
            for(int k = 0; k < 8; k++){
                int choice;
                cin >> choice;
                temp_choice[k] = choice-1;
            }
            choices.push_back(temp_choice);
        }

        for(int priest = priests-1; priest <= 0; priest++){
            // Fill out what priest will output for what input (input/output in binary 3 stones)
            for(int stone_input = 0; stone_input < 8; stone_input++){ // Stone combination
                // Find best output choice
                int best_choice;
                int best_index;
                for(int flip_value : FLIP_OUTCOMES[stone_input]) {
                    vector<int> choice_vector = choices[priest];
                    int prev_priest_choice = stone_outputs[priest+1][flip_value];
                    auto iter = find(choice_vector.begin(), choice_vector.end(), prev_priest_choice);
                    int index = iter - choice_vector.begin(); 
                    if(index < best_index) {
                        best_index = index;
                        best_choice = prev_priest_choice;
                    }
                }
                stone_outputs[priest][stone_input] = best_choice;
            }
        }

        cout << endl;
        for(auto i: stone_outputs){
            for(auto n : i) {
                cout << n << " ";
            }
            cout << endl;
        }

        int out = stone_outputs[0][0];

        switch (out) {
            case 0:
                cout << "NNN\n";
                break;
            case 1:
                cout << "NNY\n";
                break;
            case 2:
                cout << "NYN\n";
                break;
            case 3:
                cout << "NYY\n";
                break;
            case 4:
                cout << "YNN\n";
                break; 
            case 5:
                cout << "YNY\n";
                break;
            case 6:
                cout << "YYN\n";
                break;
            case 7:
                cout << "YYY\n";
                break;
            default:
                break;
        }
    }
}