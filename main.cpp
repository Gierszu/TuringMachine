#include "MainIncludes.h"
#include "DEFINITIONS.h"

CGraphics graphic;
NumberConverter convert;
TuringMachine machine;

bool is_complete = 0;
bool is_working = 0;

int main() {
	

	while (graphic.window.isOpen())
	{	
		if (graphic.SEND && is_working == 0)
		{
			machine.Setup(graphic.FIRST_VALUE, graphic.SECOND_VALUE, graphic.OPERATION);
			graphic.SEND = 0;
			is_working = 1;
		}
		graphic.sync(machine.get_tape(), machine.get_pos(), machine.get_state()); //(pointer to tape's array, position(0-18),pointer's value)
		graphic.drawAll();
		if (is_working)
		{
			is_complete = machine.Step();
			Sleep(50);
			if (is_complete)
			{
				is_working = 0;
				graphic.resultText.setString(std::to_string(machine.result()));
				graphic.resultText.setCharacterSize(40);
			}
		}
		
		if (is_working == 0)
		{
			graphic.controls();
		}
	}
	return 0;


    //Test;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //   int costam[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  //  int* pointer = costam;
    
	

	/*

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

	bool is_complete = false;
	while (is_complete == false) {
		is_complete = machine.increment();
	}

	std::cout << "\nMain : Wykonano inkrementacje.";

	std::cout << "\nMain : Wynik inkrementacji metoda maszyny Turinga : " << machine.result() << "\n\n";

	*/
	

}