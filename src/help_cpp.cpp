#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

enum Swap_case { do_nothing, swap_first, swap_second, not_same };

/**
 * @brief Seperates a input string with spaces into a vector.
 *
 * @param str
 * @return vector<string>
 */
vector<string> separate_string (string str) {
    stringstream ss{str};
    // Iterates over ss and puts every word into a vector<string> (through constructor)
    return { istream_iterator<string>{ ss }, istream_iterator<string>{}  };
}

/**
 * @brief Formats a string vector to a string diving words with a space.
 *
 * @param str_vec
 * @return string
 */
string output_string(vector<string> str_vec) {
    string str;
    for(auto elem : str_vec) {
            str += elem + " ";
    }
    str.pop_back();
    return str;
}

/**
 * @brief Return the current state of the given pair string.
 *
 * @param first
 * @param second
 * @return Swap_case
 */
Swap_case check_pair(string first, string second) {
    bool first_is_placeholder = first[0] == '<';
    bool second_is_placeholder = second[0] == '<';

    if(first_is_placeholder && second_is_placeholder){
        return do_nothing;
    } else if(first_is_placeholder && !second_is_placeholder) {
        return swap_first;
    } else if(!first_is_placeholder && second_is_placeholder) {
        return swap_second;
    } else if(first != second) {
        return not_same;
    }

    // case where first and second are same
    return do_nothing;
}

/**
 * @brief Goes through both lists and changes/ swaps the the placeholders if possible.
 *
 * @param first_row
 * @param second_row
 * @return string
 */
string check_whole_lists(vector<string> first_row, vector<string> second_row) {
    int i = 0;
    while(i < first_row.size()) {
        string first = first_row[i];
        string second = second_row[i];
        i++;
        Swap_case case_number = check_pair(first, second);

        switch(case_number)
        {
            case do_nothing:
                // Both paceholders or same words, go to next pair.
                continue;
                break;

            case swap_first:
                for(int k = 0; k < first_row.size(); k++){
                    if(first_row[k] == first){
                        first_row[k] = second;
                    }
                }
                // Reset to check all pairs from beginning.
                i = 0;
                break;

            case swap_second:
                for(int k = 0; k < second_row.size(); k++){
                    if(second_row[k] == second){
                        second_row[k] = first;
                    }
                }
                // Reset to check all pairs from beginning.
                i = 0;
                break;

            case not_same:
                return "-";
                break;

            default:
                return "-";
                break;

        }
    }
    // replace placeholders with random word (placeholder).
    for(int i = 0; i < first_row.size(); i++) {
        if(first_row[i][0] == '<'){
            first_row[i] = "placeholder";
        }
    }
    return output_string(first_row);

}

/**
 * @brief Main function, takes input from terminal and outputs answer to terminal.
 *
 * @return int
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string input;
    getline(cin, input);
    int testcases = stoi(input);

    for(int i = 0; i < testcases; i++) {
        // Divide first and second rows into vectors of strings (words).
        vector<string> first_row;
        vector<string> second_row;
        getline(cin, input);
        first_row = separate_string(input);
        getline(cin, input);
        second_row = separate_string(input);
        // Checks for easy cases. Not the same length and no length.
        if(first_row.size() != second_row.size()) {
            cout << "-" << "\n";
            continue;
        } else if(first_row.size() == 0) {
            cout << "" << "\n";
            continue;
        }
        string output = check_whole_lists(first_row, second_row);
        cout << output << "\n";
    }
}