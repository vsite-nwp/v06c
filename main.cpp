#include "main.h"
#include "rc.h"


int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetReal(IDC_EDIT1, period);
	SetText(IDC_EDIT2, txtLegenda);
	return true;
}

bool SinDialog::OnOK() {
	try {
		period = GetInt(IDC_EDIT1);
		txtLegenda = GetText(IDC_EDIT2);
	}
	catch (XCtrl&) {
		MessageBox(*this, "Aj ti opet", "Krivi unos", MB_OK | MB_SETFOREGROUND);
		return true;
	}
}

void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);

	//x os
	MoveToEx(hdc, 0, rect.bottom / 2, NULL);
	LineTo(hdc, rect.right, rect.bottom / 2);
	//y os
	MoveToEx(hdc, rect.right / 2, 0, NULL);
	LineTo(hdc, rect.right / 2, rect.bottom);
	
	MoveToEx(hdc, rect.left, (1 - sin(rect.right / 2 * xperiod / rect.right))*rect.bottom /2, NULL);
	for (int x = 0, y = 0; x <= rect.right; ++x)
	{
		y = (1 - sin((x - rect.right / 2)*xperiod / rect.right))*rect.bottom/2;
		LineTo(hdc, x, y);
	}
	
	DrawText(hdc, text.c_str(), -1, &rect, DT_RIGHT | DT_TOP | DT_SINGLELINE);
}

void MainWindow::OnCommand(int id){
	switch(id){
	case ID_LEGEND: {
		SinDialog sinDialog;
		sinDialog.period = xperiod;
		sinDialog.txtLegenda = text;
		if (sinDialog.DoModal(0, *this) == IDOK) {
			xperiod = sinDialog.period;
			text = sinDialog.txtLegenda;
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

