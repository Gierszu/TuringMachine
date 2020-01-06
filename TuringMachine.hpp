#pragma once

#include "DEFINITIONS.h"
#include "NumberConverter.hpp"


class TuringMachine {
public:
	// Pusty konstruktor i dekonstruktor:
	TuringMachine() {};
	~TuringMachine() {};

	// Inicjalizacja maszyny, nie przez konstruktor, ¿eby mo¿na by³o u¿ywaæ jednej maszyny wiele razy:
	void Init(int tape[19], Direction dir);

	// Funkcja odbieraj¹ca zmienne od u¿ytkownika i przygotowuj¹ca dzia³anie maszyny.
	void Setup(int dec_1, int dec_2, Operation op);
	void Setup(int dec, Operation op);

	// Robi kolejny krok obliczeñ. Zwraca TRUE, gdy nie bêdzie ju¿ kroku do wykonania.
	bool Step();

	// Przesy³anie danych:
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
	int _tape[19];
	int _pos;
	int _state;
	int _symbol;
	Direction _dir;

	Operation _op;

	// Dzia³ania:
	bool add();
	bool subtract();
	bool multiply();
	bool divide();

	// Testowe:
	void print();
	void state();
};

