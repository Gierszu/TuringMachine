#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "DEFINITIONS.h"

class NumberConverter {
public:
	int d2b(int dec);
	int b2d(int bin);
	
	std::vector<int> vd2b(int dec);
};

