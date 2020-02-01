#include "MainIncludes.h"
#include "DEFINITIONS.h"

CGraphics graphic;
NumberConverter convert;
TuringMachine machine;

bool is_complete = 0; 
bool is_working = 0; //for disabling control panel while the machine is working

int main() {
	

	while (graphic.window.isOpen()) 
	{	
		if (graphic.SEND && is_working == 0) //entry data is acquired
		{
			machine.Setup(graphic.FIRST_VALUE, graphic.SECOND_VALUE, graphic.OPERATION); //starting machine
			graphic.SEND = 0;
			is_working = 1;
		}
		graphic.sync(machine.get_tape(), machine.get_pos(), machine.get_state()); //syncing graphics with machine's data
		graphic.drawAll(); //displays graphics
		if (is_working)
		{

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
}