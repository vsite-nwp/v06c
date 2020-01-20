#include <windows.h>
#include <tchar.h>

#include <vector>

#include "nwpwin.h"
#include "nwpdlg.h"

std::vector<POINT> pts;

class SinDialog : public Dialog {
public:
	int n;
	tstring s;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	int nPeriod = 0;
	tstring tekst = _T("tekst legende");
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
 