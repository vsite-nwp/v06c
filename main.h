#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"

class SinDialog : public Dialog {
public:
	double period;
	tstring tekst;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	double m_period=6.28;
	tstring m_tekst="Legenda";
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
 