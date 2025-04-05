#include <iostream>

class Digit {
private:
    int data;
public:
    Digit(int d = 0) : data(d) {}

    // Prefix --
    Digit operator--() {
        data *= 4;
        return *this;
    }

    // Postfix --
    Digit operator--(int) {
        Digit snapshot = *this;
        data /= 4;
        return snapshot;
    }

    friend std::ostream& operator<<(std::ostream& out, const Digit& d) {
        out << d.data;
        return out;
    }
};

int main() {
    Digit val(16);
    std::cout << "Initial: " << val << std::endl;
    std::cout << "Prefix --: " << --val << std::endl;
    std::cout << "Postfix --: " << val-- << std::endl;
    std::cout << "Final: " << val << std::endl;
    return 0;
}
