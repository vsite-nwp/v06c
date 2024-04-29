#include "main.h"
#include "rc.h"

int sin_dialog::idd() const 
{
	return IDD_LEGEND;
}

bool sin_dialog::on_init_dialog() 
{
	set_real(IDC_EDIT1, sin);
	set_text(IDC_EDIT2, legend);
	return true;
}

bool sin_dialog::on_ok() 
{
	sin = get_real(IDC_EDIT1);
	legend = get_text(IDC_EDIT2);
	return true;
}

void main_window::on_paint(HDC hdc) 
{
	RECT rc;
	GetClientRect(*this, &rc);
	DrawText(hdc, tekst.c_str(), -1, &rc, DT_RIGHT | DT_TOP | DT_SINGLELINE);

	MoveToEx(hdc, rc.right / 2, rc.top, NULL);   
	LineTo(hdc, rc.right / 2, rc.bottom);           
	MoveToEx(hdc, rc.left, rc.bottom / 2, NULL);     
	LineTo(hdc, rc.right, rc.bottom / 2);            
	
	MoveToEx(hdc, rc.left, (1 - sin((rc.left - rc.right / 2.0) * period / rc.right)) * rc.bottom / 2, NULL);
	for (double x = rc.left, y = 0; x <= rc.right; x++)
	{
		y = (1 - sin((x - (rc.right / 2)) * period / rc.right)) * rc.bottom / 2;
		LineTo(hdc, x, y);
	}
}

void main_window::on_command(int id) 
{
	switch (id) 
	{
	case ID_LEGEND:
	{
		sin_dialog dlg;
		dlg.SetPeriod(period);
		dlg.SetText(tekst);
		if (dlg.do_modal(0, *this) == IDOK) 
		{
			period = dlg.GetPeriod();
			tekst = dlg.GetText();
			InvalidateRect(*this, NULL, true);
		}
	}
	break;

	case ID_EXIT:
		::DestroyWindow(*this);
		break;
	}
}

void main_window::on_destroy() 
{
	::PostQuitMessage(0);
}


int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}