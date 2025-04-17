#include <iostream>
#include <string>

using namespace std;

class Shape {
public:
    virtual double getArea() = 0;

    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) {
        length = l;
        width = w;
    }

    double getArea() override {
        return length * width;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    Triangle(double b, double h) {
        base = b;
        height = h;
    }

    double getArea() override {
        return 0.5 * base * height;
    }
};

int main() {
    Rectangle rect(5.0, 3.0);
    cout << "Area of Rectangle: " << rect.getArea() << endl;

    Triangle tri(4.0, 6.0);
    cout << "Area of Triangle: " << tri.getArea() << endl;

    return 0;
}
