#pragma once

#include "DEFINITIONS.h"
#include "NumberConverter.hpp"


class TuringMachine {
public:
	// Pusty konstruktor i dekonstruktor:
	TuringMachine() {};
	~TuringMachine() {};

	// Inicjalizacja maszyny, nie przez konstruktor, �eby mo�na by�o u�ywa� jednej maszyny wiele razy:
	void Init(int tape[40], Direction dir);

	// Funkcja odbieraj�ca zmienne od u�ytkownika i przygotowuj�ca dzia�anie maszyny.
	void Setup(int dec_1, int dec_2, Operation op);
	void Setup(int dec, Operation op);

	// Robi kolejny krok oblicze�. Zwraca TRUE, gdy nie b�dzie ju� kroku do wykonania.
	bool Step();

	// Przesy�anie danych:
	int result();
	int* get_tape();
	int get_pos();
	int get_state();
	int get_symbol();

	// Testowe:
	bool increment();
private:

	// Funkcje maszyny:
	void read();
	void _step(int new_symbol, int new_state, Direction dir);

	// Dane maszyny:
	int _tape[40];
	int _pos;
	int _state;
	int _symbol;
	Direction _dir;

	Operation _op;

	// Dzia�ania:
	bool add();
	bool subtract();
	bool multiply();
	bool divide();

	// Testowe:
	void print();
	void state();
};

