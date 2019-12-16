#include "main.h"
#include "rc.h"

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetReal(IDC_EDIT1, inputPeriod);
	SetText(IDC_EDIT2, inputText);
	return true;
}

bool SinDialog::OnOK(){
	try
	{
		inputPeriod = GetReal(IDC_EDIT1);
		inputText = GetText(IDC_EDIT2);
		return true;
	}
	catch(XCtrl)
	{
		MessageBox(*this, "Neispravan period", "Greska", MB_OK | MB_ICONERROR);
		return false;
	}
}


void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	HPEN p = CreatePen(PS_SOLID, 2, BLACK_PEN);
	GetClientRect(*this, &rect);
	DrawText(hdc, legendText.c_str(), -1, &rect, DT_RIGHT | DT_TOP | DT_SINGLELINE);
		
	MoveToEx(hdc, 0, rect.bottom / 2, NULL);

	SelectObject(hdc, p);
	LineTo(hdc, rect.right, rect.bottom / 2);
	MoveToEx(hdc, rect.right / 2, 0, NULL);
	LineTo(hdc, rect.right / 2, rect.bottom);
		
	MoveToEx(hdc, 0, sinus(0, sinusPeriod, rect.right, rect.bottom), NULL);

	p = CreatePen(PS_SOLID, 1, BLACK_PEN);
	SelectObject(hdc, p);
	for (double x = 0, y = 0; x <= rect.right; ++x)
	{
		y = sinus(x, sinusPeriod, rect.right, rect.bottom);
		LineTo(hdc, x, y);
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_LEGEND:
		{
			SinDialog inputParam(sinusPeriod, legendText);
			if (inputParam.DoModal(0, *this) == IDOK) {
				sinusPeriod = inputParam.inputPeriod;
				legendText = inputParam.inputText;
				InvalidateRect(*this, NULL, true);
			}
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", (int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

