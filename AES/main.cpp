#include "AES_Class.h"
#include<iostream>
using namespace std;
int main()
{
	AES_Class a;
	a.func();                              //intro :)
	int ks = 0;
	cout << "\n\t\t\t\t\tEnter key Size:  (128 or 256)\n\t\t\t\t\t";
	cin >> ks;
	cin.ignore();
	a.setKeysize(ks);
	string key  =a.keyInput();             // key input
	string plaintext= a.textInput();      // plaintext input
	//key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4"; //for 256 key verification NIST document
	a.Encrypt(key, plaintext);
	cout << "helo";
}
