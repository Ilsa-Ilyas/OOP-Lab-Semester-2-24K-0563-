#include<iostream>
#include<string>

using namespace std;


class User{
    public:
    string name;
    int age;
};

int main() {
    User user;
    user.name="Teo";
    user.age=24;

    cout << "My name is " << user.name << "and I am " << user.age << " years old" << endl;

}