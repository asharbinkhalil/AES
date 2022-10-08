#include "AES_Class.h"
string AES_Class::decToHexa(int n)
{
	char hexaDeciNum[100];
	int i = 0;
	while (n != 0) {
		int temp = 0;
		temp = n % 16;
		if (temp < 10) {
			hexaDeciNum[i] = temp + 48;
			i++;
		}
		else {
			hexaDeciNum[i] = temp + 55;
			i++;
		}
		n = n / 16;
	}
	string ans = "";
	for (int j = i - 1; j >= 0; j--)
		ans += hexaDeciNum[j];

	return ans;
}
string AES_Class::ASCIItoHEX(string ascii)
{
	string hex = "";
	for (int i = 0; i < ascii.length(); i++) {
		char ch = ascii[i];
		int tmp = (int)ch;
		string part = decToHexa(tmp);
		hex += part;
	}
	return hex;
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