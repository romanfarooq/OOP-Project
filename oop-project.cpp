#include<iostream>
#include<fstream>
#include<string>
#include <cstdio>
using namespace std;

class Customer
{
private:
	string name;
	string phone;
	string email;
	string date;

public:
	Customer(string name = "", string phone = "", string email = "", string date = "")
	{
		this->name = name;
		this->phone = phone;
		this->email = email;
		this->date = date;
	}

	void setName(string name)
	{
		this->name = name;
	}

	void setPhone(string phone)
	{
		this->phone = phone;
	}

	void setEmail(string email)
	{
		this->email = email;
	}

	void setDate(string date)
	{
		this->date = date;
	}

	string getName()
	{
		return name;
	}

	void Input()
	{
		cout << "\n\t\t\t\tENTER NAME: ";
		cin >> name;
		cout << "\n\t\t\t\tENTER PHONE: ";
		cin >> phone;
		cout << "\n\t\t\t\tENTER EMIAL: ";
		cin >> email;
		cout << "\n\t\t\t\tENTER DATE: ";
		cin >> date;
	}

	
	bool readFile()
	{
		ifstream fin(name + ".txt");
		if (fin.is_open())
		{
			fin >> name;
			fin >> phone;
			fin >> email;
			fin >> date;
			fin.close();
			cout << "\n\n\t\t\t\t======================\n";
			cout << "\t\t\t\t     INFORMATION";
			cout << "\n\t\t\t\t======================\n";
			cout << "\n\t\t\t\tNAME: " << name;
			cout << "\n\t\t\t\tPHONE: " << phone;
			cout << "\n\t\t\t\tEMAIL: " << email;
			cout << "\n\t\t\t\tDATE OF OPENING: " << date;
			cout << "\n\t\t\t\tINTEREST RATE: 5.7 %";
			return true;
		}
		else
		{
			cout << "\n\t\t\t\tACCOUNT NOT EXIST: ";
			return false;
		}
	}

	void writeFile()
	{
		ofstream fout(name + ".txt");
		if (fout.is_open())
		{
			fout << name << endl;
			fout << phone << endl;
			fout << email << endl;
			fout << date << endl;
			fout.close();
		}
	}

	bool deleteFile(string name)
	{
		const char* temp = name.c_str();   /* remove function does not accept string as 
										      parameter so changing it to const char pointer */
		if (remove(temp))     // returns zero if the file is successfully deleted
		{
			cout << "\n\t\t\t\tACCOUNT NOT EXIST: ";
			return false;
		}
		return true;
	}
};

class Account
{
protected:
	int balance;
public:
	Customer customer;
	Account()
	{
		balance = 0;
	}

	virtual bool setBalance()
	{
		cout << "\n\t\t\t\tENTER BALANCE: ";
		cin >> balance;
		return true;
	}

	bool readBalance()
	{
		ifstream fin(customer.getName() + "balance.txt");
		if (fin.is_open())
		{
			fin >> balance;
			fin.close();
			return true;
		}
		else
		{
			cout << "\n\t\t\t\tACCOUNT NOT EXIST: ";
			return false;
		}
	}

	void writeBalance() 
	{
		ofstream fout(customer.getName() + "balance.txt");
		if (fout.is_open())
		{
			fout << balance;
			fout.close();
		}
	}

	void deposit()
	{
		if (!readBalance())
		{
			return;
		}
		int bal;
		cout << "\n\t\t\t\tENTER BALANCE YOU WANT TO DEPOSIT: ";
		cin >> bal;
		balance += bal;
		writeBalance();
	}

	void withdraw()
	{
		if (!readBalance())
		{
			return;
		}
		int bal;
		cout << "\n\t\t\t\tENTER BALANCE YOU WANT TO WITHDRAW: ";
		cin >> bal;
		if (balance - bal < 0)
		{
			cout << "\n\t\t\t\tCAN'T WITHDRAW. YOU ONLY HAVE RS. " << balance;
		}
		else if (balance - bal >= 0)
		{
			balance -= bal;
			cout << "\n\t\t\t\tREMAINING BALANCE RS. " << balance;
			writeBalance();
		}
	}

	void display_balance()
	{
		if (readBalance())
		{
			cout << "\n\t\t\t\tBALANCE: " << balance;
		}
	}
};



class Saving_Account : public Account
{
private:
	const float interst_rate;
public:
	Saving_Account() : interst_rate(5.7) {}

	bool setBalance()
	{
		cout << "\n\t\t\t\tENTER BALANCE: ";
		cin >> balance;
		return true;
	}
};

class Current_Account : public Account
{
private:
	const int min_balance;
public:
	Current_Account() : min_balance(1000) {}

