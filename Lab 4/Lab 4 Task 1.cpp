#include <iostream>
#include <cstdlib> 
using namespace std;

#define PI 3.14159

class Circle {
private:
    double radius;

public:
    Circle(double r) {
        radius = r;
    }

    double getArea() {
        return PI * radius * radius;
    }

    double getPerimeter() {
        return 2 * PI * radius;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Too few arguments. Please provide a radius." << endl;
        return 1; 
    }

    double r = atof(argv[1]); 
    if (r <= 0) {
        cout << "Error: Please enter a valid positive radius." << endl;
        return 1;
    }

    Circle c(r);
    cout << "Area of Circle: " << c.getArea() << endl;
    cout << "Perimeter of Circle: " << c.getPerimeter() << endl;

    return 0;
}
