#pragma once
#include <iostream>
#include<sstream>
#include <bitset>
#include <Windows.h>

using namespace std;
class AES_Class
{
	int keysize;
	string w[60];
	string keys[15];
	string fixedMatrix[4][4] = { {"02","03","01","01"},
					{"01","02","03","01"},
					{"01","01","02","03"},
					{"03","01","01","02"} };
	int sbox[16][16] =
	{
		  { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 }
		, { 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 }
		, { 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 }
		, { 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 }
		, { 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 }
		, { 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf }
		, { 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 }
		, { 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 }
		, { 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 }
		, { 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb }
		, { 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 }
		, { 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 }
		, { 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a }
		, { 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e }
		, { 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf }
		, { 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }
	};
public:
	void setKeysize(int size)
	{
		keysize = size;
	}
	int getKeysize()
	{
		return keysize;
	}
	string* getKeys()
	{
		return keys;
	}
	//--------------------------------------Utilities functions--------------------------------
	string ASCIItoHEX(string ascii);
	string toHex(string bin);
	string toBinary(const string& s);
	string Xor_binaries(string bin1, string bin2);
	void printMatrix(string** arr);
	int charHextoint(char c);
	string twoDto1dCV(string** arr)
	{
		string oned;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				oned += arr[j][i];
		return oned;
	}
	void func();
	//-----------------------------------------------------------------------------------------
	
