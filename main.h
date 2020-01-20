#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"
#define _USE_MATH_DEFINES
#include <math.h>

class SinDialog : public Dialog {
private:
	tstring legend;
	double sin;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	void SetDialText(tstring str) { legend = str; }
	tstring GetDialText() { return legend; }
	void SetDialPeriod(double period) { sin = period; }
	double GetSinPeriod() { return sin; }
};

class MainWindow : public Window {
private:
	tstring periodTxt;
	double period;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	MainWindow() : period(2 * M_PI) {}
};
 