


#include <iostream>
#include <string>
#include <format>
#include <iomanip>

//forward declarations



class LinkedList;
class Node;
class Data;
class Account;//Base class for all types of banking accounts
class Savings;//Class that represents a savings account, will inherit from account
class Credit;//Class for a credit card
class Checkings;//Class that represents a Checkings account, will inherit from account.


/*The implementation of LinkedList's and their associated types, those being "Data" and "Node" are very barebones right now. 
I don't fully understand how I want to use them in this context. However I tested them just to get an idea of how it could work.*/

class LinkedList {//Will be used for transaction history and account management
public:
	Node* head;
	LinkedList(Node *headNode):head(headNode) {
	}

};



class Data {};

class Node {
public :
	Data* data;
	Node* tail;
	std::string name = "";
	Node(std::string nam): name(nam){
		tail = nullptr;
	}
	void setTail(Node* ptr) { tail = ptr; }
	
};

class Person;//Represents a real life person

class Person {
private:
	std::string address;
	int customerID;
	int ssn[9];//social security number

	std::string password;


	//Contact details
	int phonenumber[10];
	std::string emailaddress;
	
public:
	std::string firstName;
	std::string lastName;
	std::string middleName;
	Person(){
			
	}



};



enum CompoundFrequency {//Enum for the frequency at which interest is added to a savings account
	DAILY,
	WEEKLY,
	MONTHLY,
	QUATERLY,
	ANNUALLY
};

//Implementation for account
class Account{
private:
	std::string password;
	
public:
	float balance = 0;
	std::string identificationNumber;
	Account() {

	}
	~Account() {};

	void operator+=(float value) {//This overload is for depositing to an accounts balance
		balance += value;
	}
	virtual void transfer(Account *toTransfer, float amount) {//A function for transferring money between accounts, this only needs to be overloaded if the balance needs special handling.
		if (this->balance >= amount) {
			toTransfer->balance += amount;
			this->balance -= amount;
			printf("=============\nTransfer Receipt\n=============\n$%.2f transferred from %s to %s\n%s Balance : $%.2f\n%s Balance : $%2.f\n", amount, this->identificationNumber.c_str(), toTransfer->identificationNumber.c_str(), this->identificationNumber.c_str(), this->balance, toTransfer->identificationNumber.c_str(), toTransfer->balance);
			printf("This accounts (%s) new balance is $%.2f\n", this->identificationNumber.c_str(), this->balance);
		}
		else {
			std::cout << "Sorry! This transfer cannot be completed as your balance is not high enough." << std::endl;
		}

	}
	virtual void printDetails() {
		//to be implemented
	}
	void operator+=(Account *account) {//This overload is for combining accounts.
		balance += account->balance;
		std::cout << "rhs account will be closed" << std::endl;
		account->~Account();
		//Include account closing process
	}

	void operator-=(float value) {//This overload is for withdrawing from an account
		balance -= value;
	}
	float getBalance() { return balance; }
	void setBalance(float value) { balance = value; }

	void winTheLottery() { balance = 9999999999.0f; }//Testing balance case

	

	virtual void printBalance() = 0;//Make this class abstract so it cannot be created

};

class Checkings : public Account {//Checkings account, derives from account
public:
	Checkings() {
		balance = 0.0f;
		std::cout << "Created a checkings account. The balance is $" << balance << std::endl;
	}
	Checkings(float value){
		balance = value;
		std::cout << "Created a checkings account. The balance is $" << balance << std::endl;
		//print("Created a checkings account with a balance of $" + std::to_string(balance));
	}
	~Checkings() {};
	virtual void printBalance() {
		printf("=============\nCheckings Summary\n=============\nAccount : %s\nYou have a current balance of $%.2f\n", identificationNumber.c_str(), balance);
	}


};

class Credit : public Account {
private:
	float limit;
public:
	CompoundFrequency compoundFrequency;
	float rate;
	//printDetails() is disabled for now because it looks bad on the output screenshot.
	Credit():limit(0), rate(0.01f), compoundFrequency(DAILY) {
		balance = 0;
		printDetails();
	}
	Credit(float limit):limit(limit),rate(0.01f), compoundFrequency(DAILY) {
		balance = 0;
		printDetails();
	}
	Credit(float limit, CompoundFrequency frequency, float interestRate):limit(limit), rate(interestRate), compoundFrequency(frequency){
		balance = 0;
		printDetails();
		
	}
	virtual void printBalance() {
		printf("=============\nCredit Summary\n=============\nYour current card balance is $%.2f\nYou have $%.2f left out of your $%.2f balance.\n", balance, limit-balance, limit);
	}
	virtual void printDetails() {
		//printf("=============\nDetails\n=============\nCredit limit : %.2f\nInterest rate : %.2f\nCompound Frequency : %s\n", limit, rate, "TBA");
		std::cout << "Created a credit card!" << std::endl;
	}

	virtual void transfer(Account* toTransfer, float amount) {//Special transfer case for credit accounts.
		if (this->limit-balance >= amount) {
			toTransfer->balance += amount;
			this->balance += amount;
			printf("=============\nTransfer Receipt\n=============\n$%.2f transferred from %s to %s\n%s Balance : $%.2f\n%s Balance : $%2.f\n", amount, this->identificationNumber.c_str(), toTransfer->identificationNumber.c_str(), this->identificationNumber.c_str(), this->balance, toTransfer->identificationNumber.c_str(), toTransfer->balance);
			printf("This accounts (%s) new balance is $%.2f.", this->identificationNumber.c_str(), this->balance);
		}
		else {
			std::cout << "Sorry! This tranfer cannot be completed as it would set you over your credit limit." << std::endl;
		}
	}
};

class Savings : public Account {//Not fully implemented yet but will have some way to add
private:
	float rate;
	CompoundFrequency frequency;
public:
	Savings():frequency(ANNUALLY),rate(0.01f) {
	}
	Savings(CompoundFrequency desiredFrequency, float startingRate):frequency(desiredFrequency), rate(startingRate){
	}
	~Savings() {
	}

};

Person *login(std::string username, std::string ) {//Will, in the future, load customer information from a file
	Person *customer = new Person();
	//load from file
	return customer;
}




int main()
{

	Credit credit = Credit(400);
	Checkings debit_one = Checkings(5000);
	Checkings debit_two = Checkings(4900);
	credit.identificationNumber = "Credit Card";
	debit_one.identificationNumber = "Debit Card One";
	debit_two.identificationNumber = "Debit Card Two";

	std::cout << "Checkings to Checkings\n";
	debit_one.transfer(&debit_two, 100);

	std::cout << "Credit to Checkings\n";
	credit.transfer(&debit_one, 100);
	
	credit.printBalance();
	debit_one.printBalance();
	debit_two.printBalance();

	//fail test
	credit.transfer(&debit_one, 400);




	

	

}

