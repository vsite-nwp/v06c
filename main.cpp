#include "main.h"
#include "rc.h"

double Y(RECT r, double interval, double x)
{
	return (1 - sin((x - r.right / 2) * interval / r.right)) * r.bottom / 2;
}

int sin_dialog::idd() const
{
	return IDD_LEGEND;
}

bool sin_dialog::on_init_dialog()
{
	set_real(IDC_EDIT1, sinInterval);
	set_text(IDC_EDIT2, legend);
	return true;
}

bool sin_dialog::on_ok()
{
	try
	{
		sinInterval = get_real(IDC_EDIT1);
		legend = get_text(IDC_EDIT2);
	}
	catch (std::exception)
	{
		MessageBox(*this, L"Error", nullptr, MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc)
{
	RECT graph;
	GetClientRect(*this, &graph);
	DrawText(hdc, text.c_str(), -1, &graph, DT_RIGHT | DT_TOP | DT_SINGLELINE);

	int height = graph.bottom / 2;
	int width = graph.right / 2;

	MoveToEx(hdc, 0, height, nullptr);
	LineTo(hdc, graph.right, height);
	MoveToEx(hdc, width, 0, nullptr);
	LineTo(hdc, width, graph.bottom);
	MoveToEx(hdc, graph.left, Y(graph, interval, 0), nullptr);

	for (double x = graph.left, y = 0; x <= graph.right; x++)
	{
		y = Y(graph, interval, x);
		LineTo(hdc, x, y);
	}
}

void main_window::on_command(int id)
{
	switch (id)
	{
	case ID_LEGEND:
	{
		sin_dialog dialog;
		dialog.SetSinInterval(interval);
		dialog.SetLegendText(text);
		if (dialog.do_modal(0, *this) == IDOK)
		{
			interval = dialog.GetSinInterval();
			text = dialog.GetLegendText();
			InvalidateRect(*this, nullptr, true);
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