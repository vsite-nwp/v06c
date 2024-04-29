#include "nwpwin.h"
#include "nwpdlg.h"
#define _USE_MATH_DEFINES
#include <math.h>

class sin_dialog : public vsite::nwp::dialog 
{
public:
	void SetText(tstring str) 
	{
		legend = str; 
	}
	
	tstring GetText() 
	{ 
		return legend; 
	}
	void SetPeriod(double period) 
	{ 
		sin = period; 
	}
	
	double GetPeriod() 
	{ 
		return sin; 
	}

protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;

private:
	tstring legend;
	double sin;

};

class main_window : public vsite::nwp::window 
{
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

private:
	tstring tekst;
	double period;
	
public:
	main_window() : period(2 * M_PI) {} 
};