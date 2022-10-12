#include"../AES/AES.h"
#include<iostream>
#include<fstream>
using namespace std;
int main()
{	
	AES_Encrypt a;
	char choice = a.func();  //intro :)
	fstream Fe;
	string key;
	int s;
	cin >> s;
	a.setKeysize(s);
	Fe.open("main/Key.txt");
	if (!Fe)
		cout << "File doesn’t exist.";
	else
		getline(Fe,key); // key input
	Fe.close();
	string plaintext, ciphertext;
	if (choice == 'E')
	{
		fstream FileName;
		FileName.open("main/Text.txt");
		getline(FileName, plaintext);
		FileName.close();
		// plaintext = a.textInput();       // plaintext input
		 ciphertext = a.Encrypt(key, plaintext);
		 cout << "\nCipher text : START" <<ciphertext << "END";
		 ofstream FileNam("main/Text.txt");
			FileNam << ciphertext;
	}
	else if(choice =='D')
	{
		ciphertext ="";
		fstream FileName;
		FileName.open("main/Text.txt");
		if (!FileName)
			cout << "File doesn’t exist.";
		else
			getline(FileName, ciphertext);
		FileName.close();
		//cout << ciphertext<<"||||" << ciphertext.length();
		key = a.ASCIItoHEX(key);
		a.generate_round_keys(key);
		a.printKeys();
		plaintext= a.hexToASCII(a.Decrypt(ciphertext));
		ofstream of("main/Text.txt");
		of << plaintext;
		of.close();

	}
	else
	{
		plaintext = a.textInput();       // plaintext input
		ciphertext = a.Encrypt(key, plaintext);
		cout << ciphertext;
		cout << a.hexToASCII(a.Decrypt(ciphertext));
	}
}
