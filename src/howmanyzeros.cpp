#include <iostream>
using namespace std;
typedef long long ll;

/**
 * @brief Counts number of zeros from 1 to n.
 * 
 * @param n 
 * @return ll 
 */
ll num_zeroes(ll n) {
    ll place = 1;
    ll count = 0;

    // Counts how many numbers have zero in this place
    while(true) {
        ll higher = n / (place * 10);
        ll lower = n % place;
        ll current = (n / place) % 10;

        // Base case, no more higher digits
        if(higher == 0) {
            return count;
        }

        // Special case when we have curr zero, count only up to lower end (and +1 for whole lower being zeroes)
        if(current == 0) {
            count += (higher - 1) * place + (lower + 1);
        } else {
            count += higher * place;
        }
        place *= 10;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll start, end;
    while(true) {
        cin >> start >> end;
        if(start == -1 && end == -1) {
            break;
        }

        ll start_zeroes;
        if(start == 0) {
            start_zeroes = -1;
        } else {
            start_zeroes = num_zeroes(start-1);
        }

        ll end_zeroes;
        if(end == 0) {
            end_zeroes = 1;
        } else {
            end_zeroes = num_zeroes(end);
        }

        cout << (end_zeroes - start_zeroes) << endl;
    }
}