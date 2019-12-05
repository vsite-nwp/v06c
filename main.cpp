#include "main.h"
#include "rc.h"

int SinDialog::IDD()
{
	return IDD_LEGEND;
}

bool SinDialog::OnInitDialog()
{
	SetReal(IDC_EDIT1, sinPeriod);
	SetText(IDC_EDIT2, dialText);
	return true;
}

bool SinDialog::OnOK()
{
	sinPeriod = GetReal(IDC_EDIT1);
	dialText = GetText(IDC_EDIT2);
	return true;
}


void MainWindow::OnPaint(HDC hdc) {
	RECT rect;
	GetClientRect(*this, &rect);
	DrawText(hdc, winText.c_str(), -1, &rect, DT_RIGHT | DT_TOP | DT_SINGLELINE);
	MoveToEx(hdc, 0, rect.bottom / 2, NULL);
	LineTo(hdc, rect.right, rect.bottom / 2);
	MoveToEx(hdc, rect.right / 2, 0, NULL);
	LineTo(hdc, rect.right / 2, rect.bottom);
	MoveToEx(hdc, rect.left, rect.bottom / 2, NULL);
	for (double x = 0, y = 0; x <= rect.right; x++)
	{
		y = (1 - sin((x - (rect.right / 2)) * winPeriod / rect.right)) * rect.bottom / 2;
		LineTo(hdc, x, y);
	}
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_LEGEND:
	{
		SinDialog sd;
		sd.SetDialPeriod(winPeriod);
		sd.SetDialText(winText);
		if (sd.DoModal(0, *this) == IDOK)
		{
			winPeriod = sd.GetSinPeriod();
			winText = sd.GetDialText();
		}
	}
	InvalidateRect(*this, NULL, true);
	break;
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

