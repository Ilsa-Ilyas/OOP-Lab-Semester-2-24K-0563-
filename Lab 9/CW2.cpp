#include <iostream>
#include <string>

using namespace std;

class Logger
{
private:
    static const int MAX_LOGS = 1000;
    string logs[MAX_LOGS];
    int logCount;

    void storeLog(const string &severity, const string &module, const string &message)
    {
        string formatted = "[" + severity + "] (" + module + "): " + message;

        if (logCount < MAX_LOGS)
        {
            logs[logCount++] = formatted;
        }
        else
        {
            for (int i = 1; i < MAX_LOGS; ++i)
            {
                logs[i - 1] = logs[i];
            }
            logs[MAX_LOGS - 1] = formatted;
        }
    }

public:
    Logger() : logCount(0) {}

    void logInfo(const string &module, const string &message)
    {
        storeLog("INFO", module, message);
    }

    void logWarning(const string &module, const string &message)
    {
        storeLog("WARNING", module, message);
    }

    void logError(const string &module, const string &message)
    {
        storeLog("ERROR", module, message);
    }

    friend class AuditingSystem;
};

class AuditingSystem
{
private:
    string validAuditorToken;

    bool authenticate(const string &token) const
    {
        return token == validAuditorToken;
    }

public:
    AuditingSystem(const string &token = "secure123") : validAuditorToken(token) {}

    void retrieveLogs(const Logger &logger, const string &token) const
    {
        if (!authenticate(token))
        {
            cout << "Access Denied: Invalid auditor token.\n";
            return;
        }

        cout << "--- Logs ---\n";
        for (int i = 0; i < logger.logCount; ++i)
        {
            cout << logger.logs[i] << endl;
        }
        cout << "--- End of Logs (" << logger.logCount << " entries) ---\n";
    }
};

int main()
{
    Logger l;

    l.logInfo("Network", "Connected to server.");
    l.logWarning("Database", "Slow response on query.");
    l.logError("Auth", "Login attempt failed.");
    l.logInfo("UI", "User clicked 'Submit'.");

    AuditingSystem auditor;

    cout << "\n--- Attempt with correct token ---\n";
    auditor.retrieveLogs(l, "secure123");

    cout << "\n--- Attempt with wrong token ---\n";
    auditor.retrieveLogs(l, "wrongToken");

    return 0;
}
