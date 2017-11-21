#include "main.h"
#include "rc.h"

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetReal(IDC_EDIT1, period);
	SetText(IDC_EDIT2, text);
	return true;
}

bool SinDialog::OnOK() {
	try {
		period = GetReal(IDC_EDIT1);
		text = GetText(IDC_EDIT2);
	}
	catch (XCtrl&){
		MessageBox(*this, "Make sure every field is filled in with a value", "ERR: Blank Field", MB_ICONWARNING);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	DrawText(hdc, wintext.c_str(), -1, &rect, DT_LEFT | DT_TOP | DT_SINGLELINE);
	MoveToEx(hdc, 0, rect.bottom/2, NULL);
	LineTo(hdc, rect.right, rect.bottom/2);
	MoveToEx(hdc, rect.right/2, 0, NULL);
	LineTo(hdc, rect.right/2, rect.bottom);
	MoveToEx(hdc, rect.left, (1 - sin(rect.right/2*winperiod/rect.right))*rect.bottom/2, NULL);
	for(int x = 0, y = 0; x <= rect.right; x++){
			y = (1 - sin((x - rect.right/2)*winperiod/rect.right))*rect.bottom/2;
			LineTo(hdc, x, y);
		}
}

void MainWindow::OnCommand(int id){
	switch (id) {
	case ID_LEGEND: {
		SinDialog sinDialog;
		sinDialog.period = winperiod;
		sinDialog.text = wintext;
		if (sinDialog.DoModal(0, *this) == IDOK) {
			winperiod = sinDialog.period;
			wintext = sinDialog.text;
		}
	}
		InvalidateRect(*this, NULL, true);
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

