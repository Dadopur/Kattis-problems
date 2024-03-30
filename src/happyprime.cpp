
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool is_prime(int n) {
    // 1 is not prime in this problem
    if(n == 1) {
        return false;
    }
    // check if even number (reduces computations later on)
    if(n % 2 == 0 && n != 2) {
        return false;
    }

    for(int i = 3; i <= sqrt(n); i += 2) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

bool is_happy(int n) {
    vector<int> seen;
    while(n != 1) {
        if(find(seen.begin(), seen.end(), n) != seen.end()) {
            return false;
        } else {
            seen.push_back(n);
            int sum = 0;
            while(n > 0) {
                sum += pow(n % 10, 2);
                n = floor(n/10);
            }
            n = sum;
        }
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int rounds;
    cin >> rounds;
    for(int round = 0; round < rounds; round++) {
        int dataset;
        int number;
        cin >> dataset >> number;
        if(is_prime(number) && is_happy(number)) {
            cout << dataset << " " << number << " YES\n";
        } else {
            cout << dataset << " " << number << " NO\n";
        }
    }
}