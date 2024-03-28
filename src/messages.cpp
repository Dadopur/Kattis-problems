
/**
 * @file stringmatching.cpp
 * @author Daniel Purgal
 * @brief Find maching pattern in a text using KNP (Knuth-Morris-Pratt) algorithm.
 * The time complexity of the whole algorithm is O(n + m) where n is the size of the text and m is the size of the pattern.
 * O(m) is the time complexity of the pre_process function and O(n) for the search.
 * The space complexity of the algorithm is O(m) where m is the size of the pattern.
 * @version 0.1
 * @date 2024-03-26 
 */
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
    int iter = 1;
    int ps_length = 0;
    lps[0] = 0;
    while(iter < pattern.size()) {
        if(pattern[iter] == pattern[ps_length]) {
            lps[iter] = ps_length + 1;
            ps_length++;
            iter++;
        } else {
            if(ps_length != 0) {
                ps_length = lps[ps_length - 1];
            } else {
                lps[iter] = 0;
                iter++;
            }
        }
    }
    return lps;
}

/**
 * @brief Find all positions of matches of the pattern in the text.
 * 
 * @param pattern 
 * @param text 
 * @return vector<int> With all positions the of mached pattern in the text.
 */
vector<int> find_maches(string pattern, string text) {
    vector<int> matches{};
    vector<int> lps = pre_process(pattern);
    int pattern_size = pattern.size();
    int text_size = text.size();

    int pattern_pointer = 0;
    int text_pointer = 0;

    while(text_pointer < text_size) {
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

struct Interval {
    int start;
    int end;
};

bool compare_intervals(Interval a, Interval b) {
    return a.end < b.end;
}

int find_most_maches(vector<string> patterns, string text) {
    vector<Interval> intervals;
    for(string pattern : patterns) {
        vector<int> matches = find_maches(pattern, text);
        for(auto match : matches) {
            intervals.push_back(Interval{match, match + int(pattern.size())-1});
        }
    }
    sort(intervals.begin(), intervals.end(), compare_intervals);

    // cout << "intervals " << intervals.size() << endl;
    // for(auto interval : intervals) {
    //     cout << interval.start << " " << interval.end << endl;
    // }

    vector<Interval> result;
    int last_end = -1;
    int count = 0;
    for(auto interval : intervals) {
        if(interval.start > last_end) {
            count++;
            result.push_back(interval);
            last_end = interval.end;
        }
    }
    // for(auto interval : result) {
    //     cout << interval.start << " " << interval.end << endl;
    // }
    return count;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<string> patterns;
    string pattern, text;
    while(cin >> pattern && pattern != "#") {
        patterns.push_back(pattern);
    }

    string total_text = "";
    while(cin >> text && text != "#") {
        total_text += text;
        if(text.back() == '|') {
            total_text.pop_back();
            cout << find_most_maches(patterns, total_text) << "\n";
            total_text = "";
        }
    }   
}