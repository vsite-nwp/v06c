#define _USE_MATH_DEFINES
#include "main.h"
#include "rc.h"
#include <cmath>


int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, n);
	SetText(IDC_EDIT2, s);
	return true;
}

bool SinDialog::OnOK(){
	try
	{
		n = GetInt(IDC_EDIT1);
	}
	catch (XCtrl e) {return false;}
	s = GetText(IDC_EDIT2);
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	if (nPeriod) {
		POINT p;
		RECT rc; ::GetClientRect(*this, &rc);
		::MoveToEx(hdc, 0, rc.bottom / 2, NULL);
		::LineTo(hdc, rc.right, rc.bottom / 2);
		::MoveToEx(hdc, rc.right / 2, 0, NULL);
		::LineTo(hdc, rc.right / 2, rc.bottom);
		pts.clear();
		::MoveToEx(hdc, 0, rc.bottom / 2, NULL);
		for (int i = 0; i <= rc.right; ++i) {
			p.x = i; p.y = -sin(i*(nPeriod * 2 * M_PI / rc.right))*rc.bottom / 2 + rc.bottom / 2;
			pts.push_back(p);
		}
		::Polyline(hdc, &*pts.begin(), pts.size());
		::SetTextAlign(hdc, TA_TOP | TA_RIGHT);
		::TextOut(hdc, rc.right - 10, rc.top + 10, tekst.c_str(), tekst.length());
	}
}

void MainWindow::OnCommand(int id){
	SinDialog sdlg;
	switch(id){
		case ID_LEGEND:
			sdlg.n = nPeriod; sdlg.s = tekst;
			if (sdlg.DoModal(NULL, *this) == IDOK) {
				nPeriod = sdlg.n; tekst = sdlg.s;
				::InvalidateRect(*this, NULL, TRUE);
			}
			break;
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

