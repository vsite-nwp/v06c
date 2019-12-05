#include <windows.h>
#include <tchar.h>
#include <math.h>

#include "nwpwin.h"
#include "nwpdlg.h"


class SinDialog : public Dialog {
	tstring dialText;
	double sinPeriod;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	void SetDialText(tstring str) { dialText = str; }
	tstring GetDialText() { return dialText; }
	void SetDialPeriod(double period) { sinPeriod = period; }
	double GetSinPeriod() { return sinPeriod; }

};

class MainWindow : public Window {
	tstring winText;
	double winPeriod;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	MainWindow() : winPeriod(0.0), winText("") {}
};
 