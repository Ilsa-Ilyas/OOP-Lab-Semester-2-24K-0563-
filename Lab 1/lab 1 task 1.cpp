#include <iostream>
using namespace std;

int main() {
    float arr[6] = {5,5,4,3,2,1};

    int n = sizeof(arr) / sizeof(arr[0]);  

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) < *(arr + j + 1)) {  
                float temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }

    float highest = *arr;
    float secondHighest = -1;

    for (int i = 1; i < n; i++) {
        if (*(arr + i) < highest) {  
            secondHighest = *(arr + i);
            break;
        }
    }

    if (secondHighest != -1) {
        cout << "The second highest number is " << secondHighest << endl;
    } else {
        cout << "There is no second highest number (all values are the same)." << endl;
    }

    return 0;
}
