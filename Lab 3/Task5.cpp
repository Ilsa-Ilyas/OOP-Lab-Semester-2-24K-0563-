#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    string bookName;
    string isbnNumber;
    string authorName;
    string publisher;

public:
    Book()
    {
        bookName = "";
        isbnNumber = "";
        authorName = "";
        publisher = "";
    }

    Book(string bookName, string isbnNumber, string authorName, string publisher)
    {
        this->bookName = bookName;
        this->isbnNumber = isbnNumber;
        this->authorName = authorName;
        this->publisher = publisher;
    }

    string getBookName()
    {
        return this->bookName;
    }

    string getIsbnNumber()
    {
        return this->isbnNumber;
    }

    string getAuthorName()
    {
        return this->authorName;
    }

    string getPublisher()
    {
        return this->publisher;
    }

    string getBookInfo()
    {
        return "Book Name: " + bookName + "\nISBN: " + isbnNumber +
               "\nAuthor: " + authorName + "\nPublisher: " + publisher;
    }
};

int main(int argc, char *argv[])
{
    const int numBooks = 5;
    Book books[numBooks];

    for (int i = 0; i < numBooks; i++)
    {
        string bookName = argv[i * 4 + 1];
        string isbnNumber = argv[i * 4 + 2];
        string authorName = argv[i * 4 + 3];
        string publisher = argv[i * 4 + 4];

        books[i] = Book(bookName, isbnNumber, authorName, publisher);
    }

    for (int i = 0; i < numBooks; i++)
    {
        cout << "Book " << i + 1 << " Info:\n";
        cout << books[i].getBookInfo() << endl;
        cout << "-----------------------------------\n";
    }

    return 0;
}
