#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"

#define _USE_MATH_DEFINES
#include "math.h"


class SinDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	tstring inputText;
	double inputPeriod;
	SinDialog(double inputPeriod, tstring inputText) : inputPeriod(inputPeriod), inputText(inputText) {}
};

class MainWindow : public Window {
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	tstring legendText;
	double sinusPeriod;
	MainWindow() : sinusPeriod(2 * M_PI) {}
};

