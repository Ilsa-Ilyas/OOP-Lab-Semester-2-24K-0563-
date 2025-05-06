#include <iostream>
#include "Safestack.h"

int main() {
    SafeStack<int> myStack;

    try {
        myStack.push(100);
        myStack.push(200);

        std::cout << "Top element: " << myStack.top() << std::endl; 

        myStack.pop();
        std::cout << "Top after pop: " << myStack.top() << std::endl; 

        myStack.pop();
        myStack.pop(); // This will throw an exception

    } catch (const SafeStackUnderflowException& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
