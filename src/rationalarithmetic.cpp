/**
 * @file rationalarithmetic.cpp
 * @author Daniel Purgal
 * @brief Using operator overloading to perform arithmetic operations on rational numbers.
 * @version 0.1
 * @date 2024-03-31 
 */
#include <iostream>
using namespace std;
typedef long long ll;

/**
 * @brief Find the greatest common divisor of a and b.
 * 
 * @param a 
 * @param b 
 * @return ll 
 */
ll gcd(ll a, ll b) {
    while(b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * @brief Class to represent a rational number. 
 */
class Ratonal_number{
public:
    Ratonal_number(ll num, ll den) {
        if(den < 0) {
            numirator = num * -1;
            denominator = den * -1;
        } else {
            numirator = num;
            denominator = den;
        }
        simplify();
    }
    
    Ratonal_number() {
        numirator = 1;
        denominator = 1;
    }

    Ratonal_number operator+(Ratonal_number addend){
        ll num2 = addend.get_numirator();
        ll den2 = addend.get_demnomirator();
        ll factor = gcd(denominator, den2);

        ll num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);

        // Make new numirator/denominator
        ll new_num = num1 + num2;
        ll new_den = denominator * (den2/factor);

        return Ratonal_number{new_num, new_den};
    }

    Ratonal_number operator-(Ratonal_number subtrahend){
        ll num2 = subtrahend.get_numirator();
        ll den2 = subtrahend.get_demnomirator();
        ll factor = gcd(denominator, den2);

        ll num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);

        // Make new numirator/denominator
        ll new_num = num1 - num2;
        ll new_den = denominator * (den2/factor);

        return Ratonal_number{new_num, new_den};
    }


    Ratonal_number operator*(Ratonal_number factor2){
        ll num2 = factor2.get_numirator();
        ll den2 = factor2.get_demnomirator();

        // Make new numirator/denominator
        ll new_num = numirator * num2;
        ll new_den = denominator * den2;

        return Ratonal_number{new_num, new_den};
    }

    Ratonal_number operator/(Ratonal_number divisor){
        ll num2 = divisor.get_numirator();
        ll den2 = divisor.get_demnomirator();

        // Make new numirator/denominator
        ll new_num = numirator * den2;
        ll new_den = denominator * num2;

        return Ratonal_number{new_num, new_den};
    }

    
    inline bool operator==(Ratonal_number other){
        return ((numirator == other.get_numirator()) && (denominator == other.get_demnomirator()));
    }

    inline bool operator!=(Ratonal_number other){
        return !((numirator == other.get_numirator()) && (denominator == other.get_demnomirator()));
    }

    bool operator<(Ratonal_number other){
        ll num2 = other.get_numirator();
        ll den2 = other.get_demnomirator();
        ll factor = gcd(denominator, den2);

        ll num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 < num2;
    }

    bool operator<=(Ratonal_number other){
        ll num2 = other.get_numirator();
        ll den2 = other.get_demnomirator();
        ll factor = gcd(denominator, den2);

        ll num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 <= num2;
    }

    bool operator>(Ratonal_number other){
        ll num2 = other.get_numirator();
        ll den2 = other.get_demnomirator();
        ll factor = gcd(denominator, den2);

        ll num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 > num2;
    }

    bool operator>=(Ratonal_number other){
        ll num2 = other.get_numirator();
        ll den2 = other.get_demnomirator();
        ll factor = gcd(denominator, den2);

        ll num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 >= num2;
    }

    Ratonal_number& operator=(const Ratonal_number& obj) {
        if (this != &obj) {
            numirator = obj.numirator;
            denominator = obj.denominator;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Ratonal_number& obj) {
        os << obj.numirator << " / " << obj.denominator;
        return os;
    }

    friend istream& operator>>(istream& is, Ratonal_number& obj) {
        is >> obj.numirator >> obj.denominator;
        obj.simplify();
        return is;
    }

    ll get_numirator() {
        return numirator;
    }
    
    ll get_demnomirator() {
        return denominator;
    }

    void simplify() {
        ll factor = gcd(abs(numirator), abs(denominator));
        numirator = numirator / factor;
        denominator = denominator / factor;
    }

private:
    ll numirator, denominator;
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int rounds;
    cin >> rounds;
    for(int round = 0; round < rounds; round++) {
        char operation;
        Ratonal_number r1, r2, r3;
        cin >> r1 >> operation >> r2;
        
        if(operation == '+') {
            r3 = r1 + r2;
        } else if(operation == '-') {
            r3 = r1 - r2;
        } else if(operation == '*') {
            r3 = r1 * r2;
        } else if(operation == '/') {
            r3 = r1 / r2;
        }

        cout << r3 << "\n";
    }
}