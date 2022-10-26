#include "AES.h"
//--------------------------------------Getter Setters-------------------------------------
void AES_Encrypt::setKeysize(int size)
{
	keysize = size;
}
int AES_Encrypt::getKeysize()
{
	return keysize;
}
string* AES_Encrypt::getKeys()
{
	return keys;
}
//--------------------------------------Utilities functions--------------------------------
string AES_Encrypt::ASCIItoHEX(string ascii)
{
	stringstream ss;
	string hexs;
	for (const auto& item : ascii)
		ss << hex << int(item);
	hexs = ss.str();
	return hexs;
}
string AES_Encrypt::hexToASCII(string hex)
{
	string ascii = "";
	for (size_t i = 0; i < hex.length(); i += 2)
	{
		string part = hex.substr(i, 2);
		char ch = stoul(part, nullptr, 16);
		ascii += ch;
	}
	return ascii;
}
string AES_Encrypt::toHex(string bin)
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
	return hexVal;
}
string AES_Encrypt::toBinary(const string& s) {
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
string AES_Encrypt::Xor_binaries(string bin1, string bin2)
{
	string output;
	for (int i = 0; i < bin1.length(); i++)
	{
		output += ((bin1[i] - 48) ^ (bin2[i] - 48)) + 48;
	}
	return output;
}

char AES_Encrypt::func()
{
	cout << "\t\t\t\t------------------- ASHAR KHALIL----------------------\n";
	cout << "\t\t\t\t-------------	      20K - 1724         --------------\n";
	cout << "\t\t\t\t--------------- Number Theory & Crypto ---------------\n";
	cout << "\t\t\t\t-------------    AES Implementation    ---------------\n\n\n";
	cout << "\t\t\t\t\t/--------------------------------------/";
	cout << "\n\t\t\t\t\t|    Copyrights: Poor_logics by Ashar  | ";
	cout << "\n\t\t\t\t\t| -> Loads data from a file.           |";
	cout << "\n\t\t\t\t\t| -> Generate Keys.                    |";
	cout << "\n\t\t\t\t\t| -> Show Visualization of Encryption  |";
	cout << "\n\t\t\t\t\t| -> Show Visualization of Decryption  |";
	cout << "\n\t\t\t\t\t| -> Change the file contents.  CT/PT  |";
	cout << "\n\t\t\t\t\t/--------------------------------------/\n";
	char choice='a';
	cout << "\n\t\t\t\tEnter you choice: E for Encryption D for Decryption\n\t\t\t\t";
	while (choice != 'E' && choice != 'D' && choice != 'B')
	{	
		cin >> choice;
		if (choice != 'E' && choice != 'D' && choice != 'B')
			cout << "\n\t\t\t\t\tPlease Enter Valid Choice: E for Encryption D for Decryption\n\t\t\t\t\t";
	}
	return choice;

}
void AES_Encrypt::printMatrix(string** arr)
{
	cout << "\n\t\t\t\t\t";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << arr[i][j]<<" ";
		cout << "\n\t\t\t\t\t";
	}
	cout << "\n";
	
}
int AES_Encrypt::charHextoint(char c)
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
string AES_Encrypt::twoDto1dCV(string** arr)
{
	string oned;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			oned += arr[j][i];
	return oned;
}
string AES_Encrypt::galois(int a, int b) {

	int p = 0;
	while (b) {
		if (b & 1) {
			p ^= a;
		}

		a <<= 1;
		if (a & 0x100)
			a ^= 0x1b;
		b >>= 1;
	}
	p = p & 0xff;
	std::ostringstream sso;
	sso << std::hex << p;
	return sso.str();
}

//-----------------------------------------------------------------------------------------

