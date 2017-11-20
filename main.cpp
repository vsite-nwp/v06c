#include "main.h"
#include "rc.h"

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetText(IDC_EDIT2, tekst);
	SetReal(IDC_EDIT1, period);
	return true;
}

bool SinDialog::OnOK(){
	tekst = GetText(IDC_EDIT2);
	period = GetReal(IDC_EDIT1);	
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rc;
	GetClientRect(*this, &rc);
	DrawText(hdc, m_tekst.c_str(), -1, &rc, DT_TOP | DT_RIGHT | DT_SINGLELINE);
	MoveToEx(hdc,0,rc.bottom/2, NULL);
	LineTo(hdc, rc.right, rc.bottom/2);
	MoveToEx(hdc, rc.right / 2, 0, NULL);
	LineTo(hdc, rc.right / 2, rc.bottom);
	MoveToEx(hdc, rc.left, rc.bottom / 2, NULL);
	for (double x =-rc.right /2, y = 0; x <= rc.right; ++x) {
		y = (1-(sin(x*m_period/rc.right)*rc.bottom/2))+rc.bottom/2;
		LineTo(hdc, x + rc.right / 2, y);
	}

}

void MainWindow::OnCommand(int id){
	switch(id){
	case ID_LEGEND: {
		SinDialog dialog;
		dialog.period = m_period;
		dialog.tekst = m_tekst;
		dialog.DoModal(0, *this);
		m_tekst = dialog.tekst;
		m_period = dialog.period;
		InvalidateRect(*this, NULL, true);
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, (LPCTSTR)"NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

