#include "MainIncludes.h"
#include "DEFINITIONS.h"

CGraphics graphic;
NumberConverter convert;
TuringMachine machine;

int main() {

	while (graphic.window.isOpen())
	{

		graphic.drawAll();
		graphic.sync(machine.get_tape(), machine.get_pos(), machine.get_state()); //(pointer to tape's array, position(0-18),pointer's value)
		if (graphic.SEND)
		{
			machine.Setup(graphic.FIRST_VALUE, graphic.OPERATION);
			graphic.SEND = 0;
		}
		if (machine.Step() == 0)
		{
			graphic.controls();
		}
	}
	return 0;






    //Test;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //   int costam[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  //  int* pointer = costam;
    
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////												Test konwertera												////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	/*
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

	std::cout << "\n\nMain : Maszyna stworzona.";
	machine.Init(tape, Direction::LEFT);
	std::cout << "\n\nMain : Maszyna zainicjalizowana.";

	int is_complete = 0;
	while (is_complete == 0) {
		is_complete = machine.increment();
	}

	std::cout << "\nMain : Wykonano inkrementacje.";

	std::cout << "\nMain : Wynik inkrementacji metoda maszyny Turinga : " << machine.result() << "\n\n";
	*/

	

}