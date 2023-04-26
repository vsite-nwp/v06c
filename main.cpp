#include "main.h"
#include "rc.h"

sin_dialog::sin_dialog(tstring const& text, double const& period)
	: legendText(text)
	, sinPeriod(period)
{
}

int sin_dialog::idd() const {
	return IDD_LEGEND; 
}

bool sin_dialog::on_init_dialog(){
	set_real(IDC_EDIT1, sinPeriod);
	set_text(IDC_EDIT2, legendText);
	return true;
}

void
sin_dialog::setLegendText(tstring const& text) {
	legendText = text;
}

void
sin_dialog::setSinPeriod(double const& period) {
	sinPeriod = period;
}

tstring
sin_dialog::getLegendText() const {
	return legendText;
}

double
sin_dialog::getPeriod() const {
	return sinPeriod;
}

bool sin_dialog::on_ok(){
	try {
		setLegendText(get_text(IDC_EDIT2));
		setSinPeriod(get_real(IDC_EDIT1));
	}
	catch (std::exception e) {
		// do nothing for now
		return false;
	}
	return true;
}

main_window::main_window()
	: legendText()
	, sinPeriod(0)
{
}

void main_window::on_paint(HDC hdc){
	RECT rc;
	GetClientRect(*this, &rc);

	// draw coordinate system
	MoveToEx(hdc, rc.right / 2, rc.top, NULL);
	LineTo(hdc, rc.right / 2, rc.bottom);
	MoveToEx(hdc, rc.left, rc.bottom / 2, NULL);
	LineTo(hdc, rc.right, rc.bottom / 2);

	// draw legend
	DrawText(hdc, legendText.c_str(), -1, &rc, DT_RIGHT | DT_TOP);

	// draw sine
	for (int x = 0, y = 0; x < rc.right; ++x) {
		y = (1 - sin((x - rc.right / 2) * sinPeriod / rc.right)) * rc.bottom / 2;
		if (x == 0) MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x, y);
	}
}

void main_window::on_command(int id){
	switch(id){
	case ID_LEGEND: {
		sin_dialog dialog(legendText, sinPeriod);
		
		if (dialog.do_modal(0, *this) == IDOK) {
			legendText = dialog.getLegendText();
			sinPeriod = dialog.getPeriod();
		}
		InvalidateRect(*this, NULL, true);
		break;
	}
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
