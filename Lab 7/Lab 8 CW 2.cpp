#include <iostream>
#include <vector>
#include <string>

class AlgebraTools;

class Equation {
private:
    std::vector<int> terms;
    friend class AlgebraTools;

    void clean() {
        while (!terms.empty() && terms.back() == 0) {
            terms.pop_back();
        }
    }

public:
    Equation() = default;
    Equation(const std::vector<int>& coeffList) : terms(coeffList) {
        clean();
    }

    Equation operator+(const Equation& rhs) const {
        std::vector<int> sum(std::max(terms.size(), rhs.terms.size()), 0);
        for (size_t i = 0; i < terms.size(); ++i) sum[i] += terms[i];
        for (size_t i = 0; i < rhs.terms.size(); ++i) sum[i] += rhs.terms[i];
        return Equation(sum);
    }

    Equation operator-(const Equation& rhs) const {
        std::vector<int> diff(std::max(terms.size(), rhs.terms.size()), 0);
        for (size_t i = 0; i < terms.size(); ++i) diff[i] += terms[i];
        for (size_t i = 0; i < rhs.terms.size(); ++i) diff[i] -= rhs.terms[i];
        return Equation(diff);
    }

    Equation operator*(const Equation& rhs) const {
        std::vector<int> prod(terms.size() + rhs.terms.size(), 0);
        for (size_t i = 0; i < terms.size(); ++i) {
            for (size_t j = 0; j < rhs.terms.size(); ++j) {
                prod[i + j] += terms[i] * rhs.terms[j];
            }
        }
        return Equation(prod);
    }

    friend std::ostream& operator<<(std::ostream& out, const Equation& eq) {
        if (eq.terms.empty()) return out << "0";
        bool isFirst = true;
        for (int i = eq.terms.size() - 1; i >= 0; --i) {
            if (eq.terms[i] == 0) continue;
            if (!isFirst) {
                out << (eq.terms[i] > 0 ? " + " : " - ");
                out << abs(eq.terms[i]);
            } else {
                out << eq.terms[i];
                isFirst = false;
            }
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
        }
        return out;
    }
};

class AlgebraTools {
public:
    static int solveAt(const Equation& eq, int value) {
        int result = 0;
        int multiplier = 1;
        for (int coeff : eq.terms) {
            result += coeff * multiplier;
            multiplier *= value;
        }
        return result;
    }

    static Equation getDerivative(const Equation& eq) {
        std::vector<int> deriv;
        for (size_t i = 1; i < eq.terms.size(); ++i) {
            deriv.push_back(eq.terms[i] * i);
        }
        return Equation(deriv);
    }
};

int main() {
    Equation eq1({1, 2, 3});
    Equation eq2({0, 1, 1});
    std::cout << "eq1: " << eq1 << std::endl;
    std::cout << "eq2: " << eq2 << std::endl;
    std::cout << "eq1 + eq2: " << (eq1 + eq2) << std::endl;
    std::cout << "eq1 - eq2: " << (eq1 - eq2) << std::endl;
    std::cout << "eq1 * eq2: " << (eq1 * eq2) << std::endl;
    std::cout << "eq1 evaluated at x=2: " << AlgebraTools::solveAt(eq1, 2) << std::endl;
    std::cout << "Derivative of eq1: " << AlgebraTools::getDerivative(eq1) << std::endl;
    return 0;
}
