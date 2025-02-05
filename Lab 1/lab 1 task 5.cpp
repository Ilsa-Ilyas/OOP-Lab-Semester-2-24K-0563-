#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    string movieName;
    double adultTicketPrice, childTicketPrice;
    int adultTicketsSold, childTicketsSold;
    double donationPercentage, grossAmount, donationAmount, netSale;

    cout << "Enter the movie name: ";
    getline(cin, movieName); 

    cout << "Enter adult ticket price: ";
    cin >> adultTicketPrice;

    cout << "Enter child ticket price: ";
    cin >> childTicketPrice;

    cout << "Enter number of adult tickets sold: ";
    cin >> adultTicketsSold;

    cout << "Enter number of child tickets sold: ";
    cin >> childTicketsSold;

    cout << "Enter percentage of gross amount to be donated: ";
    cin >> donationPercentage;

    donationPercentage /= 100.0;

    grossAmount = (adultTicketPrice * adultTicketsSold) + (childTicketPrice * childTicketsSold);
    donationAmount = grossAmount * donationPercentage;
    netSale = grossAmount - donationAmount;

    cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
    cout << fixed << setprecision(2);  
    cout << left << "Movie Name: " << movieName << endl;
    cout << left << "Number of Tickets Sold: " << right << (adultTicketsSold + childTicketsSold) << endl;
    cout << left << "Gross Amount: " << right << "$ " << grossAmount << endl;
    cout << left << "Percentage of Gross Amount Donated: " << right << (donationPercentage * 100) << "%" << endl;
    cout << left << "Amount Donated: " << right << "$ " << donationAmount << endl;
    cout << left << "Net Sale: " << right << "$ " << netSale << endl;

    return 0;
}
