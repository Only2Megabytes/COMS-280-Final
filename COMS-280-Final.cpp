


#include <iostream>
#include <string>
#include <format>
#include <iomanip>
#include <ctime>
#include <chrono>
//forward declarations




template <class T>
class LinkedList;

template <class T>
class Node;

template <class T>
class HeadNode;

template <class T>
class InternalNode;

template <class T>
class TailNode;






class Account;//Base class for all types of banking accounts
class Savings;//Class that represents a savings account, will inherit from account
class Credit;//Class for a credit card
class Checkings;//Class that represents a Checkings account, will inherit from account.

//This is an object for searching through linkedlists.
template <class T, class X> //T is the type of list/node we are searching for. X is the type of value we are comparing.
struct ListSearcher  {
	friend class LinkedList<T>;
public:
	LinkedList<T>* searchList(LinkedList<T>* list, X compareBy) {
		Node<T>* node = list->getHead();//This will search for every node until nullptr is found, meaning we are at the last element. It will find every element that matches.
		LinkedList<T>* foundNodes = new LinkedList<T>;
		while (node != nullptr) {
			if (node->getValue()->isMe(compareBy)) {
				foundNodes->Insert(node->getValue());
			}
			node = node->getNext();
		}
		return foundNodes;
	};
};


struct Transaction {//object for storing transactions
private:
	float OriginalBalance;
	float TransactionAmount;
	std::string transfereeID;
	std::string notes;
	std::string TransactionID;
	
	

public:

	Transaction(float OriginalBalance, float TransactionAmount, std::string transfereeID, std::string notes)//constructor that is called when a transaction is made	
	:OriginalBalance(OriginalBalance), TransactionAmount(TransactionAmount),transfereeID(transfereeID),notes(notes){

	}

	void printTransaction() {//for printing out the transactions when an account wishes to view them.
		printf("Transaction Number : %s\n$%.2f -> %s\nNew balance : %.2f\nNotes : %s\n",TransactionID.c_str(), TransactionAmount, transfereeID.c_str(), OriginalBalance - TransactionAmount, notes.c_str());

	}

	bool isMe(std::string TransactionID) {//for comparing transactions
		if (TransactionID == this->TransactionID) {
			return true;
		}
	}
};



template<class T>
class LinkedList {
private:
	Node<T>* head;
	int count;
public:
	LinkedList<T>() :head(nullptr), count(0) {}
	void Insert(T* value) {
		if (head == nullptr) {
			head = new Node<T>(value);
		}
		else {
			head->Insert(value);

		}
		count++;
	}
	void Find() {

	}
	void Delete(int position) {
		count = 0;
		Node<T>* PriorNode = head;
		Node<T>* FollowingNode = nullptr;
		while (count < position-1) {
			PriorNode = PriorNode->getNext();
			count++;
		}
		Node<T>* Node = PriorNode->getNext();
		FollowingNode = Node->getNext();
		delete Node;
		Node = nullptr;
		PriorNode->setNext(FollowingNode);
		this->count--;
		
	}
	/*
	Node<T>* index(int index) {
		Node<T>* value = head;
		for (int i = 0; i > index; i++) {
			value = value->getNext();
		}
		return value;
	}
	*/

	

	Node<T>* getHead() {
		return head;
	}
};

template<class T>
class Node {//This is a node that will go into a linkedlist
private:
	Node<T>* next;
public:
	T* value;
	Node<T>(T* value) :value(value), next(nullptr) {}
	void Insert(T* value) {//check if the value after us in the list is taken
		if (next == nullptr) {//It isn't, put the value there
			next = new Node<T>(value);
		}
		else {//Make the next node deal with it.
			next->Insert(value);
		}
	}

	T* getValue() {//get the value we contain.
		return value;
	}

	Node<T>* getNext() {//tell someone what our next is.
		return next;
	}
	void setNext(Node<T>* next) {//let someone else set out next value
		this->next = next;
	}
};




class Person;//Represents a real life person

class Person {
private:
	std::string address;
	int customerID;
	int ssn;

	std::string password;

