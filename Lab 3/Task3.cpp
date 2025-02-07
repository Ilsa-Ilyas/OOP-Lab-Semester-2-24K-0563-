#include <iostream>
#include <string>

using namespace std;

class Glass
{
public:
    int liquidlevel;

    void drink(int millilitres)
    {
        liquidlevel -= millilitres;
        if (liquidlevel < 100)
        {
            Refill();
        }
    }

    void Refill()
    {
        liquidlevel = 200;
    }
};

int main()
{
    int initialliquidlevel = 200;
    Glass glass;
    glass.liquidlevel = initialliquidlevel;
    while (true)
    {
        string input;
        int amount;

        cout << "Enter command (Drink or Quit): ";
        cin >> input;

        if (input == "Quit")
        {
            break;
        }
        else if (input == "Drink")
        {
            cin >> amount;
            glass.drink(amount);
            cout << "Current liquid level: " << glass.liquidlevel << " ml" << endl;
        }
        else
        {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
};