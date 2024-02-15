
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int rounds;
    cin >> rounds;
    for(int round = 0; round < rounds; round++){
        int squares, prince, princess;
        cin >> squares >> prince >> princess;
        vector<int> prince_moves(prince, -1);
        int move;
        for(int i = 0; i < prince; i++){
            cin >> move;
            prince_moves[i] = move;            
        }

        vector<int> princess_moves(princess, -1);
        for(int i = 0; i < princess; i++){
            cin >> move;
            princess_moves[i] = move;
        }

        // check dynamic backtracking what is best.
    }
}