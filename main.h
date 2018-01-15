#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"


class SinDialog : public Dialog {
public:
	double dPeriod;
	tstring dStr;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	double wPeriod = 3.14;
	tstring wStr = "Legenda";
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};