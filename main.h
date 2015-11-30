#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"
#include <vector>

class SinDialog : public Dialog {
public:
	double period;
	tstring legText;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	
	tstring sText;
	//LOGFONT logFont;
	double dPeriod;
public:
	MainWindow() : dPeriod(6.28), sText("Legenda") {}
	/*{
		::ZeroMemory(&logFont, sizeof(logFont));
		_tcscpy(logFont.lfFaceName, _T("Arial"));
	}*/
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
 