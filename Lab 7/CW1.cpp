#include <iostream>
using namespace std;

class Fraction
{
    int numerator;
    int denominator;

public:
    Fraction(int n, int d) : numerator(n), denominator(d)
    {
        if (denominator == 0)
        {
            cout << "Error: Denominator cannot be zero" << endl;
        }
        else
        {
            reduce(); 
        }
    }

    int reduce()
    {
        int number;
        int gcd = 1; // Initialize gcd to 1 to handle edge cases

        if (numerator < denominator)
        {
            number = numerator;
        }
        else
        {
            number = denominator;
        }

        for (int i = 1; i <= number; i++)
        {
            if (numerator % i == 0 && denominator % i == 0)
            {
                gcd = i; // Update gcd if i divides both numerator and denominator
            }
        }

        // Reduce the fraction by the gcd
        numerator /= gcd;
        denominator /= gcd;

        // Ensure the denominator is positive
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }

        return gcd; 
    }

    void display() const
    {
        cout << numerator << "/" << denominator << endl;
    }
};

int main()
{
    Fraction F(125, 25);

    F.display(); 

    return 0;
}
