#include <iostream>
#include <vector>

using namespace std;

class Car {
private:
    string name;
    int ID;

public:
    Car(string carname, int carID) : name(carname), ID(carID) {}

    string getname() const {
        return name;
    }

    int getID() const {
        return ID;
    }
};

class Garage {
private:
    vector<Car*> cars;

public:
    void parkCar(Car* c) {
        cars.push_back(c);  
    }

    void listCar() {
        cout << "Cars in garage: ";
        for (Car* c : cars) {
            cout << c->getname() << " ";  
        }
        cout << endl; 
    }
};

int main() {
    Car c1("Honda", 2005);
    Car c2("BMW", 1997);
    Car c3("Audi", 2009);

    Garage garage;
    garage.parkCar(&c1);
    garage.parkCar(&c2);
    garage.parkCar(&c3);  

    garage.listCar(); 

    return 0;
}
