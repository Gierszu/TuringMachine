#include "NumberConverter.hpp"
#include "DEFINITIONS.h"



/// W razie jakby pow() nie dzia³a³o jak chcemy.
double NumberConverter::power(int nr, int exp) {
	double out = 1;
	for (int i = 0; i < exp; i++) {
		out *= nr;
	}
	return out;
}

/// Przyjmuje liczbê decymaln¹ i zwraca wektor liczby w postaci binarnej.
std::vector<int> NumberConverter::vd2b(long long dec) {
	std::vector<int> bin;
	for (int i = 0; dec > 0; i++) {
		bin.push_back(dec % 2);
		dec /= 2;
	}
	std::reverse(bin.begin(), bin.end());
	return bin;
}


/// Przyjmuje liczbê decymaln¹ i zwraca liczbê w postaci binarnej.
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

/// Przyjmuje liczbê binarn¹ i zwraca liczbê w postaci decymalnej.
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

/// Przyjmuje wektor binarny i robi liczbê decymaln¹.
long long NumberConverter::b2d(std::vector<int> bin) {
	std::reverse(bin.begin(), bin.end());
	long long dec = 0;

	for (int i = 0; i < bin.size(); i++) {
		dec += bin[i] * pow(2, i);
	}
	return dec;
}

/// Przyjmuje dwie liczby decymalne i dzia³anie i robi z nich pointer do taœmy, sprawdzaj¹c, czy obie siê zmieszcz¹, oraz czy wynik dzia³ania siê zmieœci.
int* NumberConverter::give_tape(int tape[19], int dec_1, int dec_2, Operation op) {
	std::vector<int> bin_1 = vd2b(dec_1);
	std::vector<int> bin_2 = vd2b(dec_2);
	std::vector<int> bin_result;

	if (op == Operation::ADD) {
		bin_result = vd2b(dec_1 + dec_2);
	}
	else if (op == Operation::SUB) {
		bin_result = vd2b(dec_1 - dec_2);
	}
	else if (op == Operation::MUL) {
		bin_result = vd2b(dec_1 * dec_2);
	}
	else if (op == Operation::DIV) {
		bin_result = vd2b(dec_1 / dec_2);
	}
	else {
		std::cout << "Nie rozpoznano dzialania.";
		return tape;
	}

	if ((bin_1.size() + bin_2.size()) < 18 && bin_result.size() < 18) {
		for (int i = 0; i < 19; i++) {
			if (i < bin_1.size()) {
				tape[i] = bin_1[i];
			}
			else if (i == bin_1.size()) {
				tape[i] = EMPTY;
			}
			else if (i > bin_1.size() && i <= (bin_1.size() + bin_2.size())) {
				tape[i] = bin_2[i - 1 - bin_1.size()];
			}
			else if (i > (bin_1.size() + bin_2.size())) {
				tape[i] = EMPTY;
			}
		}
	}
	else {
		std::cout << "\nERROR - Podane liczby sa za duze do tasmy! Podaje pusta tasme.";
		return tape;
	}

	return tape;
}


// Testowe:

/// Przyjmuje dwie liczbê decymaln¹ i robi z niej pointer do taœmy, sprawdzaj¹c, czy siê zmieœci.
int* NumberConverter::give_tape(int tape[19],int dec) {
	std::vector<int> bin = vd2b(dec);

	if (bin.size() < 18) {
		for (int i = 0; i < 19; i++) {
			if (i < bin.size()) {
				tape[i] = bin[i];
			}
			else if (i >= bin.size()) {
				tape[i] = EMPTY;
			}
		}
	}
	else {
		std::cout << "\nERROR - Podana liczba jest za duza do tasmy! Podaje pusta tasme.";
		return tape;
	}
	return tape;
}