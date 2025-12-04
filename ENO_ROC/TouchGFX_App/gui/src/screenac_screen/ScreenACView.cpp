#include <gui/screenac_screen/ScreenACView.hpp>
#include <touchgfx/Unicode.hpp>
#include "PDM.h"
#include "AC.h"

ScreenACView::ScreenACView()
{

}

void ScreenACView::setupScreen()
{
    ScreenACViewBase::setupScreen();
}

void ScreenACView::tearDownScreen()
{
    ScreenACViewBase::tearDownScreen();
}

void ScreenACView::handleTickEvent()
{
	static uint8_t loop_count;

	float Outlet_Temp;

	//Resistance
    Outlet_Temp = (pdm_analog_inputs[0] / 1023.0f) * 10000.0f;
    Unicode::snprintfFloat(textResBuffer,TEXTRES_SIZE,"%.2f", Outlet_Temp);

    //TEMP
    Outlet_Temp = 25.0f - (Outlet_Temp - 2000.0f) / 88.0f;
    Unicode::snprintfFloat(textTempBuffer,TEXTTEMP_SIZE,"%.2f", Outlet_Temp);

    //Clutch Engage/Disengage
    if(COMP == 1)
    {
    	Unicode::strncpy(textCompBuffer,"Engaged", TEXTCOMP_SIZE);
    }
    else{Unicode::strncpy(textCompBuffer,"Disabled", TEXTCOMP_SIZE);}
	if(++loop_count > 19)
		{
			loop_count = 0;
			this->invalidate();
		}
}

void ScreenACView::FanSpeed()
{

	if((LOW == 0) && (MED == 0) && (HIGH == 0))
	{
		LOW=1;MED=0;HIGH=0;
		Unicode::strncpy(textFanBuffer,"LOW", TEXTFAN_SIZE);
	}
	else if((LOW == 1) && (MED == 0) && (HIGH == 0))
	{
		LOW=0;MED=1;HIGH=0;
		Unicode::strncpy(textFanBuffer,"MED", TEXTFAN_SIZE);
	}
	else if((LOW == 0) && (MED == 1) && (HIGH == 0))
	{
		LOW=0;MED=0;HIGH=1;
		Unicode::strncpy(textFanBuffer,"HIGH", TEXTFAN_SIZE);
	}
	else if((LOW == 0) && (MED == 0) && (HIGH == 1))
	{
		LOW=0;MED=0;HIGH=0;
		Unicode::strncpy(textFanBuffer,"OFF", TEXTFAN_SIZE);
	}
	else{LOW = 0;MED=0;HIGH=0;Unicode::strncpy(textFanBuffer,"OFF", TEXTFAN_SIZE);}

}

void ScreenACView::INC()
{
	Resistance_Setpoint = Resistance_Setpoint + 200;
	if(Resistance_Setpoint > 4000)
	{
		Resistance_Setpoint = 4000;
	}
}

void ScreenACView::DEC()
{
	Resistance_Setpoint = Resistance_Setpoint - 200;
	if(Resistance_Setpoint < 0)
	{
		Resistance_Setpoint = 0;
	}
}
