#include <iostream>
#include <string>

using namespace std;

class Books {
protected:
    string genre;

public:
    Books(string g) : genre(g) {}

    void displayGenre() {
        cout << "Genre is: " << genre << endl;
    }
};

class Novel : public Books {
private:
    string title;
    string author;

public:
    Novel(string genre, string title, string author) 
        : Books(genre), title(title), author(author) {}

    void displayDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        displayGenre();
    }
};

class Mystery : public Books {
private:
    string title;
    string author;

public:
    Mystery(string genre, string title, string author)
        : Books(genre), title(title), author(author) {}

    void displayDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        displayGenre();
    }
};

int main() {
    Novel novel("Fiction", "Pride and Prejudice", "Jane Austen");
    Mystery mystery("Mystery", "The Silent Patient", "Alex Michaelides");

    cout << "Novel Book Details:" << endl;
    novel.displayDetails();
    cout << endl;

    cout << "Mystery Book Details:" << endl;
    mystery.displayDetails(); 

    return 0;
}
