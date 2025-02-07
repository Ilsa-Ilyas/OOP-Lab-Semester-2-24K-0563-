#include <iostream>
#include <string>

using namespace std;

class Date
{
    int month;
    int day;
    int year;

public:
    void set_month(int m)
    {
        month = m;
    }
    void set_day(int d)
    {
        day = d;
    }
    void set_year(int y)
    {
        year = y;
    }
    int get_month()
    {
        return month;
    }
    int get_day()
    {
        return day;
    }
    int get_year()
    {
        return year;
    }
    void Displaydate()
    {
        cout << month << "/" << day << "/" << year;
    }
};

int main()
{
    Date date;
    date.set_day(07);
    date.set_month(02);
    date.set_year(2025);
    date.Displaydate();
    return 0;
}