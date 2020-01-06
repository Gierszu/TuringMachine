#include "TuringMachine.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Dzia³anie												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// Inicjalizuje, b¹dŸ resetuje maszynê.
void TuringMachine::Init(int tape[19], Direction dir) {
	std::cout << "\n\nMasszyna Turinga utworzona. Inicjalizowanie zmiennych...";
	
	// Inicjalizowanie zmiennych:
	_pos = 0;
	_state = 0;
	_symbol = EMPTY;
	_dir = dir;

	std::cout << "\nZmienne zainicjalizowane. Czyszczenie tasmy...";

	// Czyszczenie taœmy:
	for (int i = 0; i < 19; i++) {
		_tape[i] = EMPTY;
	}

	state();

	std::cout << "\nTasma wyczyszczona. Przygotowywanie tasmy pod obliczenia...";

	// Przypisywanie nowej taœmy, zostawiaj¹c dwa pola puste z przodu:
	for (int i = 2; i < 19; i++) {
		_tape[i] = tape[i-2];
	}

	state();

	std::cout << "\nTasma przygotowana. Ustawianie poczatkowej pozycji...";

	// Ustawianie pocz¹tkowej pozycji:
	if (_dir == Direction::LEFT) {
		for (int i = 18; i > 0; i--) {
			if (_tape[i] != EMPTY && _pos == 0) {
				_pos = i;
				state();
			}
		}
	}
	else {
		_pos = 2;
		state();
	}

	std::cout << "\nPoczatkowa pozycja ustalona : " << _pos << "\nMaszyna zainicjalizowana.\n";
}

/// Zbiera dane od u¿ytkownika i na ich podstawie przygotowuje maszynê do pracy.
void TuringMachine::Setup(int dec_1, int dec_2, Operation op) {
	_op = op;
	
	NumberConverter convert;
	int* tape;
	tape = convert.give_tape(_tape, dec_1, dec_2, op);

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
		std::cout << "\n\nERROR - Nie rozpoznano operacji! Nie uda³o siê ustawiæ maszyny.\n\n";
		return;
		break;
	}
}

void TuringMachine::Setup(int dec, Operation op) {
	_op = op;

	NumberConverter convert;
	int* tape;
	tape = convert.give_tape(_tape, dec);

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
	else if (_dir == Direction::RIGHT && _pos < 18) {
		_pos += 1;
	}
}

/// Zwraca wynik w postaci decymalnej. Do u¿ycia po wykonaniu ca³ego dzia³ania.
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
	for (int i = 0; i < 19; i++) {
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

	for (int i = 0; i < 19; i++) {
		std::cout << _tape[i];
	}

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
	case 1:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 2:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 3:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 4:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 5:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 6:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 7:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 10:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 11:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	case 99:
		switch (_symbol) {
		case EMPTY:

			break;
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		default:
			std::cout << "\n\nERROR - Nierozpoznany symbol." << _symbol << "Konczenie programu.";
			state();
			return true;
			break;
		}
	default:
		std::cout << "ERROR - Nierozpoznany stan.";
		return true;
		break;
	}
	return true;
}

bool TuringMachine::subtract() {
	return true;
}

bool TuringMachine::multiply() {
	return true;
}

bool TuringMachine::divide() {
	return true;
}