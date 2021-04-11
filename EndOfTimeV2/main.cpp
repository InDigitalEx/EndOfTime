#include <Windows.h>
#include <sstream>
#include <ctime>
#include <string>
#include "utility.h"


using namespace Utility;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
	using namespace std;

	// ������� �����
	time_t nowSeconds = time(NULL);
	tm now;
	localtime_s(&now, &nowSeconds);
	now.tm_min--;

	// ���� ��� �� ����, ����� ������ � ���� ����, ���� ���, �� � ���������...
	tm start = initTmStruct(1, 6, now.tm_mon < 5 ? now.tm_year : now.tm_year + 1);

	// ���� ��� �� ��������, ����� ����� � ���� ����, ���� ���, �� � ���������...
	tm end = initTmStruct(1, 9, now.tm_mon < 8 ? now.tm_year : now.tm_year + 1);

	stringstream ss;
	double diff;

	// �������� �� ������� ������ (���� �� ������, ��� ��� "END OF TIME" :("
	if (now.tm_mon >= 5 && now.tm_mon < 8) {
		ss << "�� ����� ���� ";
		diff = difftime(mktime(&end), mktime(&now));
	}
	else {
		ss << "�� ������ ���� ";
		diff = difftime(mktime(&start), mktime(&now));
	}

	// ������ ����������� ������� �� ����, �����, �������
	int total = static_cast<int>(diff);
	int days = total / 86400;
	int hours = (total % 86400) / 3600;
	int minutes = ((total % 86400) % 3600) / 60;

	// ����� (�������� �� ��������� ������ (��� ��������� ����� "��������"))
	if (days == 0 && hours == 0 && minutes != 0) {
		ss << "��������";
	}
	else {
		ss << getWordDeclension(days != 0 ? days : (hours != 0 ? hours : minutes),
			"�������", "��������", "��������");
	}
	
	ss << " ���";

	// ���������� ��������� ����, ����� � ����� 
	if (days != 0) {
		ss << ' ' << days << ' ' << getWordDeclension(days,
			"����", "���", "����");
	}
	if (hours != 0) {
		ss << ' ' << hours << ' ' << getWordDeclension(hours,
			"���", "����", "�����");
	}
	if (minutes != 0) {
		ss << ' ' << minutes << ' ' << getWordDeclension(minutes,
			"������", "������", "�����");
	}

	MessageBoxA(NULL, ss.str().c_str(), "����������", MB_OK | MB_ICONINFORMATION);
	return 0;
}