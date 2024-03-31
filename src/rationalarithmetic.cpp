#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
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
    }
    
    Ratonal_number() {
        numirator = 0;
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

        // Normelize
        factor = gcd(new_num, new_den);
        return Ratonal_number{(new_num/factor), (new_den/factor)};
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

        // Normelize
        factor = gcd(new_num, new_den);
        return Ratonal_number{(new_num/factor), (new_den/factor)};
    }


    Ratonal_number operator*(Ratonal_number factor2){
        int num2 = factor2.get_numirator();
        int den2 = factor2.get_demnomirator();

        // Make new numirator/denominator
        int new_num = numirator * num2;
        int new_den = denominator * den2;

        // Normelize
        int new_gcd = gcd(new_num, new_den);
        return Ratonal_number{(new_num/new_gcd), (new_den/new_gcd)};
    }

    Ratonal_number operator/(Ratonal_number divisor){
        int num2 = divisor.get_numirator();
        int den2 = divisor.get_demnomirator();

        // Make new numirator/denominator
        int new_num = numirator * den2;
        int new_den = denominator * num2;

        // Normelize
        int factor = gcd(new_num, new_den);
        return Ratonal_number{(new_num/factor), (new_den/factor)};
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

        int num1 = numirator * (denominator/factor);
        num2 = num2 * (den2/factor);
        int new_den = denominator * (denominator/factor);
        return num1 < num2;
    }

    bool operator<=(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (denominator/factor);
        num2 = num2 * (den2/factor);
        int new_den = denominator * (denominator/factor);
        return num1 <= num2;
    }

    bool operator>(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (denominator/factor);
        num2 = num2 * (den2/factor);
        int new_den = denominator * (denominator/factor);
        return num1 > num2;
    }

    bool operator>=(Ratonal_number other){
        int num2 = other.get_numirator();
        int den2 = other.get_demnomirator();
        int factor = gcd(denominator, den2);

        int num1 = numirator * (denominator/factor);
        num2 = num2 * (den2/factor);
        int new_den = denominator * (denominator/factor);
        return num1 >= num2;
    }

    void operator=(Ratonal_number obj) {
        numirator = obj.get_numirator();
        denominator = obj.get_demnomirator();
    }

    friend ostream& operator<<(ostream& os, const Ratonal_number& obj) {
        os << obj.numirator << " / " << obj.denominator;
        return os;
    }

    int get_numirator() {
        return numirator;
    }
    
    int get_demnomirator() {
        return denominator;
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
        int num1, num2, den1, den2;
        char operation;
        cin >> num1 >> den1 >> operation >> num2 >> den2;
        Ratonal_number r1(num1, den1);
        Ratonal_number r2(num2, den2);
        Ratonal_number r3;

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