#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string prev_animal;
    int choices_left;
    cin >> prev_animal >> choices_left;

    vector<int> chars_first(26, 0);
    vector<string> potential_animals;
    string next_animal;
    for(int i = 0; i < choices_left; i++) {
        cin >> next_animal;
        if(next_animal[0] == prev_animal.back()) {
            potential_animals.push_back(next_animal);
        }
        // Increace the count for this first character of the string
        int char_num = ((int) next_animal[0] - 97);
        chars_first[char_num] += 1;
    }

    if(potential_animals.size() == 0){
        cout << "?\n";
    } else {
        string output_animal = "unknown";
        for(auto animal : potential_animals) {
            // check if there is a case where last char not existing as first char.
            int char_num_back = ((int) animal.back() - 97);
            int char_num_front = ((int) animal[0] - 97);
            chars_first[char_num_front] -= 1;

            if(chars_first[char_num_back] == 0) {
                output_animal = animal;
                break;
            }
            chars_first[char_num_front] += 1;
        }
        if(output_animal == "unknown") {
            cout << potential_animals[0] << "\n";
        } else {
            cout << output_animal << '!' << "\n";
        }
    }
}