	bool setBalance()
	{
		int bal;
		cout << "\n\t\t\t\tENTER BALANCE: ";
		cin >> bal;
		if (bal > min_balance)
		{
			balance = bal;
			return true;
		}
		else
		{
			cout << "\n\t\t\t\tStarting Balance must be greater than 1000 to open a Current Account\n";
			system("pause");
			return false;
		}
	}

};

class Loan
{
private:
	int amount;
public:
	Customer customer;
	Loan(int amount = 0)
	{
		this->amount = amount;
	}

	void setAmount()
	{
		cout << "\n\t\t\t\tENTER LOAN AMOUNT: ";
		cin >> amount;
	}

	bool readLoan()
	{
		ifstream fin(customer.getName() + "loan.txt");
		if (fin.is_open())
		{
			fin >> amount;
			fin.close();
			return true;
		}
		else
		{
			cout << "\n\t\t\t\tLOAN NOT EXIST: ";
			return false;
		}
	}

	void writeLoan()
	{
		ofstream fout(customer.getName() + "loan.txt");
		if (fout.is_open())
		{
			fout << amount;
			fout.close();
		}
	}

	void payLoan()
	{
		if (!readLoan())
		{
			return;
		}
		int num;
		cout << "\n\t\t\t\tENTER AMOUNT YOU WANT TO PAY: ";
		cin >> num;
		if (amount - num >= 0)
		{
			amount -= num;
			cout << "\n\t\t\t\tYOUR REMAINING LOAN IS RS. " << amount;
			if (amount == 0)
			{
				if (customer.deleteFile(customer.getName() + ".txt"))
				{
					if (customer.deleteFile(customer.getName() + "loan.txt"))
					{
						cout << "\n\n\t\t\t\tYOU HAVE PAID YOUR LOAN\n\t\t\t\tSUCCESFULLY DELETED!";
					}
				}
			}
			else
			{
				writeLoan();
			}
		}
		else
		{
			cout << "\n\t\t\t\tYOU ARE PAYING " << num << " WHILE YOUR REMAING LOAN IS " << amount;
		}
	}

	void display_loan()
	{
		if (readLoan())
		{
			cout << "\n\t\t\t\tLOAN: " << amount;
		}
	}
};


class Bank
{
private:
	Account* account;
	Saving_Account* saving_account;
	Current_Account* current_account;
	Loan* loan;
public:
	Bank()
	{
		account = nullptr;
		saving_account = nullptr;
		current_account = nullptr;
		loan = nullptr;
	}

	void setAccount(Account* acc)
	{
		account = acc;
	}

	void setSavingAccount(Saving_Account* acc)
	{
		saving_account = acc;
	}

	void setCurrentAccount(Current_Account* acc)
	{
		current_account = acc;
	}

	void setLoan(Loan* l)
	{
		loan = l;
	}

};


