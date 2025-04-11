#include <iostream>
#include <string>

using namespace std;

class Passenger;

class Flight
{
private:
    string flightNumber;
    string departure;
    string arrival;
    int totalCapacity;
    int bookedSeats;
    string passengerIDs[100]; // fixed size for up to 100 passengers

public:
    Flight(string fNum, string dep, string arr, int capacity)
        : flightNumber(fNum), departure(dep), arrival(arr), totalCapacity(capacity), bookedSeats(0) {}

    bool bookSeat(const string &passengerID)
    {
        if (bookedSeats >= totalCapacity)
        {
            cout << "Booking failed: Flight " << flightNumber << " is full.\n";
            return false;
        }

        for (int i = 0; i < bookedSeats; ++i)
        {
            if (passengerIDs[i] == passengerID)
            {
                cout << "Booking failed: Passenger already booked.\n";
                return false;
            }
        }

        passengerIDs[bookedSeats++] = passengerID;
        cout << "Booking successful for passenger " << passengerID << " on flight " << flightNumber << ".\n";
        return true;
    }

    bool cancelSeat(const string &passengerID)
    {
        for (int i = 0; i < bookedSeats; ++i)
        {
            if (passengerIDs[i] == passengerID)
            {
                // Shift remaining passengers
                for (int j = i; j < bookedSeats - 1; ++j)
                {
                    passengerIDs[j] = passengerIDs[j + 1];
                }
                --bookedSeats;
                cout << "Cancellation successful for passenger " << passengerID << " on flight " << flightNumber << ".\n";
                return true;
            }
        }

        cout << "Cancellation failed: Passenger not found on flight.\n";
        return false;
    }

    bool upgradeSeat(const string &passengerID)
    {
        for (int i = 0; i < bookedSeats; ++i)
        {
            if (passengerIDs[i] == passengerID)
            {
                cout << "Upgrade successful for passenger " << passengerID << " on flight " << flightNumber << ".\n";
                return true;
            }
        }

        cout << "Upgrade failed: Passenger not booked on flight.\n";
        return false;
    }

    void displayFlightStatus() const
    {
        cout << "Flight " << flightNumber << " | From " << departure << " to " << arrival
             << " | Seats booked: " << bookedSeats << "/" << totalCapacity << endl;
    }

    friend class Passenger;
};

class Passenger
{
private:
    string passengerID;
    string name;

public:
    Passenger(string id, string pname) : passengerID(id), name(pname) {}

    void requestBooking(Flight &flight)
    {
        flight.bookSeat(passengerID);
    }

    void requestCancellation(Flight &flight)
    {
        flight.cancelSeat(passengerID);
    }

    void requestUpgrade(Flight &flight)
    {
        flight.upgradeSeat(passengerID);
    }

    void showDetails() const
    {
        cout << "Passenger: " << name << " | ID: " << passengerID << endl;
    }
};

int main()
{
    Flight flight1("AA789", "America", "LA", 2);

    Passenger p1("P001", "Ilsa");
    Passenger p2("P002", "Umais");
    Passenger p3("P003", "Wasay");

    p1.requestBooking(flight1);
    p2.requestBooking(flight1);
    p3.requestBooking(flight1);

    flight1.displayFlightStatus();

    p1.requestUpgrade(flight1);
    p2.requestCancellation(flight1);
    p3.requestBooking(flight1); 

    flight1.displayFlightStatus();

    return 0;
}