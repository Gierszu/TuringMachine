#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "DEFINITIONS.h"

class NumberConverter {
public:
	long long d2b(long long dec);			//  Przyjmuje liczb� decymaln� i zwraca liczb� w postaci binarnej
	long long b2d(long long bin);			//  Przyjmuje liczb� binarn� i zwraca liczb� w postaci decymalnej
	
	std::vector<int> vd2b(long long dec); //  Przyjmuje liczb� decymaln� i zwraca wektor liczby w postaci binarnej
};

