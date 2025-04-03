#include <iostream>
#include <string>
using namespace std;

// Base class for all media items
class Media {
protected:
    string mediaTitle;
    string publishDate;
    string mediaID;
    string mediaPublisher;

public:
    // Constructor to initialize core media attributes
    Media(string title, string date, string id, string publisher)
        : mediaTitle(title), publishDate(date), mediaID(id), mediaPublisher(publisher) {}

    // Virtual function to display media information
    virtual void displayInfo() {
        cout << "Title: " << mediaTitle << endl;
        cout << "Publication Date: " << publishDate << endl;
        cout << "ID: " << mediaID << endl;
        cout << "Publisher: " << mediaPublisher << endl;
    }

    // Function to simulate checking out a media item
    void checkOut() {
        cout << mediaTitle << " has been checked out." << endl;
    }

    // Function to simulate returning a media item
    void returnItem() {
        cout << mediaTitle << " has been returned." << endl;
    }
};

// Book class derived from Media
class Book : public Media {
    string bookAuthor;
    string isbnCode;
    int totalPages;

public:
    // Constructor to initialize all book attributes
    Book(string title, string date, string id, string publisher, string author, string isbn, int pages)
        : Media(title, date, id, publisher), bookAuthor(author), isbnCode(isbn), totalPages(pages) {}

    // Overridden function to display book-specific info
    void displayInfo() override {
        Media::displayInfo();
        cout << "Author: " << bookAuthor << endl;
        cout << "ISBN: " << isbnCode << endl;
        cout << "Pages: " << totalPages << endl;
    }
};

// DVD class derived from Media
class DVD : public Media {
    string dvdDirector;
    int movieDuration; // in minutes
    string movieRating;

public:
    // Constructor to initialize DVD attributes
    DVD(string title, string date, string id, string publisher, string director, int duration, string rating)
        : Media(title, date, id, publisher), dvdDirector(director), movieDuration(duration), movieRating(rating) {}

    // Overridden function to display DVD-specific info
    void displayInfo() override {
        Media::displayInfo();
        cout << "Director: " << dvdDirector << endl;
        cout << "Duration: " << movieDuration << " mins" << endl;
        cout << "Rating: " << movieRating << endl;
    }
};

// CD class derived from Media
class CD : public Media {
    string albumArtist;
    int trackCount;
    string musicGenre;

public:
    // Constructor to initialize CD attributes
    CD(string title, string date, string id, string publisher, string artist, int tracks, string genre)
        : Media(title, date, id, publisher), albumArtist(artist), trackCount(tracks), musicGenre(genre) {}

    // Overridden function to display CD-specific info
    void displayInfo() override {
        Media::displayInfo();
        cout << "Artist: " << albumArtist << endl;
        cout << "Tracks: " << trackCount << endl;
        cout << "Genre: " << musicGenre << endl;
    }
};

// Main function demonstrating functionality
int main() {
    // Create a book object
    Book cppBook("Mastering C++", "2022-06-15", "BK102", "CodeWorld", "Alice Morgan", "987-654321", 640);
    
    // Create a DVD object
    DVD sciFiDVD("Interstellar", "2014-11-07", "DVD309", "Paramount", "Christopher Nolan", 169, "PG-13");
    
    // Create a CD object
    CD popAlbum("Future Nostalgia", "2020-03-27", "CD147", "Warner Records", "Dua Lipa", 11, "Pop");

    // Display details
    cppBook.displayInfo();
    cout << "-----------------------------" << endl;
    sciFiDVD.displayInfo();
    cout << "-----------------------------" << endl;
    popAlbum.displayInfo();
    cout << "-----------------------------" << endl;

    // Demonstrate checkOut and return functionality
    cppBook.checkOut();
    sciFiDVD.returnItem();

    return 0;
}
