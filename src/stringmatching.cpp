
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/**
 * @brief Create a longest proper prefix suffix array. 
 * 
 * @param pattern 
 * @return vector<int> of longest prefix suffix (lps) 
 */
vector<int> pre_process(string pattern) {
    vector<int> lps(pattern.size(), 0);
    if(pattern.size() == 1) {
        return lps;
    }

    int length = 1;
    while(length < pattern.size()) {
        int longest = 0;
        // Find the longest prefix suffix for current length
        for(int i = 0; i <= length; i++) {
            int end_p = length - i;
            int start_p = 0;
            bool is_pre_suff = true;
            for(int j = 0; j < i; j++) {
                if(pattern[start_p] == pattern[end_p]) {
                    start_p++;
                    end_p++;
                } else {
                    is_pre_suff = false;
                    break;
                }   
            }
            if(is_pre_suff && i > longest) {
                longest = i;
            }
        }
        lps[length] = longest;
        length++;
    }
    return lps;
}

vector<int> find_maches(string pattern, string text) {
    vector<int> matches;
    vector<int> lps = pre_process(pattern);
    int pattern_size = pattern.size();
    int text_size = text.size();

    int pattern_pointer = 0;
    int text_pointer = 0;

    while(text_pointer < text_size - pattern_size + 1) {
        if(pattern[pattern_pointer] == text[text_pointer]) {
            pattern_pointer++;
            text_pointer++;
        } else {
            if(pattern_pointer != 0) {
                pattern_pointer = lps[pattern_pointer - 1];
            } else {
                text_pointer++;
            }
        
        }
        if(pattern_pointer == pattern_size) {
            matches.push_back(text_pointer - pattern_size);
            pattern_pointer = lps[pattern_pointer - 1];
        }
    }
    return matches;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string pattern, text;
    while(getline(cin, pattern)) {
        getline(cin, text);
        vector<int> matches = find_maches(pattern, text);
        for(int match : matches) {
            cout << match << " ";
        } cout << "\n";
    }
}