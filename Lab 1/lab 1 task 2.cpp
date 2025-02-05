#include <iostream>
using namespace std;

int main()
{
    float arr[] = {1.2, 4.5, 2.5, 6.2, 5.2, 6.5, 7.4, 8.0, 120.56};
    int n = sizeof(arr) / sizeof(arr[0]); 
    float sum = 0;

    float *ptr = arr; 
    
    for (int i = 0; i < n; i++)
    {
        sum += *(ptr + i);
    }

    cout << "Sum of elements in the arr is: " << sum << endl;

    return 0;
}