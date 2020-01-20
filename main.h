#include <windows.h>
#include <tchar.h>
#include <math.h>
#define _USE_MATH_DEFINES

#include "nwpwin.h"
#include "nwpdlg.h"

class SinDialog : public Dialog
{
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	double sinPeriod;
	tstring legendText;
};

class MainWindow : public Window
{
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	double inputedPeriod;
	tstring inputedText;

	MainWindow::MainWindow() :inputedPeriod(M_PI * 2), inputedText("Legend") {}

};
