#include "AES_Class.h"
#include <Windows.h>
#include<iostream>
using namespace std;
string AES_Class::decToHexa(int n)
{
	char hexaDeciNum[100];
	int i = 0;
	while (n != 0) {
		int temp = 0;
		temp = n % 16;
		if (temp < 10) {
			hexaDeciNum[i] = temp + 48;
			i++;
		}
		else {
			hexaDeciNum[i] = temp + 55;
			i++;
		}
		n = n / 16;
	}
	string ans = "";
	for (int j = i - 1; j >= 0; j--)
		ans += hexaDeciNum[j];

	return ans;
}
string AES_Class::ASCIItoHEX(string ascii)
{
	string hex = "";
	for (int i = 0; i < ascii.length(); i++) {
		char ch = ascii[i];
		int tmp = (int)ch;
		string part = decToHexa(tmp);
		hex += part;
	}
	return hex;
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
	string dummyinput, keyinput;
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
		keyinput += dummyinput[i];
	return keyinput;
}
string  AES_Class::textInput()
{
	string dummyinput, textinput;
	while (dummyinput.length() < 16)//exception handling for key length
	{
		cout << "Enter Plaintext : (atleast 16 ascii characters)\n";
		getline(cin, dummyinput);
		if (dummyinput.length() < 16)
		{
			cout << "Pls Enter Plaintext Again: ";
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