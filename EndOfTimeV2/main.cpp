#include <Windows.h>
#include <sstream>
#include <ctime>
#include <string>
#include "utility.h"


using namespace Utility;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
	using namespace std;

	// Текущее время
	time_t nowSeconds = time(NULL);
	tm now;
	localtime_s(&now, &nowSeconds);
	now.tm_min--;

	// Если еще не июнь, тогда начало в этом году, если уже, то в следующем...
	tm start = initTmStruct(1, 6, now.tm_mon < 5 ? now.tm_year : now.tm_year + 1);

	// Если еще не сентябрь, тогда конец в этом году, если уже, то в следующем...
	tm end = initTmStruct(1, 9, now.tm_mon < 8 ? now.tm_year : now.tm_year + 1);

	stringstream ss;
	double diff;

	// Проверка на текущий период (Лето ли сейчас, или уже "END OF TIME" :("
	if (now.tm_mon >= 5 && now.tm_mon < 8) {
		ss << "До конца лета ";
		diff = difftime(mktime(&end), mktime(&now));
	}
	else {
		ss << "До начала лета ";
		diff = difftime(mktime(&start), mktime(&now));
	}

	// Расчет оставшегося времени по дням, часам, минутам
	int total = static_cast<int>(diff);
	int days = total / 86400;
	int hours = (total % 86400) / 3600;
	int minutes = ((total % 86400) % 3600) / 60;

	// Вывод (Проверка на последнюю минуту (для склонения слова "осталось"))
	if (days == 0 && hours == 0 && minutes != 0) {
		ss << "осталась";
	}
	else {
		ss << getWordDeclension(days != 0 ? days : (hours != 0 ? hours : minutes),
			"остался", "осталось", "осталось");
	}
	
	ss << " ещё";

	// Нахождение склонения дней, часов и минут 
	if (days != 0) {
		ss << ' ' << days << ' ' << getWordDeclension(days,
			"день", "дня", "дней");
	}
	if (hours != 0) {
		ss << ' ' << hours << ' ' << getWordDeclension(hours,
			"час", "часа", "часов");
	}
	if (minutes != 0) {
		ss << ' ' << minutes << ' ' << getWordDeclension(minutes,
			"минута", "минуты", "минут");
	}

	MessageBoxA(NULL, ss.str().c_str(), "Информация", MB_OK | MB_ICONINFORMATION);
	return 0;
}