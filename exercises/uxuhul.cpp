#include <iostream>
#include <bitset> 
#include <vector>
using namespace std;

bool flip_stone(bitset<4> stones, bitset<4> choice){
    if(stones.flip(0) == choice) {
        return true;
    }
    stones.flip(0);
    if (stones.flip(1) == choice) {
        return true;
    }
    stones.flip(1);

    if (stones.flip(2) == choice) {
        return true;
    } 
    stones.flip(2);

    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int rounds;
    cin >> rounds;
    // How many test cases/ rounds will go down.
    for(int i = 0; i < rounds; i++) {
        int priests;
        cin >> priests;
        vector<vector<bitset<4>>> stone_outputs(priests, vector<bitset<4>>(8,bitset<4>(4)));
        // Make one priest choice for all priests.
        for(int priest = 0; priest < priests; priest++) {
            vector<int> choices(8,0);
            // Get the priests prefered answers
            for(int k = 0; k < 8; k++){
                int choice;
                cin >> choice;
                choices[k] = choice-1;
            }
            // Fill out what priest will output for what input (input/output in binary 3 stones)
            for(int stone_input = 0; stone_input < 8; stone_input++){ // Stone combination
                for(int choice : choices){ // What the order of wanted result is
                    bitset<4> combination = stone_outputs[priest][stone_input];
                    // If output not set for current stone combination, set it, otherwise go to next combination
                    if(int(combination.to_ulong()) == 4) {
                        bitset<4> optimal_stones(choice);
                        bitset<4> input_stones_bits(stone_input);
                        // Possible to go to current choice from current stones?
                        if(flip_stone(input_stones_bits, optimal_stones)){
                            stone_outputs[priest][stone_input] = optimal_stones;
                        }
                    } else {
                        break;
                    }
                }
            }
        }

        // Go backwards and check if it is possible for this stone combination at the end to exist.
        // Take optimal combination for the last priest that is valid.
        
        int temp;

        switch (temp) {
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