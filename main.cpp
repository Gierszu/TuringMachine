#include "MainIncludes.h"
#include "DEFINITIONS.h"

int main() {
	NumberConverter convert;
	long long n;
	
	std::cout << "Wprowadz liczbe do konwersji do binarnych: ";
	std::cin >> n;
	std::vector<int> out1;
	long long out2, dec;
	
	out1 = convert.vd2b(n);
	out2 = convert.d2b(n);
	dec = convert.b2d(out2);
	
	std::cout << "\nPostac wektorowa: ";
	for (int i = 0; i < out1.size(); i++) {
		std::cout << out1[i];
	}
	std::cout << "\nPostac liczbowa: " << out2 << "\nPostac dziesietna, przekonwertowana: " << dec << "\n\n";
	
	return 0;
}