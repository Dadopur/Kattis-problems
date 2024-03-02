#include <iostream>
#include <cmath>
using namespace std;

int negative_x(long x) {
    // b can only go up to sqrt x cuz this is biggest b can be and still have a power = x
    double sqrt_x = sqrt(x);
    // Begin at -2 and go to up to sqrt x
    for(int b = 2; (double) b <= sqrt_x; b++) {
        // We only need to look at odd exponents (odd p)
        for(int p = 1; p <= 32; p++) {
            // p found
            if((int(pow(b,p)) == x)) {
                return p;
            }       
       }
    }
    // p can only be 1 if returning here
    return 1;
}

int positive_x(long x) {
    // b can only go up to sqrt x cuz this is biggest b can be and still have a power = x
    double sqrt_x = sqrt(x);
    // Begin at 2 and go to up to sqrt x
    for(int b = 2; (double) b <= sqrt_x; b++) {
        // We only need to look at odd exponents (odd p)
        for(int p = 1; p <= 32; p++) {
            if(int(pow(b,p)) == x) {
                return p;
            }       
       }
    }
    // p can only be 1 if returning here
    return 1;   
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long x;
    int p;
    while(cin >> x) {
        if (x == 0){
            break;
        } else if(x < 0) {
            p = negative_x(abs(x));
            cout << p << "\n";
        } else {
            p = positive_x(x);
            cout << p << "\n";
        }
    }
}