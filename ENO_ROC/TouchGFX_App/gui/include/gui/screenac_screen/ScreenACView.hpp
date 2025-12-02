#ifndef SCREENACVIEW_HPP
#define SCREENACVIEW_HPP

#include <gui_generated/screenac_screen/ScreenACViewBase.hpp>
#include <gui/screenac_screen/ScreenACPresenter.hpp>

class ScreenACView : public ScreenACViewBase
{
public:
    ScreenACView();
    virtual ~ScreenACView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENACVIEW_HPP
