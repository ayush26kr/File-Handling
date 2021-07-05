#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Book{
    int id;
    char name[30];
    float price;
    public:
    Book(){
        id=0;
        strcpy(name,"No title");
        price=0;
    }
    void setdata();
    void showdata();

    //file handling functions
    int storedata();
    void viewalldata();
    void searchdata(char*);
    void deletedata(char*);
    void updatedata(char*);
};
void Book::setdata()
{
    cout<<"Enter ID, title , Price : "<<endl;
    cin>>id;
    cin.ignore();
    cin.getline(name,19);
    cin>>price;
}
void Book::showdata()
{
    cout<<"ID :"<<id<<endl<<"Title :"<<name<<endl<<"Price :"<<price<<endl;
}
int Book::storedata()
{
    if(id==0 && price==0){
        cout<<"\n Data not initialised ";
        return 0;
    }
    else{
    ofstream fout;
    fout.open("Books.txt,ios::app");
    fout.write((char*)this,sizeof(*this));
    fout.close();
    }
}
void Book::viewalldata()
{
    ifstream fin;
    fin.open("Books.txt",ios::in);
    if(!fin)
    {
        cout<<"\nFile not found "<<endl;
    }
    else{
        fin.read((char*)this,sizeof(*this));  //read data
        while(!fin.eof())
        {
            showdata();
            cout<<endl;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }
}

void Book::searchdata(char* t)
{
    int count=0;
    ifstream fin;
    fin.open("Books.txt",ios::in);
    if(!fin){
        cout<<"\nFile not found"<<endl;
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,this->name))
            {
                showdata();
                count++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(count==0)
        {
            cout<<"Data not found "<<endl;
        }
        fin.close();
    }
}
void Book::deletedata(char* t)
{
    ifstream fin;
    ofstream fout;
    fin.open("Books.txt",ios::in);
    if(fin)
    {
        cout<<"\nFile does not exist"<<endl;
    }
    else
    {
        fout.open("Tempo.txt",ios::out);
        fin.read((char*)this,sizeof(*this));
        while (!fin.eof())
        {
            if(strcmp(name,t))
            {
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("Books.txt");
        rename("Tempo.txt","Books.txt");
    }
}
void Book::updatedata(char* t)
{
    fstream file;
    file.open("Books.txt",ios::in|ios::out|ios::ate);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(t,name))
        {
            setdata();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
}
main()
{
    display();
    Book b1;
     int choice;
    cout<<"Welcome to BOOK MANAGEMENT SYSTEM ";
    cout<<"1.SET DATA"<<endl<<"2.STORE DATA"<<endl<<"3.Show data"<<endl<<"4.Search Data"<<endl<<"5.UPDATE DATA"<<endl<<"6.VIEW ALL DATA"<<endl<<"7.DELETE DATA"<<endl<<"8.exit"<<endl;
    cout<<"\n\n\t\tENTER YOUR CHOICE: ";
    cin>>choice;
    string name_search;
    switch(choice)
    {
        while(choice!=8)
        {
            case 1:b1.setdata();
            break;
            case 2:b1.storedata();
            break;
            case 3:b1.showdata();
            break;
            case 4:cout<<"Enter name to be searched: ";
                    cin>>name_search;
                    b1.searchdata(name_search);
                    break;
            case 5:cout<<"Enter data to be updated: ";
                cin>>name_search;
                b1.updatedata(name_search);
            case 6:b1.viewalldata();
            break;
            case 7:cout<<"Enter name to be deleted: ";
            cin>>name_search;
            b1.deletedata(name_search);
            default:cout<<"Wrong choice";

        }
    }
   // b1.setdata();
    //b1.showdata();
    //b1.storedata();
}