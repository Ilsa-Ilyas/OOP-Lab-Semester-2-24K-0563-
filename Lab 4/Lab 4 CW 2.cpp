#include <iostream>
using namespace std;

class Polynomial {
    double* coefficients;
    int degree;

public:
    Polynomial() {
        degree = 0;
        coefficients = new double[1];
        coefficients[0] = 0;
    }

    Polynomial(int deg, const double* coeffs) {
        degree = deg;
        coefficients = new double[degree + 1];

        for (int i = 0; i <= degree; ++i) {
            coefficients[i] = coeffs[i];
        }
    }

    Polynomial(const Polynomial& other) {
        degree = other.degree;
        coefficients = new double[degree + 1];
        for (int i = 0; i <= degree; ++i) {
            coefficients[i] = other.coefficients[i];
        }
    }

    Polynomial(Polynomial&& other) noexcept {
        coefficients = other.coefficients;
        degree = other.degree;
        other.coefficients = nullptr;
        other.degree = 0;
    }

    ~Polynomial() {
        delete[] coefficients;
    }

    int getDegree() const {
        return degree;
    }

    double evaluate(double x) const {
        double result = 0;
        double power = 1;
        for (int i = 0; i <= degree; ++i) {
            result += coefficients[i] * power;
            power *= x;
        }
        return result;
    }

    Polynomial add(const Polynomial& other) const {
        int maxDegree = (degree > other.degree) ? degree : other.degree;
        double* newCoeffs = new double[maxDegree + 1]{ 0 };

        for (int i = 0; i <= degree; ++i) {
            newCoeffs[i] += coefficients[i];
        }

        for (int i = 0; i <= other.degree; ++i) {
            newCoeffs[i] += other.coefficients[i];
        }

        Polynomial result(maxDegree, newCoeffs);
        delete[] newCoeffs;
        return result;
    }

    Polynomial multiply(const Polynomial& other) const {
        int newDegree = degree + other.degree;
        double* newCoeffs = new double[newDegree + 1]{ 0 };

        for (int i = 0; i <= degree; ++i) {
            for (int j = 0; j <= other.degree; ++j) {
                newCoeffs[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        Polynomial result(newDegree, newCoeffs);
        delete[] newCoeffs;
        return result;
    }

    void print() const {
        bool firstTerm = true;  
        for (int i = degree; i >= 0; --i) {
            if (coefficients[i] != 0) {
                if (!firstTerm) {
                    cout << (coefficients[i] > 0 ? " + " : " - ");
                } else {
                    if (coefficients[i] < 0) cout << "-";
                    firstTerm = false;
                }
                cout << abs(coefficients[i]);
                if (i > 0) {
                    cout << "x^" << i;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    double coeffs1[] = { 4, 3, 2 }; 
    Polynomial p1(2, coeffs1);

    double coeffs2[] = { 1, 2, 1 }; 
    Polynomial p2(2, coeffs2);

    cout << "Polynomial p1: ";
    p1.print();

    cout << "Polynomial p2: ";
    p2.print();

    cout << "p1 evaluated at x = 1: " << p1.evaluate(1) << endl;

    Polynomial sum = p1.add(p2);
    cout << "Sum of p1 and p2: ";
    sum.print();

    Polynomial product = p1.multiply(p2);
    cout << "Product of p1 and p2: ";
    product.print();

    return 0;
}
