#pragma once

#include "DEFINITIONS.h"
#include "NumberConverter.h"

class TuringMachine {
public:
	TuringMachine() {};

	void Init(std::vector<int> tape, Direction dir);
	
	void add();
	void subtract();
	void multiply();
	void divide();

	int result();

	// Testowe:
	void increment();
private:
	int read();
	void write();
	void move();

	std::vector<int> _tape;
	Direction _dir;
	int _state;
};

