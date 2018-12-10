#define _USE_MATH_DEFINES
#include <cmath>
#include "main.h"
#include "rc.h"

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetText(IDC_EDIT2, headerString);
	SetReal(IDC_EDIT1, piNumber);
	return true;
}

bool SinDialog::OnOK(){
	char s[128];

	LoadString(GetModuleHandle(NULL), ERR_STR, s, sizeof s);
	try {
		headerString = GetText(IDC_EDIT2);
		piNumber = GetReal(IDC_EDIT1);
	}
	catch(XCtrl&) {
		MessageBox(*this, s, NULL, MB_ICONWARNING);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rc;
	GetClientRect(*this, &rc);

	DrawText(hdc, setHeader.c_str(), setHeader.length(), &rc, DT_RIGHT | DT_TOP);

	MoveToEx(hdc, rc.right / 2, 0, NULL);
	LineTo(hdc, rc.right / 2, rc.bottom);
	MoveToEx(hdc, 0, rc.bottom / 2, NULL);
	LineTo(hdc, rc.right, rc.bottom / 2);

	SetViewportOrgEx(hdc, rc.right / 2, rc.bottom / 2, NULL);
	int width = rc.right / 2;
	int height = rc.bottom / 2;

	MoveToEx(hdc, - width, 0, NULL);

	for (int x = - width; x <= width; ++x) {
		double y = - height * sin((setPi/width) * x);
		LineTo(hdc, x, y);
	}	
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_LEGEND:
		{
			SinDialog dial;
			bool onOk;

			dial.headerString = setHeader;
			dial.piNumber = setPi;

			if (dial.DoModal(0, *this) == IDOK) {
				setHeader = dial.headerString;
				setPi = dial.piNumber;
				InvalidateRect(*this, NULL, true);
			}
			break;
		}
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
} 


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;	
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

