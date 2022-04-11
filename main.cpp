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
	try
	{
		sin = get_real(IDC_EDIT1);
		legend = get_text(IDC_EDIT2);
	}
	catch (std::exception &e)
	{
		MessageBox(*this, L"Invalid input", nullptr, MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void main_window::on_paint(HDC hdc)
{
	RECT graph;
	GetClientRect(*this, &graph);
	DrawText(hdc, interval_text.c_str(), -1, &graph, DT_RIGHT | DT_TOP | DT_SINGLELINE);

	int graph_height = graph.bottom / 2;
	int graph_width = graph.right / 2;

	MoveToEx(hdc, 0, graph_height, nullptr);
	LineTo(hdc, graph.right, graph_height);
	MoveToEx(hdc, graph_width, 0, nullptr);
	LineTo(hdc, graph_width, graph.bottom);
	MoveToEx(hdc, graph.left, graph_height, nullptr);

	for (double x = 0, y = 0; x <= graph.right; x++)
	{
		y = (1 - sin((x - graph_width) * interval / graph.right)) * graph_height;
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
		dialog.SetLegendText(interval_text);
		if (dialog.do_modal(0, *this) == IDOK)
		{
			interval = dialog.GetSinInterval();
			interval_text = dialog.GetLegendText();
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