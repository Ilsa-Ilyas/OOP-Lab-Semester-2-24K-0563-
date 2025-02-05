#include <iostream>
#include <cstring>
using namespace std;

struct Person
{
    int id;
    char name[50];
};

void swap(Person &a, Person &b)
{
    Person temp = a;
    a = b;
    b = temp;
}

void sortByID(Person persons[], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (persons[j].id > persons[j + 1].id)
            {
                swap(persons[j], persons[j + 1]);
            }
        }
    }
}

void sortByName(Person persons[], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (strcmp(persons[j].name, persons[j + 1].name) > 0)
            {
                swap(persons[j], persons[j + 1]);
            }
        }
    }
}

void printData(Person persons[], int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "ID: " << persons[i].id << ", Name: " << persons[i].name << endl;
    }
    cout << endl;
}

int main()
{
    int N;
    cout << "Enter the number of persons: ";
    cin >> N;

    Person persons[N];

    for (int i = 0; i < N; i++)
    {
        cout << "Enter ID for person " << i + 1 << ": ";
        cin >> persons[i].id;
        cout << "Enter Name for person " << i + 1 << ": ";
        cin.ignore();
        cin.getline(persons[i].name, 50);
    }

    sortByID(persons, N);
    cout << "\nSorted by ID (Ascending Order):\n";
    printData(persons, N);

    sortByName(persons, N);
    cout << "\nSorted by Name (Lexicographical Order):\n";
    printData(persons, N);

    return 0;
}
