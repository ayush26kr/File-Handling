#include<fstream>
#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
	ofstream fout;
	fout.open("Myfirstfile.dat");
	getch();
	fout<<"My name is Ayush Kumar";
	getch();
	fout.close();
	getch();
}
