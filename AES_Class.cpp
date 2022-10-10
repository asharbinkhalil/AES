#include "AES_Class.h"
//--------------------------------------Getter Setters-------------------------------------
void AES_Class::setKeysize(int size)
{
	keysize = size;
}
int AES_Class::getKeysize()
{
	return keysize;
}
string* AES_Class::getKeys()
{
	return keys;
}
//--------------------------------------Utilities functions--------------------------------
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
	if (hexVal.length() == 1)
		hexVal = "0" + hexVal;
	
	//if (hexVal.length()== 3)
	//{
	//	hexVal = hexVal.substr(1, 2);
	//	hexVal = toHex(Xor_binaries(toBinary(hexVal), toBinary("1b")));
	//	cout << "|" << hexVal << "|\n";
	//}
	
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
	if (out.length() < 8)
		return "0000" + out;
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
void AES_Class::printMatrix(string** arr)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << arr[i][j] << " ";
		cout << "\n\t\t\t\t\t";
	}
}
int AES_Class::charHextoint(char c)
{
	int val = 0;
	if (c >= '0' && c <= '9')
		val = c - 48;
	if (c >= 'A' && c <= 'F')
		val = c - 55;
	else if (c >= 'a' && c <= 'f')
		val = c - 87;
	return val;
}
string AES_Class::twoDto1dCV(string** arr)
{
	string oned;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			oned += arr[j][i];
	return oned;
}

//-----------------------------------------------------------------------------------------

//--------------------------------------Input functions------------------------------------
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
		cout << "\t\t\t\t\tEnter Key : (atleast " << n << " ascii characters)\n\t\t\t\t\t";
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

//--------------------------------------Key Generation-------------------------------------
string AES_Class::substiteBytesW(string w_last)
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
string AES_Class::find_G(string w_last, int rc)
{
	reverse(w_last.begin(), w_last.begin() + 2);
	reverse(w_last.begin() + 2, w_last.end());
	reverse(w_last.begin(), w_last.end());

	string gw_last, byte_substituted;
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
	string round_constant[14] = { "01000000","02000000","04000000","08000000",
									"10000000","20000000","40000000","80000000",
									"1b000000","36000000","6c000000","d8000000",
									"AB000000","4d000000" };
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
void AES_Class::printKeys()
{
	int n = 0;
	if (keysize == 256)
		n = 15;
	else
		n = 11;
	for (int i = 0; i < n; i++)
		cout << "\n\t\t\t\tKey " << i << (i < 10 ? " : " : ": ") << keys[i];

}
void AES_Class::generate_round_keys(string key)
{
	int j = 0, count = 0;
	int rounds = 0, quads = 0, w_count = 0;
	if (keysize == 256)
		rounds = 14, quads = 7, w_count = 60;
	else
		rounds = 10, quads = 3, w_count = 44;
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
	string temp, temp2;
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
			if (i == 3 && keysize == 256)
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
			keys[i] = "";
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 4; j++, k++)
			keys[i] += w[k];
}
//-----------------------------------------------------------------------------------------

//-----------------------------------ADD Round Key---------------------------------
string** AES_Class::GenerateStateMatrix(string str)
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
string** AES_Class::AddRoundKey(string plaintext, string key)
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
			temp = toHex(Xor_binaries(toBinary(PTstateMat[i][j]), toBinary(KeystateMat[i][j])));
			if (temp.length() == 1)
				temp = '0' + temp;
			stateMat[i][j] = temp;
		}
	}
	return stateMat;
}

//----------------------------------------------------------------------------------------- 

//-------------------------------------Substitute Bytes------------------------------------
string** AES_Class::SubstituteBytes(string** arr)
{
	int val, val2;
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
void AES_Class::leftshift(string arr[], int size)
{
	string temp = arr[0];
	for (int i = 0; i < size - 1; i++)
		arr[i] = arr[i + 1];
	arr[size - 1] = temp;
}
void AES_Class::LeftShiftNtTime(string arr[], int size, int k)
{
	for (int i = 0; i < k; i++)
		leftshift(arr, size);
}
string** AES_Class::ShiftRows(string** D2)
{
	for (int i = 0; i < 4; i++)
		LeftShiftNtTime(D2[i], 4, i);
	return D2;
}
//-----------------------------------------------------------------------------------------

//-------------------------------------Mix Column------------------------------------------
string** AES_Class::mixColumns(string** mt1, string** mt2)
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
void AES_Class::Encrypt(string key, string plaintext)
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