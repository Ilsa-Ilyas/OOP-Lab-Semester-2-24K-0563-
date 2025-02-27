#include <iostream>
#include <string>
using namespace std;

class BlendJuice {
public:
    void blend() {
        cout << "Blending.\n";
        for (int i = 0; i < 700000000; i++); 
        cout << "Blended!\n";
    }
};

class GrindJuice {
public:
    void grind() {
        cout << "Grinding.\n";
        for (int i = 0; i < 700000000; i++); 
        cout << "Done!\n";
    }
};

class JuiceMaker {
private:
    BlendJuice b;
    GrindJuice g;

public:
    void makeJuice() {
        b.blend();
        g.grind();
        cout << "Juice is ready!\n";
    }
};

int main() {
    JuiceMaker juice;
    juice.makeJuice();
    return 0;
}
