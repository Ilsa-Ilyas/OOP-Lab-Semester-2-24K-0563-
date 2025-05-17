//Part B

//investor
    // Pure virtual function
    virtual bool canBuyStock(Stock& stock, int purchaseQuantity) const = 0;
    
//dayTrader
    bool canBuyStock(Stock& stock, int purchaseQuantity) const override {
        if (hasLoan) {
            cout << "Error: DayTrader cannot buy stock while having a loan.\n";
            return false;
        }

        double totalCost = stock.getPrice() * purchaseQuantity;
        if (totalCost > availableFunds) {
            cout << "Error: Insufficient funds for DayTrader to buy stock.\n";
            return false;
        }
        return stock.isEligibleToBuy(purchaseQuantity);
    }
};

//long term investor
    bool canBuyStock(Stock& stock, int purchaseQuantity) const override {
        if (hasLoan && availableFunds < 50000) {
            cout << "Error: LongTermInvestor with a loan must have at least 50,000 in available funds.\n";
            return false;
        }

        if (purchaseQuantity > stock.getMaxQuantityPerInvestor()) {
            cout << "Error: Purchase quantity exceeds max allowed per investor.\n";
            return false;
        }

        return stock.isEligibleToBuy(purchaseQuantity);
    }
};