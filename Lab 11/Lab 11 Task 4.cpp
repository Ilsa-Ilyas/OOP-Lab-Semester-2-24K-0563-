#include <iostream>
using namespace std;

template<typename T>
class Base {
protected:
    T a, b;

public:
    Base(T val1, T val2) : a(val1), b(val2) {}

    T multiplyBase() const {
        return a * b;
    }

    void displayBase() const {
        cout << "Base class multiplication: " << multiplyBase() << endl;
    }
};

template<typename T>
class Derived : public Base<T> {
private:
    T x, y;

public:
    Derived(T val1, T val2, T val3, T val4) : Base<T>(val1, val2), x(val3), y(val4) {}

    T multiplyDerived() const {
        return x * y;
    }

    void displayDerived() const {
        this->displayBase();
        cout << "Derived class multiplication: " << multiplyDerived() << endl;
    }
};
