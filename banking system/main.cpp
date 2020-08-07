//
//  main.cpp
//  banking system
//
//  Created by Alka Wadhwa on 21/07/20.
//  Copyright © 2020 Alka Wadhwa. All rights reserved.
//

#include <iostream>
#include<fstream>
#include<map>
#include<cstdlib>
#include<vector>
using namespace std;
#define MIN_BALANCE 500
class insufficientFunds{};
class Account{
private:
    string Firstname;
    string Lastname;
    long accountNumber;
    float balance;
    static long NextAccountNumber;
public:
    Account(){};
    Account(string fn,string ln,float a){
        NextAccountNumber++;
        Firstname=fn;
        Lastname=ln;
        balance=a;
        accountNumber=NextAccountNumber;
    }
    string getFirstName(){
        return Firstname;
    }
    string getLastName(){
        return Lastname;
    }
    float getBalance(){
        return balance;
    }
    long getAccNo(){
        return accountNumber;
    }
    void deposit(float amount){
        balance+=
        amount;
    }
    void withdraw(float amount){
        if(balance-=amount==MIN_BALANCE)
            throw insufficientFunds();
        balance-=amount;
    }
    friend ofstream & operator<<(ofstream &ofs, Account &a);
    friend ostream & operator<<(ostream &os, Account &a);
    friend ifstream & operator>>(ifstream &ifs, Account &a);
    static void setLastAccNumber(long AccountNo ){
        NextAccountNumber=AccountNo;
        }
    static long getLastaccNumber(){
        return NextAccountNumber;
    }
    
};
ofstream & operator<<(ofstream &ofs, Account &a){
    ofs<<a.Firstname<<endl;
    ofs<<a.Lastname<<endl;
    ofs<<a.accountNumber<<endl;
    ofs<<a.balance<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs, Account &a){
    ifs>>a.Firstname;
    ifs>>a.Lastname;
    ifs>>a.accountNumber;
    ifs>>a.balance;
    return ifs;
}
ostream & operator<<(ostream &os, Account &a){
    os<<"First Name:"<<a.Firstname<<endl;
     os<<"Last Name:"<<a.Lastname<<endl;
    os<<"Account No.:"<<a.accountNumber<<endl;
    os<<"Balance:"<<a.balance<<endl;
    return os;
}
long Account::NextAccountNumber=0;
class Bank{
private:
    map<long,Account> accounts;
public:
    Bank();
    Account openaccount(string fname, string lname, float balance);
    Account balanceEnquiry(long accountNumber);
    Account deposit(long accountNumber, float amount);
    Account withdraw(long accountNumber, float amount);
    void closeaccount(long accountNumber);
    void showallaccounts();
    ~Bank();
    
};
Bank::Bank(){
    Account account;
    ifstream infile;
    infile.open("Bank.account");
    if(!infile){
        cout<<"file does not exist"<<endl;
        return;}
    while(!infile.eof()){
        infile>>account;
    accounts.insert(pair<long,Account>(account.getAccNo(),account));
    }
    Account::setLastAccNumber(account.getAccNo());
    infile.close();
}
Account Bank::openaccount(string fname, string lname, float balance){
ofstream outfile;
       Account account(fname,lname,balance);
       accounts.insert(pair<long,Account>(account.getAccNo(),account));
       outfile.open("bank.account");
       map<long,Account>::iterator itr;
       for(itr=accounts.begin();itr!=accounts.end();itr++){
           outfile<<itr->second;
       }
       outfile.close();
    return account;
    
}

    Account Bank::balanceEnquiry(long accountNumber){
        map<long,Account>::iterator itr;
        itr=accounts.find(accountNumber);
        return itr->second;
    }
Account Bank::deposit(long accountNumber,float amount){
    map<long,Account>::iterator itr;
    itr=accounts.find(accountNumber);
    itr->second.deposit(amount);
    return itr->second;
}
Account Bank::withdraw(long accountNumber,float amount){
    map<long,Account>::iterator itr;
    itr=accounts.find(accountNumber);
    itr->second.withdraw(amount);
    return itr->second;
}
void Bank::closeaccount(long accountNumber){
    map<long,Account>::iterator itr;
    itr=accounts.find(accountNumber);
    cout<<"Account Deleted"<<itr->second<<endl;
    accounts.erase(accountNumber);
}
void Bank::showallaccounts(){
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++){
        cout<<itr->first<<" "<<itr->second<<endl;
    }
}
Bank::~Bank()
{
    ofstream outfile;
    outfile.open("bank.account");
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();
}

int main() {
    Account a;
    Bank b;
    int choice;
    float balance;
    long accountNumber;
    float amount;
    string fname,lname;
    cout<<"Banking System"<<endl;
    do{
        cout<<"\nselect an option below"<<endl;
        cout<<"1 Open an account"<<endl;
        cout<<"2 Balance enquiry"<<endl;
        cout<<"3 Deposit"<<endl;
        cout<<"4 Withdraw"<<endl;
        cout<<"5 Close an account"<<endl;
        cout<<"6 show all accounts "<<endl;
        cout<<"7 Quit"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>choice;
        switch (choice) {
            case 1:
                cout<<"First Name"<<endl;
                cin>>fname;
                cout<<"Last Name"<<endl;
                cin>>lname;
                cout<<"Initial balance"<<endl;
                cin>>balance;
                a=b.openaccount(fname,lname,balance);
                cout<<"cougratulations "<<fname<<" "<<lname<<"your account has been created"<<endl;
                cout<<a;
                break;
            case 2:
                cout<<"Account Number"<<endl;
                cin>>accountNumber;
                a=b.balanceEnquiry(accountNumber);
                cout<<"bank details are: "<<endl;
                cout<<a;
                break;
            case 3:
                cout<<"Account Number"<<endl;
                cin>>accountNumber;
                cout<<"Amount to be deposited"<<endl;
                cin>>amount;
                a=b.deposit(accountNumber,amount);
                cout<<"Balance is: "<<a<<endl;
                break;
            case 4:
                cout<<"Account Number"<<endl;
                cin>>accountNumber;
                cout<<"Amount to be withdrawn"<<endl;
                cin>>amount;
                a=b.withdraw(accountNumber,amount);
                cout<<"Balance is: "<<a<<endl;
                break;
            case 5:
                cout<<"Account Number"<<endl;
                cin>>accountNumber;
                b.closeaccount(accountNumber);
                cout<<endl<<"Account is Closed"<<endl;
                cout<<a;
                break;
            case 6:
                b.showallaccounts();
                break;
            case 7:
                break;
            default:
                cout<<"enter a correct choice"<<endl;
                exit(0);
        }
        
    }
    while(choice!=7);
    
    return 0;
}
