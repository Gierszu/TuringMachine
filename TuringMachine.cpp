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
		_tape[i] = tape[i - 20];
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
		Init(tape, Direction::LEFT);
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
	read();
	std::cout << "\nPrzeczytano symbol.";
	state();

	switch (_state) {
	case 0:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 0, Direction::LEFT);
			break;
		case 0:
			_step(0, 1, Direction::LEFT);
			break;
		case 1:
			_step(1, 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, _state * 10, Direction::LEFT);
			break;
		case 0:
			_step(0, _state + 1, Direction::LEFT);
			break;
		case 1:
			_step(1, _state + 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 8:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, _state * 10, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 10:
	case 20:
	case 30:
	case 40:
	case 50:
	case 60:
	case 70:
	case 80:
		switch (_symbol) {
		case 0:
		case 1:
			_step(_symbol, _state + 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 45:
	case 46:
	case 47:
	case 48:
	case 56:
	case 57:
	case 58:
	case 67:
	case 68:
	case 78:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 90, Direction::RIGHT);
			break;
		case 8:
			_step(8, 90, Direction::RIGHT);
			break;
		case 0:
		case 1:
			_step(_symbol, _state + 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 11:
	case 22:
	case 33:
	case 44:
	case 55:
	case 66:
	case 77:
	case 88:
		switch (_symbol) {
		case EMPTY:
		case 8:
			_step(_symbol, 301, Direction::RIGHT);
			break;
		case 0:
		case 1:
			_step(_symbol, _state + 1, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 21:
	case 31:
	case 32:
	case 41:
	case 42:
	case 43:
	case 51:
	case 52:
	case 53:
	case 54:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 81:
	case 82:
	case 83:
	case 84:
	case 85:
	case 86:
	case 87:
		switch (_symbol) {
		case EMPTY:
		case 8:
			return true;
			break;
		case 0:
		case 1:
			_step(_symbol, _state + 1, Direction::LEFT);
			break;
		}
		break;
	case 90:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 91, Direction::RIGHT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
		case 8:
			_step(_symbol, 90, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 91:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 92, Direction::LEFT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			_step(_symbol, 91, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 92:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 100, Direction::LEFT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			_step(_symbol, 90, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 93:
		switch (_symbol) {
		case EMPTY:
			_step(8, 94, Direction::LEFT);
			break;
		case 8:
			_step(8, 95, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 93, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 94:
		switch (_symbol) {
		case EMPTY:
		case 8:
			_step(8, 95, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 94, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 95:
		switch (_symbol) {
		case EMPTY:
			_step(8, 96, Direction::LEFT);
			break;
		case 8:
			_step(8, 95, Direction::LEFT);
			break;
		case 1:
		case 0:
			_step(_symbol, 96, Direction::STOP);
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 96:
		switch (_symbol) {
		case 0:
		case EMPTY:
			_step(1, 900, Direction::RIGHT);
			break;
		case 1:
			_step(0, 96, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 900:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 901, Direction::RIGHT);
			break;
		case 0:
		case 1:
		case 8:
			_step(_symbol, 900, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 900, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 901:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 0, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 901, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 901, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 902:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 903, Direction::RIGHT);
			break;
		case 0:
		case 1:
		case 8:
			_step(_symbol, 902, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 902, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 903:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 100, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 903, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 903, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 904:
		switch (_symbol) {
		case EMPTY:
		case 8:
			_step(_symbol, 902, Direction::RIGHT);
			break;
		case 0:
		case 1:
			_step(_symbol, 904, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 904, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 905:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 904, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 905, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 905, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 953:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 9999, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 953, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 953, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 952:
		switch (_symbol) {
		case EMPTY:
			_step(EMPTY, 953, Direction::RIGHT);
			break;
		case 0:
		case 1:
			_step(_symbol, 952, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 952, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 951:
		switch (_symbol) {
		case EMPTY:
		case 8:
			_step(_symbol, 952, Direction::RIGHT);
			break;
		case 0:
		case 1:
			_step(_symbol, 951, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 951, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 950:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 951, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, 950, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step((_symbol - 2), 950, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 100:
	case 110:
	case 120:
	case 130:
	case 140:
	case 150:
	case 160:
	case 170:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 93, Direction::LEFT);
			break;
		case 0:
			_step(2, _state + 10, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step(_symbol, _state + 10, Direction::LEFT);
			break;
		case 1:
			_step(3, _state + 11, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 111:
	case 121:
	case 131:
	case 141:
	case 151:
	case 161:
	case 171:
	case 181:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, _state + 100, Direction::LEFT);
			break;
		case 0:
		case 1:
			_step(_symbol, _state, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 211:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, _state, Direction::LEFT);
			break;
		case 0:
			_step(1, _state, Direction::LEFT);
			break;
		case 1:
			_step(0, 400, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 221:
	case 231:
	case 241:
	case 251:
	case 261:
	case 271:
	case 281:
		switch (_symbol) {
		case 0:
		case 1:
			_step(_symbol, _state - 10, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 301:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 951, Direction::LEFT);
			break;
		case 0:
			_step(2, 302, Direction::RIGHT);
			break;
		case 1:
			_step(3, 312, Direction::RIGHT);
			break;
		case 2:
		case 3:
			_step(_symbol, _state, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 302:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 303, Direction::RIGHT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			_step(_symbol, _state, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 303:
		switch (_symbol) {
		case 0:
			_step(2, 304, Direction::RIGHT);
			break;
		case 1:
			_step(_symbol, 950, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step(_symbol, _state, Direction::RIGHT);
			break;
		case EMPTY:
			_step(_symbol, 905, Direction::LEFT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 304:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 305, Direction::LEFT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			_step(_symbol, _state, Direction::LEFT);
			break;
		}
		break;
	case 305:
		switch (_symbol) {
		case EMPTY:
		case 8:
			_step(_symbol, 301, Direction::RIGHT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			_step(_symbol, _state, Direction::LEFT);
			break;
		}
		break;
	case 312:
		switch (_symbol) {
		case EMPTY:
			_step(_symbol, 313, Direction::RIGHT);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			_step(_symbol, 312, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 313:
		switch (_symbol) {
		case 0:
			_step(_symbol, 905, Direction::LEFT);
			break;
		case 1:
			_step(3, 304, Direction::LEFT);
			break;
		case 2:
		case 3:
			_step(_symbol, 313, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 400:
		switch (_symbol) {
		case 0:
			_step(_symbol, _state, Direction::LEFT);
			break;
		case 1:
			_step(_symbol, 90, Direction::RIGHT);
			break;
		case 8:
		case EMPTY:
			_step(8, 401, Direction::RIGHT);
			break;
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 401:
		switch (_symbol) {
		case 0:
			_step(8, _state, Direction::RIGHT);
			break;
		case 1:
			_step(_symbol, 90, Direction::RIGHT);
		default:
			std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
			break;
		}
		break;
	case 9999:
		std::cout << "\n\nDzielenie zakonczone." << "\n\n";
		return true;
		break;
	default:
		std::cout << "\n\nNie rozpoznano kombinacji stan : " << _state << ", symbol : " << _symbol << "\n\n";
		break;
	}

	return false;
}