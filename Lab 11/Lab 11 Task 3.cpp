#include <iostream>
#include <vector>
#include <string>
using namespace std;

class IndexOutOfRangeException : public exception {
public:
    const char* what() const noexcept override {
        return "IndexOutOfRangeException: Accessed index is out of valid range.";
    }
};

template<typename T>
class SafeArray {
private:
    vector<T> elements;

public:
    SafeArray(size_t length) : elements(length) {}

    T& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(elements.size())) {
            throw IndexOutOfRangeException();
        }
        return elements[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(elements.size())) {
            throw IndexOutOfRangeException();
        }
        return elements[index];
    }

    size_t size() const {
        return elements.size();
    }
};
