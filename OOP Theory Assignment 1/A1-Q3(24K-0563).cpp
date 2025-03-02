#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    string model;
    float rentalPrice;
    string eligibility;

public:
    Vehicle(string m, float p, string e) {
        model = m;
        rentalPrice = p;
        eligibility = e;
    }

    void display() {
        cout << model << "\t" << rentalPrice << "\t" << eligibility << endl;
    }

    void setModel(string m) { model = m; }
    void setPrice(float p) { rentalPrice = p; }
    void setEligibility(string e) { eligibility = e; }

    string getModel() { return model; }
    string getEligibility() { return eligibility; }
    float getRentalPrice() { return rentalPrice; }
};

class User {
    int age;
    string licenseType;
    string contactInfo;
    string userID;
    Vehicle* rentedVehicle; 

public:
    User() { rentedVehicle = nullptr; }
    
    User(int a, string l, string c, string id) {
        age = a;
        licenseType = l;
        contactInfo = c;
        userID = id;
        rentedVehicle = nullptr; 
    }

    int getAge() { return age; }
    string getLicenseType() { return licenseType; }
    string getContactInfo() { return contactInfo; }
    string getUserID() { return userID; }
    Vehicle* getRentedVehicle() { return rentedVehicle; }  

    void updateAge(int newAge) { age = newAge; }
    void updateLicenseType(string newLicense) { licenseType = newLicense; }
    void updateContactInfo(string newContact) { contactInfo = newContact; }
    void setUserID(string id) { userID = id; }
    
    void rentVehicle(Vehicle* v) {
        if (licenseType == "Expert" || 
           (licenseType == "Experienced" && (v->getEligibility() == "Experienced" || v->getEligibility() == "Learner")) || 
           (v->getEligibility() == licenseType)) {
            rentedVehicle = v; 
            cout << "\n Vehicle rented successfully!\nDetails:\n";
            v->display();
        } else {
            cout << "\n You are not eligible to rent this vehicle.\n";
        }
    }
};  

int main() {
    cout << "==============================\n";
    cout << "   Vehicle Rental System   \n";
    cout << "==============================\n";

    Vehicle** vehicleList = new Vehicle*[6];
    if (!vehicleList) {
        cout << "Memory allocation failed.\n";
        return 1;
    }

    vehicleList[0] = new Vehicle("Mazda CX-5", 48.0, "Expert");
    vehicleList[1] = new Vehicle("Tesla Model 3", 65.0, "Expert");
    vehicleList[2] = new Vehicle("Chevrolet Malibu", 45.0, "Experienced");
    vehicleList[3] = new Vehicle("Volkswagen Polo", 40.0, "Experienced");
    vehicleList[4] = new Vehicle("Fiat 500", 35.0, "Learner");
    vehicleList[5] = new Vehicle("Toyota Yaris", 38.0, "Learner");

    User user;
    int choice;
    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Register \n";
        cout << "2. Update User Info\n";
        cout << "3. View Available Vehicles\n";
        cout << "4. Rent a Vehicle\n";
        cout << "5. Exit\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {  
            int age;
            string license, contact, id;
            int licenseChoice;

            cout << "Enter Age: ";
            cin >> age;
            
            cout << "Select License Type:\n";
            cout << "1. Learner\n2. Experienced\n3. Expert\n";
            cout << "Choice: ";
            cin >> licenseChoice;

            if (licenseChoice == 1) license = "Learner";
            else if (licenseChoice == 2) license = "Experienced";
            else license = "Expert";

            cout << "Enter Contact Info: ";
            cin >> contact;

            cout << "Enter User ID: ";
            cin >> id;

            user = User(age, license, contact, id);
            cout << "\nUser registered!\n";

        } else if (choice == 2) {  
            int updateChoice;
            cout << "\nWhat would you like to update?\n";
            cout << "1. License Type\n2. Age\n3. Contact Info\n4. User ID\n";
            cout << "Choice: ";
            cin >> updateChoice;

            if (updateChoice == 1) {
                int licenseChoice;
                cout << "Select New License Type:\n";
                cout << "1. Learner\n2. Experienced\n3. Expert\n";
                cout << "Choice: ";
                cin >> licenseChoice;
                string newLicense = (licenseChoice == 1) ? "Learner" : (licenseChoice == 2) ? "Experienced" : "Expert";
                user.updateLicenseType(newLicense);
                cout << "License Type Updated!\n";
            } 
            else if (updateChoice == 2) {
                int newAge;
                cout << "Enter New Age: ";
                cin >> newAge;
                user.updateAge(newAge);
                cout << "Age Updated!\n";
            } 
            else if (updateChoice == 3) {
                string newContact;
                cout << "Enter New Contact Info: ";
                cin >> newContact;
                user.updateContactInfo(newContact);
                cout << "Contact Info Updated!\n";
            } 
            else if (updateChoice == 4) {
                string newID;
                cout << "Enter New User ID: ";
                cin >> newID;
                user.setUserID(newID);
                cout << "User ID Updated Successfully!\n";
            }
            else {
                cout << "Invalid Choice.\n";
            }

        } else if (choice == 3) {  
            cout << "\n===============================\n";
            cout << "   Available Vehicles List  \n";
            cout << "===============================\n";
            cout << "Model\t\tRent/Day\tEligibility\n";
            cout << "-------------------------------------\n";
            for (int i = 0; i < 6; i++) {
                cout << i + 1 << ") ";
                vehicleList[i]->display();
            }

        } else if (choice == 4) {  
            cout << "\n===============================\n";
            cout << "   Select a Vehicle to Rent  \n";
            cout << "===============================\n";
            cout << "Model\t\tRent/Day\tEligibility\n";
            cout << "-------------------------------------\n";
            for (int i = 0; i < 6; i++) {
                cout << i + 1 << ") ";
                vehicleList[i]->display();
            }

            int vehicleChoice;
            cout << "Select a vehicle (1-6): ";
            cin >> vehicleChoice;

            if (vehicleChoice >= 1 && vehicleChoice <= 6) {
                user.rentVehicle(vehicleList[vehicleChoice - 1]);
            } else {
                cout << "Invalid choice!\n";
            }

        } else if (choice == 5) {  
            cout << "\nThank you for using the Vehicle Rental System. \n";
        } else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    for (int i = 0; i < 6; i++) {
        delete vehicleList[i];
    }
    delete[] vehicleList;

    return 0;
}









