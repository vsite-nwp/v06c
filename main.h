#include "nwpwin.h"
#include "nwpdlg.h"
#define _USE_MATH_DEFINES
#include <math.h>

class sin_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
private:
	tstring legend;
	double sin;
public:
	void SetDialText(tstring str) { legend = str; }
	tstring GetDialText() { return legend; }
	void SetDialPeriod(double period) { sin = period; }
	double GetSinPeriod() { return sin; }
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
private:
	tstring description;
	double period;
public:
	main_window() : period(2 * M_PI) {}
};

double GetY(RECT rect, double period, double x);
