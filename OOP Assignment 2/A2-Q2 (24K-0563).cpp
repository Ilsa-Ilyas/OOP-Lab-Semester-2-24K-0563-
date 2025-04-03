#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "Ilsa Ilyas"
#define STUDENT_ID "24K-0563"

// Constants
const int MAX_GHOSTS = 10;
const int MAX_VISITORS = 10;

// Forward declaration
class Visitor;

// -------------------- Base Ghost Class --------------------
class Ghost {
protected:
    string operatorName;
    int frightFactor;

public:
    Ghost(string name, int fright) : operatorName(name), frightFactor(fright) {}

    virtual void performHaunt() const = 0;
    virtual string getType() const = 0;

    int getFright() const { return frightFactor; }

    virtual ~Ghost() {}

    friend ostream& operator<<(ostream& out, const Ghost& g) {
        out << g.getType() << " played by: " << g.operatorName 
            << ", Scare Level: " << g.frightFactor;
        return out;
    }

    // Overload +
    friend Ghost* operator+(const Ghost& g1, const Ghost& g2);
};

// -------------------- Upgraded Ghost --------------------
class UpgradedGhost : public Ghost {
public:
    UpgradedGhost(string name, int fright) : Ghost(name, fright) {}

    void performHaunt() const override {
        cout << "Upgraded Ghost (" << operatorName 
             << ") haunts with combined scare level " << frightFactor << "!" << endl;
    }

    string getType() const override {
        return "UpgradedGhost";
    }
};

Ghost* operator+(const Ghost& g1, const Ghost& g2) {
    string combined = g1.operatorName + " & " + g2.operatorName;
    int combinedFright = g1.frightFactor + g2.frightFactor;
    return new UpgradedGhost(combined, combinedFright);
}

// -------------------- Derived Ghost Types --------------------
class Poltergeist : virtual public Ghost {
public:
    Poltergeist(string name, int fright) : Ghost(name, fright) {}

    void performHaunt() const override {
        cout << "Poltergeist " << operatorName << " moves objects!" << endl;
    }

    string getType() const override {
        return "Poltergeist";
    }
};

class Banshee : public Ghost {
public:
    Banshee(string name, int fright) : Ghost(name, fright) {}

    void performHaunt() const override {
        cout << "Banshee " << operatorName << " screams loudly!" << endl;
    }

    string getType() const override {
        return "Banshee";
    }
};

class ShadowGhost : virtual public Ghost {
public:
    ShadowGhost(string name, int fright) : Ghost(name, fright) {}

    void performHaunt() const override {
        cout << "ShadowGhost " << operatorName << " whispers creepily..." << endl;
    }

    string getType() const override {
        return "ShadowGhost";
    }
};

class ShadowPoltergeist : public Poltergeist, public ShadowGhost {
public:
    ShadowPoltergeist(string name, int fright)
        : Ghost(name, fright), Poltergeist(name, fright), ShadowGhost(name, fright) {}

    void performHaunt() const override {
        cout << "ShadowPoltergeist " << operatorName 
             << " moves objects and whispers at scare level " << frightFactor << "!" << endl;
    }

    string getType() const override {
        return "ShadowPoltergeist";
    }
};

// -------------------- Visitor Class --------------------
class Visitor {
    string name;
    int bravery;

public:
    Visitor(string name, int bravery) : name(name), bravery(bravery) {}

    string getName() const { return name; }
    int getBravery() const { return bravery; }

    void getBraveryRange(int& low, int& high) const {
        if (bravery <= 4) {
            low = 1; high = 4;
        } else if (bravery <= 7) {
            low = 5; high = 7;
        } else {
            low = 8; high = 10;
        }
    }
};

// -------------------- Haunted House Class --------------------
class HauntedHouse {
    string name;
    Ghost* ghosts[MAX_GHOSTS];
    int ghostCount;

public:
    HauntedHouse(string name) : name(name), ghostCount(0) {}

    void addGhost(Ghost* g) {
        if (ghostCount < MAX_GHOSTS) {
            ghosts[ghostCount++] = g;
        }
    }

    string getHouseName() const { return name; }

    Ghost** getGhosts() { return ghosts; }
    int getGhostCount() const { return ghostCount; }

    ~HauntedHouse() {
        for (int i = 0; i < ghostCount; ++i) {
            delete ghosts[i];
        }
    }

    friend void simulateVisit(HauntedHouse& house, Visitor visitors[], int numVisitors);
};

// -------------------- Global Simulation Function --------------------
void simulateVisit(HauntedHouse& house, Visitor visitors[], int numVisitors) {
    cout << "\n=== Haunted House: " << house.getHouseName() << " ===\n";
    for (int i = 0; i < house.getGhostCount(); ++i) {
        Ghost* g = house.getGhosts()[i];
        cout << *g << endl;
        g->performHaunt();

        for (int j = 0; j < numVisitors; ++j) {
            int low, high;
            visitors[j].getBraveryRange(low, high);
            cout << "Visitor " << visitors[j].getName() << " (Bravery " << visitors[j].getBravery() << "): ";

            if (g->getFright() < low) {
                cout << "laughs and taunts the ghost!" << endl;
            } else if (g->getFright() > high) {
                cout << "screams and runs away!" << endl;
            } else {
                cout << "responds with a shaky voice..." << endl;
            }
        }
        cout << "-------------------------------\n";
    }
}

// -------------------- Main --------------------
int main() {
    // Visitors
    Visitor visitors[] = {
        Visitor("Ali", 3),
        Visitor("Sara", 6),
        Visitor("Zain", 9)
    };
    int numVisitors = 3;

    // Haunted Houses
    HauntedHouse house1("Whispering Manor");
    HauntedHouse house2("Cursed Asylum");

    // Add ghosts to house 1
    house1.addGhost(new Poltergeist("Raza", 3));
    house1.addGhost(new Banshee("Mira", 7));
    house1.addGhost(new ShadowGhost("Usman", 5));
    house1.addGhost(new ShadowPoltergeist("Lina", 6));

    // Add ghosts to house 2
    Ghost* g1 = new Banshee("Ayan", 4);
    Ghost* g2 = new ShadowGhost("Noor", 6);
    Ghost* upgraded = *g1 + *g2;

    house2.addGhost(g1);
    house2.addGhost(g2);
    house2.addGhost(upgraded);

    // Simulate visits
    simulateVisit(house1, visitors, numVisitors);
    simulateVisit(house2, visitors, numVisitors);

    return 0;
}
