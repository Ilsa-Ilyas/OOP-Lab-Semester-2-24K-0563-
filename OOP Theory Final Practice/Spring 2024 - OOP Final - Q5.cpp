#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class JewelleryItem {
	protected: 
	    string ItemCode;
		string ItemName;
		double weightGrams;
		int purity;
	
	public:
		JewelleryItem (string code, string name, double weight, int p) {
			ItemCode = code;
			ItemName = name;
			weightGrams = weight;
			purity = p;
		}
		
		virtual void displayDetails() const = 0;
		
		virtual double calculatePrice() const = 0;
		
		// Virtual destructor for proper cleanup
        virtual ~JewelleryItem() {}
};

class GoldJewellery : public JewelleryItem {
	private:
		int goldKarat;
		
	public:
		GoldJewellery (int karat, string code, string name, double weight, int p) : JewelleryItem (code, name, weight, p) {
			goldKarat = karat;
		}
		
		void setGoldKarat (int karat) {
			goldKarat = karat;
		}
		
		double calculatePrice () const override {
		return weightGrams * (purity / 100.0) * goldKarat * 50; // Example pricing formula
        }
 	    
 	   void displayDetails () const override {
 	   	cout << "Gold Jewelry Item\n";
        cout << "Item Code: " << ItemCode << endl;
        cout << "Item Name: " << ItemName << endl;
        cout << "Weight: " << weightGrams << " grams\n";
        cout << "Purity: " << purity << "K\n";
        cout << "Gold Karat: " << goldKarat << "K\n";
        cout << "Price: PKR " << calculatePrice() << endl;
       } 
};

class DiamondJewellery : public JewelleryItem {
	private:
		int numDiamonds;
		double DiamondCarat;
		
	public:
		DiamondJewellery (int number, double carat, string code, string name, double weight, int p) : JewelleryItem (code, name, weight, p) {
			numDiamonds = number;
			DiamondCarat = carat;
		}
		
		void addDiamonds (int number, double carat) {
			numDiamonds = number;
			DiamondCarat = carat;
		}
		
		void displayDetails() const override {
		cout << "Item Code: " << itemCode << endl;
		cout << "Item Name: " << itemName << endl;
		cout << "Weight: " << weightInGrams << " grams" << endl;
		cout << "Purity: " << purity << "%" << endl;
		cout << "Number of Diamonds: " << numDiamonds << endl;
		cout << "Diamond Carat: " << diamondCarat << endl;
		}
		
		double calculatePrice() const override {
		return weightInGrams * (purity / 100.0) * diamondCarat * 1000; // Example pricing formula
		}
};

class Customer {
private:
    string CustomerID;
    string name;
    JewelryItem* purchasedGold;
    JewelryItem* purchasedDiamond;

public:
    Customer(string id, string n) {
        CustomerID = id;
        name = n;
        purchasedGold = NULL;
        purchasedDiamond = NULL;
    }

    void purchaseGold(GoldJewellery* gold) {
        purchasedGold = gold; 
    }

    void purchaseDiamond(DiamondJewellery* diamond) {
        purchasedDiamond = diamond; 
    }

    double calculateTotalPurchasePrice() {
        double total = 0.0;

        if (purchasedGold != NULL) {
            total += purchasedGold->calculatePrice();
        }
        if (purchasedDiamond != NULL) {
            total += purchasedDiamond->calculatePrice();
        }
        return total;
    }
};

class StoreInventory {
    static const int MAX_ITEMS = 10;
    JewelryItem* inventory[MAX_ITEMS];  // Array of base class pointers
    int itemCount;                      // Number of items added
    
    public:
    StoreInventory() {
        itemCount = 0;
        for (int i = 0; i < MAX_ITEMS; i++)
            inventory[i] = NULL;
    }
    
    // Add item to inventory
    void addItemToInventory(JewelryItem* item) {
        if (itemCount < MAX_ITEMS) {
            inventory[itemCount++] = item;
        } else {
            cout << "Inventory full. Cannot add more items.\n";
        }
    }

    // Display all inventory items
    void displayInventory() const {
        cout << "----- Store Inventory -----\n";
        for (int i = 0; i < itemCount; i++) {
            if (inventory[i] != NULL) {
                inventory[i]->displayDetails();
                cout << "---------------------------\n";
            }
        }
    }
};

    // Overload comparison operators based on price
	bool operator<(const JewelleryItem& item1, const JewelleryItem& item2) {
    return item1.calculatePrice() < item2.calculatePrice();
    }
	
	bool operator>(const JewelleryItem& item1, const JewelleryItem& item2) {
    return item1.calculatePrice() > item2.calculatePrice() 
	}
	
	bool operator==(const JewelleryItem& item1, const JewelleryItem& item2) {
    return item1.calculatePrice() == item2.calculatePrice()
	}

	




