#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class LargeInt {
private:
    std::vector<int> digits;
    bool negative = false;

    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0) negative = false;
    }

public:
    LargeInt() : digits{0} {}
    
    LargeInt(const std::string& input) {
        if (input.empty()) {
            digits.push_back(0);
        } else {
            int idx = (input[0] == '-') ? 1 : 0;
            negative = (input[0] == '-');
            for (int i = input.size() - 1; i >= idx; --i) {
                digits.push_back(input[i] - '0');
            }
        }
        removeLeadingZeros();
    }

    LargeInt operator+(const LargeInt& rhs) const {
        if (negative != rhs.negative) {
            LargeInt temp = rhs;
            temp.negative = !temp.negative;
            return *this - temp;
        }

        LargeInt result;
        result.negative = negative;
        result.digits.clear();
        int carry = 0;
        size_t len = std::max(digits.size(), rhs.digits.size());

        for (size_t i = 0; i < len || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < rhs.digits.size()) sum += rhs.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        return result;
    }

    LargeInt operator-(const LargeInt& rhs) const {
        if (negative != rhs.negative) {
            LargeInt temp = rhs;
            temp.negative = !temp.negative;
            return *this + temp;
        }

        if (this->absolute() < rhs.absolute()) {
            LargeInt result = rhs - *this;
            result.negative = !negative;
            return result;
        }

        LargeInt result;
        result.digits.clear();
        int borrow = 0;

        for (size_t i = 0; i < digits.size(); ++i) {
            int diff = digits[i] - borrow;
            if (i < rhs.digits.size()) diff -= rhs.digits[i];
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(diff);
        }

        result.removeLeadingZeros();
        return result;
    }

    LargeInt absolute() const {
        LargeInt result = *this;
        result.negative = false;
        return result;
    }

    friend bool operator<(const LargeInt& x, const LargeInt& y) {
        if (x.negative != y.negative) return x.negative;
        if (x.digits.size() != y.digits.size()) {
            return x.negative ? (x.digits.size() > y.digits.size()) : (x.digits.size() < y.digits.size());
        }
        for (int i = x.digits.size() - 1; i >= 0; --i) {
            if (x.digits[i] != y.digits[i]) {
                return x.negative ? (x.digits[i] > y.digits[i]) : (x.digits[i] < y.digits[i]);
            }
        }
        return false;
    }

    friend bool operator==(const LargeInt& x, const LargeInt& y) {
        return x.negative == y.negative && x.digits == y.digits;
    }

    friend bool operator!=(const LargeInt& x, const LargeInt& y) { return !(x == y); }
    friend bool operator>(const LargeInt& x, const LargeInt& y) { return y < x; }
    friend bool operator<=(const LargeInt& x, const LargeInt& y) { return !(y < x); }
    friend bool operator>=(const LargeInt& x, const LargeInt& y) { return !(x < y); }

    friend std::ostream& operator<<(std::ostream& os, const LargeInt& value) {
        if (value.negative) os << '-';
        for (auto it = value.digits.rbegin(); it != value.digits.rend(); ++it) {
            os << *it;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& in, LargeInt& value) {
        std::string str;
        in >> str;
        value = LargeInt(str);
        return in;
    }
};

int main() {
    LargeInt num1("1234");
    LargeInt num2("5678");

    std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
    std::cout << "num1 - num2 = " << (num1 - num2) << std::endl;
    std::cout << "num1 < num2? " << (num1 < num2) << std::endl;
    std::cout << "num1 == num2? " << (num1 == num2) << std::endl;

    return 0;
}
