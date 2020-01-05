#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "DEFINITIONS.h"

class NumberConverter {
public:
	double power(int nr, int exp);

	long long d2b(long long dec);
	long long b2d(long long bin);
	long long b2d(std::vector<int> bin);
	
	std::vector<int> vd2b(long long dec); 

	int* give_tape(int dec_1, int dec_2, Operation op);
	int* give_tape(int dec);
};

