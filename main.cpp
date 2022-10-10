#include "AES_Class.h"
#include<iostream>
using namespace std;
int main()
{
	AES_Class a;
	a.func();                              //intro :)
	a.setKeysize(128);
	string key ;             // key input
	string plaintext =a.textInput();      // plaintext input
	plaintext = a.ASCIItoHEX(plaintext);
	//key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
	key = a.keyInput();
	key = a.ASCIItoHEX(key);
	a.generate_round_keys(key);            //generating round keys AES-128(10), AES-256(16)
 	a.printKeys();
	string** stateMatrix = a.AddRoundKey(plaintext, key);
	cout << "\n\n\n\n\t\t\t\t\tState Matrix, Round 0 \n\t\t\t\t\t";
	a.printMatrix(stateMatrix);

	////-------------------------------------Round 1-------------------------------------------------
	string** ss = a.SubstituteBytes(stateMatrix);
	cout << "\n\n\n\n\t\t\t\t\tByte Sustituted, Round 1 \n\t\t\t\t\t";
	a.printMatrix(ss);
	cout << "\n\n\n\n\t\t\t\t\tLeft Shifted, Round 1 \n\t\t\t\t\t";
	string** shiftedrows = a.ShiftRows(ss);
	a.printMatrix(shiftedrows);

}
