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
    
    return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int rounds;
    cin >> rounds;
    for(int i = 0; i < rounds; i++) {
        int priests;
        cin >> priests;
        bitset<3> stones; 
        for(int priest = 0; priest < priests; priest++) {
            for(int k = 0; k < 8; k++){ // MAKE K A LIST OF ALL CHOICES FOR EVERY PRIEST; THEN WE CAN BREAK (we take inputs now per line)
                int choice;
                cin >> choice;
                bitset<3> optimal_stones(choice-1);
                cout << "priest " << priest << endl;
                cout << "bit: " << optimal_stones << endl;
                int swap = flip_stone(stones, optimal_stones);
                cout << "SWAP " << swap << endl;
                if (swap == -1){
                    continue;
                } else {
                    //cout << "BEFORE flipped: " << stones << endl;
                    stones.flip(swap);
                    //cout << "AFTER flipped: " << stones << endl;
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