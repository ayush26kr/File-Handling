#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

    public:
    void create_account();  //get data from user
    void show_account() const;  //show data on screen
    void modify(); //to add new data
    void dep(int);  //accept amount and add to balance
    void draw(int);  //accept amount and subtract from balance
    void report() const;  //show datain tabular form
    int retacno() const;  //return account number
    int retdeposit() const;  //return balance amount
    char rettype() const;  //retunr type of account
};

void account::create_account()
{
    cout<<"\t\twelcome to create account page "<<endl<<endl;
    cout<<"\nEnter the account number: ";
    cin>>acno;
    cout<<"\nEnter the name of the account holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter type of the account : ";
    cin>>type;
    type=_toupper(type);
    cout<<"\nEnter the initial amount: ";
    cin>>deposit;
    cout<<"\n\t\tACCOUNT CREATED";
}
void account::show_account() const
{
    cout<<"\nAccount Number: "<<acno;
    cout<<"\nAccount Holder name: "<<name;
    cout<<"\nType of account: "<<type;
    cout<<"\nBalance amount: "<<deposit;
}
void account::modify()
{
    cout<<"\nAccount No :"<<acno;
    cout<<"\nModify Account Holder's Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify type of account: ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance amount : ";
    cin>>deposit;
}
void account::dep(int x)
{
    deposit+=x;

}
void account::draw(int x)
{
    deposit-=x;
}
void account::report() const{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
    }
int account::retacno()const{
    return acno;
}
int account::retdeposit()const{
    return deposit;
}
char account::rettype()const{
    return type;
}

//******** function delaration*************
void write_account();  //write account in binary file
void display_sp(int);  //display account details given by user
void modify_account(int); //modify record to file
void delete_account(int);  //delete record of a file
void display_all();  //function to display all account details
void deposit_withdraw(int,int); //function to deposit/withdraw amount for given account
void intro();  //introductory screen function
int main()
{
    int choice;
    int num;
    cout<<"\t\t\t====================================="<<endl;
    cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM"<<endl;
    cout<<"\t\t\t====================================="<<endl;
    cout<<"\t\t\t1.NEW ACCOUNT"<<endl<<"\t\t\t2.DEPOSIT AMOUNT"<<endl<<"\t\t\t3.WITHDRAW AMOUNT"<<endl<<"\t\t\t4.BALANCE ENQUIRY"<<endl<<"\t\t\t5.ALL ACCOUNT HOLDER LIST"<<endl;
    cout<<"\t\t\t6.CLOSE AN ACCOUNT"<<endl<<"\t\t\t7.MODIFY ACCOUNT DETAILS"<<endl<<"\t\t\t8.EXIT"<<endl;
    cout<<"\n\t\t\t\tEnter your choice: ";
    cin>>choice;
    while(choice!='8'){
    system("cls");
    switch(choice)
    {
        case 1:write_account();
        break;
        case 2:cout<<"\n\n\nEnter the account number: ";
        cin>>num;
        deposit_withdraw(num,1);
        break;
        case 3:
        cout<<"\n\n\tEnter the account number: ";
        cin>>num;
        deposit_withdraw(num,2);
        break;
        case 4:
        cout<<"\n\nEnter the account number: ";
        cin>>num;
        display_sp(num);
        break;
        case 5:display_all();
        break;
        case 6:
        cout<<"\n\nEnter the account number: ";
        cin>>num;
        delete_account(num);
        break;
        case 7:
        cout<<"\n\nEnter the account number: ";
        cin>>num;
        modify_account(num);
        break;
        case 8:
        cout<<"Thanks for visiting the Project";
        break;
        default:cout<<"Enter right choice "<<"\a\a\a";
    }
    cin.ignore();
    cin.get();
    }
}
void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File couldn't be opened .RESS ANY KEY....";
        return ;
    }
    cout<<"\nBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"\n\nAccount number does not exist ";
    }
}

void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be opened !! Press any key....";
        return;
    }
    while(!File.eof()&&found==false)
    {
        File.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"Enter the New Details of the account "<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\nRecord updated ";
            found=true;
        }
    }
    File.close();
    if(found==false)
    cout<<"\n\nRecord not Found ";
}

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !!PRESS ANY KEY ";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno()!=n){
            outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRECORD DELETED ";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be opened !! PRESS ANY KEY ...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"\t\t------------------------------\n";
    cout<<"A/c no.  Name  Type  Balance\n";
    cout<<"\t\t=========================\n";
    while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}
void deposit_withdraw(int n,int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! PRESS ANY KEY ...";
        return;
    }
    while(!File.eof() && found ==false)
    {
        File.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tDeposit Amount";
                cout<<"\n\nEnter the amount to be deposited ";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tWithdraw Amount ";
                cout<<"\n\nEnter amount to be withdraw ";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 &&ac.rettype()=='S')||(bal<1000 && ac.rettype()=='C'))
                cout<<"INSUFFICIENT BALANCE ";
                else
                ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\t\tRecord Updated ";
        }
    }
    File.close();
    if(found==false)
    cout<<"\n\nRECORD NOT FOUND";
}
