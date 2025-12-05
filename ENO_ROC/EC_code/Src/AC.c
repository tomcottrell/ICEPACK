#include "PDM.h"
#include "AC.h"
#include "Engine_App.h"

bool LOW = 0;
bool MED = 0;
bool HIGH = 0;
bool COMP = 0;

uint8_t AC_PRESSURE_SWITCH = 0;
float Resistance_Setpoint = 2000; //BETWEEN 0 and 4000

//Resistance increases as temperature decreases

void AC_app()
{
	float Outlet_Resistance;
	Outlet_Resistance = (pdm_analog_inputs[0] / 1023.0f) * 10000.0f;


	if(Resistance_Setpoint < Outlet_Resistance)
	{
		COMP = 1;
	}
	else{COMP = 0;}

	if((AC_PRESSURE_SWITCH == 2) || (ENGINE_RUNNING == 0))
	{
		COMP = 0;
	}
}

