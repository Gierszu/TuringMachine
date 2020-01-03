#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "DEFINITIONS.h"

class NumberConverter {
public:
	long long d2b(long long dec);			//  Przyjmuje liczbê decymaln¹ i zwraca liczbê w postaci binarnej
	long long b2d(long long bin);			//  Przyjmuje liczbê binarn¹ i zwraca liczbê w postaci decymalnej
	
	std::vector<int> vd2b(long long dec); //  Przyjmuje liczbê decymaln¹ i zwraca wektor liczby w postaci binarnej
};

