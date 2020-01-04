#include "TuringMachine.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Dzia³anie												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TuringMachine::Init(std::vector<int> tape, Direction dir) {
	_tape = tape;
	_dir = dir;

	_tape.push_back(EMPTY);
	_tape.insert(_tape.begin(), EMPTY);

	if (_dir == Direction::LEFT) {
		_pos = _tape.size() - 1;
	}
	else {
		_pos = 1;
	}

	_state = 0;
}

void TuringMachine::read() {
	_symbol = _tape[_pos];
}

void TuringMachine::write(int newSymbol) {
	_tape[_pos] = newSymbol;
}

void TuringMachine::move(Direction dir) {
	_dir = dir;
	
	if (_dir == Direction::LEFT && _pos > 0) {
		_pos -= 1;
	}
	else if (_dir == Direction::LEFT && _pos < _tape.size()) {
		_pos += 1;
	}
}

int TuringMachine::result() {
	_tape.erase(std::remove(_tape.begin(), _tape.end(), EMPTY), _tape.end());

	NumberConverter convert;

	return convert.b2d(_tape);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////												Algorytmy												////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TuringMachine::increment() {
	read();
	std::cout << "\nPrzeczytano symbol.";

	switch (_symbol) {
	case 0:
		switch (_state) {
		case 0 :
			write(1);
			_state = 1;
			move(Direction::RIGHT);
			break;
		case 1 :
			write(0);
			_state = 1;
			move(Direction::RIGHT);
			break;
		default:
			return;
			break;
		}
		break;
	case 1:
		switch (_state) {
		case 0:
			write(0);
			_state = 0;
			move(Direction::LEFT);
			break;
		case 1:
			write(1);
			_state = 1;
			move(Direction::RIGHT);
			break;
		default:
			return;
			break;
		}
		break;
	case EMPTY:
		switch (_state) {
		case 0:
			write(1);
			_state = 1;
			move(Direction::RIGHT);
			break;
		case 1:
			write(EMPTY);
			_state = 2;
			move(Direction::LEFT);
			break;
		default:
			return;
			break;
		}
		break;
	default:
		std::cout << "\n\nPrzeczytano niespodziewany symbol : " << _symbol << " na tasmie w miejscu : " << _pos << " przy stanie : " << _state;
		break;
	}
	std::cout << "\nWykonano program.";
	increment();
	std::cout << "\nDokonano inkrementacji.";
}

void TuringMachine::add() {

}

void TuringMachine::subtract() {

}

void TuringMachine::multiply() {

}

void TuringMachine::divide() {

}