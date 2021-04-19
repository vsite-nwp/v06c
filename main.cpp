#include "main.h"
#include "rc.h"

int sin_dialog::idd() const {
	return IDD_LEGEND; 
}

bool sin_dialog::on_init_dialog(){
	set_real(IDC_EDIT1, sin);
	set_text(IDC_EDIT2, legend);
	return true;
}

bool sin_dialog::on_ok(){
	try
	{
		sin = get_real(IDC_EDIT1);
		legend = get_text(IDC_EDIT2);
	}
	catch (std::exception&)
	{
		MessageBox(*this, L"Invalid input", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc){
	RECT graph;
	GetClientRect(*this, &graph);
	DrawText(hdc, periodTxt.c_str(), -1, &graph, DT_RIGHT | DT_TOP | DT_SINGLELINE);
	int height = graph.bottom / 2;
	int width = graph.right / 2;
	MoveToEx(hdc, 0, height, NULL);
	LineTo(hdc, graph.right, height);
	MoveToEx(hdc, width, 0, NULL);
	LineTo(hdc, width, graph.bottom);
	MoveToEx(hdc, graph.left, height, NULL);
	for (double x = 0, y = 0; x <= graph.right; x++)
	{
		y = (1 - sin((x - width) * period / graph.right)) * height;
		LineTo(hdc, x, y);
	}
}

void main_window::on_command(int id){
	switch(id){
		case ID_LEGEND: 
		{
			sin_dialog dialog;
			dialog.set_dial_period(period);
			dialog.set_dial_text(periodTxt);
			if (dialog.do_modal(0, *this) == IDOK) {
				period = dialog.get_sin_period();
				periodTxt = dialog.get_dial_text();
				InvalidateRect(*this, NULL, true);
			}
		}
		break;
		case ID_EXIT: 
			::DestroyWindow(*this); 
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
} 


int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.run();
}
