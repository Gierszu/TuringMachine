#include "TuringMachine.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Dzia�anie												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// Inicjalizuje, b�d� resetuje maszyn�.
void TuringMachine::Init(int tape[19], Direction dir) {
	// Inicjalizowanie zmiennych:
	_pos = 0;
	_state = 0;
	_symbol = EMPTY;
	_dir = dir;

	// Czyszczenie ta�my:
	for (int i = 0; i < 18; i++) {
		_tape[i] = EMPTY;
	}

	// Przypisywanie nowej ta�my, zostawiaj�c jedno pole puste z przodu i z ty�u:
	for (int i = 1; i < 17; i++) {
		_tape[i] = tape[i-1];
	}

	// Ustawianie pocz�tkowej pozycji:
	if (_dir == Direction::LEFT) {
		for (int i = 18; i > 0; i--) {
			if (_tape[i] != 2 && _pos == 0) {
				_pos = i;
			}
		}
	}
	else {
		_pos = 1;
	}
}

/// Czyta symbol na swojej pozycji.
void TuringMachine::read() {
	_symbol = _tape[_pos];
}

/// Wykonuje jeden krok dzia�ania.
void TuringMachine::step(int new_symbol, int new_state, Direction dir) {
	_tape[_pos] = new_symbol;
	_state = new_state;
	_dir = dir;
	
	if (_dir == Direction::LEFT && _pos > 0) {
		_pos -= 1;
	}
	else if (_dir == Direction::LEFT && _pos < 18) {
		_pos += 1;
	}
}

/// Zwraca wynik w postaci decymalnej. Do u�ycia po wykonaniu ca�ego dzia�ania.
int TuringMachine::result() {
	NumberConverter convert;
	std::vector<int> vec;

	for (int i = 0; i < 19; i++) {
		if (_tape[i] != EMPTY) {
			vec.push_back(_tape[i]);
		}
	}

	return convert.b2d(vec);
}

/// Zwraca pointer do ta�my.
int* TuringMachine::get_tape() {
	return _tape;
}

/// Zwraca pozycj� g�owicy.
int TuringMachine::get_pos() {
	return _pos;
}

/// Zwraca stan maszyny.
int TuringMachine::get_state() {
	return _state;
}

/// Zwraca symbol do wy�wietlenia na g�owicy.
int TuringMachine::get_symbol() {
	return _symbol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Algorytmy												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Wykonuje binarn� inkrementacj� o 1. Zwraca TRUE przy zako�czonej pracy.
bool TuringMachine::increment() {
	read();
	std::cout << "\nPrzeczytano symbol.";

	switch (_state) {
	case 0:
		switch (_symbol) {
		case 0:
			step(1, 1, Direction::RIGHT);
			break;
		case 1:
			step(0, 0, Direction::LEFT);
			break;
		case EMPTY:
			step(1, 1, Direction::RIGHT);
			break;
		}
		break;
	case 1:
		switch (_symbol) {
		case 0:
			step(0, 1, Direction::RIGHT);
			break;
		case 1:
			step(1, 1, Direction::RIGHT);
			break;
		case EMPTY:
			step(EMPTY, 2, Direction::LEFT);
			break;
		}
		break;
	case 2:
		std::cout << "\nDokonano inkrementacji.";
		return true;
		break;
	}
	std::cout << "\nWykonano krok.";
	return false;
}

void TuringMachine::add() {

}

void TuringMachine::subtract() {

}

void TuringMachine::multiply() {

}

void TuringMachine::divide() {

}