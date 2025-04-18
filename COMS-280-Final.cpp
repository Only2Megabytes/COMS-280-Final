


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
	LinkedList<T>* searchList (LinkedList<T>* list, X compareBy) {
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

	static std::string generateID() {
		std::string TransactionID = "";
		for (int i = 0; i < 9; i++) {
			TransactionID += std::to_string((1 + rand() % 9));
		}
		return TransactionID;
	}

	Transaction(float OriginalBalance, float TransactionAmount, std::string transfereeID, std::string notes)//constructor that is called when a transaction is made	
	:OriginalBalance(OriginalBalance), TransactionAmount(TransactionAmount),transfereeID(transfereeID),notes(notes){
		TransactionID = generateID();
	}

	void printTransaction() {//for printing out the transactions when an account wishes to view them.
		printf("#%s | $%.2f -> %s | New balance : %.2f | Notes : %s\n",TransactionID.c_str(), TransactionAmount, transfereeID.c_str(), OriginalBalance - TransactionAmount, notes.c_str());

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


	void Delete(int index) {
		int count = 1;
		Node<T>* node = head;
		if (index == 1) {
			head = node->getNext();
			delete node;
			count--;
		}
		else {
			count = 2;
			node = node->getNext();
			Node<T>* lastNode = node;
			while (count != index) {
				count++;
				lastNode = node;
				node = node->getNext();
			}
			lastNode->setNext(node->getNext());
			delete node;
			node = nullptr;
			count--;
		}
	}


	Node<T>* getHead() {
		return head;
	}

	int getCount() {
		return count;
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
	friend struct PersonBuilder;
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
	Person(std::string firstName, std::string middleName, std::string lastName, std::string homeAddress, std::string emailAddress, int id, int ssn, std::string password) :firstName(firstName),middleName(middleName),lastName(lastName),customerID(id),ssn(ssn), address(homeAddress), emailAddress(emailAddress), password(password)
	{
		
	}

	int getID() { return customerID; }
	std::string getAddress() { return address; }
	std::string getNumber() { return phoneNumber; }
	std::string getEmail() { return emailAddress; }

	void generateCustomerID() {
		std::string tempID = "";
		for (int i = 0; i < 8; i++) {
			tempID += std::to_string((1 + rand() % 9));
		}
		try {
			customerID = std::stoi(tempID);
		}
		catch (std::invalid_argument exception){
			std::cout << "Failed to generate ID! Please contact support to have it fixed.";
		}
	}

	Person() :customerID(0), ssn(0){
		firstName = "Name";
		password = "Password"; 
	}
	Person(int id):customerID(id),ssn(0) {
	}
	bool isMe(int ID) {//compare the customerID
		if (ID == customerID) {
			return true;
		}
		return false;

	}
	bool isMe(std::string email) {//compare the customers email
		if (email == emailAddress) {
			return true;
		}
		return false;
	}
	void printSSN() {
		for (int i = 0; i < 9; i++) {

		}
		std::cout << "\n";
	}

	LinkedList<Account>* getAccounts(){ return AccountList; }

	bool validateLogin(std::string password) { return this->password == password; }

	



};

struct PersonBuilder {//Helps with building people, especially for testing.
	friend class Person;

	void setId(Person* person, int num) {
		person->customerID = num;
	}
	void addAccount(Person* person, Account* acc) {
		person->AccountList->Insert(acc);
	}

	void setAddress(Person* person, std::string address) {
		person->address = address;
	}

	void setPhone(Person* person, std::string phonenumber) {
		person->phoneNumber = phonenumber;
	}

	void setEmail(Person* person, std::string email) {
		person->emailAddress = email;
	}

	void setSSN(Person* person, int ssn) {
		person->ssn = ssn;
	}

	void setPassword(Person* person, std::string password) {
		person->password = password;
	}

};



enum CompoundFrequency {//Enum for the frequency at which interest is added to a savings account
	SECONDLY,
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

	
public:
	float balance = 0;
	std::string identificationNumber;
	LinkedList<Transaction>* transactionHistory = nullptr;
	Account() {
		transactionHistory = new LinkedList<Transaction>();
	}
	~Account() {};

	virtual void generateIDNumber() = 0;

	bool isMe(std::string accountNumber) {
		return (identificationNumber == accountNumber);
	}

	
	void getTransactionHistory() {
		Node<Transaction>* transaction = transactionHistory->getHead();
		std::cout << "Transaction History : " << std::endl;
		while (transaction != nullptr) {
			transaction->getValue()->printTransaction();
			transaction = transaction->getNext();
		} 

	}


	virtual float returnBalance() { return balance; }

	virtual void receiveTransfer(float amount) {
		balance += amount;
	}

	virtual void transfer(Account *toTransfer, float amount, std::string notes) {//A function for transferring money between accounts, this only needs to be overloaded if the balance needs special handling.
		float originalBalance = balance;
		if (this->balance >= amount) {
			toTransfer->receiveTransfer(amount);
			this->balance -= amount;
			//printf("=============\nTransfer Receipt\n=============\n$%.2f transferred from %s to %s\n%s Balance : $%.2f\n%s Balance : $%2.f\n", amount, this->identificationNumber.c_str(), toTransfer->identificationNumber.c_str(), this->identificationNumber.c_str(), this->balance, toTransfer->identificationNumber.c_str(), toTransfer->balance);
			//printf("This accounts (%s) new balance is $%.2f\n", this->identificationNumber.c_str(), this->balance);
			transactionHistory->Insert(new Transaction(originalBalance, amount, toTransfer->identificationNumber, notes));
		}

	}
	virtual void printSummary() = 0;
	virtual void printDetails() {
		//to be implemented
	}
	virtual void operator* (Account * account){//This overload is for combining accounts.
		balance += account->balance;
		std::cout << "rhs account will be closed" << std::endl;
		account->~Account();
		//Include account closing process
	}

	virtual void  operator+= ( float integer) {
		balance += integer;
	}
	virtual bool operator==(Account* value) {
		if (this-> identificationNumber == value->identificationNumber) {
			return true;
		}
		return false;
	}


	void operator-=(float value) {//This overload is for withdrawing from an account
		balance -= value;
	}
	float getBalance() { return balance; }
	void setBalance(float value) { balance = value; }

	
	void printPlainBalance() {
		printf("\n======Account Balance======\nAccount Number : %s\nBalance :%.2f\n",identificationNumber.c_str(), balance);
	}
	virtual void printBalance() = 0;//Make this class abstract so it cannot be created

	virtual void show() {
		std::cout << identificationNumber << std::endl;
	}

};





class Checkings : public Account {//Checkings account, derives from account
public:

	Checkings() {
		balance = 0.0f;
		generateIDNumber();
	}
	Checkings(float value) {
		
		balance = value;
		generateIDNumber();
		//print("Created a checkings account with a balance of $" + std::to_string(balance));
	}
	~Checkings() {};
	virtual void printBalance() {
		printf("=============\nCheckings Summary\n=============\nAccount : %s\nYou have a current balance of $%.2f\n", identificationNumber.c_str(), balance);
	}




	virtual void printSummary() {
		printf("====Checking Account====\nAccount Number : %s\nBalance : %.2f\nLastest Transaction : ", identificationNumber.c_str(),balance);
		Node<Transaction>* latestTransaction = transactionHistory->getHead();
		if (latestTransaction == nullptr) {
			printf("Null\n");
		}
		else {
			while (latestTransaction->getNext() != nullptr) {
				latestTransaction = latestTransaction->getNext();
			}
			latestTransaction->getValue()->printTransaction();
			printf("\n");
		}
	}


	virtual void show() {
		std::cout << "ID: " << identificationNumber << "\nType : Checking Account" <<std::endl;
	}


	virtual void generateIDNumber() {
		identificationNumber += "1000";
		for (int i = 0; i < 8; i++) {
			identificationNumber += std::to_string((1 + rand() % 9));
		}
	}


};

class Credit : public Account {
private:
	float limit;
public:

	Credit():limit(1000) {
		balance = 0;
		generateIDNumber();
	}
	Credit(float limit):limit(limit) {
		balance = 0;
		generateIDNumber();
	}


	virtual float returnBalance() { return -balance; }

	//I know these operator overloads seem weird, and the book talks about the negatives of it, but it is done this way because
	//when adding to the credit account, the balance should be lessened, and when subtracting from the credit account, the balance should be greatened.
	virtual void operator+= (float amount) {
		balance -= amount;
	}
	virtual void operator-= (float amount) {
		balance += amount;
	}

	virtual void receiveTransfer(float amount) {
		balance -= amount;
	}
	virtual void transfer(Account* toTransfer, float amount, std::string notes) {//transfer overload specifically for credit accounts that check if it would go above your limit rather than below 0.
		if (balance + amount > limit) {
			std::cout << "Continuing this transaction would set you over the limit and has thus been denied.";
			return;
		}
		else {
			balance += amount;
			toTransfer->receiveTransfer(amount);
			transactionHistory->Insert(new Transaction(balance - amount, amount, toTransfer->identificationNumber, notes));
		}
	}

	virtual void printSummary() {
		printf("====Credit Account====\nAccount Number : %s\nBalance  / Limit : %.2f / %.2f\nLastest Transaction : ", identificationNumber.c_str(), balance,limit);
		Node<Transaction>* latestTransaction = transactionHistory->getHead();
		if (latestTransaction == nullptr) {
			printf("Null\n");
		}
		else {
			while (latestTransaction->getNext() != nullptr) {
				latestTransaction = latestTransaction->getNext();
			}
			latestTransaction->getValue()->printTransaction();
			printf("\n");
		}
	}

	virtual void generateIDNumber() {
		identificationNumber += "2000";
		for (int i = 0; i < 8; i++) {
			identificationNumber += std::to_string((1 + rand() % 9));
		}
	}

	virtual void printBalance() {
		printf("=============\nCredit Summary\n=============\nYour current card balance is $%.2f\nYou have $%.2f left out of your $%.2f balance.\n", balance, limit-balance, limit);
	}
	virtual void printDetails() {
		//printf("=============\nDetails\n=============\nCredit limit : %.2f\nInterest rate : %.2f\nCompound Frequency : %s\n", limit, rate, "TBA");
		std::cout << "Created a credit card!" << std::endl;
	}


};

LinkedList<Savings>* savingsAccounts = new LinkedList<Savings>();

class Savings : public Account {//Not fully implemented yet but will have some way to add
private:
	float rate;
	CompoundFrequency frequency;
	void startCompounding() {

		compound = time(0);
		switch (frequency) {
		case SECONDLY:
			compound += 1;
			break;
		case DAILY:
			compound += 86400;
			break;
		case WEEKLY:
			compound += 86400 * 7;
			break;
		case MONTHLY:
			compound += 86400 * 7 * 4;
			break;
		case QUATERLY:
			compound += 86400 * 7 * 4 * 3;
			break;
		case ANNUALLY:
			compound += 86400 * 7 * 4 * 3 * 4;
			break;
		}
		savingsAccounts->Insert(this);
	}
public:
	std::time_t compound = 0;
	Savings():frequency(ANNUALLY),rate(0.01f) {
		generateIDNumber();
		startCompounding();

	}
	Savings(CompoundFrequency desiredFrequency, float startingRate):frequency(desiredFrequency), rate(startingRate){
		generateIDNumber();
		startCompounding();

	}
	~Savings() {
	}
	virtual void printBalance() {
		printf("=============\nSavings Summary\n=============\nAccount : %s\nYou currently have $%.2f saved in this account.\n", identificationNumber.c_str(), balance);
	}
	virtual void generateIDNumber() {
		identificationNumber += "3000";
		for (int i = 0; i < 8; i++) {
			identificationNumber += std::to_string((1 + rand() % 9));
		}
	}
	CompoundFrequency getFrequency() { return frequency; }
	void Compound() {
		balance += balance * rate;
		compound = time(0);
	}

	virtual void printSummary() {
		std::string interestFormat = std::string();
		switch (frequency) {
			case SECONDLY://format for summary printing so the user can see how often they gain interest without seeing just a number
				interestFormat = "secondly";
				break;
			case DAILY:
				interestFormat = "daily";
				break;
			case WEEKLY:
				interestFormat = "weekly";
				break;
			case MONTHLY:	
				interestFormat = "monthly";
				break;
			case QUATERLY:
				interestFormat = "quarterly";
				break;
			case ANNUALLY:
				interestFormat = "annually";
				break;
		}
		printf("====Savings Account====\nAccount Number : %s\nBalance : %.2f\nRate : %.2f %s\nLastest Transaction : ", identificationNumber.c_str(), balance, rate,interestFormat .c_str());
		Node<Transaction>* latestTransaction = transactionHistory->getHead();
		if (latestTransaction == nullptr) {
			printf("Null\n");
		}
		else {
			while (latestTransaction->getNext() != nullptr) {
				latestTransaction = latestTransaction->getNext();
			}
			latestTransaction->getValue()->printTransaction();
			printf("\n");
		}
	}
};






LinkedList<Person>* users = new LinkedList<Person>();


Person* user = nullptr;

struct Console {
	enum State {
		LOGIN,
		DASHBOARD,
		ACCOUNT_CREATION,
		ACCOUNT_VIEW,
		TRANSFER,
		CLOSE_ACCOUNT,
		SIGNUP,
		PERSON_DETAILS,
	};

	State currentState = LOGIN;

	Account* accountView = nullptr;

	std::string errorMessage;

	std::string userInput;
	
	void switchState(State newState) {
		system("cls");
		currentState = newState;
	}

	void printHeader()
	{
		std::cout << "Welcome " << user->firstName << "!\n";
		if (errorMessage != "") {
			std::cout << errorMessage << "\n";
		}
	}


	void printLogin() {
		printf("=== Login ===\n");
		printf("Please enter your email address or customer identification number. If you would like to create an account, enter \"create.\" \n");
		user = nullptr;
		getInput();
		if (userInput == "create")
		{
			switchState(SIGNUP);
			return;
		}
		bool enteringPassword = false;
		if (userInput.find('@') == std::string::npos) {//We did not find the @ sign so we are gonna assume they attempted to enter an identification number
			try {
				int id = std::stoi(userInput);//parse
				ListSearcher<Person, int>* findById = new ListSearcher<Person, int>();//create a listsearcher to find the person

				Node<Person>* headNode = findById->searchList(users, id)->getHead();
				
				if (headNode == nullptr) {
					printf("Did not find an account with that id! Please reenter your details and contact support if you need further assistance!\n\n");
				}
				else {
					user = headNode->getValue();//set global user to this
					delete findById;
					findById = nullptr;
				}
			}
			catch(std::invalid_argument exception){//It was either an email address without the @ symbol, or they messed up entering their idf
				printf("Could not validate input!\nInput assumed to be identification number.\n\n");
			}
			
		}
		else {//We found an @sign, so this is at the very least an ATTEMPT at entering their email.
			ListSearcher<Person, std::string>* findByEmail = new ListSearcher<Person, std::string>();
			Node<Person>* headNode = findByEmail->searchList(users, userInput)->getHead();
			if (headNode == nullptr)
			{
				printf("Did not find an account associated with that email! Please reenter your details and contact support if you need further assistance!\n\n");
			}
			else {
				user = headNode->getValue();
			}
			delete findByEmail;
			findByEmail = nullptr;
		}
		if (user == nullptr) {
			printf("We could not find your account! Please reenter your details\n\n");
		}
		else {
			enteringPassword = true;
		}
		while (enteringPassword) {
			printf("Please enter your password!\nIf you wish to go back, enter nothing.\n");
			getInput();
			if (userInput == "") {
				enteringPassword = false;
				break;
			}
			if (user->validateLogin(userInput)) {
				printf("Success! Logging you in");
				switchState(DASHBOARD);
				enteringPassword = false;
			}
		}
		
		


	}
	void printDash();
	void printAccountCreation();
	void printAccountView();
	void printTransfer();
	void printAccountClose();
	void printSignup();
	void printUserDetails();

	void printScreen() {
		
		switch (currentState) {
		case LOGIN:
			system("cls");
			printLogin();
			break;
		case DASHBOARD:
			system("cls");
			printHeader();
			printDash();
			break;
		case ACCOUNT_CREATION:
			printHeader();
			printAccountCreation();
			break;
		case ACCOUNT_VIEW:
			printHeader();
			printAccountView();
			break;
		case TRANSFER:
			printHeader();
			printTransfer();
			break;
		case CLOSE_ACCOUNT:
			printHeader();
			printAccountClose();
			break;
		case SIGNUP:
			printSignup();
			break;
		case PERSON_DETAILS:
			printHeader();
			printUserDetails();
			break;
		}
	}

	void getInput() {
		std::getline(std::cin, userInput);
	}
};

void Console::printUserDetails() {//Prints account information
	system("cls");
	std::cout << "====== Your Account =======" << std::endl;

	std::cout << "\n=== General Information ===" << std::endl;
	std::cout << "Customer Identification Number : " << user->getID() << std::endl;
	std::cout << user->firstName << " " << user->middleName << " " << user->lastName << "." << std::endl;

	float totalBalance = 0;
	LinkedList<Account>* accounts = user->getAccounts();

	Node<Account>* node = accounts->getHead();
	while (node != nullptr) {//totals up the combined balance of all of the users accounts to display their "net worth"
		totalBalance += node->getValue()->returnBalance();
		node = node->getNext();
	}

	std::cout << "Estimated Net Worth : " << totalBalance << std::endl;
	std::cout << "*This is a combination of the money in all checkings and savings accounts, with all credit balances subtracted" << std::endl;

	std::cout << "Number of bank accounts : " << user->getAccounts()->getCount();
	std::cout << "\n=== Contact Information ===" << std::endl;
	std::cout << "Phone Number : " << user->getNumber() << std::endl;
	std::cout << "Home Address : " << user->getAddress() << std::endl;
	std::cout << "Email Address : " << user->getEmail() << std::endl;

	std::cout << "\n\nPress enter to go back...";
	getInput();
	switchState(DASHBOARD);

}

void Console::printSignup() {
	std::cout << "Welcome! We are happy that you wish to sign up for our bank!";
	Person* newUser = new Person();
	PersonBuilder pb = PersonBuilder();
	std::cout << "Let's start with your name" << std::endl;
	bool inputValidated = false;

	
	while (!inputValidated) {//Get the users full name and make sure it is correct.
		std::cout << "What is your first-name?" << std::endl;
		getInput();

		newUser->firstName = userInput;
		std::cout << "What is your middle-name?" << std::endl;
		getInput();
		newUser->middleName = userInput;

		std::cout << "What is your last-name?" << std::endl;
		getInput();
		newUser->lastName = userInput;

		do {
			std::cout << "Your name is " << newUser->firstName << " " << newUser->middleName << " " << newUser->lastName << ". Is this correct? \"yes\" or \"no\"" << std::endl;
			getInput();
		} while (userInput != "yes" && userInput != "no");
		if (userInput == "yes") {
			inputValidated = true;
		}
	}
	//SSN
	std::cout << "Please enter your social security number. Exclude any special characters." << std::endl;
	int ssn = 0;
	do {
		getInput();
		if (userInput.size() != 9)
		{
			std::cout << "A valid SSN should only contain 9 numbers!" << std::endl;
			userInput = std::string();
		}
		else {
			try {
				ssn = std::stoi(userInput);
			}
			catch (std::invalid_argument exception) {
				std::cout << "\nCould not validate SSN, please reenter." << std::endl;
				userInput = std::string();

			}
		}

	} while (userInput.size() != 9);
	pb.setSSN(newUser, ssn);
		
	//HOME ADDRESS

	inputValidated = false;
	std::cout << "Next, enter your address." << std::endl;
	while (!inputValidated) {
		getInput();
		pb.setAddress(newUser, userInput);
		std::cout << userInput << ". is this correct? \"yes\" or \"no\"";
		do {
			getInput();
		} while (userInput != "yes" && userInput != "no");
		if (userInput == "yes") {
			inputValidated = true;
		}
	}

	//PHONE NUMBER
	inputValidated = false;
	std::cout << "Now for your phone number. Exclude any special characters such as '()' or '-'.";
	while (!inputValidated) {
		getInput();
		pb.setPhone(newUser, userInput);
		std::cout << "Your phone number is : " << userInput << ". is this correct? \"yes\" or \"no\"";
		do {
			getInput();
		} while (userInput != "yes" && userInput != "no");
		if (userInput == "yes") {
			inputValidated = true;
		}
	}

	//EMAIL ADDRESS
	inputValidated = false;
	std::cout << "Next, enter your email address." << std::endl;
	while (!inputValidated) {
		getInput();
		if (userInput.find('@') == std::string::npos) {
			std::cout << "Invalid email detected! Please retry." << std::endl;
		}
		else {
			pb.setEmail(newUser,userInput);
			std::cout << userInput << ". is this correct? \"yes\" or \"no\"";
			do {
				getInput();
			} while (userInput != "yes" && userInput != "no");
			if (userInput == "yes") {
				inputValidated = true;
			}
		}
	}

	//PASSWORD
	newUser->generateCustomerID();
	std::cout << "Lastly, please choose a password." << std::endl;
	inputValidated = false;
	while (!inputValidated) {
		getInput();
		pb.setPassword(newUser, userInput);
		std::cout << userInput << ". is this correct? \"yes\" or \"no\"";
		do {
			getInput();
		} while (userInput != "yes" && userInput != "no");
		if (userInput == "yes") {
			inputValidated = true;
		}
	}

	users->Insert(newUser);
	switchState(LOGIN);

}

void Console::printAccountView() {
	accountView->printPlainBalance();
	accountView->getTransactionHistory();
	if (accountView->transactionHistory->getCount() == 0) {
		std::cout << "You haven't made any transactions with this account yet!";
	}
	std::cout << "==== Controls ====" << std::endl;
	std::cout << "= Transfer Money = \n\"t\" " << std::endl;
	std::cout << "= Close Account = \n\"c\"" << std::endl;
	std::cout << "= Back =\n\"b\"" << std::endl;
	getInput();
	char control = '0';
	try
	{
		control = userInput.at(0);
	}
	catch (std::out_of_range exception) {

	}
	switch (control) {
		case 't':
			switchState(TRANSFER);
			break;
		case 'c':
			switchState(CLOSE_ACCOUNT);
			break;
		case 'b':
			switchState(DASHBOARD);
			break;
	}
}

void Console::printAccountClose() {
	std::cout << "We are sorry to hear you wish to close this account!" << std::endl;
	if (accountView->balance > 0) {
		std::cout << "It appears you still have money left in this account, before we continue, this must be transferred elsewhere. Please go to this account and transfer the money before retrying." << std::endl;
		std::cout << "Press enter to continue...";
		getInput();
	}
	else {
		LinkedList<Account>* accounts = user->getAccounts();
		Node<Account>* node = accounts->getHead();
		int count = 1;
		getInput();
		while (!(node->getValue()->identificationNumber == accountView->identificationNumber) && node != nullptr) {
			count++;
			node = node->getNext();
		}
		if (node == nullptr) {
			std::cout << "Something went wrong in closing your account! Please try again or contact support." << std::endl; 
		}
		else {
			accounts->Delete(count);
			accountView = nullptr;
			switchState(DASHBOARD);
		}
	}
}

void Console::printTransfer() {
	enum Target {
		PERSON,
		ACCOUNT,
		NONE,
	};
	Target target = PERSON;
	std::cout << "Would you like to send money to a (1) person, or a (2) specific account? (3) Back" << std::endl;
	char control = '0';
	bool sendingToPerson = false;
	do {
		getInput();
		try
		{
			control = userInput.at(0);
		}
		catch (std::out_of_range exception) {

		}
	} while (control != '1' && control != '2' && control != '3');
	switch (control) {
		case '1':
			target = PERSON;
			break;
		case '2':
			target = ACCOUNT;
			break;
		case '3':
			target = NONE;
			switchState(DASHBOARD);
			break;
	}
	switch (target) {
		
		case PERSON:
			{
			ListSearcher<Person, std::string>* searchForPerson = new ListSearcher<Person, std::string>();
			bool transferring = true;
			while (transferring) {
				std::cout << "Enter the email address you would like to send money too!"<<std::endl;
				getInput();
				std::cout << "Looking for " << userInput << "in our records..." << std::endl;
				LinkedList<Person>* tempList = searchForPerson->searchList(users, userInput);
				Node<Person>* foundPerson = tempList->getHead();
				if (foundPerson != nullptr) {
					std::cout << "Found them!" << std::endl;
					LinkedList<Account>* accountList = foundPerson->getValue()->getAccounts();
					std::cout << "How much money would you like to send?" << std::endl;
					bool confirmed = false;
					float amount;
					while (confirmed == false) {//allow confirmation for money amount
						getInput();
						try {
							amount = std::stof(userInput);
							if (amount <= 0) {
								std::cout << "Negative values cannot be transferred!"<<std::endl;
							}
							else {
								std::cout << "What notes would you like to add to the transfer?" << std::endl;
								getInput();
								accountView->transfer(accountList->getHead()->getValue(), amount, "Note : " + userInput);
								std::cout << "Press enter to continue...";
								getInput();
								confirmed = true;
								switchState(ACCOUNT_VIEW);
								transferring = false;
							}
						}
						catch (std::invalid_argument exception)
						{
							std::cout << "Value is invalid, please try again!" << std::endl;
						}
					}	
				}
			}
			}
			break;
		case ACCOUNT:
			{
			std::cout << "Enter the account number you are searching for." << std::endl;
			getInput();
			std::cout << "Searching for account " << userInput << std::endl;
			ListSearcher<Account, std::string>* searchForAccount = new ListSearcher<Account, std::string>();
			Node<Person>* person =  users->getHead();
			Node<Account>* account = nullptr;
			while (person != nullptr) {
				account = searchForAccount->searchList(person->getValue()->getAccounts(), userInput)->getHead();
				if (account != nullptr) {
					break;
				}
				person = person->getNext();
			}
			if (account == nullptr) {
				std::cout << "Sorry! We could not find an account by that number " << userInput << ". Please check the number and retry!" << std::endl;
			}
			else {
				bool transferring = true;
				while (transferring) {
					std::cout << "How much would you like to transfer?" << std::endl;
					getInput();
					try {
						float amount = std::stof(userInput);
						if (amount <= 0.01) {
							std::cout << "Sorry! That is not a valid amount." << std::endl;
						}
						else {
							std::cout << "What note would you like to add to the transaction?" << std::endl;
							getInput();
							accountView->transfer(account->getValue(), amount, userInput);
							transferring = false;
						}
					}
					catch (std::invalid_argument exception) {
						std::cout << "Your input was invalid. Please try again!" << std::endl;
					}

				}
			}
			
			}
			break;

	}
	
}

void Console::printDash() {
	LinkedList<Account>* accounts = user->getAccounts();
	Node<Account>* node = accounts->getHead();
	if (node == nullptr) {
		printf("You don't have any accounts with our bank. Type \"start\" to start account creation. Type \"cancel\" to be logged out.?\n");
		do {
			getInput();
		} while (userInput != "start" && userInput != "cancel");
		if (userInput == "start") {
			switchState(ACCOUNT_CREATION);
		}
		else {
			switchState(LOGIN);
		}
		
	}
	else {
		int count = 0;
		do {
			std::cout << "#" << ++count << ". \n";
			node->getValue()->printSummary();
			node = node->getNext();
			std::cout << std::endl;
		} while (node != nullptr);
		std::cout << "Get 2% extra cash back on all purchases made via your credit card for 12 months\nif a friend opens a credit account through the bank!" << std::endl;
		std::cout << "==== Controls ====" << std::endl;
		std::cout << "= View Account = \nnumber located above the account summary." << std::endl;
		std::cout << "= View Customer Account = \n\"v\" " << std::endl;
		std::cout << "= Create Account = \n\"c\" " << std::endl;
		std::cout << "= Logout = \n\"l\" " << std::endl;
		getInput();
		char control = ' ';
		try
		{
			control = userInput.at(0);
		}
		catch(std::out_of_range exception){

		}
		if (control == 'v') {
			switchState(PERSON_DETAILS);
		}
		if (control == 'l') {
			switchState(LOGIN);
			user = nullptr;
		}
		else if (control == 'c') {
			switchState(ACCOUNT_CREATION);
		}
		else {
			try {
				int num = control - '0';
				LinkedList<Account>* accountList = user->getAccounts();
				Node<Account>* account = accountList->getHead();

				for (int i = 1; i != num; i++) {
					account = account->getNext();
					if (account == nullptr) {
						std::cout << "You do not have an account associated with that number!\n";
						break;
					}
				}
				if (account != nullptr)
				{
					accountView = account->getValue();
					switchState(ACCOUNT_VIEW);
				}
			}
			catch(std::invalid_argument exception){
				std::cout << "Your input is not one of the presented options! Please try again." << std::endl;
			}
		}
		
	}

}

void Console::printAccountCreation() {
	char type = '0';
	if (user->getAccounts()->getCount() == 0) {
		std::cout << "It shows that you have no accounts with us currently! Would you like to start with a checking account? (\"yes\" or \"no\")" << std::endl;
		do {
			getInput();
		} while (userInput != "yes" && userInput != "no");
		if (userInput == "yes") {
			type = '1';
		}
	}
	if (type == '0') {
		std::cout << "What kind of account will we be creating today?\n1.Checking Account\n2.Savings Account\n3. Credit Account\nEnter the associated number." << std::endl;
		do {
			getInput();
			type = userInput.at(0);
		} while (type != '1' && type != '2' && type != '3');
	}
	Account* newAccount = nullptr;
	switch (type) {
		case '1':
			newAccount = new Checkings();
			break;
		case '2':
			newAccount = new Savings();
			break;
		case '3':
			newAccount = new Credit();
			break;
		default:
			std::cout << "Error creating account! Please try again!";
			break;
	}
	user->getAccounts()->Insert(newAccount);
	accountView = newAccount;
	switchState(ACCOUNT_VIEW);

	
}



void giveAccounts(Person* person) {
	LinkedList<Account>* accounts = person->getAccounts();
	Checkings* checkingAccount = new Checkings(100 + rand() % 10000);
	LinkedList<Transaction>* checkingTransactions = checkingAccount->transactionHistory;
	
	for (int i = 0; i < 1 + rand()%7; i++) {
		checkingTransactions->Insert(new Transaction(100 + rand() % 500, 5 + rand() % 50, Transaction::generateID(), "None"));
	}

	Savings* savingsAccount = new Savings(SECONDLY,0.01f);
	LinkedList<Transaction>* savingsTransactions = savingsAccount->transactionHistory;

	for (int i = 0; i < 1 + rand()%7; i++) {
		savingsTransactions->Insert(new Transaction(100 + rand() % 500, 5 + rand() % 50, Transaction::generateID(), "None"));
	}
	savingsAccount->balance = 100 + rand() % 200;
	Credit* creditAccount = new Credit(100 + rand() % 1200);
	LinkedList<Transaction>* creditTransactions = creditAccount->transactionHistory;
	for (int i = 0; i < 1 + rand()%7; i++) {
		creditTransactions->Insert(new Transaction(100 + rand() % 500, 5 + rand() % 50, Transaction::generateID(), "None"));
	}

	creditAccount->balance = 25 + rand() % 100;
	accounts->Insert(checkingAccount);
	accounts->Insert(savingsAccount);
	accounts->Insert(creditAccount);
}//for testings purposes


bool running = true;

int main()
{


	//	Person(std::string firstName, std::string middleName, std::string lastName, std::string homeAddress, std::string emailAddress, int id, int ssn, std::string password) :firstName(firstName),middleName(middleName),lastName(lastName),customerID(id),ssn(ssn), address(homeAddress), emailAddress(emailAddress), password(password)

	//generate testing uisers
	Person* rox = new Person("Rox", "Suzanne", "Morris", "Somewhere in MI", "rox@gmail.com", 0, 111111111, "st4rbucks");
	Person* alex = new Person("Alexandra", "Wuan-Feng Garland", "Bowman", "Marquette, Michigan", "alex@gmail.com", 0, 222222222, "0tt3r5");
	Person* hayden = new Person("Hayden", "Herold", "Martineau", "Grand Blanc, Michigan", "hayden@gmail.com", 0, 333333333, "y4kuz4");
	Person* val = new Person("Val", "Oconic", "Batchelder", "Somewhere in MI", "val@gmail.com", 0, 111111111, "m4g1c");
	Person* thomas = new Person("Thomas", "James", "Cookenmaster", "Grand Blanc, Michigan", "thomas@gmail.com", 0, 444444444, "c00k4321");
	Person* jason = new Person("Jason", "Nathaniel", "Jackson", "Somewhere in TX", "jason@gmail.com", 0, 555555555, "!4nimeAdv3ntures");
	Person* brandon = new Person("Brandon", "Diterich", "Muzer", "Grand Blanc, Michigan,", "brandon@gmail.com", 0, 666666666, "br4nd0n");
	Person* julio = new Person("Julio", "Chance", "$Bucks$", "\"New Jersey\"", "julio@gmail.com", 0, 777777777, "d4rkm45t3r");
	rox->generateCustomerID();
	alex->generateCustomerID();
	hayden->generateCustomerID();
	val->generateCustomerID();
	thomas->generateCustomerID();
	jason->generateCustomerID();
	brandon->generateCustomerID();
	julio->generateCustomerID();

	//Give random accounts to testing users
	giveAccounts(rox);
	giveAccounts(alex);
	giveAccounts(hayden);
	giveAccounts(val);
	giveAccounts(thomas);
	giveAccounts(jason);
	giveAccounts(brandon);
	giveAccounts(julio);

	//Insert testing users
	users->Insert(rox);
	users->Insert(alex);
	users->Insert(hayden);
	users->Insert(val);
	users->Insert(thomas);
	users->Insert(jason);
	users->Insert(brandon);
	users->Insert(julio);




	std::cout << "These are the newly generated ids for testing accounts. Save them if you wish to test them when logging into one of the accounts" << std::endl;
	std::cout << "rox #" << rox->getID() << std::endl;
	std::cout << "alex #" << alex->getID() << std::endl;
	std::cout << "hayden #" << hayden->getID() << std::endl;
	std::cout << "val #" << val->getID() << std::endl;
	std::cout << "thomas #" << thomas->getID() << std::endl;
	std::cout << "jason #" << jason->getID() << std::endl;
	std::cout << "brandon #" << brandon->getID() << std::endl;
	std::cout << "julio #" << julio->getID() << std::endl;

	std::cout << std::endl << "press enter to continue with the program." << std::endl;
	std::cin.ignore();

	system("cls");
	

	Console console = Console();

	int count = 0;


	srand(time(0));
	while (running) {
		Node<Savings>* node = savingsAccounts->getHead();
		while (node != nullptr) {
			Savings* value = node->getValue();
			switch (value->getFrequency()) {
			case SECONDLY:
				if (time(0) - value->compound > 0) {
					value->Compound();
				}
				break;
			case DAILY:
				if (time(0) - value->compound > 86400) {
					value->Compound();
				}
				break;
			case WEEKLY:
				if (time(0) - value->compound > (86400*7)) {
					value->Compound();
				}
				break;
			case MONTHLY:
				if (time(0) - value->compound > ((86400 * 7) * 4)) {
					value->Compound();
				}
				break;
			case QUATERLY:
				if (time(0) - value->compound > ((86400 * 7) * 4) *3) {
					value->Compound();
				}
				break;
			case ANNUALLY:
				if (time(0) - value->compound > ((86400 * 7) * 4) * 12) {
					value->Compound();
				}
				break;
			}
			node = node->getNext();
			
		}
		console.printScreen();
	}

}

