#include<iostream>
using namespace std;
class Book{
    string author;
    string title;
    string publisher;
    int stock;
    float price;
    public:
    Book(string a, string t, string p, int s,float pr):author(a),title(t),publisher(p),price(pr){
        if(s<0){
            stock=0;
        }
        else{
            stock=s;
        }
    };
    void getBookDetails(){
        cout<<"\n Author : "<< author;
        cout<<"\n Title : "<<title;
        cout<<"\n Publisher : "<<publisher;
        cout<<"\n Stock : "<<stock;
    };
    string getAuthor(){
        return author;
    };
    string getTitle(){
        return title;
    };
    int getStock(){
        return stock;
    };
    double getTotal(int quantity){
        return quantity*price;
    }
    void updateStock(int n){
        stock-=n;
    }
};
class Store{
    Book** book;
    int bookCount;
    int bookCapacity;
    public:
    Store(int c):bookCount(0),bookCapacity(c){
        book=new Book*[bookCapacity];
    };
    ~Store() {
        for (int i = 0; i < bookCount; i++) {
            delete book[i];
        }
        delete[] book;
    }
    void addbook(Book* b){
        if(bookCount<bookCapacity){
            book[bookCount]=b;
            bookCount++;
            cout<<"Book Added Successfully"<<endl;            
        }else{
            bookCapacity*=2;
            Book** temp=new Book*[bookCapacity];
            for (int i = 0; i < bookCount; i++)
            {
                temp[i]=book[i];
            }
            delete[] book;
            book=temp;
            book[bookCount]=b;
            bookCount++;
            cout<<"Book Added Successfully"<<endl;            
        }
    }
    void purchaseBook(string tit,string aut){
        int flag=0;
        for (int i = 0; i < bookCount; i++)
        {
            if (book[i]->getTitle()==tit && book[i]->getAuthor()==aut)
            {
                flag=1;
                cout<<"\n Book found ";
                book[i]->getBookDetails();
                int n;
                cout<<"\n Enter Number of Copies : ";
                cin>>n;
                if (n<=book[i]->getStock())
                {
                    cout<<"\n Required Stock available \n Total Cost : "<<book[i]->getTotal(n);
                    book[i]->updateStock(n);
                }else{
                    cout<<"\n Not enough Stock";
                }
                return;
            }
            
        }
        if(!flag){
            cout<<"\n No Book Found";  
        }
        
    }
};
int main() {
    Store store(2);

    while (true) {
        cout << "\n--- Book Store Menu ---";
        cout << "\n1. Add Book";
        cout << "\n2. Purchase Book";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string author, title, publisher;
            int stock;
            float price;

            cout << "\nEnter Book Author: ";
            getline(cin, author);
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Publisher: ";
            getline(cin, publisher);
            cout << "Enter Stock: ";
            cin >> stock;
            cout << "Enter Price: ";
            cin >> price;

            Book* b = new Book(author, title, publisher, stock, price);
            store.addbook(b);
        } else if (choice == 2) {
            string author, title;
            cout << "\nEnter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);

            store.purchaseBook(title, author);
        } else if (choice == 3) {
            cout << "\nExiting program...\n";
            break;
        } else {
            cout << "\nInvalid Choice. Try again!\n";
        }
    }

    return 0;
}