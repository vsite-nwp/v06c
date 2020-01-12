#include "main.h"
#include "rc.h"


const double pi = 3.14159265358979323846;
int nPeriod(0);
tstring s = _T("tekst legende");
SinDialog sdlg;

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, ::nPeriod);
	SetText(IDC_EDIT2, ::s);
	return true;
}

bool SinDialog::OnOK(){
	try
	{
		nPeriod = GetInt(IDC_EDIT1);
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
		pts.erase(pts.begin(),pts.end());
		::MoveToEx(hdc, 0, rc.bottom / 2, NULL);
		for (int i = 0; i <= rc.right; ++i) {
			p.x = i; p.y = -sin(i*(nPeriod * 2 * pi / rc.right))*rc.bottom / 2 + rc.bottom / 2;
			pts.push_back(p);
		}
		for (POINT p : pts) {
			::PolyBezier(hdc, &*pts.begin(), rc.right);
		}
		::SetTextAlign(hdc, TA_TOP | TA_RIGHT);
		::TextOut(hdc, rc.right - 10, rc.top + 10, s.c_str(), s.length());
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_LEGEND:
			if (sdlg.DoModal(NULL, *this) == IDOK) {
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

