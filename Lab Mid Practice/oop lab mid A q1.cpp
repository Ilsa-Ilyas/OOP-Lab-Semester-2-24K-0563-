#include <iostream>
#include <string>

using namespace std;

class BankAccount {
	static int AccNumber; // To generate unique account numbers
	static int TotalAccs; // To track total active accounts
	static const string bankName;  // Constant bank name for all accounts
	const int accountNumber;  // Unique and immutable account number
	double balance;   // Account balance
	
	public:
	BankAccount () : accountNumber(AccNumber ++), balance (0.0) {
		TotalAccs ++;
	}
	~BankAccount() {
		TotalAccs--;
	}
	
	void deposit(double amount) {
		if(amount > 0){
			balance+=amount;
			cout << "Deposited: $ " << amount << endl;
		}
		else {
			cout << "Invalid Deposit" << endl;
		}
	}
	
	void withdraw(double amount) {
		if(amount <= balance) {
			balance-=amount;
			cout << "Withdrawn: " << amount << endl;
		}
		else{
			cout << "Invalid Withdrawel Amount" << endl;
		}
	}
	
	void display() const{
		cout << "Account Number: " << accountNumber << endl;
		cout << "Balance: " << balance << endl;
		cout << "Bank Name: " << bankName << endl;
	}
	
	static int getActiveAccountCount () {
		return TotalAccs;
	}
	};
	
	// Initialize static members
	int BankAccount :: AccNumber = 5300;
	int BankAccount :: TotalAccs = 0;
	const string BankAccount :: bankName = "LALA Bank";
	
	int main() {
		// Create accounts dynamically
		BankAccount *a1 = new BankAccount ();
		BankAccount *a2 = new BankAccount ();
		
		cout << "Account Details: " << endl;
		a1->display();
		a2->display();
		
		cout << "Total Active Accounts: " << BankAccount::getActiveAccountCount() << endl;
		
		a1->deposit(1900);
		a1->withdraw(2000);
		
		a2->deposit(200);
		a2->withdraw(50);
		
		cout << "Updated Account Details: " << endl;
		a1->display();
		a2->display();
		
		delete a2;
		cout << "Active Accounts Remaining: " << BankAccount::getActiveAccountCount() << endl;
		
		return 0;
	}
	
	