#include "AES_Class.h"
#include<iostream>
using namespace std;
int main()
{

	AES_Class a;
	a.func(); //intro :)
	a.setKeysize(256);
	string key = a.keyInput();
	string plaintext = a.textInput();
	key = a.ASCIItoHEX(key);
	a.generate_round_keys(key);
	a.printKeys();

}
