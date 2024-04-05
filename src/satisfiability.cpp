#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <utility>
#include <map>
#include <bitset>
#include <cmath>
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
        cin.ignore();
        //vector<pair<vector<bool>, vector<bool>>> clauses_vector(clauses, make_pair(vector<bool>(variables, false), vector<bool>(variables, false)));
        vector<pair<bitset<20>, bitset<20>>> clauses_vector(clauses, make_pair(bitset<20>(), bitset<20>()));
        map<string, int> variable_map;

        string input;
        int variable_number = 0;
        for(int clause_num = 0; clause_num < clauses; clause_num++) {
            getline(cin, input);
            vector<string> s_clasues = separate_string(input);
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

                // for(auto p : variable_map) {
                //     cout << p.first << " " << p.second << endl;
                // }

                int var_num = variable_map[s];
                // cout << "var_num: " << s << " "<< var_num << endl;

                // if(is_negated) {
                //     clauses_vector[clause_num].second[var_num] = true;
                // } else {
                //     clauses_vector[clause_num].first[var_num] = true;
                // }

                if(is_negated) {
                    clauses_vector[clause_num].second.set(var_num);
                } else {
                    clauses_vector[clause_num].first.set(var_num);
                }

                // if(clauses_vector[clause_num].first[var_num] && clauses_vector[clause_num].second[var_num]) {
                //     // Set alla variables to true when a tautology is found
                //     for(int i = 0; i < variables; i++) {
                //         clauses_vector[clause_num].first[i] = true;
                //         clauses_vector[clause_num].second[i] = true;
                //     }
                //     break;
                // }

                if(clauses_vector[clause_num].first.test(var_num) && clauses_vector[clause_num].second.test(var_num)) {
                    // Set alla variables to true when a tautology is found
                    clauses_vector[clause_num].first.set();
                    clauses_vector[clause_num].second.set();
                    break;
                }

            } 
        }
        bool satisfiable = false;
        // check if satisfiable trugh brute force

        // int i=0;
        // for(auto p : clauses_vector) {
        //     cout << i << " " << p.first << " " << p.second << endl;
        //     i++;
        // }


        for(int i = 0; i < pow(2, variables); i++) {
            for(int c = 0; c < clauses; c++) {
                bitset<20> bits(i);
                bitset<20> and_bits(i);
                bitset<20> neg_and_bits(i);
                neg_and_bits.flip();
                and_bits &= clauses_vector[c].first;
                neg_and_bits &= clauses_vector[c].second;

                //cout <<  i << " bits: " << bits << endl;
                // cout << "and_bits: " << and_bits << endl;
                // cout << "neg_and_bits: " << neg_and_bits << endl;

                if(and_bits.any() || neg_and_bits.any()) {
                    // cout << "came here1" << endl;
                    satisfiable = true;
                    continue;
                } else {
                    // cout << "came here2" << endl;
                    satisfiable = false;
                    break;
                }
            }
            if(satisfiable) {
                break;
            }
        }

        if(satisfiable) {
            cout << "satisfiable\n";
        } else {
            cout << "unsatisfiable\n";
        }
    }
}
