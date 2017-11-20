#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"


class SinDialog : public Dialog {
public:	
	tstring text;
	double period;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	tstring wintext;
	double winperiod;
	MainWindow() : winperiod(3.14), wintext("ughh") {}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
 