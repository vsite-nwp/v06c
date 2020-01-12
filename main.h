#include <windows.h>
#include <tchar.h>

#include <vector>

#include "nwpwin.h"
#include "nwpdlg.h"


class SinDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	
	std::vector<POINT> pts;

protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
 