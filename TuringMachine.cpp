#include "TuringMachine.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Dzia³anie												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// Inicjalizuje, b¹dŸ resetuje maszynê.
void TuringMachine::Init(int tape[40], Direction dir) {
	std::cout << "\n\nMasszyna Turinga utworzona. Inicjalizowanie zmiennych...";
	
	// Inicjalizowanie zmiennych:
	_pos = 0;
	_state = 0;
	_symbol = EMPTY;
	_dir = dir;

	std::cout << "\nZmienne zainicjalizowane. Czyszczenie tasmy...";

	// Czyszczenie taœmy:
	for (int i = 0; i < 40; i++) {
		_tape[i] = EMPTY;
	}

	state();

	std::cout << "\nTasma wyczyszczona. Przygotowywanie tasmy pod obliczenia...";

	// Przypisywanie nowej taœmy, zostawiaj¹c szesnascie pol pustych z przodu:
	for (int i = 20; i < 40; i++) {
		_tape[i] = tape[i-20];
	}

	state();

	std::cout << "\nTasma przygotowana. Ustawianie poczatkowej pozycji...";

	// Ustawianie pocz¹tkowej pozycji:
	if (_dir == Direction::LEFT) {
		for (int i = 39; i > 0; i--) {
			if (_tape[i] != EMPTY && _pos == 0) {
				_pos = i;
				state();
			}
		}
	}
	else {
		_pos = 20;
		state();
	}

	std::cout << "\nPoczatkowa pozycja ustalona : " << _pos << "\nMaszyna zainicjalizowana.\n";
}

/// Zbiera dane od u¿ytkownika i na ich podstawie przygotowuje maszynê do pracy.
void TuringMachine::Setup(int dec_1, int dec_2, Operation op) {
	_op = op;
	
	NumberConverter convert;
	int actual_tape[40];
	int* tape;
	tape = convert.give_tape(actual_tape, dec_1, dec_2, op);

	switch (_op) {
	case Operation::ADD:
		Init(tape, Direction::LEFT);
		break;
	case Operation::SUB:
		Init(tape, Direction::LEFT);
		break;
	case Operation::MUL:
		Init(tape, Direction::LEFT);
		break;
	case Operation::DIV:
		Init(tape, Direction::RIGHT);
		break;
	default:
		std::cout << "\n\nERROR - Nie rozpoznano operacji! Nie uda³o sie ustawic maszyny.\n\n";
		return;
		break;
	}
}

void TuringMachine::Setup(int dec, Operation op) {
	_op = op;

	NumberConverter convert;
	int actual_tape[40];
	int* tape;
	tape = convert.give_tape(actual_tape, dec);

	switch (_op) {
	case Operation::INC:
		Init(tape, Direction::LEFT);
		break;
	default:
		std::cout << "\n\nERROR - Nie rozpoznano operacji! Nie uda³o siê ustawiæ maszyny.\n\n";
		return;
		break;
	}
}

bool TuringMachine::Step() {
	switch (_op) {
	case Operation::ADD:
		return add();
		break;
	case Operation::SUB:
		return subtract();
		break;
	case Operation::MUL:
		return multiply();
		break;
	case Operation::DIV:
		return divide();
		break;
	case Operation::INC:
		return increment();
		break;
	default:
		std::cout << "\n\nERROR - Nie rozpoznano operacji! Nie uda³o siê wykonaæ kroku.\n\n";
		return true;
		break;
	}

	std::cout << "ERROR - Wyszed³em poza switcha w Step()!";
	return true;
}

/// Czyta symbol na swojej pozycji.
void TuringMachine::read() {
	_symbol = _tape[_pos];
}

/// Wykonuje jeden krok dzia³ania.
void TuringMachine::_step(int new_symbol, int new_state, Direction dir) {
	_tape[_pos] = new_symbol;
	_state = new_state;
	_dir = dir;
	
	if (_dir == Direction::LEFT && _pos > 0) {
		_pos -= 1;
	}
	else if (_dir == Direction::RIGHT && _pos < 39) {
		_pos += 1;
	}
	else {

	}
}

/// Zwraca wynik w postaci decymalnej. Do u¿ycia po wykonaniu ca³ego dzia³ania.
int TuringMachine::result() {
	NumberConverter convert;
	std::vector<int> vec;

	for (int i = 0; i < 40; i++) {
		if (_tape[i] != EMPTY) {
			vec.push_back(_tape[i]);
		}
	}

	return convert.b2d(vec);
}

/// Zwraca pointer do taœmy.
int* TuringMachine::get_tape() {
	return _tape;
}

/// Zwraca pozycjê g³owicy.
int TuringMachine::get_pos() {
	return _pos;
}

/// Zwraca stan maszyny.
int TuringMachine::get_state() {
	return _state;
}

/// Zwraca symbol do wyœwietlenia na g³owicy.
int TuringMachine::get_symbol() {
	return _symbol;
}

/// Wyœwietla zawartoœæ taœmy.
void TuringMachine::print() {
	std::cout << "\n|";
	for (int i = 0; i < 40; i++) {
		std::cout << _tape[i] << "|";
	}
	std::cout << "\n";
}

