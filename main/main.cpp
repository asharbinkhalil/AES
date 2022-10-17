#include"../AES/AES.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
string readFileIntoString(const string& path) {
	ifstream input_file(path);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<< path << "'" << endl;
		exit(EXIT_FAILURE);
	}
	return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}
int main()
{	
	AES_Encrypt a;
	char choice = a.func();  //intro :)
	
	string key;
	int ks = 0;
	cout << "\n\t\t\t\t\tEnter key Size:  (128 | 192 | 256)\n\t\t\t\t\t";
	cin >> ks;
	a.setKeysize(ks);
	fstream Fe;
	Fe.open("main/Key.txt");
	if (!Fe)
		cout << "File doesn’t exist.";
	else
		getline(Fe,key); // key input
	Fe.close();
	string plaintext, ciphertext;
	if (choice == 'E')
	{
			plaintext = readFileIntoString("main/Text.txt");
			ciphertext = a.Encrypt(key, plaintext.substr(0,16));
			ofstream FileNam("main/Text.txt");
			FileNam << ciphertext;
			FileNam.close();
	}
	else if(choice =='D')
	{
		ciphertext ="";
		ciphertext = readFileIntoString("main/Text.txt");

		key = a.ASCIItoHEX(key);
		a.generate_round_keys(key);
		a.printKeys();

		plaintext= a.hexToASCII(a.Decrypt(ciphertext.substr(0,32)));
		ofstream of("main/Text.txt");
		of << plaintext;
		of.close();
	}
	else
	{
		cin.ignore();
		plaintext = a.textInput();       // plaintext input
		ciphertext = a.Encrypt(key, plaintext);
		cout << ciphertext;
		cout << a.hexToASCII(a.Decrypt(ciphertext));
	}
}
