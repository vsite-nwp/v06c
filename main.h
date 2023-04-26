#include "nwpwin.h"
#include "nwpdlg.h"
#include <cmath>

class sin_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;

public:
	sin_dialog(tstring const&, double const& period);
	void setLegendText(tstring const& text);
	void setSinPeriod(double const& period);
	tstring getLegendText() const;
	double getPeriod() const;

private:
	tstring legendText;
	double sinPeriod;
};

class main_window : public vsite::nwp::window {
public:
	main_window();
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

private:
	tstring legendText;
	double sinPeriod;
};
