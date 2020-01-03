#include "NumberConverter.h"
#include "DEFINITIONS.h"

double power(int nr, int exp) {
	double out = 1;
	for (int i = 0; i < exp; i++) {
		out *= nr;
	}
	return out;
}

std::vector<int> NumberConverter::vd2b(long long dec) {
	std::vector<int> bin;
	for (int i = 0; dec > 0; i++) {
		bin.push_back(dec % 2);
		dec /= 2;
	}
	std::reverse(bin.begin(), bin.end());
	return bin;
}

long long NumberConverter::d2b(long long dec) {
	int i = 0, r = 0;
	double bin = 0;
	while (dec != 0)
	{
		r = dec % 2;
		dec /= 2;
		bin += r * power(10, i);
		i++;
	}
	return bin;
}

long long NumberConverter::b2d(long long bin)
{
	int i = 0;
	double dec = 0, r = 0;
	while (bin != 0)
	{
		r = bin % 10;
		bin /= 10;
		dec += r * power(2, i);
		i++;
	}
	return dec;
};

