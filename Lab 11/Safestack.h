#pragma once
#include <vector>
#include <exception>

// Custom exception class for stack underflow
class SafeStackUnderflowException : public std::exception {
public:
    const char* what() const noexcept override {
        return "SafeStackUnderflowException: Stack is empty.";
    }
};

// Templated stack class
template<typename T>
class SafeStack {
private:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    void pop() {
        if (elements.empty()) {
            throw SafeStackUnderflowException();
        }
        elements.pop_back();
    }

    T& top() {
        if (elements.empty()) {
            throw SafeStackUnderflowException();
        }
        return elements.back();
    }

    const T& top() const {
        if (elements.empty()) {
            throw SafeStackUnderflowException();
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    std::size_t size() const {
        return elements.size();
    }
};