	//--------------------------------------Input functions------------------------------------
	string keyInput();
	string textInput();
	//-----------------------------------------------------------------------------------------
	 
	
	//--------------------------------------Key Generation-------------------------------------
	string substiteBytesW(string w_last)
	{
		string  byte_substituted;
		for (int i = 0; i < w_last.length(); i += 2)
		{
			int val = charHextoint(w_last[i]);
			int val2 = charHextoint(w_last[i + 1]);

			std::ostringstream sso;
			sso << std::hex << sbox[val][val2];
			string temp;
			if (sso.str().length() == 1)
			{
				temp = '0';
				temp += sso.str();
				byte_substituted += temp;
			}
			else
				byte_substituted += sso.str();
		}
		return byte_substituted;

	}
	string find_G(string w_last, int rc)
	{
		reverse(w_last.begin(), w_last.begin() + 2);
		reverse(w_last.begin() + 2, w_last.end());
		reverse(w_last.begin(), w_last.end());
		
		string gw_last, byte_substituted;
		for (int i = 0; i < w_last.length(); i += 2)
		{
			int val = charHextoint(w_last[i]);
			int val2 = charHextoint(w_last[i+1]);

			std::ostringstream sso;
			sso << std::hex << sbox[val][val2];
			string temp;
			if (sso.str().length() == 1)
			{
				temp = '0';
				temp += sso.str();
				byte_substituted += temp;
			}
			else
				byte_substituted += sso.str();
		}
		string round_constant[14] = {	"01000000","02000000","04000000","08000000",
										"10000000","20000000","40000000","80000000",
										"1b000000","36000000","6c000000","d8000000",
										"AB000000","4d000000"};
		round_constant[rc] = toBinary(round_constant[rc]);
		byte_substituted = toBinary(byte_substituted);
		gw_last = Xor_binaries(round_constant[rc], byte_substituted);
		gw_last = toHex(gw_last);
		int l_temp = gw_last.length();
		if (l_temp < 8)
		{
			string temp = gw_last;
			gw_last = "";
			for (int i = 0; i < 8 - l_temp; i++)
				gw_last += '0';
			gw_last += temp;
		}
		return gw_last;
	}
	void printKeys()
	{
		int n = 0;
		if (keysize == 256)
			n = 15;
		else
			n = 11;
		for (int i = 0; i < n; i++)
			cout << "\n\t\t\t\tKey " << i << (i < 10 ? " : " : ": ") << keys[i];
		
	}
	void generate_round_keys(string key)
	{
		int j = 0, count = 0;
		int rounds = 0, quads = 0, w_count=0;
		if (keysize == 256)
			rounds = 14, quads = 7,w_count=60;
		else
			rounds = 10, quads = 3,w_count=44;
		for (int i = 0; i < key.length(); i++)
		{
			if (count < 8)
			{
				w[j] += key[i];
				count++;
			}
			else
			{
				count = 0;
				j++;
				i--;
			}
		}
		int w_index = 0, r = 0;
		int roundconst_c = 0;
		count = 8;
		int temp_length = 0;
		string temp,temp2;
		while (j < w_count)
		{
			j++;
			w[j] = Xor_binaries(toBinary(find_G(w[j - 1], roundconst_c++)), toBinary(w[w_index++]));
			w[j] = toHex(w[j]);
			temp_length = w[j].length();
			if (temp_length < 8)
			{
				temp = w[j];
				w[j] = "";
				for (int i = 0; i < 8 - temp_length; i++)
					w[j] += '0';
				w[j] += temp;
			}
			for (int i = 0; i < quads; i++)
			{
				j++;
				if (i == 3 && keysize==256)
					temp2 = substiteBytesW(w[j - 1]);
				else
					temp2 = w[j - 1];
				w[j] = Xor_binaries(toBinary(temp2), toBinary(w[w_index++]));
				w[j] = toHex(w[j]);
				
				temp_length = w[j].length();

				if (temp_length < 8)
				{
					temp = w[j];
					w[j] = "";
					for (int i = 0; i < 8 - temp_length; i++)
						w[j] += '0';
					w[j] += temp;
				}
				if (w[j].length() == 8)
					count++;
			}
		}
		int k = 0;
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 4; j++)
				keys[i] ="";
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 4; j++, k++)
				keys[i] += w[k];
	}
	//-----------------------------------------------------------------------------------------

	//-----------------------------------Generate State Matrix---------------------------------
	string** GenerateStateMatrix(string str)
	{
		string** ptr = new string * [4];
		for (int i = 0; i < 4; i++)
			ptr[i] = new string[4];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				ptr[j][i] = str.substr(i * 8 + j * 2, 2);
			}
		return ptr;
	}
	string** AddRoundKey(string plaintext,string key)
	{
		string** PTstateMat = GenerateStateMatrix(plaintext);
		string** KeystateMat = GenerateStateMatrix(key);
		string** stateMat = new string * [4];
		for (int i = 0; i < 4; i++)
			stateMat[i] = new string[4];

		string temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp= toHex(Xor_binaries(toBinary(PTstateMat[i][j]), toBinary(KeystateMat[i][j])));
				if (temp.length() == 1)
					temp = '0' + temp;
				stateMat[i][j] = temp;
			}
		}
		return stateMat;
	}

	//----------------------------------------------------------------------------------------- 
	
	//-------------------------------------Substitute Bytes------------------------------------
	string** SubstituteBytes(string** arr)
	{
		int val, val2 ;
		string tempo;
		string** ptr = new string * [4], val3, byte_substituted;
		for (int i = 0; i < 4; i++)
			ptr[i] = new string[4];


		for (int i = 0; i < 4; i++)
		{
			std::ostringstream sso;
			for (int j = 0; j < 4; j++)
			{
				val3 = arr[i][j];
				val = charHextoint(val3[0]);
				val2 = charHextoint(val3[1]);
				
				sso << std::hex << sbox[val][val2];
				tempo = sso.str();
				if (tempo.length() == 1)
					tempo = '0' + sso.str();
				byte_substituted += tempo;
				sso.str("");
				sso.clear();
				ptr[i][j] = byte_substituted;
				byte_substituted = "";
			}
		}
		return ptr;
	}
	//-----------------------------------------------------------------------------------------

	//-------------------------------------Shift Rows------------------------------------------
	void leftshift(string arr[], int size)
	{
		string temp = arr[0];
		for (int i = 0; i < size - 1; i++)
			arr[i] = arr[i + 1];
		arr[size - 1] = temp;
	}
	void LeftShiftNtTime(string arr[], int size, int k)
	{
		for (int i = 0; i < k; i++)
			leftshift(arr, size);
	}
	string** ShiftRows(string **D2)
	{
		for (int i = 0; i < 4; i++)
			LeftShiftNtTime(D2[i], 4, i);
		return D2;
	}
	//-----------------------------------------------------------------------------------------

	//-------------------------------------Mix Column------------------------------------------
	string** mixColumns(string **mt1, string** mt2)
	{
		string** muli = new string * [4];
		for (int i = 0; i < 4; i++)
			muli[i] = new string[4];
		string mul[4][4];
		string temp, temp2, t1;
		for (int i = 0; i < 4; i++)
		{
			if (i == 1)
				i = i;
			for (int j = 0; j < 4; j++)
			{
				mul[i][j] = "";
				if (i == 1)
					i = i;
				for (int k = 0; k < 4; k++)
				{
					t1 = "";
					temp2 = "";
					if (mt1[i][k] == "01")
						t1 = mt2[k][j];
					if (mt1[i][k] == "02")
					{
						temp = toBinary(mt2[k][j]);
						for (int i = 1; i < temp.length(); i++)
							temp2 += temp[i];
						temp2 += "0";
						t1 = toHex(temp2);
						if (temp[0] == '1')
							t1 = toHex(Xor_binaries(toBinary(t1), "00011011"));
					}
					if (mt1[i][k] == "03")
					{
						temp = toBinary(mt2[k][j]);

						for (int i = 1; i < temp.length(); i++)
							temp2 += temp[i];
						temp2 += "0";
						t1 = toHex(temp2);
						t1 = toHex(Xor_binaries(toBinary(t1), toBinary(mt2[k][j])));
						if (temp[0] == '1')
							t1 = toHex(Xor_binaries(toBinary(t1), "00011011"));
					}
					if (!mul[i][j].size())
						mul[i][j] = t1;
					else
						mul[i][j] = toHex(Xor_binaries(toBinary(t1), toBinary(mul[i][j])));
				}
			}
		}
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				muli[i][j] = mul[i][j];
		return muli;
	}
	//-----------------------------------------------------------------------------------------
	// 
	//-------------------------------------Encrypt---------------------------------------------
	void Encrypt(string key, string plaintext)
	{
		key = ASCIItoHEX(key);
		plaintext = ASCIItoHEX(plaintext);
		generate_round_keys(key);            //generating round keys AES-128(10), AES-256(16)
		printKeys();

		string** stateMatrix = AddRoundKey(plaintext, key);
		cout << "\n\n\n\n\t\t\t\t\tState Matrix    Round 0 \n\t\t\t\t\t";
		printMatrix(stateMatrix);


		string** fixedMat = new string * [4];
		for (int i = 0; i < 4; i++)
			fixedMat[i] = new string[4];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				fixedMat[i][j] = fixedMatrix[i][j];
		////-------------------------------------Round 1-------------------------------------------------
		string** ss = SubstituteBytes(stateMatrix);
		cout << "\n\n\n\n\t\t\t\t\tByte Sustituted Round 1 \n\t\t\t\t\t";
		printMatrix(ss);
		cout << "\n\n\n\n\t\t\t\t\tLeft Shifted    Round 1 \n\t\t\t\t\t";
		string** shiftedrows = ShiftRows(ss);
		printMatrix(shiftedrows);

		cout << "\n\n\n\n\t\t\t\t\tMixed Columns   Round 1 \n\t\t\t\t\t";
		printMatrix(mixColumns(fixedMat, shiftedrows));
		cout << "\n\n\n\n\t\t\t\t\tAdd Round Key   Round 1 \n\t\t\t\t\t";
		string** rk = AddRoundKey(twoDto1dCV(mixColumns(fixedMat, shiftedrows)), getKeys()[1]);
		printMatrix(rk);
		///--------------------------------------Round 2-------------------------------------------------
		int v = 0;
		if (getKeysize() == 256)
			v = 14;
		else
			v = 9;
		for (int i = 2; i <= v; i++)
		{
			cout << "\n\n\n\n\t\t\t\t\tByte Sustituted Round " << i << "\n\t\t\t\t\t";
			printMatrix(SubstituteBytes(rk));
			cout << "\n\n\n\n\t\t\t\t\tLeft Shifted    Round " << i << " \n\t\t\t\t\t";
			printMatrix(ShiftRows(SubstituteBytes(rk)));
			cout << "\n\n\n\n\t\t\t\t\tMixed Columns   Round " << i << " \n\t\t\t\t\t";
			printMatrix(mixColumns(fixedMat, ShiftRows(SubstituteBytes(rk))));
			cout << "\n\n\n\n\t\t\t\t\tAdd Round Key   Round " << i << " \n\t\t\t\t\t";
			rk = AddRoundKey(twoDto1dCV(mixColumns(fixedMat, ShiftRows(SubstituteBytes(rk)))), getKeys()[i]);
			printMatrix(rk);
		}
		cout << "\n\n\n\n\t\t\t\t\tByte Sustituted    Round last \n\t\t\t\t\t";
		printMatrix(SubstituteBytes(rk));
		cout << "\n\n\n\n\t\t\t\t\tLeft Shifted       Round last \n\t\t\t\t\t";
		printMatrix(ShiftRows(SubstituteBytes(rk)));
		cout << "\n\n\n\n\t\t\t\t\tAdd Round Key      Round last \n\t\t\t\t\t";
		rk = AddRoundKey(twoDto1dCV(ShiftRows(SubstituteBytes(rk))), getKeys()[10]);
		printMatrix(rk);
	}
};