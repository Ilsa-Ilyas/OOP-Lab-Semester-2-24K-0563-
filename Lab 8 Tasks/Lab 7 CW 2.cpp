#include<iostream>
#include<string>
using namespace std;

// Base class: Shape
class Shape {
protected:
    int posX, posY;           // Coordinates for shape's position
    string fillColor;         // Color of the shape
    int outlineThickness;     // Thickness of the border

public:
    // Constructor for shape
    Shape(int x, int y, string color, int thickness)
        : posX(x), posY(y), fillColor(color), outlineThickness(thickness) {}

    // Virtual draw method to be overridden
    virtual void draw() {
        cout << "Drawing generic shape at: " << posX << ", " << posY << endl;
    }

    // Virtual area method
    virtual void calculateArea() {
        cout << "Calculating area for base shape..." << endl;
    }

    // Virtual perimeter method
    virtual void calculatePerimeter() {
        cout << "Calculating perimeter for base shape..." << endl;
    }
};

// Circle class derived from Shape
class Circle : public Shape {
    double radius;

public:
    Circle(int x, int y, string color, int thickness, double r)
        : Shape(x, y, color, thickness), radius(r) {}

    void draw() override {
        cout << "Drawing circle at: " << posX << ", " << posY << endl;
    }

    void calculateArea() override {
        double area = 3.142 * radius * radius;
        cout << "Circle area: " << area << endl;
    }

    void calculatePerimeter() override {
        double perimeter = 2 * 3.142 * radius;
        cout << "Circle perimeter: " << perimeter << endl;
    }
};

// Rectangle class derived from Shape
class Rectangle : public Shape {
    int width, height;
    int topLeftX, topLeftY;  // Top-left corner position

public:
    Rectangle(int x, int y, string color, int thickness, int w, int h, int tlx, int tly)
        : Shape(x, y, color, thickness), width(w), height(h), topLeftX(tlx), topLeftY(tly) {}

    void draw() override {
        cout << "Drawing rectangle at: " << posX << ", " << posY << endl;
    }

    void calculateArea() override {
        int area = width * height;
        cout << "Rectangle area: " << area << endl;
    }

    void calculatePerimeter() override {
        int perimeter = 2 * (width + height);
        cout << "Rectangle perimeter: " << perimeter << endl;
    }

    void printTopLeftCorner() {
        cout << "Top-left corner is at: " << topLeftX << ", " << topLeftY << endl;
    }
};

// Triangle class derived from Shape
class Triangle : public Shape {
    int baseLen, heightVal;

public:
    Triangle(int x, int y, string color, int thickness, int base, int h)
        : Shape(x, y, color, thickness), baseLen(base), heightVal(h) {}

    void draw() override {
        cout << "Drawing triangle at: " << posX << ", " << posY << endl;
    }

    void calculateArea() override {
        double area = 0.5 * baseLen * heightVal;
        cout << "Triangle area: " << area << endl;
    }

    void calculatePerimeter() override {
        // Assuming a right-angled triangle for simplicity
        double hypotenuse = sqrt(baseLen * baseLen + heightVal * heightVal);
        double perimeter = baseLen + heightVal + hypotenuse;
        cout << "Triangle perimeter: " << perimeter << endl;
    }
};

// Polygon class derived from Shape
class Polygon : public Shape {
    int numSides, sideLen;

public:
    Polygon(int x, int y, string color, int thickness, int sides, int length)
        : Shape(x, y, color, thickness), numSides(sides), sideLen(length) {}

    void draw() override {
        cout << "Drawing polygon at: " << posX << ", " << posY << endl;
    }

    void calculateArea() override {
        // Approximation for area of regular polygon
        double area = (numSides * sideLen * sideLen) / (4 * tan(3.142 / numSides));
        cout << "Polygon area (approx): " << area << endl;
    }

    void calculatePerimeter() override {
        double perimeter = numSides * sideLen;
        cout << "Polygon perimeter: " << perimeter << endl;
    }
};

int main() {
    // Create shape objects with sample data
    Circle circleShape(10, 20, "white", 2, 5.0);
    Rectangle rectShape(30, 40, "sage", 1, 8, 6, 30, 40);
    Triangle triShape(50, 60, "lilac", 3, 4, 5);
    Polygon polyShape(70, 80, "burgandy", 1, 6, 2);

    // Use polymorphism to store all shapes in a base class pointer array
    Shape* designObjects[] = { &circleShape, &rectShape, &triShape, &polyShape };

    // Perform operations on each shape
    for (Shape* shape : designObjects) {
        shape->draw();
        shape->calculateArea();
        shape->calculatePerimeter();
        cout << "-------------------------" << endl;
    }

    // Specific method for rectangle
    rectShape.printTopLeftCorner();

    return 0;
}
