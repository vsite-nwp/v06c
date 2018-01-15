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
	dStr = GetText(IDC_EDIT2);
	dPeriod = GetReal(IDC_EDIT1);
	return true;
}


void MainWindow::OnPaint(HDC hdc) {
	RECT rc;
	GetClientRect(*this, &rc);
	DrawText(hdc, wStr.c_str(), -1, &rc, DT_TOP | DT_RIGHT);
	double halfX = rc.right / 2, halfY = rc.bottom / 2;


	MoveToEx(hdc, halfX, 0, NULL);
	LineTo(hdc, halfX, rc.bottom);
	MoveToEx(hdc, rc.right, halfY, NULL);
	LineTo(hdc, rc.left, halfY);
	
	for (double x = -1*halfX; x <= halfX; ++x)
	{
		int y = -1 * (halfY) * sin(wPeriod *  (x / halfX));
		LineTo(hdc, x + halfX, y + halfY);
	}
}

void MainWindow::OnCommand(int id) {
	switch (id) {
		case ID_LEGEND:
		{
			SinDialog dlg;
			dlg.dPeriod = wPeriod;
			dlg.dStr = wStr;

			if (dlg.DoModal(0, *this) == IDOK) {
				wStr = dlg.dStr;
				wPeriod = dlg.dPeriod;
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

