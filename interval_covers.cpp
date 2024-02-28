/**
 * @file interval_covers.cpp
 * @author Daniel Purgal, danpu323 (danpu323@student.liu.se)
 * @brief Find what given intervals are needed to cover a given interval, in O(NlogN) complexity. 
 *  Printing "impossible" if it cannot be done.
 * @version 0.1
 * @date 2024-02-06
 * 
 */

// Includes
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <cfloat>
using namespace std;

/**
 * @brief Compares two tuples to find who has larger first value.
 * 
 * @param i1 Tuple of type double, double,  int 
 * @param i2 Tuple of type double, double,  int
 * @return true if i1 has larger first value.
 * @return false otherwise
 */
bool interval_compare(tuple<double, double, int>& i1, tuple<double, double, int>& i2) {
    return (get<0>(i1) < get<0>(i2));
}

/**
 * @brief A greedy approch to find minimal amount of intervals to cover a given interval.
 * 
 * @param interval tuple of double, double, int - interval to be check.
 * @param intervals vector of intervals of type tuple: double, double, int.
 * @return vector<int> of which indexes of original intervals vector that are needed to cover interval. 
 *  First value -1 if impossible. 
 */
vector<int> count_intervals(tuple<double, double> interval, vector<tuple<double, double, int>> intervals) {
    // Initiate variables
    double primary_start = get<0>(interval);
    double primary_end = get<1>(interval);
    double start = primary_start;
    double end = start - 1;
    vector<int> indexes;

    // Sort interval with complexity O(NlogN) on start value (of tuple).
    sort(intervals.begin(), intervals.end(), interval_compare);

    // Padding to not go outside boundaries.
    intervals.push_back(make_tuple(DBL_MAX, DBL_MAX, -1));
    
    int index = -1;
    // Main loop checking all intervals.
    for (unsigned i = 0; i < intervals.size();) {
        tuple<double, double, int> new_interval = intervals[i];
        double new_start = get<0>(new_interval);
        double new_end = get<1>(new_interval);

        // Update end, is it a better interval or worse?
        if (new_start <= start) {
            // Only update if new end is better (higher)
            if (new_end > end) {
                end = new_end;
                index = get<2>(new_interval);
            }
            i++;
        } else {
            // Current interval doesn't cover the start, need a new interval
            start = end;

            if (index != -1) { indexes.push_back(index);}
            // End of loop, impossible or done
            if (new_start > end || end >= primary_end) {
                break;
            }
        }
    }

    // Returns
    if (end < primary_end) {
        // Can't find valid intervals to cover interval.
        vector<int> invalid = {-1};
        return invalid;
    }
    
    return indexes;
}

/**
 * @brief Executes algorithm.
 * 
 * @return int 
 */
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Get interval to be checked
    double start_interval;
    double end_interval;
    while(cin >> start_interval >> end_interval) {
        tuple<double, double> interval = make_tuple(start_interval, end_interval);
        // Number of intervals that will be given. 
        int num_intervals;
        cin >> num_intervals;

        // Create intervals vector
        vector<tuple<double, double, int>> intervals;
        for (int i = 0; i < num_intervals; i++) {
            cin >> start_interval >> end_interval;
            intervals.push_back(make_tuple(start_interval, end_interval, i));
        }

        // Find number of counts
        vector<int> interval_count = count_intervals(interval, intervals);

        // Print results
        if (interval_count.size() != 0 && interval_count.front() == -1) {
            cout << "impossible\n";
        } else {
            cout << interval_count.size() << "\n";
            for(int count : interval_count) {
                cout << count << " ";
            }
            cout << "\n";
        }
    }
}