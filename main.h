#include <windows.h>
#include <tchar.h>

#include "nwpwin.h"
#include "nwpdlg.h"


class SinDialog : public Dialog {
public:
	double piNumber;
	tstring headerString;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	double setPi = 3.14;
	tstring setHeader = "HEADER";
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
 