#include<iostream>
#include<vector>
using namespace std;
class Menu{
    string name;
    string type;
    int price;
    public:
    Menu(string n, string t, int p):name(n),type(t){
        if(p<0){
            price=0;
        }
        else{
            price=p;
        }
    };
    void display(){
        cout<<"\n Name : "<<name;
        cout<<"\n Type : "<<type;
        cout<<"\n Price : "<<price;
    };
    string getType(){
        return type;
    };
    string getName(){
        return name;
    };
    int getTotal(int num){
        return num*price;
    }
    int getPrice(){
        return price;
    }
};
class CoffeeShop{
    Menu** menu;
    int menuCount;
    int menuCapacity;
    vector<string> order;
    public:
    CoffeeShop(int c):menuCount(0),menuCapacity(c){
        menu=new Menu*[menuCapacity];
    };
    void addMenu(Menu* m){
        if(menuCount<menuCapacity){
            menu[menuCount]=m;
            menuCount++;
            cout<<"Menu Added Successfully"<<endl;
        }else{
            menuCapacity*=2;
            Menu** temp=new Menu*[menuCapacity];
            for (int i = 0; i < menuCount; i++)
            {
                temp[i]=menu[i];
            }
            delete[]menu;
            menu=temp;
            menu[menuCount]=m;
            menuCount++;
            cout<<"Menu Added Successfully"<<endl;
        }
    };
    void displayMenu(){
        for (int i = 0; i < menuCount; i++)
        {
            menu[i]->display();
        }
    };
    void addOrder(string n){
        int flag=0;
        for (int i = 0; i < menuCount; i++)
        {
            if (menu[i]->getName()==n)
            {
                order.push_back(n);
                cout<<"\n Order Added Successfully";
                flag=1;
                return;
            }
        }
        if (!flag)
        {
            cout<<"\n No such item found";
        }
    };
    void fullFilledOrder(){
        if (order.empty())
        {
            cout<<"\n All Order Has Been Full Filled ";
        }else{
            for (auto i = order.begin(); i != order.end(); ++i)
            {
                cout << "\n The Item : " << *i << " is ready ";
            }
        }
        
    };
    void listOrder(){
        if (order.empty())
        {
            cout<<"\n {}";
        }else{
            for (auto i = order.begin(); i != order.end(); ++i)
            {
                cout << "\n " << *i ;
            }
        }
    };
    int dueAmount(){
        int total=0;
        for (auto i = order.begin(); i != order.end(); ++i)
        {
            for (int j = 0; j < menuCount; j++)
            {
                if (menu[j]->getName()==*i)
                {
                    total+=menu[j]->getPrice();
                }
                
            }
            
        }
        return total;
    }
 void cheapestItem(){
    if (menuCount == 0) {
        cout << "\n No items in the menu.";
        return;
    }
    
    int min = menu[0]->getPrice(); 
    string cheapestItem = menu[0]->getName();

    for (int i = 1; i < menuCount; i++) { 
        if (menu[i]->getPrice() < min) {
            min = menu[i]->getPrice();
            cheapestItem = menu[i]->getName();
        }
    }
    cout << "\n Cheapest Item : " << cheapestItem << " (Price: " << min << ")";
}

    void drinksOnly(){
        for (int i = 0; i < menuCount; i++)
        {
            if (menu[i]->getType()=="drink")
            {
                menu[i]->display();
            }
        }
    };
    void foodOnly(){
        for (int i = 0; i < menuCount; i++)
        {
            if (menu[i]->getType()=="food")
            {
                menu[i]->display();
            }
        }
    };
};
int main(){
    CoffeeShop c(5);
    Menu m1("Coffee","drink",100);
    Menu m2("Tea","drink",50);
    Menu m3("Burger","food",200);
    Menu m4("Pizza","food",300);
    Menu m5("Cold Drink","drink",40);
    c.addMenu(&m1);
    c.addMenu(&m2);
    c.addMenu(&m3);
    c.addMenu(&m4);
    c.addMenu(&m5);
    c.displayMenu();
    c.addOrder("Coffee");
    c.addOrder("Tea");
    c.addOrder("Burger");
    c.addOrder("Pizza");
    c.addOrder("Cold Drink");
    c.fullFilledOrder();
    c.listOrder();
    cout<<"\n Due Amount : "<<c.dueAmount();
    c.cheapestItem();
    c.drinksOnly();
    c.foodOnly();
    return 0;
}