#include <iostream>

class Figure {
private:
    double surface;
public:
    Figure(double s = 0.0) : surface(s) {}

    double getSurface() const {
        return surface;
    }

    Figure operator+(const Figure& other) {
        return Figure(surface + other.surface);
    }

    friend std::ostream& operator<<(std::ostream& out, const Figure& f) {
        out << f.surface;
        return out;
    }
};

int main() {
    Figure fig1(10.5), fig2(20.3);
    Figure combined = fig1 + fig2;

    std::cout << "Combined surface area: " << combined << std::endl;
    return 0;
}
