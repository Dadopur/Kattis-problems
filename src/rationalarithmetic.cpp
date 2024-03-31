/**
 * @file rationalarithmetic.cpp
 * @author Daniel Purgal
 * @brief Using operator overloading to perform arithmetic operations on rational numbers.
 * @version 0.1
 * @date 2024-03-31 
 */
#include <iostream>
using namespace std;

// int gcd(int a, int b) {
//     if(b == 0) {
//         return a;
//     }
//     return gcd(b, a % b);
// }

int gcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Ratonal_number{
public:
    Ratonal_number(int num, int den) {
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
        int num2 = addend.get_numirator();
        int den2 = addend.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);

        // Make new numirator/denominator
        int new_num = num1 + num2;
        int new_den = denominator * (den2/factor);

        return Ratonal_number{new_num, new_den};
    }

    Ratonal_number operator-(Ratonal_number subtrahend){
        int num2 = subtrahend.get_numirator();
        int den2 = subtrahend.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);

        // Make new numirator/denominator
        int new_num = num1 - num2;
        int new_den = denominator * (den2/factor);

        return Ratonal_number{new_num, new_den};
    }


    Ratonal_number operator*(Ratonal_number factor2){
        int num2 = factor2.get_numirator();
        int den2 = factor2.get_demnomirator();

        // Make new numirator/denominator
        int new_num = numirator * num2;
        int new_den = denominator * den2;

        return Ratonal_number{new_num, new_den};
    }

    Ratonal_number operator/(Ratonal_number divisor){
        int num2 = divisor.get_numirator();
        int den2 = divisor.get_demnomirator();

        // Make new numirator/denominator
        int new_num = numirator * den2;
        int new_den = denominator * num2;

        return Ratonal_number{new_num, new_den};
    }

    
    inline bool operator==(Ratonal_number other){
        return ((numirator == other.get_numirator()) && (denominator == other.get_demnomirator()));
    }

    inline bool operator!=(Ratonal_number other){
        return !((numirator == other.get_numirator()) && (denominator == other.get_demnomirator()));
    }

    bool operator<(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 < num2;
    }

    bool operator<=(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 <= num2;
    }

    bool operator>(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (den2/factor);
        num2 = num2 * (denominator/factor);
        return num1 > num2;
    }

    bool operator>=(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (den2/factor);
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

    int get_numirator() {
        return numirator;
    }
    
    int get_demnomirator() {
        return denominator;
    }

    void simplify() {
        int factor = gcd(abs(numirator), abs(denominator));
        numirator = numirator / factor;
        denominator = denominator / factor;
    }

private:
    int numirator, denominator;
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