	LinkedList<Account>* AccountList = new LinkedList<Account>();

	//Contact details
	std::string phoneNumber;
	std::string emailAddress;

public:
	std::string firstName;
	std::string lastName;
	std::string middleName;
	Person( std::string homeAddress, std::string emailAddress, std::string password):address(homeAddress), emailAddress(emailAddress), password(password)
	{

		customerID = 0;

		printf("\n============ Personal Details ============\n");
		printf("Please enter your social security number.\n>>");
		std::string tempSSN = std::string();
		do {
			std::cin >> tempSSN;
			if (tempSSN.size() != 9)
			{
				std::cout << "A valid SSN should only contain 9 numbers!" << std::endl;
				tempSSN = std::string();
			}
			else {
				try {
					ssn = std::stoi(tempSSN);
				}
				catch (std::invalid_argument exception) {
					std::cout << "\nCould not validate SSN, please reenter." << std::endl;
					tempSSN = std::string();

				}
			}
			
		} while (tempSSN.size() != 9);

		printf("\n===== Name ======");
		std::string tempName = std::string();
		bool validated = false;
		char verification = '0';
		do {
			system("cls");
			//First name
			printf("Please enter your first name\n>>");
			std::cin >> firstName;

			//Middle name
			printf("\nPlease enter your middle name\n>>");
			std::cin >> middleName;

			//Last name
			printf("\nPlease enter your last name\n>>");
			std::cin >> lastName;
			
			while (verification != 'y' && verification != 'n') {
				std::cin.ignore();
				system("cls");
				printf("Is this correct?\n%s %s %s\nY or N >>", firstName.c_str(), middleName.c_str(), lastName.c_str());
				verification = std::cin.get();
			}
			if (verification == 'y') {
				validated = true;
			}
			else {
				verification = '0';
			}

		} while (!validated);


	}
	Person() {
		customerID = 0;
		firstName = "Name";
	}
	Person(int id):customerID(id) {
	}
	bool isMe(int ID) {//compare the customerID
		if (ID == customerID) {
			return true;
		}
	}
	bool isMe(std::string email) {//compare the customers email
		if (email == emailAddress) {
			return true;
		}
	}
	void printSSN() {
		for (int i = 0; i < 9; i++) {

		}
		std::cout << "\n";
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
friend struct Transaction;
private:
	std::string password;
	Account* linkedProtection;//nested class for linked account overdraft protection.
	
public:
	float balance = 0;
	std::string identificationNumber;
	LinkedList<Transaction>* transactionHistory = nullptr;
	Account():linkedProtection(nullptr) {
		transactionHistory = new LinkedList<Transaction>();
	}
	~Account() {};

	virtual void generateIDNumber() = 0;

	void operator+=(float value) {//This overload is for depositing to an accounts balance
		balance += value;
	}

	
	void getTransactionHistory() {
		Node<Transaction>* transaction = transactionHistory->getHead();
		do {
			transaction->getValue()->printTransaction();
			transaction = transaction->getNext();
		} while (transaction != nullptr);

	}

	virtual void overdraftProtection() {
		std::cout << "Overdraft protection is not available for this account!" << std::endl;
	}


	virtual void transfer(Account *toTransfer, float amount, std::string notes) {//A function for transferring money between accounts, this only needs to be overloaded if the balance needs special handling.
		float originalBalance = balance;
		if (this->balance >= amount) {
			toTransfer->balance += amount;
			this->balance -= amount;
			printf("=============\nTransfer Receipt\n=============\n$%.2f transferred from %s to %s\n%s Balance : $%.2f\n%s Balance : $%2.f\n", amount, this->identificationNumber.c_str(), toTransfer->identificationNumber.c_str(), this->identificationNumber.c_str(), this->balance, toTransfer->identificationNumber.c_str(), toTransfer->balance);
			printf("This accounts (%s) new balance is $%.2f\n", this->identificationNumber.c_str(), this->balance);
			transactionHistory->Insert(new Transaction(originalBalance, amount, toTransfer->identificationNumber, notes));
		}
		else {
			if (linkedProtection != nullptr) {
				float amountOver = (this->balance - amount) *-1;
				this->balance -= amount;
				linkedProtection->transfer(this, amountOver,"linked account overdraft protection");
			}
			else {
				std::cout << "Sorry! This transfer cannot be completed as your balance is not high enough." << std::endl;
			}
		}
	}

	virtual void printDetails() {
		//to be implemented
	}
	void operator+= (Account * account){//This overload is for combining accounts.
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

	virtual void show() {
		std::cout << identificationNumber << std::endl;
	}

};



class Checkings : public Account {//Checkings account, derives from account
public:
	Account* linkedProtection;
	Checkings() {
		balance = 0.0f;
		generateIDNumber();
		std::cout << "Created a checkings account. The balance is $" << balance << std::endl;
	}
	Checkings(float value) {
		
		balance = value;
		generateIDNumber();
		std::cout << "Created a checkings account. The balance is $" << balance << std::endl;
		//print("Created a checkings account with a balance of $" + std::to_string(balance));
	}
	~Checkings() {};
	virtual void printBalance() {
		printf("=============\nCheckings Summary\n=============\nAccount : %s\nYou have a current balance of $%.2f\n", identificationNumber.c_str(), balance);
	}

	virtual void overdraftProtection(Account* link){
		linkedProtection = link;
	}
	virtual void show() {
		std::cout << "ID: " << identificationNumber << "\nType : Checking Account" <<std::endl;
	}

	virtual void generateIDNumber() {
		identificationNumber += "1000";
		for (int i = 0; i < 4; i++) {
			identificationNumber += std::to_string((1 + rand() % 9));
		}
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

	virtual void generateIDNumber() {
		identificationNumber += "2000";
		for (int i = 0; i < 4; i++) {
			identificationNumber += (1 + rand() % 9);
		}
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
			printf("This accounts (%s) new balance is $%.2f.\n", this->identificationNumber.c_str(), this->balance);
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
		generateIDNumber();
	}
	Savings(CompoundFrequency desiredFrequency, float startingRate):frequency(desiredFrequency), rate(startingRate){
		generateIDNumber();
	}
	~Savings() {
	}
	virtual void printBalance() {
		printf("=============\nSavings Summary\n=============\nAccount : %s\nYou currently have $%.2f saved in this account.\n", identificationNumber.c_str(), balance);
	}
	virtual void generateIDNumber() {
		identificationNumber += "3000";
		for (int i = 0; i < 4; i++) {
			identificationNumber += std::to_string((1 + rand() % 9));
		}
	}

};

Person *login(std::string username, std::string ) {//Will, in the future, load customer information from a file
	Person *customer = new Person();
	//load from file
	return customer;
}




Person* createPerson() {
	Person* person = new Person();


	std::string tempName;
	std::cout << "\nWelcome!\nThank you for choosing us for your finanical needs. Before we continue, please enter your full name!"<< std::endl << "First name : ";
	std::cin >> tempName;

	return new Person();
	
}
template <class T>
void transfer(Account* transferer, Account* transferee, T amount) {
	if (transferer->balance >= amount) {
		transferee->balance += amount;
		transferer->balance -= amount;
	}
	else {
		printf("%s does not have enough money to compelte this transaction!", transferer->identificationNumber);
	}

}

int main()
{
	srand(time(0));




	LinkedList<int>* ll_Int = new LinkedList<int>();
	LinkedList<Person>* personList = new LinkedList<Person>();
	personList->Insert(new Person());
	for (int i = 0; i < 4; i++) {
		personList->Insert(new Person());
	}
	Person* andrew = new Person(5);
	andrew->firstName = "andrew";
	personList->Insert(andrew);
	
	ListSearcher<Person, int>* Searcher = new ListSearcher<Person, int>{};
	
	

	LinkedList<Person>* list =  Searcher->searchList(personList,5);
	std::cout << "Found object : " << list->getHead()->getValue()->firstName << std::endl;

	Checkings* checkingAccount = new Checkings(1200);
	Savings* savingsAccount = new Savings();
	savingsAccount->balance = 500;
	Credit* creditAccount = new Credit();

	


}

