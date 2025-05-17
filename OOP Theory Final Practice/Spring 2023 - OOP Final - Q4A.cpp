//Part A

//stock
    virtual bool isEligibleToBuy(int purchaseQuantity) const {
        if (purchaseQuantity <= 0) {
            cout << "Error: purchase quantity is invalid\n";
            return false;
        }
        if (purchaseQuantity > maxQuantityPerInvestor) {
            cout << "Error: purchase quantity exceeds maximum limit per investor\n";
            return false;
        }
        if (purchaseQuantity > availableQuantity) {
            cout << "Error: purchase quantity exceeds available quantity\n";
            return false;
        }
        return true;
    }

//tech stock
    bool isEligibleToBuy(int purchaseQuantity) const override {
        // first ensure base conditions pass
        if (!Stock::isEligibleToBuy(purchaseQuantity)) 
            return false;

        if (purchaseQuantity % 10 != 0) {
            cout << "Error: purchase quantity must be a multiple of 10 for TechStock\n";
            return false;
        }
        if (purchaseQuantity > 100) {
            cout << "Error: maximum purchase quantity for TechStock is 100\n";
            return false;
        }
        return true;
    }
};

//pharma stock
    // 3. PharmaStock adds two different checks
    bool isEligibleToBuy(int purchaseQuantity) const override {
        if (!Stock::isEligibleToBuy(purchaseQuantity))
            return false;

        if (purchaseQuantity < 50) {
            cout << "Error: minimum purchase quantity for PharmaStock is 50\n";
            return false;
        }
        if (purchaseQuantity % 5 != 0) {
            cout << "Error: purchase quantity must be a multiple of 5 for PharmaStock\n";
            return false;
        }
        return true;
    }
};