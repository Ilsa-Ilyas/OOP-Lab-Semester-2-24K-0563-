#include <iostream>
#include <cstdlib>  
using namespace std;

int main(int argc, char *argv[]) {
    int sum = 0;

    if (argc < 2) {
        cout << "At least 2 numbers required" << endl;
        return 1;
    }

    char **ptr = argv + 1;  
    for (int i = 1; i < argc; i++, ptr++) {
        sum += atoi(*ptr);  
    }

    cout << "The sum is: " << sum << endl;
    return 0;
}
