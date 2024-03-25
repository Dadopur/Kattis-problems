
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // prime factor M and see what powers all of their primes have
    // Check for those primes what exponent N! has, if less than M then return false, otherwise continue
    int N, M;
    while(cin >> N >> M) {
        if(M == 0) {
            cout << M << " does not divide " << N << "!\n";
            continue;
        }
        
        if(N == 0 || N == 1) {
            if(M == 1) {
                cout << M << " divides " << N << "!\n";
            } else {
                cout << M << " does not divide " << N << "!\n";
            }
            continue;
        }

        // Prime factors of M
        unordered_map<int, int> prime_factors;
        int temp = M;
        while(temp % 2 == 0) {
            prime_factors[2]++;
            temp /= 2;
        }
        for(int i = 3; i <= sqrt(temp); i += 2) {
            while(temp % i == 0) {
                prime_factors[i]++;
                temp /= i;
            }
        }

        if(temp != 1) {
            prime_factors[temp]++;
        }

        bool divides = true;

        for(auto kv : prime_factors) {
            int prime = kv.first;
            int exponent_m = kv.second;
            int exponent_n = 0;
            for(int i = 1; i < sqrt(N); i++) {
                int cont = floor(N / pow(prime, i));
                exponent_n += cont;
                if (cont == 0) {
                    break;
                }
            }
            if(exponent_n < exponent_m) {
                cout << M << " does not divide " << N << "!\n";
                divides = false;
                break;
            }
        }
        if(divides){
            cout << M << " divides " << N << "!\n";
        }
    } 
}