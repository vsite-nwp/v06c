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
	catch (std::runtime_error &err)
	{
		return false;
	}
	return true;
}
double GetY(RECT rect, double period, double x) {

	return (1 - sin((x - rect.right / 2.0) * period / rect.right)) * rect.bottom / 2;
}

void main_window::on_paint(HDC hdc){
	RECT graph;
	GetClientRect(*this, &graph);
	DrawText(hdc, description.c_str(), -1, &graph, DT_RIGHT | DT_TOP | DT_SINGLELINE);
	MoveToEx(hdc, 0, graph.bottom / 2, NULL);
	LineTo(hdc, graph.right, graph.bottom / 2);
	MoveToEx(hdc, graph.right / 2, 0, NULL);
	LineTo(hdc, graph.right / 2, graph.bottom);
	MoveToEx(hdc, graph.left, GetY(graph, period, 0.0), NULL);
	for (double x = graph.left, y = 0; x <= graph.right; x++)
	{
		y = GetY(graph, period, x) ;
		LineTo(hdc, x, y);
	}
}

void main_window::on_command(int id){
	switch(id){
		case ID_LEGEND: 
		{
			sin_dialog dlg;
			dlg.SetDialPeriod(period);
			dlg.SetDialText(description);
			if (dlg.do_modal(0, *this) == IDOK) {
				period = dlg.GetSinPeriod();
				description = dlg.GetDialText();
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
