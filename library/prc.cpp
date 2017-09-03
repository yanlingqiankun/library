#include"stdafx.h"

using namespace std;

INT_PTR CALLBACK Dlgwel(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_SYSCOMMAND :
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(hdlg);
		}
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
