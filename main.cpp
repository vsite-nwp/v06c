#include "main.h"
#include "rc.h"
#include <math.h>

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetReal(IDC_EDIT1, period);
	SetText(IDC_EDIT2, legText);
	return true;
}

bool SinDialog::OnOK(){
	try
	{
		period = GetReal(IDC_EDIT1);
		legText = GetText(IDC_EDIT2);
	}
	catch (XCtrl)
	{
		MessageBox(*this, "Krivi unos!", "Greška!", MB_OK | MB_ICONERROR|MB_SETFOREGROUND);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	//axes 
	MoveToEx(hdc, 0, rect.bottom / 2, NULL);
	LineTo(hdc, rect.right, rect.bottom / 2);
	MoveToEx(hdc, rect.right / 2, 0,NULL);
	LineTo(hdc, rect.right / 2, rect.bottom);
	//sine function
	MoveToEx(hdc, 0, (1 + sin(rect.right / 2*dPeriod / rect.right))*rect.bottom / 2,NULL);
	for (int x =0; x <= rect.right; ++x)
	{
		int y = (1 - sin((x-rect.right/2)*dPeriod / rect.right))*rect.bottom / 2;
		LineTo(hdc, x, y);
	}
	DrawText(hdc, sText.c_str(), -1, &rect, DT_RIGHT | DT_TOP|DT_SINGLELINE);
	InvalidateRect(*this, &rect, false);
}

void MainWindow::OnCommand(int id){
	switch(id)
	{
		case ID_LEGEND:
		{
			SinDialog sdlg;
			sdlg.period = dPeriod;
			sdlg.legText = sText;
			if (sdlg.DoModal(0, *this) == IDOK)
			{
				dPeriod = sdlg.period;
				sText = sdlg.legText;
			}
		}
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
	InvalidateRect(*this, NULL, TRUE);
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

