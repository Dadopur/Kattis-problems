/**
 * @file primesieve.cpp
 * @author Daniel Purgal
 * @brief Using the sieve of Eratosthenes to find prime numbers up to a given limit. 
 * Memory complexity is O(n) and time complexity is O(n*log(log(n))) where n is the number
 * of elements in the sieve (from 0 to limit).
 * @version 0.1
 * @date 2024-03-30
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief PrimeSieve class to create a sieve of Eratosthenes.
 */
class PrimeSieve {
public:
    /**
     * @brief Construct a new Prime Sieve object
     * 
     * @param limit of the sieve.
     */
    PrimeSieve(int limit) : sieve_limit(limit) {
        // Create sieve from 0 to limit
        sieve = vector<bool>(limit + 1, true);
        // 0 and 1 are not primes
        sieve[0] = false;
        sieve[1] = false;
        for(int p = 2; p * p <= limit; p++) {
            // p is prime
            if(sieve[p] == true) {
                // All multiples of p are not prime
                for(int not_prime = p * p; not_prime <= limit; not_prime += p) {
                    sieve[not_prime] = false;
                }
            }
        }
    }

    /**
     * @brief Is number n prime?
     * 
     * @param n 
     * @return true 
     * @return false 
     */
    bool is_prime(int n) {
        return sieve[n];
    }

    /**
     * @brief Number of primes in the sieve.
     * 
     * @return int 
     */
    int number_of_primes() {
        return count(sieve.begin(), sieve.end(), true);
    }

private:
    vector<bool> sieve;
    int sieve_limit;
    int num_primes;
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int limit, queries;
    cin >> limit >> queries;
    PrimeSieve sieve = PrimeSieve(limit);
    cout << sieve.number_of_primes() << "\n";
    for(int i = 0; i < queries; i++) {
        int query;
        cin >> query;
        if(sieve.is_prime(query)) {
            cout << "1\n";
        } else {
            cout << "0\n";
        }
    }

}