/// Wyœwietla status maszyny.
void TuringMachine::state() {
	std::cout << "\n\nStan : " << _state << "\nSymbol : " << _symbol << "\nPozycja : " << _pos;
	print();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Algorytmy												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Wykonuje binarn¹ inkrementacjê o 1. Zwraca TRUE przy zakoñczonej pracy.
bool TuringMachine::increment() {
	state();
	read();
	std::cout << "\nPrzeczytano symbol.";
	state();

	switch (_state) {
	case 0:
		switch (_symbol) {
		case 0:
			_step(1, 1, Direction::RIGHT);
			state();
			break;
		case 1:
			_step(0, 0, Direction::LEFT);
			state();
			break;
		case EMPTY:
			_step(1, 1, Direction::RIGHT);
			state();
			break;
		default:
			std::cout << "ERROR - Nierozpoznany symbol. Konczenie programu.";
			return true;
			break;
		}
		break;
	case 1:
		switch (_symbol) {
		case 0:
			_step(0, 1, Direction::RIGHT);
			state();
			break;
		case 1:
			_step(1, 1, Direction::RIGHT);
			state();
			break;
		case EMPTY:
			_step(EMPTY, 2, Direction::LEFT);
			state();
			break;
		default:
			std::cout << "ERROR - Nierozpoznany symbol. Konczenie programu.";
			return true;
			break;
		}
		break;
	case 2:
		std::cout << "\nDokonano inkrementacji.";
		state();
		return true;
		break;
	default:
		std::cout << "ERROR - Nierozpoznany stan.";
		return true;
		break;
	}
	std::cout << "\nWykonano krok. Stan tasmy : ";

	state();
	return false;
}

bool TuringMachine::add() {
	state();
	read();
	std::cout << "\nPrzeczytano symbol.";
	state();

	switch (_state) {
	case 0:
		switch (_symbol) {
		case 0:
			_step(EMPTY, 6, Direction::LEFT);
			break;
		case 1:
			_step(EMPTY, 1, Direction::LEFT);
			break;
		case EMPTY:
			_step(EMPTY, 10, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 1:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 2, Direction::LEFT);
			break;
		case 0:
			_step(0, 1, Direction::LEFT);
			break;
		case 1:
			_step(1, 1, Direction::LEFT);
			break;
		case 2:
			_step(2, 1, Direction::LEFT);
			break;
		case 3:
			_step(3, 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 2:
		switch (_symbol) {
		case EMPTY:
			_step(3, 4, Direction::RIGHT);
			break;
		case 0:
			_step(3, 4, Direction::RIGHT);
			break;
		case 1:
			_step(2, 3, Direction::LEFT);
			break;
		case 2:
			_step(2, 2, Direction::LEFT);
			break;
		case 3:
			_step(3, 2, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 3:
		switch (_symbol) {
		case EMPTY:
			_step(1, 4, Direction::RIGHT);
			break;
		case 0:
			_step(1, 4, Direction::RIGHT);
			break;
		case 1:
			_step(0, 3, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 4:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 5, Direction::RIGHT);
			break;
		case 0:
			_step(0, 4, Direction::RIGHT);
			break;
		case 1:
			_step(1, 4, Direction::RIGHT);
			break;
		case 2:
			_step(2, 4, Direction::RIGHT);
			break;
		case 3:
			_step(3, 4, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 5:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 0, Direction::LEFT);
			break;
		case 0:
			_step(0, 5, Direction::RIGHT);
			break;
		case 1:
			_step(1, 5, Direction::RIGHT);
			break;
		case 2:
			_step(2, 5, Direction::RIGHT);
			break;
		case 3:
			_step(3, 5, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 6:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 7, Direction::LEFT);
			break;
		case 0:
			_step(0, 6, Direction::LEFT);
			break;
		case 1:
			_step(1, 6, Direction::LEFT);
			break;
		case 2:
			_step(2, 6, Direction::LEFT);
			break;
		case 3:
			_step(3, 6, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 7:
		switch (_symbol) {
		case EMPTY:
			_step(2, 4, Direction::RIGHT);
			break;
		case 0:
			_step(2, 4, Direction::RIGHT);
			break;
		case 1:
			_step(3, 4, Direction::RIGHT);
			break;
		case 2:
			_step(2, 7, Direction::LEFT);
			break;
		case 3:
			_step(3, 7, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 10:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 11, Direction::RIGHT);
			break;
		case 0:
			_step(0, 11, Direction::RIGHT);
			break;
		case 1:
			_step(1, 11, Direction::RIGHT);
			break;
		case 2:
			_step(0, 10, Direction::LEFT);
			break;
		case 3:
			_step(1, 10, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 11:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 99, Direction::LEFT);
			break;
		case 0:
			_step(0, 11, Direction::RIGHT);
			break;
		case 1:
			_step(1, 11, Direction::RIGHT);
			break;
		case 2:
			_step(2, 11, Direction::RIGHT);
			break;
		case 3:
			_step(3, 11, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 99:
		std::cout << "\nDodawanie zakonczone.";
		return true;
		break;
	default:
		std::cout << "ERROR - Nierozpoznany stan.";
		return true;
		break;
	}
	return false;
}

bool TuringMachine::subtract() {
	state();
	read();
	std::cout << "\nPrzeczytano symbol.";
	state();

	switch (_state / 10)
	{
	case 0:
		switch (_state % 10)
		{
		case 0:
			if (_symbol == 1)
			{
				_step(0, 11, Direction::LEFT);
			}
			else
			{
				_step(_symbol, 2, Direction::LEFT);
			}
			break;

		default:
			if (_symbol == 1) _step(0, _state + 10, Direction::LEFT);
			else if (_symbol == EMPTY) _step(_symbol, 70, Direction::LEFT);
			else _step(_symbol, _state + 1, Direction::LEFT);
			break;
		}
		break;
	case 1:
		if (_symbol == EMPTY) _step(_symbol, _state + 9, Direction::LEFT);
		else _step(_symbol, _state, Direction::LEFT);
		break;
	case 2:
		if (_state % 10 == 0)
		{
			if (_symbol == 1) _step(0, 30, Direction::RIGHT);
			else _step(_symbol, 51, Direction::LEFT);
		}
		else _step(_symbol, _state - 1, Direction::LEFT);
		break;
	case 3:
		if (_symbol == EMPTY) _step(_symbol, 40, Direction::RIGHT);
		else _step(_symbol, _state, Direction::RIGHT);
		break;
	case 4:
		if (_symbol == EMPTY) _step(_symbol, 1, Direction::LEFT);
		else _step(_symbol, _state, Direction::RIGHT);
		break;
	case 5:
		if (_symbol == 1)_step(0, _state + 9, Direction::RIGHT);
		else _step(_symbol, _state + 1, Direction::LEFT);
		break;
	case 6:
		if (_state % 10 == 0)_step(1, 30, Direction::RIGHT);
		else _step(1, _state - 1, Direction::RIGHT);
		break;
	case 7:
		if (_symbol == EMPTY) _step(_symbol, 80, Direction::RIGHT);
		else _step(_symbol, _state, Direction::LEFT);
		break;
	case 8:
		if (_symbol == 0) _step(EMPTY, _state, Direction::RIGHT);
		else if (_symbol == EMPTY)_step(_symbol, 120, Direction::LEFT);
		else _step(_symbol, 90, Direction::RIGHT);
		break;
	case 9:
		if (_symbol == EMPTY) _step(_symbol, 100, Direction::RIGHT);
		else _step(_symbol, _state, Direction::RIGHT);
		break;
	case 10:
		if (_symbol == EMPTY) _step(_symbol, 110, Direction::LEFT);
		else _step(EMPTY, _state, Direction::RIGHT);
		break;
	case 11:
		if (_symbol != EMPTY) return true;
		else _step(_symbol, _state, Direction::LEFT);
		break;
	case 12:
		_step(0, 90, Direction::RIGHT);
		break;
	}
	return false;
}

bool TuringMachine::multiply() {
	state();
	read();
	std::cout << "\nPrzeczytano symbol.";
	state();

	switch (_state) {
	case 0:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 1, Direction::LEFT);
			break;
		case 0:
			_step(EMPTY, 10, Direction::LEFT);
			break;
		case 1:
			_step(EMPTY, 20, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 1:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 2, Direction::LEFT);
			break;
		case 0:
			_step(EMPTY, 1, Direction::LEFT);
			break;
		case 1:
			_step(EMPTY, 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 2:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 3, Direction::RIGHT);
			break;
		case 0:
			_step(0, 3, Direction::RIGHT);
			break;
		case 1:
			_step(1, 3, Direction::RIGHT);
			break;
		case 4:
			_step(1, 2, Direction::LEFT);
			break;
		case 5:
			_step(0, 2, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 3:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 99, Direction::LEFT);
			break;
		case 0:
			_step(0, 3, Direction::RIGHT);
			break;
		case 1:
			_step(1, 3, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 10:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 11, Direction::LEFT);
			break;
		case 0:
			_step(0, 10, Direction::LEFT);
			break;
		case 1:
			_step(1, 10, Direction::LEFT);
			break;
		case 2:
			_step(2, 10, Direction::LEFT);
			break;
		case 3:
			_step(3, 10, Direction::LEFT);
			break;
		case 4:
			_step(4, 10, Direction::LEFT);
			break;
		case 5:
			_step(5, 10, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 11:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 12, Direction::LEFT);
			break;
		case 0:
			_step(0, 11, Direction::LEFT);
			break;
		case 1:
			_step(1, 11, Direction::LEFT);
			break;
		case 2:
			_step(2, 11, Direction::LEFT);
			break;
		case 3:
			_step(3, 11, Direction::LEFT);
			break;
		case 4:
			_step(4, 11, Direction::LEFT);
			break;
		case 5:
			_step(5, 11, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 12:
		switch (_symbol) {
		case EMPTY:
			_step(5, 15, Direction::RIGHT);
			break;
		case 0:
			_step(5, 15, Direction::RIGHT);
			break;
		case 1:
			_step(4, 15, Direction::RIGHT);
			break;
		case 4:
			_step(4, 12, Direction::LEFT);
			break;
		case 5:
			_step(5, 12, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 15:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 16, Direction::RIGHT);
			break;
		case 0:
			_step(0, 15, Direction::RIGHT);
			break;
		case 1:
			_step(1, 15, Direction::RIGHT);
			break;
		case 2:
			_step(2, 15, Direction::RIGHT);
			break;
		case 3:
			_step(3, 15, Direction::RIGHT);
			break;
		case 4:
			_step(4, 15, Direction::RIGHT);
			break;
		case 5:
			_step(5, 15, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 16:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 17, Direction::RIGHT);
			break;
		case 0:
			_step(0, 16, Direction::RIGHT);
			break;
		case 1:
			_step(1, 16, Direction::RIGHT);
			break;
		case 2:
			_step(2, 16, Direction::RIGHT);
			break;
		case 3:
			_step(3, 16, Direction::RIGHT);
			break;
		case 4:
			_step(4, 16, Direction::RIGHT);
			break;
		case 5:
			_step(5, 16, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 17:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 0, Direction::LEFT);
			break;
		case 0:
			_step(0, 17, Direction::RIGHT);
			break;
		case 1:
			_step(1, 17, Direction::RIGHT);
			break;
		case 2:
			_step(2, 17, Direction::RIGHT);
			break;
		case 3:
			_step(3, 17, Direction::RIGHT);
			break;
		case 4:
			_step(4, 17, Direction::RIGHT);
			break;
		case 5:
			_step(5, 17, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 20:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 21, Direction::LEFT);
			break;
		case 0:
			_step(0, 20, Direction::LEFT);
			break;
		case 1:
			_step(1, 20, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 21:
		switch (_symbol) {
		case 0:
			_step(2, 22, Direction::LEFT);
			break;
		case 1:
			_step(3, 26, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 22:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 23, Direction::LEFT);
			break;
		case 0:
			_step(0, 22, Direction::LEFT);
			break;
		case 1:
			_step(1, 22, Direction::LEFT);
			break;
		case 2:
			_step(2, 22, Direction::LEFT);
			break;
		case 3:
			_step(3, 22, Direction::LEFT);
			break;
		case 4:
			_step(4, 22, Direction::LEFT);
			break;
		case 5:
			_step(5, 22, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 23:
		switch (_symbol) {
		case EMPTY:
			_step(5, 24, Direction::RIGHT);
			break;
		case 0:
			_step(5, 24, Direction::RIGHT);
			break;
		case 1:
			_step(4, 24, Direction::RIGHT);
			break;
		case 2:
			_step(2, 23, Direction::LEFT);
			break;
		case 3:
			_step(3, 23, Direction::LEFT);
			break;
		case 4:
			_step(4, 23, Direction::LEFT);
			break;
		case 5:
			_step(5, 23, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 24:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 25, Direction::RIGHT);
			break;
		case 0:
			_step(0, 24, Direction::RIGHT);
			break;
		case 1:
			_step(1, 24, Direction::RIGHT);
			break;
		case 2:
			_step(2, 24, Direction::RIGHT);
			break;
		case 3:
			_step(3, 24, Direction::RIGHT);
			break;
		case 4:
			_step(4, 24, Direction::RIGHT);
			break;
		case 5:
			_step(5, 24, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 25:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 25, Direction::RIGHT);
			break;
		case 0:
			_step(0, 25, Direction::RIGHT);
			break;
		case 1:
			_step(1, 25, Direction::RIGHT);
			break;
		case 2:
			_step(2, 30, Direction::LEFT);
			break;
		case 3:
			_step(3, 30, Direction::LEFT);
			break;
		case 4:
			_step(4, 25, Direction::RIGHT);
			break;
		case 5:
			_step(5, 25, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 26:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 27, Direction::LEFT);
			break;
		case 0:
			_step(0, 26, Direction::LEFT);
			break;
		case 1:
			_step(1, 26, Direction::LEFT);
			break;
		case 2:
			_step(2, 26, Direction::LEFT);
			break;
		case 3:
			_step(3, 26, Direction::LEFT);
			break;
		case 4:
			_step(4, 26, Direction::LEFT);
			break;
		case 5:
			_step(5, 26, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 27:
		switch (_symbol) {
		case EMPTY:
			_step(4, 24, Direction::RIGHT);
			break;
		case 0:
			_step(4, 24, Direction::RIGHT);
			break;
		case 1:
			_step(5, 28, Direction::LEFT);
			break;
		case 2:
			_step(2, 27, Direction::LEFT);
			break;
		case 3:
			_step(3, 27, Direction::LEFT);
			break;
		case 4:
			_step(4, 27, Direction::LEFT);
			break;
		case 5:
			_step(5, 27, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 28:
		switch (_symbol) {
		case EMPTY:
			_step(1, 24, Direction::RIGHT);
			break;
		case 0:
			_step(1, 24, Direction::RIGHT);
			break;
		case 1:
			_step(0, 28, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 30:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 40, Direction::LEFT);
			break;
		case 0:
			_step(2, 31, Direction::LEFT);
			break;
		case 1:
			_step(3, 35, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 31:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 32, Direction::LEFT);
			break;
		case 0:
			_step(0, 31, Direction::LEFT);
			break;
		case 1:
			_step(1, 31, Direction::LEFT);
			break;
		case 2:
			_step(2, 31, Direction::LEFT);
			break;
		case 3:
			_step(3, 31, Direction::LEFT);
			break;
		case 4:
			_step(4, 31, Direction::LEFT);
			break;
		case 5:
			_step(5, 31, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 32:
		switch (_symbol) {
		case EMPTY:
			_step(2, 33, Direction::RIGHT);
			break;
		case 0:
			_step(2, 33, Direction::RIGHT);
			break;
		case 1:
			_step(3, 33, Direction::RIGHT);
			break;
		case 2:
			_step(2, 32, Direction::LEFT);
			break;
		case 3:
			_step(3, 32, Direction::LEFT);
			break;
		case 4:
			_step(4, 32, Direction::LEFT);
			break;
		case 5:
			_step(5, 32, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 33:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 34, Direction::RIGHT);
			break;
		case 0:
			_step(0, 33, Direction::RIGHT);
			break;
		case 1:
			_step(1, 33, Direction::RIGHT);
			break;
		case 2:
			_step(2, 33, Direction::RIGHT);
			break;
		case 3:
			_step(3, 33, Direction::RIGHT);
			break;
		case 4:
			_step(4, 33, Direction::RIGHT);
			break;
		case 5:
			_step(5, 33, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 34:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 34, Direction::RIGHT);
			break;
		case 0:
			_step(0, 34, Direction::RIGHT);
			break;
		case 1:
			_step(1, 34, Direction::RIGHT);
			break;
		case 2:
			_step(2, 30, Direction::LEFT);
			break;
		case 3:
			_step(3, 30, Direction::LEFT);
			break;
		case 4:
			_step(4, 34, Direction::RIGHT);
			break;
		case 5:
			_step(5, 34, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 35:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 36, Direction::LEFT);
			break;
		case 0:
			_step(0, 35, Direction::LEFT);
			break;
		case 1:
			_step(1, 35, Direction::LEFT);
			break;
		case 2:
			_step(2, 35, Direction::LEFT);
			break;
		case 3:
			_step(3, 35, Direction::LEFT);
			break;
		case 4:
			_step(4, 35, Direction::LEFT);
			break;
		case 5:
			_step(5, 35, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 36:
		switch (_symbol) {
		case EMPTY:
			_step(3, 33, Direction::RIGHT);
			break;
		case 0:
			_step(3, 33, Direction::RIGHT);
			break;
		case 1:
			_step(2, 37, Direction::LEFT);
			break;
		case 2:
			_step(2, 36, Direction::LEFT);
			break;
		case 3:
			_step(3, 36, Direction::LEFT);
			break;
		case 4:
			_step(4, 36, Direction::LEFT);
			break;
		case 5:
			_step(5, 36, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 37:
		switch (_symbol) {
		case EMPTY:
			_step(1, 33, Direction::RIGHT);
			break;
		case 0:
			_step(1, 33, Direction::RIGHT);
			break;
		case 1:
			_step(0, 37, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 40:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 41, Direction::RIGHT);
			break;
		case 0:
			_step(0, 40, Direction::LEFT);
			break;
		case 1:
			_step(1, 40, Direction::LEFT);
			break;
		case 2:
			_step(2, 40, Direction::LEFT);
			break;
		case 3:
			_step(3, 40, Direction::LEFT);
			break;
		case 4:
			_step(4, 40, Direction::LEFT);
			break;
		case 5:
			_step(5, 40, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 41:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 42, Direction::RIGHT);
			break;
		case 0:
			_step(0, 41, Direction::RIGHT);
			break;
		case 1:
			_step(1, 41, Direction::RIGHT);
			break;
		case 2:
			_step(0, 41, Direction::RIGHT);
			break;
		case 3:
			_step(1, 41, Direction::RIGHT);
			break;
		case 4:
			_step(4, 41, Direction::RIGHT);
			break;
		case 5:
			_step(5, 41, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 42:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 43, Direction::RIGHT);
			break;
		case 0:
			_step(0, 42, Direction::RIGHT);
			break;
		case 1:
			_step(1, 42, Direction::RIGHT);
			break;
		case 2:
			_step(0, 42, Direction::RIGHT);
			break;
		case 3:
			_step(1, 42, Direction::RIGHT);
			break;
		case 4:
			_step(4, 42, Direction::RIGHT);
			break;
		case 5:
			_step(5, 42, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 43:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 0, Direction::LEFT);
			break;
		case 0:
			_step(0, 43, Direction::RIGHT);
			break;
		case 1:
			_step(1, 43, Direction::RIGHT);
			break;
		case 2:
			_step(2, 43, Direction::RIGHT);
			break;
		case 3:
			_step(3, 43, Direction::RIGHT);
			break;
		case 4:
			_step(4, 43, Direction::RIGHT);
			break;
		case 5:
			_step(5, 43, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 99:
		std::cout << "\n\nMnozenie wykonano pomyslnie. Konczenie programu.";
		return true;
		break;
	default:
		std::cout << "\n\nERROR - Nierozpoznany stan." << _state << "Konczenie programu.";
		state();
		return true;
		break;
	}
	return false;
}

bool TuringMachine::divide() {
	state();
	read();
	std::cout << "\nPrzeczytano symbol.";
	state();

	switch (_state) {
	case 0:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 1, Direction::RIGHT);
			break;
		case 0:
			_step(0, 0, Direction::RIGHT);
			break;
		case 1:
			_step(1, 0, Direction::RIGHT);
			break;
		case 2:
			_step(2, 0, Direction::RIGHT);
			break;
		case 3:
			_step(3, 0, Direction::RIGHT);
			break;
		case 4:
			_step(4, 0, Direction::RIGHT);
			break;
		case 5:
			_step(5, 0, Direction::RIGHT);
			break;
		case 6:
			_step(6, 0, Direction::RIGHT);
			break;
		case 9:
			_step(9, 0, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 1:
		switch (_symbol) {
		case 0:
			_step(4, 6, Direction::RIGHT);
			break;
		case 1:
			_step(3, 2, Direction::RIGHT);
			break;
		case 9:
			_step(9, 8, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 2:
		switch (_symbol) {
		case EMPTY:
			_step(9, 3, Direction::RIGHT);
			break;
		case 0:
			_step(0, 2, Direction::RIGHT);
			break;
		case 1:
			_step(1, 2, Direction::RIGHT);
			break;
		case 2:
			_step(2, 2, Direction::RIGHT);
			break;
		case 3:
			_step(3, 2, Direction::RIGHT);
			break;
		case 4:
			_step(4, 2, Direction::RIGHT);
			break;
		case 5:
			_step(5, 2, Direction::RIGHT);
			break;
		case 6:
			_step(6, 2, Direction::RIGHT);
			break;
		case 9:
			_step(9, 3, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 3:
		switch (_symbol) {
		case EMPTY:
			_step(1, 4, Direction::LEFT);
			break;
		case 0:
			_step(0, 3, Direction::RIGHT);
			break;
		case 1:
			_step(1, 3, Direction::RIGHT);
			break;
		case 2:
			_step(2, 3, Direction::RIGHT);
			break;
		case 3:
			_step(3, 3, Direction::RIGHT);
			break;
		case 4:
			_step(4, 3, Direction::RIGHT);
			break;
		case 5:
			_step(5, 3, Direction::RIGHT);
			break;
		case 6:
			_step(6, 3, Direction::RIGHT);
			break;
		case 9:
			_step(9, 3, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 4:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 4, Direction::LEFT);
			break;
		case 0:
			_step(0, 4, Direction::LEFT);
			break;
		case 1:
			_step(1, 4, Direction::LEFT);
			break;
		case 2:
			_step(2, 4, Direction::LEFT);
			break;
		case 3:
			_step(3, 4, Direction::LEFT);
			break;
		case 4:
			_step(4, 4, Direction::LEFT);
			break;
		case 5:
			_step(5, 4, Direction::LEFT);
			break;
		case 6:
			_step(6, 4, Direction::LEFT);
			break;
		case 9:
			_step(9, 5, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 5:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 5, Direction::LEFT);
			break;
		case 0:
			_step(0, 5, Direction::LEFT);
			break;
		case 1:
			_step(1, 5, Direction::LEFT);
			break;
		case 2:
			_step(2, 5, Direction::LEFT);
			break;
		case 3:
			_step(3, 1, Direction::RIGHT);
			break;
		case 4:
			_step(4, 1, Direction::RIGHT);
			break;
		case 5:
			_step(5, 5, Direction::LEFT);
			break;
		case 6:
			_step(6, 5, Direction::LEFT);
			break;
		case 9:
			_step(9, 5, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 6:
		switch (_symbol) {
		case EMPTY:
			_step(9, 7, Direction::RIGHT);
			break;
		case 0:
			_step(0, 6, Direction::RIGHT);
			break;
		case 1:
			_step(1, 6, Direction::RIGHT);
			break;
		case 2:
			_step(2, 6, Direction::RIGHT);
			break;
		case 3:
			_step(3, 6, Direction::RIGHT);
			break;
		case 4:
			_step(4, 6, Direction::RIGHT);
			break;
		case 5:
			_step(5, 6, Direction::RIGHT);
			break;
		case 6:
			_step(6, 6, Direction::RIGHT);
			break;
		case 9:
			_step(9, 7, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 7:
		switch (_symbol) {
		case EMPTY:
			_step(0, 4, Direction::LEFT);
			break;
		case 0:
			_step(0, 7, Direction::RIGHT);
			break;
		case 1:
			_step(1, 7, Direction::RIGHT);
			break;
		case 2:
			_step(2, 7, Direction::RIGHT);
			break;
		case 3:
			_step(3, 7, Direction::RIGHT);
			break;
		case 4:
			_step(4, 7, Direction::RIGHT);
			break;
		case 5:
			_step(5, 7, Direction::RIGHT);
			break;
		case 6:
			_step(6, 7, Direction::RIGHT);
			break;
		case 9:
			_step(9, 7, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 8:
		switch (_symbol) {
		case 3:
			_step(1, 9, Direction::LEFT);
			break;
		case 4:
			_step(0, 8, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 9:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 10, Direction::LEFT);
			break;
		case 3:
			_step(0, 9, Direction::LEFT);
			break;
		case 4:
			_step(1, 9, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 10:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 11, Direction::RIGHT);
			break;
		case 0:
			_step(0, 10, Direction::LEFT);
			break;
		case 1:
			_step(1, 10, Direction::LEFT);
			break;
		case 2:
			_step(2, 10, Direction::LEFT);
			break;
		case 3:
			_step(3, 10, Direction::LEFT);
			break;
		case 4:
			_step(4, 10, Direction::LEFT);
			break;
		case 5:
			_step(5, 10, Direction::LEFT);
			break;
		case 6:
			_step(6, 10, Direction::LEFT);
			break;
		case 9:
			_step(9, 10, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 11:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 12, Direction::RIGHT);
			break;
		case 0:
			_step(0, 11, Direction::RIGHT);
			break;
		case 1:
			_step(1, 11, Direction::RIGHT);
			break;
		case 2:
			_step(2, 11, Direction::RIGHT);
			break;
		case 3:
			_step(3, 11, Direction::RIGHT);
			break;
		case 4:
			_step(4, 11, Direction::RIGHT);
			break;
		case 5:
			_step(5, 11, Direction::RIGHT);
			break;
		case 6:
			_step(6, 11, Direction::RIGHT);
			break;
		case 9:
			_step(9, 11, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 12:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 12, Direction::RIGHT);
			break;
		case 0:
			_step(0, 12, Direction::RIGHT);
			break;
		case 1:
			_step(1, 12, Direction::RIGHT);
			break;
		case 2:
			_step(2, 12, Direction::RIGHT);
			break;
		case 3:
			_step(3, 12, Direction::RIGHT);
			break;
		case 4:
			_step(4, 12, Direction::RIGHT);
			break;
		case 5:
			_step(5, 12, Direction::RIGHT);
			break;
		case 6:
			_step(6, 12, Direction::RIGHT);
			break;
		case 9:
			_step(9, 13, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 13:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 19, Direction::RIGHT);
			break;
		case 0:
			_step(3, 14, Direction::LEFT);
			break;
		case 1:
			_step(4, 15, Direction::LEFT);
			break;
		case 3:
			_step(3, 13, Direction::LEFT);
			break;
		case 4:
			_step(4, 13, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 14:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 36, Direction::LEFT);
			break;
		case 0:
			_step(0, 14, Direction::LEFT);
			break;
		case 1:
			_step(1, 14, Direction::LEFT);
			break;
		case 2:
			_step(2, 14, Direction::LEFT);
			break;
		case 3:
			_step(3, 14, Direction::LEFT);
			break;
		case 4:
			_step(4, 14, Direction::LEFT);
			break;
		case 5:
			_step(5, 14, Direction::LEFT);
			break;
		case 6:
			_step(6, 14, Direction::LEFT);
			break;
		case 9:
			_step(9, 14, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 15:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 16, Direction::LEFT);
			break;
		case 0:
			_step(0, 15, Direction::LEFT);
			break;
		case 1:
			_step(1, 15, Direction::LEFT);
			break;
		case 2:
			_step(2, 15, Direction::LEFT);
			break;
		case 3:
			_step(3, 15, Direction::LEFT);
			break;
		case 4:
			_step(4, 15, Direction::LEFT);
			break;
		case 5:
			_step(5, 15, Direction::LEFT);
			break;
		case 6:
			_step(6, 15, Direction::LEFT);
			break;
		case 9:
			_step(9, 15, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 16:
		switch (_symbol) {
		case EMPTY:
			_step(1, 17, Direction::STOP);
			break;
		case 0:
			_step(1, 17, Direction::STOP);
			break;
		case 1:
			_step(0, 16, Direction::LEFT);
			break;
		case 2:
			_step(2, 16, Direction::LEFT);
			break;
		case 3:
			_step(3, 16, Direction::LEFT);
			break;
		case 4:
			_step(4, 16, Direction::LEFT);
			break;
		case 5:
			_step(5, 16, Direction::LEFT);
			break;
		case 6:
			_step(6, 16, Direction::LEFT);
			break;
		case 9:
			_step(9, 16, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 17:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 18, Direction::LEFT);
			break;
		case 0:
			_step(0, 17, Direction::RIGHT);
			break;
		case 1:
			_step(1, 17, Direction::RIGHT);
			break;
		case 2:
			_step(2, 17, Direction::RIGHT);
			break;
		case 3:
			_step(3, 17, Direction::RIGHT);
			break;
		case 4:
			_step(4, 17, Direction::RIGHT);
			break;
		case 5:
			_step(5, 18, Direction::LEFT);
			break;
		case 6:
			_step(6, 18, Direction::LEFT);
			break;
		case 9:
			_step(9, 17, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 18:
		switch (_symbol) {
		case 0:
			_step(5, 11, Direction::RIGHT);
			break;
		case 1:
			_step(6, 11, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 19:
		switch (_symbol) {
		case 3:
			_step(0, 19, Direction::RIGHT);
			break;
		case 4:
			_step(1, 19, Direction::RIGHT);
			break;
		case 9:
			_step(9, 37, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 20:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 39, Direction::LEFT);
			break;
		case 0:
			_step(0, 20, Direction::LEFT);
			break;
		case 1:
			_step(1, 20, Direction::LEFT);
			break;
		case 2:
			_step(2, 20, Direction::LEFT);
			break;
		case 3:
			_step(3, 20, Direction::LEFT);
			break;
		case 4:
			_step(4, 20, Direction::LEFT);
			break;
		case 5:
			_step(0, 20, Direction::LEFT);
			break;
		case 6:
			_step(1, 20, Direction::LEFT);
			break;
		case 9:
			_step(9, 20, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 22:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 35, Direction::RIGHT);
			break;
		case 0:
			_step(5, 27, Direction::RIGHT);
			break;
		case 1:
			_step(6, 23, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 23:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 23, Direction::RIGHT);
			break;
		case 0:
			_step(0, 23, Direction::RIGHT);
			break;
		case 1:
			_step(1, 23, Direction::RIGHT);
			break;
		case 2:
			_step(2, 23, Direction::RIGHT);
			break;
		case 3:
			_step(3, 23, Direction::RIGHT);
			break;
		case 4:
			_step(4, 23, Direction::RIGHT);
			break;
		case 5:
			_step(5, 23, Direction::RIGHT);
			break;
		case 6:
			_step(6, 23, Direction::RIGHT);
			break;
		case 9:
			_step(9, 24, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 24:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 29, Direction::LEFT);
			break;
		case 0:
			_step(0, 29, Direction::LEFT);
			break;
		case 1:
			_step(6, 25, Direction::LEFT);
			break;
		case 2:
			_step(2, 24, Direction::RIGHT);
			break;
		case 3:
			_step(3, 24, Direction::RIGHT);
			break;
		case 4:
			_step(4, 24, Direction::RIGHT);
			break;
		case 5:
			_step(5, 24, Direction::RIGHT);
			break;
		case 6:
			_step(6, 24, Direction::RIGHT);
			break;
		case 9:
			_step(9, 24, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 25:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 26, Direction::LEFT);
			break;
		case 0:
			_step(0, 25, Direction::LEFT);
			break;
		case 1:
			_step(1, 25, Direction::LEFT);
			break;
		case 2:
			_step(2, 25, Direction::LEFT);
			break;
		case 3:
			_step(3, 25, Direction::LEFT);
			break;
		case 4:
			_step(4, 25, Direction::LEFT);
			break;
		case 5:
			_step(5, 25, Direction::LEFT);
			break;
		case 6:
			_step(6, 25, Direction::LEFT);
			break;
		case 9:
			_step(9, 25, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 26:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 26, Direction::LEFT);
			break;
		case 0:
			_step(0, 26, Direction::LEFT);
			break;
		case 1:
			_step(1, 26, Direction::LEFT);
			break;
		case 2:
			_step(2, 26, Direction::LEFT);
			break;
		case 3:
			_step(3, 26, Direction::LEFT);
			break;
		case 4:
			_step(4, 26, Direction::LEFT);
			break;
		case 5:
			_step(5, 22, Direction::RIGHT);
			break;
		case 6:
			_step(6, 22, Direction::RIGHT);
			break;
		case 9:
			_step(9, 26, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 27:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 27, Direction::RIGHT);
			break;
		case 0:
			_step(0, 27, Direction::RIGHT);
			break;
		case 1:
			_step(1, 27, Direction::RIGHT);
			break;
		case 2:
			_step(2, 27, Direction::RIGHT);
			break;
		case 3:
			_step(3, 27, Direction::RIGHT);
			break;
		case 4:
			_step(4, 27, Direction::RIGHT);
			break;
		case 5:
			_step(5, 27, Direction::RIGHT);
			break;
		case 6:
			_step(6, 27, Direction::RIGHT);
			break;
		case 9:
			_step(9, 28, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 28:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 29, Direction::LEFT);
			break;
		case 0:
			_step(5, 25, Direction::LEFT);
			break;
		case 1:
			_step(1, 32, Direction::RIGHT);
			break;
		case 2:
			_step(2, 28, Direction::RIGHT);
			break;
		case 3:
			_step(3, 28, Direction::RIGHT);
			break;
		case 4:
			_step(4, 28, Direction::RIGHT);
			break;
		case 5:
			_step(5, 28, Direction::RIGHT);
			break;
		case 6:
			_step(6, 28, Direction::RIGHT);
			break;
		case 9:
			_step(9, 28, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 29:
		switch (_symbol) {
		case 5:
			_step(0, 29, Direction::LEFT);
			break;
		case 6:
			_step(1, 29, Direction::LEFT);
			break;
		case 9:
			_step(9, 30, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 30:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 31, Direction::LEFT);
			break;
		case 0:
			_step(0, 30, Direction::LEFT);
			break;
		case 1:
			_step(1, 30, Direction::LEFT);
			break;
		case 2:
			_step(2, 30, Direction::LEFT);
			break;
		case 3:
			_step(3, 30, Direction::LEFT);
			break;
		case 4:
			_step(4, 30, Direction::LEFT);
			break;
		case 5:
			_step(5, 30, Direction::LEFT);
			break;
		case 6:
			_step(6, 30, Direction::LEFT);
			break;
		case 9:
			_step(9, 30, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 31:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 11, Direction::RIGHT);
			break;
		case 0:
			_step(0, 31, Direction::LEFT);
			break;
		case 1:
			_step(1, 31, Direction::LEFT);
			break;
		case 5:
			_step(0, 31, Direction::LEFT);
			break;
		case 6:
			_step(1, 31, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 32:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 0:
			_step(0, 32, Direction::RIGHT);
			break;
		case 1:
			_step(1, 32, Direction::RIGHT);
			break;
		case 2:
			_step(2, 32, Direction::RIGHT);
			break;
		case 3:
			_step(3, 32, Direction::RIGHT);
			break;
		case 4:
			_step(4, 32, Direction::RIGHT);
			break;
		case 5:
			_step(5, 32, Direction::RIGHT);
			break;
		case 6:
			_step(6, 32, Direction::RIGHT);
			break;
		case 9:
			_step(9, 32, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 33:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 34, Direction::LEFT);
			break;
		case 0:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 1:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 2:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 3:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 4:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 5:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 6:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		case 9:
			_step(EMPTY, 33, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 34:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 99, Direction::RIGHT);
			break;
		case 0:
			_step(0, 34, Direction::LEFT);
			break;
		case 1:
			_step(1, 34, Direction::LEFT);
			break;
		case 2:
			_step(2, 34, Direction::LEFT);
			break;
		case 3:
			_step(3, 34, Direction::LEFT);
			break;
		case 4:
			_step(4, 34, Direction::LEFT);
			break;
		case 5:
			_step(0, 34, Direction::LEFT);
			break;
		case 6:
			_step(1, 34, Direction::LEFT);
			break;
		case 9:
			_step(9, 34, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 35:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 29, Direction::LEFT);
			break;
		case 0:
			_step(0, 35, Direction::RIGHT);
			break;
		case 1:
			_step(1, 35, Direction::RIGHT);
			break;
		case 2:
			_step(2, 35, Direction::RIGHT);
			break;
		case 3:
			_step(3, 35, Direction::RIGHT);
			break;
		case 4:
			_step(4, 35, Direction::RIGHT);
			break;
		case 5:
			_step(5, 35, Direction::RIGHT);
			break;
		case 6:
			_step(6, 35, Direction::RIGHT);
			break;
		case 9:
			_step(9, 35, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 36:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 11, Direction::RIGHT);
			break;
		case 0:
			_step(5, 11, Direction::RIGHT);
			break;
		case 1:
			_step(6, 11, Direction::RIGHT);
			break;
		case 2:
			_step(2, 36, Direction::LEFT);
			break;
		case 3:
			_step(3, 36, Direction::LEFT);
			break;
		case 4:
			_step(4, 36, Direction::LEFT);
			break;
		case 5:
			_step(5, 36, Direction::LEFT);
			break;
		case 6:
			_step(6, 36, Direction::LEFT);
			break;
		case 9:
			_step(9, 36, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 37:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 20, Direction::LEFT);
			break;
		case 0:
			_step(0, 37, Direction::LEFT);
			break;
		case 1:
			_step(1, 37, Direction::LEFT);
			break;
		case 2:
			_step(2, 37, Direction::LEFT);
			break;
		case 3:
			_step(3, 37, Direction::LEFT);
			break;
		case 4:
			_step(4, 37, Direction::LEFT);
			break;
		case 5:
			_step(5, 37, Direction::LEFT);
			break;
		case 6:
			_step(6, 37, Direction::LEFT);
			break;
		case 9:
			_step(9, 37, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 39:
		switch (_symbol) {
		case EMPTY:
			_step(1, 40, Direction::RIGHT);
			break;
		case 0:
			_step(1, 40, Direction::RIGHT);
			break;
		case 1:
			_step(0, 39, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 40:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 41, Direction::RIGHT);
			break;
		case 0:
			_step(0, 40, Direction::RIGHT);
			break;
		case 1:
			_step(1, 40, Direction::RIGHT);
			break;
		case 2:
			_step(2, 40, Direction::RIGHT);
			break;
		case 3:
			_step(3, 40, Direction::RIGHT);
			break;
		case 4:
			_step(4, 40, Direction::RIGHT);
			break;
		case 5:
			_step(5, 40, Direction::RIGHT);
			break;
		case 6:
			_step(6, 40, Direction::RIGHT);
			break;
		case 9:
			_step(9, 40, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 41:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 41, Direction::RIGHT);
			break;
		case 0:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 1:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 2:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 3:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 4:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 5:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 6:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		case 9:
			_step(EMPTY, 22, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
		break;
	case 99:
		std::cout << "Dzielenie zakonczone. Koncze dzialanie programu";
		return 1;

		break;
	default:
		std::cout << "ERROR - Nierozpoznany stan.";
		return true;
		break;
	}
	std::cout << "\nWykonano krok. Stan tasmy : ";

	state();
	return false;
}