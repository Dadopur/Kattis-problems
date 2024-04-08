/**
 * @file chineseremainder.cpp
 * @author Daniel Purgal
 * @brief Using the chinese remainder theorem to find a number X that is congruent to a mod n and b mod m.
 * The time complexity is O(log(nm)) where n and m are the numbers to find the remainder of.
 * @version 0.1
 * @date 2024-03-30
 * 
 * 
 * THIS CODE DOES NOT WORK YET
 */

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

/**
 * @brief Extended Euclidean algorithm to find the greatest common divisor of a and b.
 * and the coefficients x and y of the equation ax + by = gcd(a, b).
 * 
 * @param a 
 * @param b 
 * @param x 
 * @param y 
 * @return ll 
 */
ll gcd_extended(ll a, ll b, ll* x, ll* y) {
    if(b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd =  gcd_extended(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - y1 * (a / b);
    return gcd;
}

/**
 * @brief Find what number X is congruent to a mod n and b mod m.
 * 
 * @param a 
 * @param n 
 * @param b
 * @param m
 * @return pair<ll, ll> where first is the number X and second is the product of n and m.
 */
pair<ll, ll> chinese_remainder(ll a, ll n, ll b, ll m) {
    ll X, k;
    k = n * m;

    ll x, y;
    ll gcd = gcd_extended(n, m, &x, &y);
    X = (a * m * y + b * n * x) % k;
    if(X < 0) {
        X += k;
    }
    return make_pair(X, k);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int num_tests;
    cin >> num_tests;
    for(int test = 0; test < num_tests; test++) {
        ll a, n, b, m;
        cin >> a >> n >> b >> m;
        pair<ll, ll> result = chinese_remainder(a, n, b, m);
        cout << result.first << " " << result.second << "\n";
    }
}