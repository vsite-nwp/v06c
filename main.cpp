#include "main.h"
#include "rc.h"

int SinDialog::IDD() {
	return IDD_LEGEND;
}

bool SinDialog::OnInitDialog() {
	SetText(IDC_EDIT2, dStr);
	SetReal(IDC_EDIT1, dPeriod);
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
		{
			SinDialog dialog;
			dialog.dPeriod = wPeriod;
			dialog.dStr = wStr;

			if (dialog.DoModal(0, *this) == IDOK) {
				wStr = dialog.dStr;
				wPeriod = dialog.dPeriod;
			}

			InvalidateRect(*this, NULL, true);
			break;
		}
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

