#include <iostream>
#include <any>
#include <string>

class BadTypeException {
public:
    const char* what() const noexcept {
        return "BadTypeException: Requested type does not match stored type.";
    }
};

class NoValueException {
public:
    const char* what() const noexcept {
        return "NoValueException: No value stored in the container.";
    }
};

class TypeSafeContainer {
private:
    std::any data;

public:
    template <typename T>
    void store(const T& value) {
        data = value;
    }

    template <typename T>
    T get() const {
        if (!data.has_value()) {
            throw NoValueException();
        }
        try {
            return std::any_cast<T>(data);
        } catch (...) {
            throw BadTypeException();
        }
    }
};