int main()
{
	Bank obj;
	char ch, flag;
	string name;
	do
	{
		system("CLS");
		cout << "\n\n\t\t\t\t======================\n";
		cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
		cout << "\n\t\t\t\t======================\n";

		cout << "\t\t\t\t    ::MAIN MENU::\n";
		cout << "\n\t\t\t\t1. ADMIN";
		cout << "\n\t\t\t\t2. USER";
		cout << "\n\t\t\t\t3. EXIT";
		cout << "\n\n\t\t\t\tSelect Your Option (1-3): ";
		cin >> ch;

		if (ch == '1')
		{
			do
			{
				system("CLS");
				cout << "\n\t\t\t\t1. BALANCE ENQUIRY";
				cout << "\n\t\t\t\t2. LOAN ENQUIRY";
				cout << "\n\t\t\t\t3. MODIFY INFORMATION";
				cout << "\n\t\t\t\t4. EXIT";
				cout << "\n\n\t\t\t\tSelect Your Option (1-4): ";
				cin >> flag;
				if (flag == '1')
				{
					Account acc;
					obj.setAccount(&acc);
					cout << "\n\t\t\t\tENTER NAME: ";
					cin >> name;
					acc.customer.setName(name);
					if (acc.customer.readFile())
					{
						acc.display_balance();
					}
				}
				else if (flag == '2')
				{
					Loan loan;
					obj.setLoan(&loan);
					cout << "\n\t\t\t\tENTER NAME: ";
					cin >> name;
					loan.customer.setName(name);
					if (loan.customer.readFile())
					{
						loan.display_loan();
					}
				}
				else if (flag == '3')
				{
					Account acc;
					obj.setAccount(&acc);
					do
					{
						system("CLS");
						cout << "\n\t\t\t\t1. CHANGE ACCOUNT";
						cout << "\n\t\t\t\t2. CHANGE LOAN";
						cout << "\n\t\t\t\t3. EXIT\n\t\t\t\t";
						cin >> flag;
						if (flag == '1')
						{
							cout << "\n\t\t\t\tENTER NAME: ";
							cin >> name;
							acc.customer.setName(name);
							if (acc.customer.deleteFile(name + ".txt"))
							{
								cout << "\n\t\t\t\tSUCCESFULLY DELETED!";
								cout << "\n\n\t\t\t\t======================\n";
								cout << "\t\t\t\t    ENTER NEW DATA      ";
								cout << "\n\t\t\t\t======================\n";
								if (acc.customer.deleteFile(name + "balance.txt"))
								{
									acc.customer.Input();
									if (acc.setBalance())
									{
										acc.customer.writeFile();
										acc.writeBalance();
									}
								}
							}
						}
						else if (flag == '2')
						{
							Loan loan;
							obj.setLoan(&loan);
							cout << "\n\t\t\t\tENTER NAME: ";
							cin >> name;
							loan.customer.setName(name);
							if (loan.customer.deleteFile(name + ".txt"))
							{
								cout << "\n\t\t\t\tSUCCESFULLY DELETED!";
								cout << "\n\n\t\t\t\t======================\n";
								cout << "\t\t\t\t    ENTER NEW DATA      ";
								cout << "\n\t\t\t\t======================\n";
								if (loan.customer.deleteFile(name + "loan.txt"))
								{
									loan.customer.Input();
									loan.customer.writeFile();
									loan.setAmount();
									loan.writeLoan();
								}
							}
						}
						if (flag != '3')
						{
							cout << endl;
							system("pause");
						}
					} while (flag != '3');	
				}
				if (flag != '4')
				{
					cout << endl;
					system("pause");
				}
			} while (flag != '4');
		}
		else if (ch == '2')
		{
			do
			{
				system("CLS");
				cout << "\n\t\t\t\t1. NEW ACCOUNT";
				cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
				cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
				cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
				cout << "\n\t\t\t\t5. CLOSE AN ACCOUNT";
				cout << "\n\t\t\t\t6. GET LOAN";
				cout << "\n\t\t\t\t7. PAY LOAN";
				cout << "\n\t\t\t\t8. LOAN ENQUIRY";
				cout << "\n\t\t\t\t9. EXIT";
				cout << "\n\n\t\t\t\tSelect Your Option (1-9): ";
				cin >> flag;
				if (flag == '1')
				{
					do
					{
						system("CLS");
						cout << "\n\t\t\t\t1. SAVING ACCOUNT";
						cout << "\n\t\t\t\t2. CURRENT ACCOUNT";
						cout << "\n\t\t\t\t3. EXIT\n\t\t\t\t";
						cin >> flag;
						if (flag == '1')
						{
							Saving_Account sav_acc;
							obj.setSavingAccount(&sav_acc);
							sav_acc.customer.Input();
							if (sav_acc.setBalance())
							{
								sav_acc.customer.writeFile();
								sav_acc.writeBalance();
							}		
						}
						else if (flag == '2')
						{
							Current_Account curr_acc;
							obj.setCurrentAccount(&curr_acc);
							curr_acc.customer.Input();
							if (curr_acc.setBalance())
							{
								curr_acc.customer.writeFile();
								curr_acc.writeBalance();
							}
						}
					} while (flag != '3');
				}
				else if (flag == '2' || flag == '3' || flag == '4' || flag == '5')
				{
					Account acc;
					obj.setAccount(&acc);
					cout << "\n\t\t\t\tENTER NAME: ";
					cin >> name;
					acc.customer.setName(name);
					if (flag == '2')
					{
						acc.deposit();
					}
					else if (flag == '3')
					{
						acc.withdraw();
					}
					else if (flag == '4')
					{
						if (acc.customer.readFile())
						{
							acc.display_balance();
						}
					}
					else if (flag == '5')
					{
						if (acc.customer.deleteFile(name + ".txt"))
						{
							if (acc.customer.deleteFile(name + "balance.txt"))
							{
								cout << "\n\t\t\t\tSUCCESFULLY DELETED!";
							}	
						}
					}
				}
				else if (flag == '6')
				{
					Loan loan;
					obj.setLoan(&loan);
					loan.customer.Input();
					loan.customer.writeFile();
					loan.setAmount();
					loan.writeLoan();
				}
				else if (flag == '7' || flag == '8')
				{
					Loan loan;
					obj.setLoan(&loan);
					cout << "\n\t\t\t\tENTER NAME: ";
					cin >> name;
					loan.customer.setName(name);
					if (flag == '7')
					{
						loan.payLoan();
					}
					else if (flag == '8')
					{
						if (loan.customer.readFile())
						{
							loan.display_loan();
						}
					}
				}
				if (flag != '9')
				{
					cout << endl;
					system("pause");
				}
			} while (flag != '9');
		}
	}
	while (ch != '3');
	return 0;
}