//--------------------------------------Input functions------------------------------------
string AES_Encrypt::keyInput()
{
	int ks = 0;
	cout << "\n\t\t\t\t\tEnter key Size:  (128 | 192 | 256)\n\t\t\t\t\t";
	cin >> ks;
	cin.ignore();
	setKeysize(ks);
	int n = 0;
	if (keysize == 256)
		n = 32;
	else if (keysize == 128)
		n = 16;
	else
		n = 24;

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
string  AES_Encrypt::textInput()
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
string AES_Encrypt::substiteBytesW(string w_last)
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
string AES_Encrypt::find_G(string w_last, int rc)
{
	rotate(w_last.begin(), w_last.begin() + 2,w_last.end());
	string gw_last, byte_substituted;
	for (int i = 0; i < w_last.length(); i += 2)
	{
		std::ostringstream sso;
		sso << std::hex << sbox[charHextoint(w_last[i])][charHextoint(w_last[i + 1])];
		string temp;
		if (sso.str().length() == 1)
			byte_substituted += "0" + sso.str();
		else
			byte_substituted += sso.str();
	}
	string round_constant[10] = { "01000000","02000000","04000000","08000000",
									"10000000","20000000","40000000","80000000",
									"1b000000","36000000"};
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
void AES_Encrypt::printKeys()
{
	int n = 0;
	if (keysize == 256)
		n = 15;
	else if (keysize == 128)
		n = 11;
	else
		n = 13;
	for (int i = 0; i < n; i++)
		cout << "\n\t\t\t\tKey " << i << (i < 10 ? " : " : ": ") << keys[i];
	cout << "\n";
}
void AES_Encrypt::generate_round_keys(string key)
{
	int j = 0, count = 0;
	int rounds = 0, quads = 0, w_count = 0;
	if (keysize == 256)
		rounds = 14, quads = 7, w_count = 60;
	else if (keysize == 128)
		rounds = 10, quads = 3, w_count = 44;
	else 
		rounds = 12, quads = 5, w_count = 52;

	int kl = 0;
	for (j = 0; j < (quads+1); j++, kl += 8)
		w[j] = key.substr(kl, 8);

	j--;
	int w_index = 0, r = 0, roundconst_c = 0, temp_length=0;
	count = 8;
	string temp, temp2;
	while (j++ < w_count)
	{
		cout << roundconst_c;
		w[j] = toHex(Xor_binaries(toBinary(find_G(w[j - 1], roundconst_c++)), toBinary(w[w_index++])));
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
	{
		keys[i] = "";
		for (int j = 0; j < 4; j++, k++)
				keys[i] += w[k];
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------ADD Round Key---------------------------------
string** AES_Encrypt::GenerateStateMatrix(string str)
{
	string** ptr = new string * [4];
	for (int i = 0; i < 4; i++)
		ptr[i] = new string[4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ptr[j][i] = str.substr(i * 8 + j * 2, 2);

	return ptr;
}
string** AES_Encrypt::AddRoundKey(string plaintext, string key)
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
string** AES_Encrypt::SubstituteBytes(string** arr,char c='e')
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
			if(c=='e')
			sso << std::hex << sbox[val][val2];
			else
			sso << std::hex << inv_sbox[val][val2];
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
void AES_Encrypt::leftshift(string arr[], int size)
{
	string temp = arr[0];
	for (int i = 0; i < size - 1; i++)
		arr[i] = arr[i + 1];
	arr[size - 1] = temp;
}
void AES_Encrypt::LeftShiftNtTime(string arr[], int size, int k)
{
	for (int i = 0; i < k; i++)
		leftshift(arr, size);
}
string** AES_Encrypt::ShiftRows(string** D2,char c)
{
	int n=0;
	if (c == 'd')
		n = 4;
	for (int i = 0; i < 4; i++)
		LeftShiftNtTime(D2[abs(n-i)], 4, i);
	return D2;
}
//-----------------------------------------------------------------------------------------

//-------------------------------------Mix Column------------------------------------------
string** AES_Encrypt::mixColumns(string mt1[4][4], string** mt2)
{
	string** muli = new string * [4];
	for (int i = 0; i < 4; i++)
		muli[i] = new string[4];
	string mul[4][4];
	string temp, temp2, t1;
	int tempo,tempo2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mul[i][j] = "";
			for (int k = 0; k < 4; k++)
			{
				t1 = "",temp2 = "";
				tempo = (16 * charHextoint(mt1[i][k][0])) + (1 * charHextoint(mt1[i][k][1]));
				tempo2= (16 * charHextoint(mt2[k][j][0])) + (1 * charHextoint(mt2[k][j][1]));
				t1 = galois(tempo, tempo2);
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


//-------------------------------------Encrypt---------------------------------------------
string AES_Encrypt::Encrypt(string key, string plaintext)
{
	key = ASCIItoHEX(key);
	plaintext = ASCIItoHEX(plaintext);
	//key =       "000102030405060708090a0b0c0d0e0f1011121314151617";
	//plaintext = "00112233445566778899aabbccddeeff";
	generate_round_keys(key);            //generating round keys AES-128(10), AES-256(16)
	printKeys();
	string** stateMatrix = AddRoundKey(plaintext, keys[0]);
	cout << "\n\t\t\t\t\tAdded round Key Round 0 \n";
	printMatrix(stateMatrix);
	int v = 0;
	if (getKeysize() == 256)
		v = 14;
	else if (getKeysize() == 128)
		v = 10;
	else
		v = 12;
	for (int i = 1; i <= v; i++)
	{
		stateMatrix = SubstituteBytes(stateMatrix);
		cout << "\n\t\t\t\t\tSusbstitute Bytes Round " << i <<"\n";
		printMatrix(stateMatrix);
		stateMatrix = ShiftRows(stateMatrix, 'e');
		cout << "\n\t\t\t\t\tShifted Rows      Round " << i << "\n";
		printMatrix(stateMatrix);
		if (i < v)
		{
			stateMatrix = mixColumns(fixedMatrix, stateMatrix);
			cout << "\n\t\t\t\t\tMixed Columns     Round " << i << "\n";
			printMatrix(stateMatrix);

		}
		stateMatrix = AddRoundKey(twoDto1dCV(stateMatrix), getKeys()[i]);
		cout << "\n\t\t\t\t\tAdded round key   Round " << i << "\n";
		printMatrix(stateMatrix);
	}
	string ciphertext="";
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ciphertext += stateMatrix[j][i];
	return ciphertext;
}
string AES_Encrypt::Decrypt(string cipher)
{
	string** c;
	int ks;
	if (getKeysize() == 256)
		 ks = 14;
	else if (getKeysize() == 128)
		 ks = 10;
	else
		 ks = 12;
	c = AddRoundKey(cipher, getKeys()[ks--]);
	cout << "\n\t\t\t\t\t\tInverse Added round key   Round 0\n";
	printMatrix(c);
	for (int i = ks; i >=0; i--)
	{
		c = ShiftRows(c, 'd');
		cout << "\n\t\t\t\t\tInverse Shifted Rows      Round " << i << "\n";
		printMatrix(c);
		c = SubstituteBytes(c, 'd');
		cout << "\n\t\t\t\t\tInverse Susbstitute Bytes Round " << i << "\n";
		printMatrix(c);
		c = AddRoundKey(twoDto1dCV(c),getKeys()[i]);
		cout << "\n\t\t\t\t\tInverse Added round key   Round " << i << "\n";
		printMatrix(c);
		if (i != 0)
		{
			c = mixColumns(fixedMatrixd, c);
			cout << "\n\t\t\t\t\tInverse Mixed Columns     Round " << i << "\n";
			printMatrix(c);
		}
	}
	string pt = twoDto1dCV(c);
	return pt;
}