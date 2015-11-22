#include "main.h"
#include "rc.h"

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	return true;
}

bool SinDialog::OnOK(){
	try
	{
		SinDialog::period = SinDialog::GetReal(IDC_EDIT1);
		SinDialog::legText = SinDialog::GetText(IDC_EDIT2);
	}
	catch (XCtrl ex)
	{
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	GetClientRect(*this, &rect);
	
	MoveToEx(hdc, 0, rect.bottom / 2, NULL);
	LineTo(hdc, rect.right, rect.bottom / 2);
	MoveToEx(hdc, rect.right / 2, 0,NULL);
	LineTo(hdc, rect.right / 2, rect.bottom);


}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_LEGEND: 
			
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

