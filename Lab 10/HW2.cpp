#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> todoList;

void fetchData() {
    ifstream input("tasks.txt");
    string line;
    while (getline(input, line)) {
        todoList.push_back(line);
    }
    input.close();
}

void updateFile() {
    ofstream output("tasks.txt");
    for (auto& item : todoList) {
        output << item << endl;
    }
    output.close();
}

void insertTask(string job) {
    todoList.push_back("[ ] " + job);
    updateFile();
}

void displayTasks() {
    for (int i = 0; i < todoList.size(); ++i) {
        cout << i + 1 << ". " << todoList[i] << endl;
    }
}

void completeTask(int pos) {
    if (pos >= 0 && pos < todoList.size()) {
        todoList[pos].replace(1, 1, "X");
        updateFile();
    }
}

int main() {
    fetchData();

    while (true) {
        cout << "\n1. New Task\n2. Show Tasks\n3. Finish Task\n4. Exit\nChoose: ";
        int inputChoice;
        cin >> inputChoice;
        cin.ignore();

        if (inputChoice == 1) {
            cout << "Describe task: ";
            string note;
            getline(cin, note);
            insertTask(note);
        }
        else if (inputChoice == 2) {
            displayTasks();
        }
        else if (inputChoice == 3) {
            displayTasks();
            cout << "Which task number was completed? ";
            int num;
            cin >> num;
            completeTask(num - 1);
        }
        else if (inputChoice == 4) {
            break;
        }
    }

    return 0;
}
