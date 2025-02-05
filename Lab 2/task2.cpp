#include <iostream>
using namespace std;

void initialise(int num[], char *argv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        num[i] = atoi(*(argv + i + 1));
    }
}

void *alter(void *num, int n)
{
    int *arr = (int *)num;
    for (int i = 0; i < n; i++)
    {
        arr[i] += 10;
    }
    return num;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "At least 1 number is required" << endl;
        return 1;
    }

    int n = argc - 1;
    int num[n];

    initialise(num, argv, n);

    alter(num, n);

    cout << "Modified array: ";
    for (int i = 0; i < n; i++)
    {
        cout << num[i] << " ";
    }
    cout << endl;

    return 0;
}