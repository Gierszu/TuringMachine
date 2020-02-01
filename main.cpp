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
			if(graphic.SECOND_VALUE == 0) machine.Setup(graphic.FIRST_VALUE, graphic.OPERATION);
			else machine.Setup(graphic.FIRST_VALUE, graphic.SECOND_VALUE, graphic.OPERATION);
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
			}
		}
		
		if (is_working == 0)
		{
			graphic.controls();
		}
	}
	return 0;
}