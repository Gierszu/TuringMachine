#include "MainIncludes.h"
#include "DEFINITIONS.h"

int main() {

    //Test;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int costam[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int* pointer = costam;
    CGraphics graphic;
    while (graphic.window.isOpen())
    {
        
        graphic.drawAll();
        graphic.sync(pointer, 18, 0); //(pointer to tape's array, position(0-18),pointer's value)
        graphic.controls();

    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Test konwertera												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NumberConverter convert;

	long long n;
	
	std::cout << "Wprowadz liczbe do konwersji do binarnych oraz binarnej inkrementacji metoda maszyny Turinga: ";
	std::cin >> n;
	std::vector<int> vbin;
	long long bin, dec, dec_from_v;
	
	vbin = convert.vd2b(n);
	bin = convert.d2b(n);
	dec = convert.b2d(bin);
	dec_from_v = convert.b2d(vbin);
	
	std::cout << "\nKonwersja do postaci wektorowej: ";
	for (int i = 0; i < vbin.size(); i++) {
		std::cout << vbin[i];
	}

	int actual_tape[19];
	for (int i = 0; i < 19; i++) {
		actual_tape[i] = EMPTY;
	}

	int* tape = convert.give_tape(actual_tape, n);
	std::cout << "\nKonwersja do postaci tasmy: ";
	for (int i = 0; i < 19; i++) {
		std::cout << tape[i];
	}

	std::cout << "\nKonwersja do postaci liczbowej: " << bin << "\nDekonwersja do postaci dziesietnej: " << dec << "\nDekonwersja do postaci dziesietnej, z wektora binarnego: " << dec_from_v << "\n\n";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Test maszyny												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TuringMachine machine;
	std::cout << "\n\nMain : Maszyna stworzona.";
	machine.Init(tape, Direction::LEFT);
	std::cout << "\n\nMain : Maszyna zainicjalizowana.";
	
	int is_complete = 0;
	while (is_complete == 0) {
		is_complete = machine.increment();
	}

	std::cout << "\nMain : Wykonano inkrementacje.";

	std::cout << "\nMain : Wynik inkrementacji metoda maszyny Turinga : " << machine.result() << "\n\n";
	
	return 0;
}