#include"../AES/AES.h"
#include<iostream>
#include<fstream>
using namespace std;
int main()
{	
	AES_Encrypt a;
	char choice = a.func();  //intro :)
	string key = a.keyInput(); // key input
	string plaintext, ciphertext;
	if (choice == 'E')
	{
		 plaintext = a.textInput();       // plaintext input
		 ciphertext = a.Encrypt(key, plaintext);
		 cout << "\nCipher text : START" <<ciphertext << "END";
		 ofstream FileName("main/CipherText.txt");
		 for(int i=0; i<ciphertext.length(); i++)
			FileName << ciphertext[i];
	}
	else if(choice =='D')
	{
		ciphertext ="";
		fstream FileName;
		FileName.open("main/CipherText.txt", ios::in);
		if (!FileName) {
			cout << "File doesn’t exist.";
		}
		else {
			char x;
			while (1) {
				FileName >> x;
				if (FileName.eof())
					break;
				ciphertext+= x;
			}
		}
		FileName.close();
		//cout << ciphertext<<"||||" << ciphertext.length();
		plaintext= a.Decrypt(ciphertext);
		cout << "\nPlain text : START" << plaintext << "END";
	}
	else
	{
		plaintext = a.textInput();       // plaintext input
		ciphertext = a.Encrypt(key, plaintext);
		cout << ciphertext;
		cout << a.hexToASCII(a.Decrypt(ciphertext));
	}
}
