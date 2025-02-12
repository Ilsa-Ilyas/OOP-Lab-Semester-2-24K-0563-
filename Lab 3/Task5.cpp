#include <iostream>
#include <string>

using namespace std;

class Book
{
private:
    string name;
    string ISBN;
    string author;
    string publisher;

public:
    Book()
    {
        name = "";
        ISBN = "";
        author = "";
        publisher = "";
    }
    Book(string name, string ISBN, string author, string publisher)
    {
        this->name = name;
        this->ISBN = ISBN;
        this->author = author;
        this->publisher = publisher;
    }

    string getName() { return name; }
    string getISBN() { return ISBN; }
    string getAuthor() { return author; }
    string getPublisher() { return publisher; }

    string getBookInfo()
    {
        return "Book Name: " + name + "\nISBN: " + ISBN + "\nAuthor: " + author + "\nPublisher: " + publisher + "\n";
    }
};

void intialize(Book b[], char *argv[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = Book(argv[i * 4 + 1], argv[i * 4 + 2], argv[i * 4 + 3], argv[i * 4 + 4]);
    }
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 4 != 0)
    {
        cout << "Insufficent arguments." << endl;
        return 1;
    }

    int n = (argc - 1) / 4;
    Book b[n];

    intialize(b, argv, n);

    cout << "Book Information:\n";
    cout << "-----------------\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "Book " << i + 1 << ":\n";
        cout << b[i].getBookInfo() << endl;
    }
}