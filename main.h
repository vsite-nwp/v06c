#include "nwpwin.h"
#include "nwpdlg.h"
#define _USE_MATH_DEFINES
#include <math.h>

class sin_dialog : public vsite::nwp::dialog {
private:
	tstring legend;
	double sin;
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
public:
	void set_dial_text(tstring str) { legend = str; }
	tstring get_dial_text() { return legend; }
	void set_dial_period(double period) { sin = period; }
	double get_sin_period() { return sin; }
};

class main_window : public vsite::nwp::window {
private:
	tstring periodTxt;
	double period;
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
public:
	main_window() : period(2 * M_PI) {}
};
