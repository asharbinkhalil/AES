#include "AES_Class.h"
#include<iostream>
using namespace std;

string fixedMatrix[4][4] = { {"02","03","01","01"},
					{"01","02","03","01"},
					{"01","01","02","03"},
					{"03","01","01","02"} };
int main()
{
	AES_Class a;
	a.func();                              //intro :)
	a.setKeysize(256);
	string key ;             // key input
	string plaintext;      // plaintext input
	
	//key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
	//key = "Thats my Kung Fu";
	key = a.keyInput();
	key = a.ASCIItoHEX(key);
	//plaintext = "Two One Nine Two";
	plaintext = a.textInput();
	plaintext = a.ASCIItoHEX(plaintext);
	a.generate_round_keys(key);            //generating round keys AES-128(10), AES-256(16)
 	a.printKeys();
	string** stateMatrix = a.AddRoundKey(plaintext, key);
	cout << "\n\n\n\n\t\t\t\t\tState Matrix, Round 0 \n\t\t\t\t\t";
	a.printMatrix(stateMatrix);


	string** fixedMat = new string * [4];
	for (int i = 0; i < 4; i++)
		fixedMat[i] = new string[4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			fixedMat[i][j] = fixedMatrix[i][j];
	////-------------------------------------Round 1-------------------------------------------------
	string** ss = a.SubstituteBytes(stateMatrix);
	cout << "\n\n\n\n\t\t\t\t\tByte Sustituted, Round 1 \n\t\t\t\t\t";
	a.printMatrix(ss);
	cout << "\n\n\n\n\t\t\t\t\tLeft Shifted, Round 1 \n\t\t\t\t\t";
	string** shiftedrows = a.ShiftRows(ss);
	a.printMatrix(shiftedrows);

	cout << "\n\n\n\n\t\t\t\t\tMixed Columns, Round 1 \n\t\t\t\t\t";
	a.printMatrix(a.mixColumns(fixedMat, shiftedrows));
	cout << "\n\n\n\n\t\t\t\t\tAdd Round Key, Round 1 \n\t\t\t\t\t";
	string **rk=a.AddRoundKey(a.twoDto1dCV(a.mixColumns(fixedMat, shiftedrows)), a.getKeys()[1]);
	a.printMatrix(rk);
	///--------------------------------------Round 2-------------------------------------------------
	for (int i = 2; i <= 14; i++)
	{
		cout << "\n\n\n\n\t\t\t\t\tByte Sustituted, Round " << i << "\n\t\t\t\t\t";
		a.printMatrix(a.SubstituteBytes(rk));
		cout << "\n\n\n\n\t\t\t\t\tLeft Shifted, Round " << i << " \n\t\t\t\t\t";
		a.printMatrix(a.ShiftRows(a.SubstituteBytes(rk)));
		cout << "\n\n\n\n\t\t\t\t\tMixed Columns, Round " << i << " \n\t\t\t\t\t";
		a.printMatrix(a.mixColumns(fixedMat, a.ShiftRows(a.SubstituteBytes(rk))));
		cout << "\n\n\n\n\t\t\t\t\tAdd Round Key, Round " << i << " \n\t\t\t\t\t";
		rk = a.AddRoundKey(a.twoDto1dCV(a.mixColumns(fixedMat, a.ShiftRows(a.SubstituteBytes(rk)))), a.getKeys()[i]);
		a.printMatrix(rk);
	}
	cout << "\n\n\n\n\t\t\t\t\tByte Sustituted, Round last \n\t\t\t\t\t";
	a.printMatrix(a.SubstituteBytes(rk));
	cout << "\n\n\n\n\t\t\t\t\tLeft Shifted, Round last \n\t\t\t\t\t";
	a.printMatrix(a.ShiftRows(a.SubstituteBytes(rk)));
	cout << "\n\n\n\n\t\t\t\t\tAdd Round Key, Round last \n\t\t\t\t\t";
	rk = a.AddRoundKey(a.twoDto1dCV(a.ShiftRows(a.SubstituteBytes(rk))), a.getKeys()[10]);
	a.printMatrix(rk);

	
	//a.printMatrix(a.SubstituteBytes(rk));






}
