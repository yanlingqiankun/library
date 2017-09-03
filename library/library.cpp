// library.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "library.h"
#include "function.h"
#include "winuser.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HDC hdc, mdc;									//HDC，不解释
HBITMAP bg;
char str1[50];                                   //以后在缓存区存储的字符
FILE * file;									//文件指针便于观察读到的数据
HWND hWnd;										//主窗口句柄
UINT message;                                   //信息变量
WNDCLASSEXW wcex;								//窗口结构体实例
long old;                                       //用来存放老过程函数
HWND button1;									//管理员登录按钮
HWND button2;									//学生登录按钮
HWND button3;									//自助还书按钮
HWND hdlg;										//管理员登录
HWND hdlg1;                                     //学生登录窗口
HWND h_newbook;									//新书录入窗口
HWND h_remove_book;								//删除书籍窗口
HWND h_newstu;									//新用户注册窗口
HWND h_delestu;									//删除用户的窗口
HWND h_record;									//查看图书借还记录
HWND h_find;									//图书查询窗口
HWND h_borrow;									//图书借阅窗口
char stu_id[100];								//记录当前登录学生的id

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LIBRARY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIBRARY));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
   // WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	HBITMAP hBitmap;
	HBRUSH hBrush;
	hBitmap = (HBITMAP)LoadImage(NULL, L"..\\img\\zhujiemian.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//这里的名字跟你添加的资源要一样。
	hBrush = CreatePatternBrush(hBitmap);
	wcex.hbrBackground = hBrush;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIBRARY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
   // wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LIBRARY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

      hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		button1=CreateWindow(L"Button", L"管理员登录", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 800, 200, 150, 70, hWnd, (HMENU)3301, hInst, NULL);
		button2=CreateWindow(L"Button", L"学生登录", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 800, 400, 150, 70, hWnd, (HMENU)3302, hInst, NULL);
		button3=CreateWindow(L"Button", L"自助还书", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 800, 600, 150, 70, hWnd, (HMENU)3303, hInst, NULL);
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_BACK:
				PostMessage(hWnd, WM_CREATE,wParam,lParam );
				break;
			case 3301:
				{hdlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ADMINI), hWnd, (DLGPROC)DlgProc);
				if (hdlg)
				{
					//显示管理员对话框 
					ShowWindow(hdlg, SW_NORMAL);
				}}
			break;
			case 3302:
			{hdlg1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_STUDEN), hWnd, (DLGPROC)DlgProc1);
			if (hdlg1)
			{
				//显示学生对话框 
				ShowWindow(hdlg1, SW_NORMAL);
			}}
			break;
			case 3303:
			{
				h_find = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FIND), hWnd, (DLGPROC)FIND);
				if (h_find)
				{
					//显示用户删除对话框
					ShowWindow(h_find, SW_NORMAL);
				}
			}break;
			case 3304:
			{h_newbook = CreateDialog(hInst, MAKEINTRESOURCE(IDD_NEWBOOK), hWnd, (DLGPROC)NEWBOOK);
			if (h_newbook)
			{
				//显示录入书籍对话框 
				ShowWindow(h_newbook, SW_NORMAL);
			}}
			break;
			case 3305:
			{h_remove_book = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REMOVE_BOOK), hWnd, (DLGPROC)REMOVE_BOOK);
			if (h_remove_book)
			{
				//显示删除书籍对话框
				ShowWindow(h_remove_book, SW_NORMAL);
			}}
			break;
			case 3306:
			{h_record = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RECOR), hWnd, (DLGPROC)RECORD);
			if (h_record)
			{
				//显示用户注册对话框
				ShowWindow(h_record, SW_NORMAL);
			}
			}
			break;
			case 3307:
			{h_newstu = CreateDialog(hInst, MAKEINTRESOURCE(IDD_NEWSTU), hWnd, (DLGPROC)NEWSTU);
				if (h_newstu)
				{
					//显示用户注册对话框
					ShowWindow(h_newstu, SW_NORMAL);
				}
			}
			break;
			case 3308:
			{
				h_delestu = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DELESTU), hWnd, (DLGPROC)DELESTU);
				if (h_delestu)
				{
					//显示用户删除对话框
					ShowWindow(h_delestu, SW_NORMAL);
				}
			}break;
			case 3310:
			{
				h_find = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FIND), hWnd, (DLGPROC)FIND);
				if (h_find)
				{
					//显示图书查询对话框
					ShowWindow(h_find, SW_NORMAL);
				}
			}break;
			case 3311:
			{
				h_borrow = CreateDialog(hInst, MAKEINTRESOURCE(IDD_BORROW), hWnd, (DLGPROC)BORROW);
				if (h_borrow)
				{
					//显示已借书籍查询对话框
					ShowWindow(h_borrow, SW_NORMAL);
				}
			}break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			hdc = GetDC(hWnd); //获得显示上下文设备的句柄
			mdc = CreateCompatibleDC(hdc);//创建一个与指定设备兼容的内存设备上下文环境
			bg = (HBITMAP)LoadImage(NULL, _T("\\img\\zhujiemian.bmp"),IMAGE_BITMAP, 1920, 1080, LR_LOADFROMFILE);//
			SelectObject(mdc, bg);//选入设备环境
			BitBlt(hdc,0,0,1920,1080,mdc,1,1,SRCAND);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
