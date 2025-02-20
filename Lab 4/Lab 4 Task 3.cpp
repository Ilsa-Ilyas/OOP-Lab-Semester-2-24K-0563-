#include <iostream>
using namespace std;

class Invoice {
private:
    string partNumber;
    string partDescription;
    int quantity;
    double pricePerItem;

public:
    Invoice(string pNumber, string pDescription, int qty, double price) {
        partNumber = pNumber;
        partDescription = pDescription;
        quantity = (qty > 0) ? qty : 0;
        pricePerItem = (price > 0) ? price : 0.0;
    }

    double getInvoiceAmount() {
        return quantity * pricePerItem;
    }

    void displayInvoice() {
        cout << "Part Number: " << partNumber << endl;
        cout << "Part Description: " << partDescription << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price per Item: " << pricePerItem << endl;
        cout << "Total Invoice Amount: " << getInvoiceAmount() << endl;
    }
};

int main() {
    string partNumber, partDescription;
    int quantity;
    double pricePerItem;

    cout << "Enter Part Number: ";
    cin >> partNumber;
    cin.ignore();
    cout << "Enter Part Description: ";
    getline(cin, partDescription);
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price per Item: ";
    cin >> pricePerItem;

    Invoice invoice(partNumber, partDescription, quantity, pricePerItem);
    
    invoice.displayInvoice();

    return 0;
}
