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