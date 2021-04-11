#pragma once
#include <string>
#include <ctime>

namespace Utility {

/// <summary>
/// ��������� ������������
/// </summary>
/// <param name="num">�������� �����</param>
/// <param name="word1">��������� ��� "1"</param>
/// <param name="word2">��������� ��� "2, 3, 4"</param>
/// <param name="word3">��������� ��� "5 ... 9"</param>
/// <returns>���������� ��������� (std::string)</returns>
std::string getWordDeclension(int num, std::string word1, std::string word2, std::string word3) {
	num %= 10;
	switch (num)
	{
	case 1: {
		return word1;
	}
	case 2:
	case 3:
	case 4: return word2;
	default: return word3;
	}
}

std::tm initTmStruct(unsigned int day, unsigned int month, unsigned int year) {
	std::tm tm_ret = { 0 };

	tm_ret.tm_mday = day;
	tm_ret.tm_mon = month - 1;
	tm_ret.tm_year = year;

	return tm_ret;
}

} // namespace Utility