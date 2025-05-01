#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Staff {
    int code;
    string employeeName;
    string position;
    int duration;
};

vector<Staff> staffList;

void exportData() {
    ofstream outFile("database.txt");
    for (const auto& s : staffList) {
        outFile << s.code << "," << s.employeeName << "," << s.position << "," << s.duration << "\n";
    }
    outFile.close();
}

void importData() {
    ifstream inFile("database.txt");
    staffList.clear();
    string entry;
    while (getline(inFile, entry)) {
        size_t p1 = entry.find(",");
        size_t p2 = entry.find(",", p1 + 1);
        size_t p3 = entry.find(",", p2 + 1);

        Staff temp;
        temp.code = stoi(entry.substr(0, p1));
        temp.employeeName = entry.substr(p1 + 1, p2 - p1 - 1);
        temp.position = entry.substr(p2 + 1, p3 - p2 - 1);
        temp.duration = stoi(entry.substr(p3 + 1));

        staffList.push_back(temp);
    }
    inFile.close();
}

vector<Staff> fetchQualifiedManagers() {
    vector<Staff> filtered;
    for (const auto& s : staffList) {
        if (s.position == "manager" && s.duration >= 2) {
            filtered.push_back(s);
        }
    }
    return filtered;
}

void retainOnly(const vector<Staff>& keep) {
    staffList = keep;
}

void appendModifiedRecords(const vector<Staff>& base) {
    for (auto s : base) {
        s.code += 100;
        s.duration += 1;
        staffList.push_back(s);
    }
}

int main() {
    staffList = {
        {1, "Zain", "manager", 3},
        {2, "Maya", "developer", 1},
        {3, "Ayan", "manager", 2},
        {4, "Sara", "designer", 4}
    };
    exportData();

    importData();
    auto managers = fetchQualifiedManagers();

    cout << "Qualified Managers:\n";
    for (const auto& s : managers) {
        cout << s.code << " " << s.employeeName << " " << s.position << " " << s.duration << "\n";
    }

    retainOnly(managers);
    exportData();

    importData();
    appendModifiedRecords(managers);
    exportData();

    importData();
    cout << "\nFinal Staff Data:\n";
    for (const auto& s : staffList) {
        cout << s.code << " " << s.employeeName << " " << s.position << " " << s.duration << "\n";
    }

    return 0;
}