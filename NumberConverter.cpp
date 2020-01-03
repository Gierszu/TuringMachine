#include "NumberConverter.h"
#include "DEFINITIONS.h"


std::vector<int> NumberConverter::vd2b(int dec) {
	std::vector<int> bin;
	for (int i = 0; dec > 0; i++) {
		bin.push_back(dec % 2);
		dec = dec / 2;
	}
	std::reverse(bin.begin(), bin.end());
	return bin;
}

int NumberConverter::d2b(int dec) {
	int bin = 0, i = 0, r;
	while (dec != 0)
	{
		r = dec % 2;
		dec /= 2;
		bin += r * pow(10, i);
		i++;
	}
	return bin;
}

int NumberConverter::b2d(int bin)
{
	int dec = 0, i = 0, r;
	while (bin != 0)
	{
		r = bin % 10;
		bin /= 10;
		dec += r * pow(2, i);
		i++;
	}
	return dec;
};

