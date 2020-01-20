#include "main.h"
#include "rc.h"

int SinDialog::IDD(){
	return IDD_LEGEND; 
}

bool SinDialog::OnInitDialog(){
	SetReal(IDC_EDIT1, sin);
	SetText(IDC_EDIT2, legend);
	return true;
}

bool SinDialog::OnOK(){
	try
	{
		sin = GetReal(IDC_EDIT1);
		legend = GetText(IDC_EDIT2);
	}
	catch (XCtrl&)
	{
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT graph;
	GetClientRect(*this, &graph);
	DrawText(hdc, periodTxt.c_str(), -1, &graph, DT_RIGHT | DT_TOP | DT_SINGLELINE);
	MoveToEx(hdc, 0, graph.bottom / 2, NULL);
	LineTo(hdc, graph.right, graph.bottom / 2);
	MoveToEx(hdc, graph.right / 2, 0, NULL);
	LineTo(hdc, graph.right / 2, graph.bottom);
	MoveToEx(hdc, graph.left, graph.bottom / 2, NULL);
	for (double x = 0, y = 0; x <= graph.right; x++)
	{
		y = (1 - sin((x - (graph.right / 2)) * period / graph.right)) * graph.bottom / 2;
		LineTo(hdc, x, y);
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_LEGEND:
		{
			SinDialog dialog;
			dialog.SetDialPeriod(period);
			dialog.SetDialText(periodTxt);
			if (dialog.DoModal(0, *this) == IDOK){
				period = dialog.GetSinPeriod();
				periodTxt = dialog.GetDialText();
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

