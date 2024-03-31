#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <utility>
#include <map>
//#include <bitset>
using namespace std;

vector<string> separate_string (string str) {
    stringstream ss{str};
    // Iterates over ss and puts every word into a vector<string> (through constructor)
    return { istream_iterator<string>{ ss }, istream_iterator<string>{} };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tests;
    cin >> tests;
    for(int test = 0; test < tests; test++) {
        int variables, clauses;
        cin >> variables >> clauses;

        vector<pair<vector<bool>, vector<bool>>> clauses_vector(clauses, make_pair(vector<bool>(variables, false), vector<bool>(variables, false)));
        map<string, int> variable_map;

        string input;
        for(int clause_num = 0; clause_num < clauses; clause_num++) {
            getline(cin, input);
            vector<string> s_clasues = separate_string(input);
            int variable_number = 0;
            for(string s : s_clasues) {
                if(s == "v") {
                    continue;
                }

                bool is_negated = false;
                if(s[0] == '~') {
                    is_negated = true;
                    s = s.substr(1);
                }

                if(variable_map.find(s) == variable_map.end()) {
                    variable_map[s] = variable_number;
                    variable_number++;
                }

                int var_num = variable_map[s];

                if(is_negated) {
                    clauses_vector[clause_num].second[var_num] = true;
                } else {
                    clauses_vector[clause_num].first[var_num] = true;
                }

                if(clauses_vector[clause_num].first[var_num] && clauses_vector[clause_num].second[var_num]) {
                    // Set alla variables to true when a tautology is found
                    for(int i = 0; i < variables; i++) {
                        clauses_vector[clause_num].first[i] = true;
                        clauses_vector[clause_num].second[i] = true;
                    }
                    break;
                }
            } 
        }

        bool satisfiable = false;
        // check if satisfiable trugh brute force
    }
}
