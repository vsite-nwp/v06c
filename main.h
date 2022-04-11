#include "nwpwin.h"
#include "nwpdlg.h"
#define _USE_MATH_DEFINES
#include <math.h>

class sin_dialog : public vsite::nwp::dialog 
{
private:
	tstring legend;
	double sin;
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
public:
	void SetLegendText(tstring str) { legend = str; }
	tstring GetLegendText() { return legend; }
	void SetSinInterval(double interval) { sin = interval; }
	double GetSinInterval() { return sin; }
};

class main_window : public vsite::nwp::window
{
private:
	tstring interval_text;
	double interval;
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
public:
	main_window() : interval(2 * M_PI) {}
};
