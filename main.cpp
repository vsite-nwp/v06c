#include "main.h"
#include "rc.h"

int SinDialog::IDD()
{
	return IDD_LEGEND;
}

bool SinDialog::OnInitDialog()
{
	SetReal(IDC_EDIT1, sinPeriod);
	SetText(IDC_EDIT2, legendText);

	return true;
}

bool SinDialog::OnOK()
{
	try
	{
		sinPeriod = GetReal(IDC_EDIT1);
		legendText = GetText(IDC_EDIT2);
	}
	catch (XCtrl&)
	{
		MessageBox(*this, "Wrong entry, please try again", "Error", MB_OK | MB_ICONWARNING);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc)
{
	RECT sinDrawing;
	GetClientRect(*this, &sinDrawing);

	DrawText(hdc, inputedText.c_str(), -1, &sinDrawing, DT_RIGHT | DT_TOP | DT_SINGLELINE);

	MoveToEx(hdc, 0, sinDrawing.bottom / 2, NULL);
	LineTo(hdc, sinDrawing.right, sinDrawing.bottom / 2);
	MoveToEx(hdc, sinDrawing.right / 2, 0, NULL);
	LineTo(hdc, sinDrawing.right / 2, sinDrawing.bottom);
	MoveToEx(hdc, sinDrawing.left, static_cast<int>((1 - sin(-sinDrawing.right / 2 * inputedPeriod / sinDrawing.right))*sinDrawing.bottom / 2), NULL);

	for (int xAxis = 0, yAxis = 0; xAxis <= sinDrawing.right; ++xAxis)
	{
		yAxis = static_cast<int>((1 - sin((xAxis - sinDrawing.right / 2)*inputedPeriod / sinDrawing.right))*sinDrawing.bottom / 2);
		LineTo(hdc, xAxis, yAxis);
	}
}

void MainWindow::OnCommand(int id)
{
	switch (id)
	{
	case ID_LEGEND:
	{
		SinDialog sinInput;
		sinInput.sinPeriod = inputedPeriod;
		sinInput.legendText = inputedText;
		if (sinInput.DoModal(0, *this) == IDOK)
		{
			inputedPeriod = sinInput.sinPeriod;
			inputedText = sinInput.legendText;
			InvalidateRect(*this, NULL, true);
		}
		break;
	}

	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
}

void MainWindow::OnDestroy()
{
	::PostQuitMessage(0);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP Lab 6c",
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.Run();
}

