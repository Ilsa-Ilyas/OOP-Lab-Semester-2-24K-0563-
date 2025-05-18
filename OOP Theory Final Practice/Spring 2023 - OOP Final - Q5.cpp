#include <iostream>
#include <string>
#include <fstream>
#include <exception>

using namespace std;

// ---- Exception Class ----
class Bot_Exception : public exception {
    string message;
public:
    Bot_Exception(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// ---- User Class ----
class User {
public:
    string username, country, interest;
    int age;

    User(string u, string c, string i, int a) : username(u), country(c), interest(i), age(a) {}
};

// ---- Base Chatbot Class ----
class Chatbot {
protected:
    string lastUser;
    int userCount = 0;
public:
    virtual string generate_response(const string& query, const User& user) = 0;
    int getUserCount() const { return userCount; }
    string getLastUser() const { return lastUser; }
    virtual ~Chatbot() {}
};

// ---- Derived Bots ----
class MedicalChatbot : public Chatbot {
public:
    string generate_response(const string& query, const User& user) override {
        lastUser = user.username;
        userCount++;
        return "MedicalBot: " + query;
    }
};

class TechnologyChatbot : public Chatbot {
public:
    string generate_response(const string& query, const User& user) override {
        lastUser = user.username;
        userCount++;
        return "TechBot: " + query;
    }
};

class LegalChatbot : public Chatbot {
public:
    string generate_response(const string& query, const User& user) override {
        lastUser = user.username;
        userCount++;
        return "LegalBot: " + query;
    }
};

class GeneralChatbot : public Chatbot {
public:
    string generate_response(const string& query, const User& user) override {
        lastUser = user.username;
        userCount++;
        return "GeneralBot: " + query;
    }
};

// ---- Chat System ----
class ChatSystem {
    MedicalChatbot med;
    TechnologyChatbot tech;
    LegalChatbot legal;
    GeneralChatbot general;

    void logError(const string& username, const string& query) {
        ofstream fout("error_log.txt", ios::app);
        fout << username << "|" << query << "\n";
        fout.close();
    }

    string getPrefix(const string& query) {
        string prefix = "";
        for (char ch : query) {
            if (ch == ' ') break;
            prefix += ch;
        }
        return prefix;
    }

public:
    string Ask(const User& user, const string& query) {
        string prefix = getPrefix(query);
        try {
            if (prefix == "doc") return med.generate_response(query, user);
            else if (prefix == "attorney") return legal.generate_response(query, user);
            else if (prefix == "guru") return tech.generate_response(query, user);
            else if (prefix == "special") {
                if (user.interest == "medical") return med.generate_response(query, user);
                else if (user.interest == "legal") return legal.generate_response(query, user);
                else if (user.interest == "technology") return tech.generate_response(query, user);
                else return general.generate_response(query, user);
            } else {
                throw Bot_Exception("Invalid query prefix: " + prefix);
            }
        } catch (const Bot_Exception& e) {
            logError(user.username, query);
            throw;
        }
    }

    void Analysis() {
        ifstream fin("error_log.txt");
        string line;
        string topUser;
        int maxCount = 0;
        const int MAX_USERS = 100;
        string users[MAX_USERS];
        int counts[MAX_USERS] = {0};
        int userSize = 0;

        while (getline(fin, line)) {
            size_t sep = line.find('|');
            if (sep == string::npos) continue;
            string uname = line.substr(0, sep);
            string query = line.substr(sep + 1);

            bool found = false;
            for (int i = 0; i < userSize; ++i) {
                if (users[i] == uname) {
                    counts[i]++;
                    if (counts[i] > maxCount) {
                        maxCount = counts[i];
                        topUser = users[i];
                    }
                    found = true;
                    break;
                }
            }
            if (!found && userSize < MAX_USERS) {
                users[userSize] = uname;
                counts[userSize] = 1;
                if (counts[userSize] > maxCount) {
                    maxCount = 1;
                    topUser = uname;
                }
                userSize++;
            }

            // Word count
            int words = 0;
            for (char ch : query) {
                if (ch == ' ') words++;
            }
            cout << uname << " query word count: " << words + 1 << endl;
        }
        fin.close();

        cout << "\nUser with most exceptions: " << topUser << " (" << maxCount << " times)\n";
    }
};

// ---- Demo Main ----
int main() {
    ChatSystem system;
    User u1("Ali", "Pakistan", "medical", 22);
    User u2("Sara", "USA", "technology", 30);
    User u3("Ahmed", "UAE", "legal", 35);

    string queries[] = {
        "doc I feel sick",
        "guru How to fix my laptop?",
        "special Suggest a remedy",
        "hello this is invalid",
        "attorney What is the law on contracts?",
        "special Help me with lawsuit",
        "nope this should error"
    };

    User users[] = {u1, u2, u1, u3, u3, u3, u2};

    for (int i = 0; i < 7; ++i) {
        try {
            cout << system.Ask(users[i], queries[i]) << "\n";
        } catch (const Bot_Exception& e) {
            cerr << "Exception: " << e.what() << "\n";
        }
    }

    system.Analysis();
    return 0;
}
