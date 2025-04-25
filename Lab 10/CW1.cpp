#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string encrypt (string text) {
    string encrypted = "";

    for (int i=0; i < text.length(); i++){
        encrypted += char(int(text[i] + (i+1)));
    }

    return encrypted;
}

string decrypt (string encrypted) {
    string decrypted = "";
    for (int i = 0; i < encrypted.length(); i++) {
        decrypted += char(encrypted[i] - (i + 1)); 
    }
    return decrypted;
}

int main() {
    string s;
    cout << "Enter String = ";
    getline(cin, s); 

    cout << "\nNormal Text: " << s;

    string encrypted = encrypt(s);

    ofstream outfile("data.txt");
    outfile << encrypted;
    outfile.close();
    cout << "\n Enxrypted";

    string fileData;
    ifstream infile("data.txt");
    getline(infile, fileData); 
    infile.close();

    string decrypted = decrypt(fileData);
    cout << "\n Decrypted:  " << decrypted;

    return 0;
}