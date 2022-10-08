#include "AES_Class.h"
#include<iostream>
#include <Windows.h>
using namespace std;
int main()
{
	cout << "\t\t\t\t------------------- ASHAR KHALIL----------------------\n";
	cout << "\t\t\t\t-------------	      20K - 1724         --------------\n";
	cout << "\t\t\t\t--------------- Number Theory & Crypto ---------------\n";
	cout << "\t\t\t\t-------------    AES Implementation    ---------------\n\n\n";
	cout << "\t\t\t\t\t/--------------------------------------/";
	cout << "\n\t\t\t\t\t|    Copyrights: Poor_logics by Ashar  | ";
	cout << "\n\t\t\t\t\t| -> Loads data from a file.           |";
	cout << "\n\t\t\t\t\t| -> Generate Keys.                    |";
	cout << "\n\t\t\t\t\t/--------------------------------------/\n\n\n\n";

	AES_Class a;
	string dummyinput,input;
	while (dummyinput.length() < 33)//exception handling for key length
	{
		cout << "Enter Key : (atleast 32 ascii characters)\n";
		getline(cin, dummyinput);
		if (dummyinput.length() < 33)
		{
			cout << "Pls Enter key Again: ";
			Sleep(700);
			system("CLS");
		}
	}
	for (int i = 0; i < 32; i++)
		input += dummyinput[i];


	string hexkey = a.ASCIItoHEX(input);
	a.generate_round_keys(hexkey);
	a.printKeys();
}
