#include "nwpwin.h"
#include "nwpdlg.h"
#define _USE_MATH_DEFINES
#include <math.h>

double Y(RECT r, double interval, double x);

class sin_dialog : public vsite::nwp::dialog
{	
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;

private:
	tstring legend;
	double sinInterval;

public:

	void SetLegendText(tstring str) { legend = str; }
	tstring GetLegendText() { return legend; }
	void SetSinInterval(double interval) { sinInterval = interval; }
	double GetSinInterval() { return sinInterval; }
};

class main_window : public vsite::nwp::window
{
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

private:
	tstring text;
	double interval;

public:

	main_window() : interval(2 * M_PI) {}
};
