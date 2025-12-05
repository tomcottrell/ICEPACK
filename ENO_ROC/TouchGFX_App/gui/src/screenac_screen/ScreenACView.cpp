#include <gui/screenac_screen/ScreenACView.hpp>
#include <touchgfx/Unicode.hpp>
#include "PDM.h"
#include "AC.h"
#include "Engine_App.h"


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

	//Resistance Outlet Temp probe
    Outlet_Temp = (pdm_analog_inputs[0] / 1023.0f) * 10000.0f;
    Unicode::snprintfFloat(textResOutletBuffer,TEXTRESOUTLET_SIZE,"%.2f", Outlet_Temp);

    //Resistance Setpoint
    Unicode::snprintfFloat(textResSetBuffer,TEXTRESSET_SIZE,"%.2f", Resistance_Setpoint);

    //TEMP
    Outlet_Temp = 25.0f - (Outlet_Temp - 2000.0f) / 88.0f; //rough equation
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

    //Clutch Engage/Disengage
    if(AC_PRESSURE_SWITCH == 2)
    {
    	Unicode::strncpy(textPressSwitchBuffer,"Active", TEXTPRESSSWITCH_SIZE);
    }
    else{Unicode::strncpy(textPressSwitchBuffer,"Disabled", TEXTPRESSSWITCH_SIZE);}

	if(++loop_count > 19)
		{
			loop_count = 0;
			this->invalidate();
		}
}

void ScreenACView::FanSpeed()
{

	if(ENGINE_RUNNING)
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
