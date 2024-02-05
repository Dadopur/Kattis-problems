#include <iostream>
#include <bitset> 
using namespace std;

int flip_stone(bitset<3> stones, bitset<3> choice){
    if(stones.flip(0) == choice) {
        return 0;
    }
    stones.flip(0);
    if (stones.flip(1) == choice) {
        return 1;
    }
    stones.flip(1);

    if (stones.flip(2) == choice) {
        return 2;
    } 
    stones.flip(2);

    return -1;
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
        bitset<3> stones;
        // Make one priest choice for all priests.
        for(int priest = 0; priest < priests; priest++) {
            int choices[8];
            // Get the priests answers
            for(int k = 0; k < 8; k++){
                int choice;
                cin >> choice;
                choices[k] = choice;
            }
            // Greedy check: take first best answer thats possible to do.
            for(int choice : choices){
                bitset<3> optimal_stones(choice-1);
                int swap = flip_stone(stones, optimal_stones);
                if (swap == -1){
                    continue;
                } else {
                    stones.flip(swap);
                    break;
                }
            }
        }

        switch (int(stones.to_ulong())) {
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