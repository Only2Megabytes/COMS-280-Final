


#include <iostream>
#include <string>
//forward declarations



class LinkedList;
class Node;
class Data;
class Account;//Base class for all types of banking accounts
class Savings;//Class that represents a savings account, will inherit from account
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
	//Personal details
	std::string firstName;
	std::string lastName;
	std::string middleName;
	std::string address;
	int customerID;//Use
	int ssn[9];//social security number

	std::string password;


	//Contact details
	int phonenumber[10];
	std::string emailaddress;
	


};



//Implementation for account
class Account{
private:
	std::string password;

public:
	float balance = 0;

	Account() {

	}
	~Account() {};

	void operator+=(float value) {//This overload is for depositing to an accounts balance
		balance += value;
	}

	void operator+=(Account *account) {//This overload is for combing accounts, if for whatever reason, one account is in debt, that will be reflected.
		balance += account->balance;
		std::cout << "rhs account will be closed" << std::endl;
		//Include account closing process
	}

	void operator-=(float value) {//This overload is for withdrawing from an account
		balance -= value;
	}
	float getBalance() { return balance; }
	void setBalance(float value) { balance = value; }
};

class Checkings : public Account {//Checkings account, derives from account
public:
	
	Checkings() {
		balance = 0;
	}
	Checkings(float value) {
		balance = value;
	}

};

Person *login(std::string username, std::string ) {//Will, in the future, load customer information from a file
	Person *customer = new Person();
	//load file from directly
	return customer;
}

int main()
{

}

