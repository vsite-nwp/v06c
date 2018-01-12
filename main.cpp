#include "main.h"
#include "rc.h"

int SinDialog::IDD() {
	return IDD_LEGEND;
}

bool SinDialog::OnInitDialog() {
	return true;
}

bool SinDialog::OnOK() {
	return true;
}


void MainWindow::OnPaint(HDC hdc) {
	RECT rc;
	GetClientRect(*this, &rc);

	MoveToEx(hdc, rc.right / 2, 0, NULL);
	LineTo(hdc, rc.right / 2, rc.bottom);
	MoveToEx(hdc, 0, rc.bottom / 2, NULL);
	LineTo(hdc, rc.right, rc.bottom / 2);
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_LEGEND:

	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
}

void MainWindow::OnDestroy() {
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

