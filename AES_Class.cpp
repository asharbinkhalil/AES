#include "AES_Class.h"
#include <Windows.h>
#include<iostream>
using namespace std;
string AES_Class::ASCIItoHEX(string ascii)
{
	stringstream ss;
	string hexs;
	for (const auto& item : ascii) {
		ss << hex << int(item);
	}
	hexs = ss.str();
	return hexs;
}
string AES_Class::toHex(string bin)
{
	int result = 0;
	for (size_t count = 0; count < bin.length(); ++count)
	{
		result *= 2;
		result += bin[count] == '1' ? 1 : 0;
	}
	stringstream ss;
	ss << hex << result;

	string hexVal(ss.str());
	return hexVal;
}
string AES_Class::toBinary(const string& s) {
	string out;
	for (auto i : s) {
		uint8_t n;
		if (i <= '9' and i >= '0')
			n = i - '0';
		else
			n = 10 + i - 'A';
		for (int8_t j = 3; j >= 0; --j)
			out.push_back((n & (1 << j)) ? '1' : '0');
	}

	return out;
}
string AES_Class::Xor_binaries(string bin1, string bin2)
{
	string output;
	for (int i = 0; i < bin1.length(); i++)
	{
		output += ((bin1[i] - 48) ^ (bin2[i] - 48)) + 48;
	}
	return output;
}
string AES_Class::keyInput()
{
	int n = 0;
	if (keysize == 256)
		n = 32;
	else
		n = 16;
	string dummyinput, keyinput;
	while (dummyinput.length() < n)//exception handling for key length
	{
		cout << "\t\t\t\t\tEnter Key : (atleast "<<n<< " ascii characters)\n\t\t\t\t\t";
		getline(cin, dummyinput);
		if (dummyinput.length() < n)
		{
			cout << "\t\t\t\t\tPls Enter key Again: \t\t\t\t\t";
			Sleep(700);
			system("CLS");
		}
	}
	for (int i = 0; i < n; i++)
		keyinput += dummyinput[i];
	return keyinput;
}
string  AES_Class::textInput()
{
	string dummyinput, textinput;
	while (dummyinput.length() < 16)//exception handling for key length
	{
		cout << "\t\t\t\t\tEnter Plaintext : (atleast 16 ascii characters)\n\t\t\t\t\t";
		getline(cin, dummyinput);
		if (dummyinput.length() < 16)
		{
			cout << "\t\t\t\t\tPls Enter Plaintext Again: ";
			Sleep(700);
			system("CLS");
		}
	}
	for (int i = 0; i < 16; i++)
		textinput += dummyinput[i];
	return textinput;
}
void AES_Class::func()
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
}
void AES_Class::check()
{
	if (keysize == 256)
		cout << keysize;
}
