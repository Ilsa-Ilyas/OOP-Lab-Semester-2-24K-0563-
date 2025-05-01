#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LogWriter {
    string prefix;
    int limitSize;
    int fileCounter;

public:
    LogWriter(string pfx, int maxLen) {
        prefix = pfx;
        limitSize = maxLen;
        fileCounter = 1;
    }

    void writeLog(string text) {
        string filename = prefix + to_string(fileCounter) + ".txt";
        ofstream outputFile(filename, ios::app);

        if (outputFile.tellp() > limitSize) {
            outputFile.close();
            fileCounter++;
            filename = prefix + to_string(fileCounter) + ".txt";
            outputFile.open(filename);
        }

        outputFile << text << endl;
        outputFile.close();
    }
};

int main() {
    LogWriter lw("record", 100);

    for (int idx = 0; idx < 50; idx++) {
        lw.writeLog("Entry number " + to_string(idx) + " in the log system.");
    }

    return 0;
}
