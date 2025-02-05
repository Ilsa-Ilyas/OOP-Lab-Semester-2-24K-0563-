#include <iostream>
using namespace std;

int main() {
    int customerID, units;
    string customerName;
    float chargePerUnit, totalBill, surcharge = 0;

    cout << "Enter Customer ID: ";
    cin >> customerID;
    cin.ignore(); 
    
    cout << "Enter Customer Name: ";
    getline(cin, customerName); 
    
    cout << "Enter Units Consumed: ";
    cin >> units;

    if (units < 200)
        chargePerUnit = 16.20;
    else if (units >= 200 && units < 300)
        chargePerUnit = 20.10;
    else if (units >= 300 && units < 500)
        chargePerUnit = 27.10;
    else
        chargePerUnit = 35.90; 

    totalBill = units * chargePerUnit;

    if (totalBill > 18000)
        surcharge = totalBill * 0.15; 

    float netAmount = totalBill + surcharge;

    cout << "\nCustomer ID : " << customerID << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Units Consumed : " << units << endl;
    cout << "Amount Charges @Rs. " << chargePerUnit << " per unit: " << totalBill << endl;
    cout << "Surcharge Amount: " << surcharge << endl;
    cout << "Net Amount Paid by the Customer: " << netAmount << endl;

    return 0;
}
