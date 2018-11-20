#include "main.h"
#include "rc.h"
#include <cmath>
#include <list>
#define PI 3.14159265358979323846

double interval = 2 * PI;
tstring txt = "";

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetReal(IDC_EDIT1, interval);
	SetText(IDC_EDIT2, txt);
	return true;
}

bool SinDialog::OnOK(){
	interval = GetReal(IDC_EDIT1);
	txt = GetText(IDC_EDIT2);
	InvalidateRect(GetParent(*this), NULL, NULL);
	return true;
}

void MainWindow::OnPaint(HDC hdc){
	RECT wndRect;
	GetClientRect(*this, &wndRect);	
	DrawText(hdc, txt.c_str(), txt.length(), &wndRect , DT_TOP | DT_RIGHT);
	MoveToEx(hdc, wndRect.right/2, 0, NULL);
	LineTo(hdc, wndRect.right / 2, wndRect.bottom);
	MoveToEx(hdc, wndRect.right, wndRect.bottom / 2, NULL);
	LineTo(hdc, 0 , wndRect.bottom / 2);
	SetViewportOrgEx(hdc, wndRect.right / 2, wndRect.bottom / 2, NULL);
	int height = wndRect.bottom / 2;
	int width = wndRect.right / 2;
	MoveToEx(hdc, -width, -height*sin(-width * (interval / width)),NULL);
	for (int x = -width; x <= width; ++x)
	{
		int y = -height * sin(x * (interval / width));
		LineTo(hdc, x, y);
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_LEGEND: 
		{
			SinDialog dlg;
			dlg.DoModal(NULL, NULL);
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
	SinDialog dlg;
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

