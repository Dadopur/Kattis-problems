/**
 * @file chineseremainder.cpp
 * @author Daniel Purgal
 * @brief Using the chinese remainder theorem to find a number X that is congruent to a mod n and b mod m.
 * The time complexity is O(log(nm)) where n and m are the numbers to find the remainder of.
 * @version 0.1
 * @date 2024-03-30
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Extended Euclidean algorithm to find the greatest common divisor of a and b.
 * and the coefficients x and y of the equation ax + by = gcd(a, b).
 * 
 * @param a 
 * @param b 
 * @param x 
 * @param y 
 * @return int 
 */
int gcd_extended(int a, int b, int* x, int* y) {
    if(b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd =  gcd_extended(b, a % b, &x1, &y1);

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
 * @return pair<int, int> where first is the number X and second is the product of n and m.
 */
pair<int, int> chinease_remainder(int a, int n, int b, int m) {
    int X, k;
    k = n * m;

    int x, y;
    int gcd = gcd_extended(n, m, &x, &y);
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
        int a, n, b, m;
        cin >> a >> n >> b >> m;
        pair<int, int> result = chinease_remainder(a, n, b, m);
        cout << result.first << " " << result.second << "\n";
    }
}