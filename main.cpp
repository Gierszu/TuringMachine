#include "MainIncludes.h"
#include "DEFINITIONS.h"

int main() {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Test konwertera												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NumberConverter convert;

	long long n;
	
	std::cout << "Wprowadz liczbe do konwersji do binarnych: ";
	std::cin >> n;
	std::vector<int> vbin;
	long long bin, dec, dec_from_v;
	
	vbin = convert.vd2b(n);
	bin = convert.d2b(n);
	dec = convert.b2d(bin);
	dec_from_v = convert.b2d(vbin);
	
	std::cout << "\nPostac wektorowa: ";
	for (int i = 0; i < vbin.size(); i++) {
		std::cout << vbin[i];
	}

	int* tape = convert.give_tape(n);
	std::cout << "\nPostac tasmy: ";
	for (int i = 0; i < 19; i++) {
		std::cout << tape[i];
	}

	std::cout << "\nPostac liczbowa: " << bin << "\nPostac dziesietna, przekonwertowana: " << dec << "\nPostac dziesietna, z wektora : " << dec_from_v << "\n\n";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Test maszyny												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	TuringMachine machine;
	std::cout << "\nMaszyna stworzona.";
	machine.Init(vbin, Direction::LEFT);
	std::cout << "\nMaszyna zainicjalizowana.";
	machine.increment();
	std::cout << "\nWykonano inkrementacjê.";

	std::cout << "Wynik inkrementacji metod¹ maszyny Turinga : " << machine.result() << "\n\n";
	*/
	
	return 0;
}