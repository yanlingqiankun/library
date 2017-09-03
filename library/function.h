#pragma once
bool log(HINSTANCE hInst, char name[],char a_pwd[]);//管理员登录函数声明
void TcharToChar(TCHAR * tchar, char * _char);//字符串转换函数声明
void CharToTchar(const char * _char, TCHAR * tchar);//字符串转宽字符
bool log_studen(HINSTANCE hInst, char name[], char pwd[]);//学生登录函数声明
INT_PTR CALLBACK Dlgwel(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);//管理员登录
INT_PTR CALLBACK DlgProc1(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//学生登录
LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NEWBOOK(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//新书入库处理函数
char * newbook(char name[], char weizhi[], char author[], char publicer[], char info[]);//新书入库函数
INT_PTR CALLBACK REMOVE_BOOK(HWND h_remove_book, UINT msg, WPARAM wParam, LPARAM lParam);//删除书籍窗口过程函数
bool f_remove_book(HWND h_remove_book, char id[]);//删除书籍函数
INT_PTR CALLBACK NEWSTU(HWND h_newstu, UINT msg, WPARAM wParam, LPARAM lParam);//用户注册窗口处理函数
bool log_newstu(HWND h_newbook, char id[], char name[], char pwd[], char aca[], char pho[]);//用户注册函数
INT_PTR CALLBACK DELESTU(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//删除用户对话框处理函数
bool f_dele_stu(HWND h_remove_book, char id[]);//用户删除函数
INT_PTR CALLBACK RECORD(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam);//图书借还记录窗口处理函数
void showrecord(HWND);//借还记录函数
INT_PTR CALLBACK FIND(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam);//图书查询窗口处理函数
void n_show(HWND ,char name[]);//按书名去查询
void i_show(HWND hListview, char name[]);//按信息查询
void a_show(HWND hListview, char name[]);//按作者查询
INT_PTR CALLBACK BORROW(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//借阅书籍的对话框处理函数
bool borrow_book(HWND h_remove_book, char id[], char stu[]);//图书借阅函数
