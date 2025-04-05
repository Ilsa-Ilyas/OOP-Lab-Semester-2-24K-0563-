#include <iostream>
#include <string>
using namespace std;

class Rational {
private:
    int num;
    int denom;

    int findGCD(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void simplify() {
        int divisor = findGCD(abs(num), abs(denom));
        num /= divisor;
        denom /= divisor;
        if (denom < 0) {
            num = -num;
            denom = -denom;
        }
    }

public:
    Rational(int n = 0, int d = 1) : num(n), denom(d) {
        simplify();
    }

    Rational operator+(const Rational& rhs) const {
        int newNum = num * rhs.denom + rhs.num * denom;
        int newDenom = denom * rhs.denom;
        return Rational(newNum, newDenom);
    }

    Rational operator-(const Rational& rhs) const {
        int newNum = num * rhs.denom - rhs.num * denom;
        int newDenom = denom * rhs.denom;
        return Rational(newNum, newDenom);
    }

    Rational operator*(const Rational& rhs) const {
        int newNum = num * rhs.num;
        int newDenom = denom * rhs.denom;
        return Rational(newNum, newDenom);
    }

    Rational operator/(const Rational& rhs) const {
        int newNum = num * rhs.denom;
        int newDenom = denom * rhs.num;
        return Rational(newNum, newDenom);
    }

    bool operator==(const Rational& rhs) const {
        return num == rhs.num && denom == rhs.denom;
    }

    bool operator!=(const Rational& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const Rational& rhs) const {
        return num * rhs.denom < rhs.num * denom;
    }

    bool operator>(const Rational& rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Rational& rhs) const {
        return !(*this > rhs);
    }

    bool operator>=(const Rational& rhs) const {
        return !(*this < rhs);
    }

    friend ostream& operator<<(ostream& out, const Rational& r) {
        out << r.num << "/" << r.denom;
        return out;
    }

    friend istream& operator>>(istream& in, Rational& r) {
        string input;
        in >> input;
        size_t slashIndex = input.find('/');
        int n = stoi(input.substr(0, slashIndex));
        int d = stoi(input.substr(slashIndex + 1));
        r = Rational(n, d);
        return in;
    }
};

int main() {
    Rational a(2, 4), b(3, 6);
    cout << (a + b) << endl; 
    return 0;
}
