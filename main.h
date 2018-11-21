#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"


class SinDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	double interval;
	tstring txt;
};

class MainWindow : public Window {
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	double interval = 2 * M_PI;
	tstring txt = "";
};
 