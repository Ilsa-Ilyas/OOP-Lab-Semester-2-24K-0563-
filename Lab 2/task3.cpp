#include <iostream>
using namespace std;

void resize(int *&arr, int &limit, int n)
{
    if (n >= limit)
    {
        int *newArr = new int[limit * 2];
        for (int i = 0; i < limit; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        limit *= 2;
        cout << "Limit has been doubled. New limit: " << limit << endl;
    }
}

int main()
{
    int limit = 5;
    int n = 0;
    int *num = new int[limit];

    while (true)
    {
        int choice;
        cout << "Enter a number (or '0' to exit): ";
        cin >> choice;

        if (choice == 0)
        {
            break;
        }

        resize(num, limit, n);

        num[n] = choice;
        n++;

        cout << "Number added: " << choice << endl;
    }

    int *finalArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        finalArr[i] = num[i];
    }
    delete[] num;

    cout << "Final array contents: ";
    for (int i = 0; i < n; i++)
    {
        cout << finalArr[i] << " ";
    }
    cout << endl;

    delete[] finalArr;

    return 0;
}