//管理员登录框的处理
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(hdlg);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(hdlg);
		break;
	case IDOK:
	{
		HWND wel;
		TCHAR a_name[6];
		TCHAR a_pwd[20];
		char ad_name[20];
		char ad_pwd[20];
		bool bl;
		GetDlgItemText(hdlg, ID_NAME, a_name,6);
		GetDlgItemText(hdlg, IDD_PWD, a_pwd, 20);
		TcharToChar(a_name, ad_name);
		TcharToChar(a_pwd, ad_pwd);
		bl = log(hInst, ad_name, ad_pwd);
		
		if (bl == 1)
		{
			MessageBox(hdlg, L"欢迎登录，亲爱的管理员", L"Welcome", 0);
			DestroyWindow(button1);
			DestroyWindow(button2);
			DestroyWindow(button3);
			DestroyWindow(hdlg);
			CreateWindow(L"Button", L"新书入库", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 600, 300, 150, 70, hWnd, (HMENU)3304, hInst, NULL);
			CreateWindow(L"Button", L"删除书籍", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 900, 300, 150, 70, hWnd, (HMENU)3305, hInst, NULL);
			CreateWindow(L"Button", L"借还记录", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 1200, 300, 150, 70, hWnd, (HMENU)3306, hInst, NULL);
			CreateWindow(L"Button", L"学生注册", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 600, 600, 150, 70, hWnd, (HMENU)3307, hInst, NULL);
			CreateWindow(L"Button", L"学生删除", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 900, 600, 150, 70, hWnd, (HMENU)3308, hInst, NULL);
			CreateWindow(L"Button", L"逾期书籍", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 1200, 600, 150, 70, hWnd, (HMENU)3309, hInst, NULL);
		}
		else
		{
			MessageBox(hdlg,L"密码错误，请重试", L"Error", 0);
		}
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//学生登录框的处理
INT_PTR CALLBACK DlgProc1(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(hdlg1);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(hdlg1);
		break;
	case IDOK:
	{
		HWND wel;
		TCHAR a_name[50];
		TCHAR a_pwd[50];
		char ad_name[50];
		char ad_pwd[50];
		bool bl;
		GetDlgItemText(hdlg1, ID_NAME, a_name, 50);
		GetDlgItemText(hdlg1, IDD_PWD, a_pwd, 50);
		TcharToChar(a_name, ad_name);
		TcharToChar(a_pwd, ad_pwd);
		bl = log_studen(hInst, ad_name, ad_pwd);

		if (bl == 1)
		{
			MessageBox(hdlg1, L"欢迎登录图书管理系统", L"Welcome", 0);
			DestroyWindow(button1);
			DestroyWindow(button2);
			DestroyWindow(button3);
			DestroyWindow(hdlg1);
			CreateWindow(L"Button", L"图书查阅", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 600, 300, 150, 70, hWnd, (HMENU)3310, hInst, NULL);
			CreateWindow(L"Button", L"借书", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 900, 300, 150, 70, hWnd, (HMENU)3311, hInst, NULL);
			CreateWindow(L"Button", L"书籍续借", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 1200, 300, 150, 70, hWnd, (HMENU)3312, hInst, NULL);
			CreateWindow(L"Button", L"还书", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 600, 600, 150, 70, hWnd, (HMENU)3313, hInst, NULL);
		}
		else
		{
			MessageBox(hdlg1, L"密码错误，请重试", L"Error", 0);
		}
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//新书录入的对话框处理函数
INT_PTR CALLBACK NEWBOOK(HWND h_newbook, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(h_newbook);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(h_newbook);
		break;
	case IDOK:
	{
		HWND wel;
		TCHAR name[35];
		TCHAR weizhi[20];
		TCHAR author[20];
		TCHAR publicer[30];
		TCHAR info[100];
		char bname[35];
		char bweizhi[20];
		char bauthor[20];
		char bpublicer[30];
		char binfo[100];
		char* bl;
		GetDlgItemText(h_newbook, IDC_BNAME, name, 35);
		GetDlgItemText(h_newbook, IDD_SHUJIA,weizhi, 20);
		GetDlgItemText(h_newbook, IDD_ZUOZHE, author, 20);
		GetDlgItemText(h_newbook, IDD_PUBLIC, publicer, 30);
		GetDlgItemText(h_newbook, IDD_INFO, info, 100);
		TcharToChar(name, bname);
		TcharToChar(weizhi, bweizhi);
		TcharToChar(author, bauthor);
		TcharToChar(publicer,bpublicer );
		TcharToChar(info, binfo);
		
		bl = newbook(bname,bweizhi,bauthor,bpublicer,binfo);

		if (bl[0]!='\0')
		{
			CharToTchar(bl, info);
			MessageBox(h_newbook, info, L"请尽快为本书贴上id：", 0);
			DestroyWindow(hdlg);
		}
		else
		{
			MessageBox(h_newbook, L"有点问题，请重试", L"Error", 0);
		}
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//删除书籍的对话框处理函数
INT_PTR CALLBACK REMOVE_BOOK(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(hdlg1);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(hdlg1);
		break;
	case IDOK:
	{
		TCHAR id[20];;
		char c_id[20];
		bool bl;
		GetDlgItemText(hdlg1, IDC_BOOKID, id, 20);
		TcharToChar(id, c_id);
		bl = f_remove_book(h_remove_book, c_id);
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//新用户注册对话框处理函数
INT_PTR CALLBACK NEWSTU(HWND h_newstu, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(h_newstu);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(h_newstu);
		break;
	case IDOK:
	{
		TCHAR id[20];
		TCHAR name[30];
		TCHAR pwd[20];
		TCHAR pwd1[20];
		TCHAR aca[30];
		TCHAR pho[12];
		char r_id[20];
		char r_name[30];
		char r_pwd[20];
		char r_pwd1[20];
		char r_aca[30];
		char r_pho[12];
		bool bl;
		GetDlgItemText(h_newstu, IDC_ID, id, 20);
		GetDlgItemText(h_newstu, IDC_NAME, name, 30);
		GetDlgItemText(h_newstu, IDC_PWD1, pwd,20);
		GetDlgItemText(h_newstu, IDC_PWD2, pwd1, 20);
		GetDlgItemText(h_newstu, IDC_AC, aca,20);
		GetDlgItemText(h_newstu, IDC_PHONE, pho, 20);
		TcharToChar(id, r_id);
		TcharToChar(name, r_name);
		TcharToChar(pwd, r_pwd);
		TcharToChar(pwd1, r_pwd1);
		TcharToChar(aca, r_aca);
		TcharToChar(pho, r_pho);
		file = fopen("test.txt", "w+");
		fprintf(file, "%s;%s", r_pwd, r_pwd1);
		fclose(file);
		if (strcmp(r_pwd, r_pwd1)==0)
		{
			bool b = 0;
			int i = 0;
			if (strlen(r_pho) != 11) {
				MessageBox(h_newstu, L"电话号码不正确，请重试", L"Error", 0); goto l1;
			}
			for (i = 0; r_pho[i] >= '0'&&r_pho[i] <= '9'; i++)
			{

			}
			if (i != 11)
			{
				MessageBox(h_newstu, L"电话号码不正确，请重试", L"Error1", 0);
				goto l1;
			}
			else
			{
				b = log_newstu(h_newbook, r_id, r_name, r_pwd, r_aca, r_pho);
				if (b)
					MessageBox(h_newstu, L"用户注册成功", L"成功", 0);
				else
					MessageBox(h_newstu, L"出现了点问题", L"Error", 0);
			}
		}
		else
		{
			MessageBox(h_newstu, L"两次输入密码不一致，请重试", L"Error", 0);
		}
		break;
	}
	}
	}
	default:
		break;
	}
l1:return (INT_PTR)FALSE;
}
//删除用户对话框处理函数
INT_PTR CALLBACK DELESTU(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(h_delestu);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(h_delestu);
		break;
	case IDOK:
	{
		TCHAR id[20];
		char c_id[20];
		bool bl;
		GetDlgItemText(h_delestu, IDC_STUID, id, 20);
		TcharToChar(id, c_id);
		bl = f_dele_stu(h_delestu, c_id);
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//显示图书借还记录对话框
INT_PTR CALLBACK RECORD(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return 0; }
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(h_delestu);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(h_delestu);
		break;
	case IDOK:
	{
		static int k = 1;
		if (k == 1) {
			// 获取ListView控件的句柄  
			HWND hListview = GetDlgItem(h_delestu, IDC_LIST1);
			// 设置ListView的列  
			LVCOLUMN vcl;
			vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			// 第一列  
			vcl.pszText = L"借书者";//列标题  
			vcl.cx = 200;//列宽  
			vcl.iSubItem = 0;//子项索引，第一列无子项  
			ListView_InsertColumn(hListview, 0, &vcl);
			// 第二列  
			vcl.pszText = L"被借书籍";
			vcl.cx = 350;
			vcl.iSubItem = 1;//子项索引  
			ListView_InsertColumn(hListview, 1, &vcl);
			// 第三列  
			vcl.pszText = L"借书时间";
			vcl.cx = 300;
			vcl.iSubItem = 2;
			ListView_InsertColumn(hListview, 2, &vcl);
			// 第三列  
			vcl.pszText = L"状态";
			vcl.cx = 300;
			vcl.iSubItem = 3;
			ListView_InsertColumn(hListview, 3, &vcl);
			showrecord(hListview);
			k = 2;
		}
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//显示图书查询对话框
INT_PTR CALLBACK FIND(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return 0; }
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(h_delestu);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(h_delestu);
		break;
	case IDC_NAME:
	{
		{
			TCHAR name1[100];
			GetDlgItemText(h_delestu, IDC_EDIT1, name1, 50);
			char name[50];
			TcharToChar(name1, name);
			// 获取ListView控件的句柄  
			HWND hListview = GetDlgItem(h_delestu, IDC_LIST2);
				ListView_DeleteAllItems(hListview);
				static int i = 1;
				if (i)
				{// 设置ListView的列  
					LVCOLUMN vcl;
					vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
					// 第一列  
					vcl.pszText = L"书名";//列标题  
					vcl.cx = 200;//列宽  
					vcl.iSubItem = 0;//子项索引，第一列无子项  
					ListView_InsertColumn(hListview, 0, &vcl);
					// 第二列  
					vcl.pszText = L"书架";
					vcl.cx = 350;
					vcl.iSubItem = 1;//子项索引  
					ListView_InsertColumn(hListview, 1, &vcl);
					// 第三列  
					vcl.pszText = L"状态";
					vcl.cx = 550;
					vcl.iSubItem = 2;
					ListView_InsertColumn(hListview, 2, &vcl);
					i = 0;
				}
				n_show(hListview, name);
			file = fopen("tst.txt", "w+");
			fprintf(file, "%s", name);
			fclose(file);
		}}
		break;
	case IDC_INFO:
	{
		{
			TCHAR name1[100];
			GetDlgItemText(h_delestu, IDC_EDIT1, name1, 50);
			char name[50];
			TcharToChar(name1, name);
			// 获取ListView控件的句柄  
			HWND hListview = GetDlgItem(h_delestu, IDC_LIST2);
			ListView_DeleteAllItems(hListview);
			static int i = 1;
			if (i)
			{// 设置ListView的列  
				LVCOLUMN vcl;
				vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
				// 第一列  
				vcl.pszText = L"书名";//列标题  
				vcl.cx = 200;//列宽  
				vcl.iSubItem = 0;//子项索引，第一列无子项  
				ListView_InsertColumn(hListview, 0, &vcl);
				// 第二列  
				vcl.pszText = L"书架";
				vcl.cx = 350;
				vcl.iSubItem = 1;//子项索引  
				ListView_InsertColumn(hListview, 1, &vcl);
				// 第三列  
				vcl.pszText = L"状态";
				vcl.cx = 550;
				vcl.iSubItem = 2;
				ListView_InsertColumn(hListview, 2, &vcl);
				i = 0;
			}
			i_show(hListview, name);
		}}
	break;
	case IDC_AUTHOR:
	{
		{
			TCHAR name1[100];
			GetDlgItemText(h_delestu, IDC_EDIT1, name1, 50);
			char name[50];
			TcharToChar(name1, name);
			// 获取ListView控件的句柄  
			HWND hListview = GetDlgItem(h_delestu, IDC_LIST2);
			ListView_DeleteAllItems(hListview);
			static int i = 1;
			if (i)
			{// 设置ListView的列  
				LVCOLUMN vcl;
				vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
				// 第一列  
				vcl.pszText = L"书名";//列标题  
				vcl.cx = 200;//列宽  
				vcl.iSubItem = 0;//子项索引，第一列无子项  
				ListView_InsertColumn(hListview, 0, &vcl);
				// 第二列  
				vcl.pszText = L"书架";
				vcl.cx = 350;
				vcl.iSubItem = 1;//子项索引  
				ListView_InsertColumn(hListview, 1, &vcl);
				// 第三列  
				vcl.pszText = L"状态";
				vcl.cx = 550;
				vcl.iSubItem = 2;
				ListView_InsertColumn(hListview, 2, &vcl);
				i = 0;
			}
			a_show(hListview, name);
		}}
	break;
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
//借阅书籍的对话框处理函数
INT_PTR CALLBACK BORROW(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			DestroyWindow(hdlg1);
		}
		break;
	case WM_COMMAND:
	{int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDCANCEL:
		DestroyWindow(hdlg1);
		break;
	case IDOK:
	{
		TCHAR id[20];;
		char c_id[20];
		bool bl;
		GetDlgItemText(hdlg1, IDC_BID, id, 20);
		TcharToChar(id, c_id);
		bl = borrow_book(h_borrow, c_id,stu_id);
		break;
	}
	}
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}