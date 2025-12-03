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
	float Outlet_Temp;
	static uint8_t loop_count;
    Outlet_Temp = (pdm_analog_inputs[0] / 1023.0f) * 5.0f;
    Unicode::snprintfFloat(textTempBuffer, TEXTEMP_SIZE, ""%.2fV", Outlet_Temp);

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
