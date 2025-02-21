#include <iostream>

using namespace std;

class Engine {
private:
    bool isRunning;
public:
    Engine() : isRunning(false) { 
        cout << "Engine constructed" << endl; 
    }
    
    ~Engine() { 
        cout << "Engine destructed" << endl;  
    }

    void start() {
        if(!isRunning) {
            isRunning = true;
            cout << "Engine started" << endl;
        }
        else {
            cout << "Engine running beforehand" << endl; 
        }
    }

    void stop() {
        if(isRunning) {
            isRunning = false;
            cout << "Engine stopped" << endl;
        }
        else {
            cout << "Engine is stopped already" << endl;
        }
    }
};

class Car {
private:
    Engine engine; 

public:
    Car() {
        cout << "Car constructed" << endl; 
    }

    ~Car() {
        cout << "Car destructed" << endl;  
    }

    void startCar() {
        engine.start();
    }

    void stopCar() {
        engine.stop();
    }
};

int main() {
    Car myCar; 
    myCar.startCar();
    myCar.stopCar();

    return 0;
}

