#pragma once
bool log(HINSTANCE hInst, char name[],char a_pwd[]);//����Ա��¼��������
void TcharToChar(TCHAR * tchar, char * _char);//�ַ���ת����������
void CharToTchar(const char * _char, TCHAR * tchar);//�ַ���ת���ַ�
bool log_studen(HINSTANCE hInst, char name[], char pwd[]);//ѧ����¼��������
INT_PTR CALLBACK Dlgwel(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);//����Ա��¼
INT_PTR CALLBACK DlgProc1(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//ѧ����¼
LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK NEWBOOK(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//������⴦����
char * newbook(char name[], char weizhi[], char author[], char publicer[], char info[]);//������⺯��
INT_PTR CALLBACK REMOVE_BOOK(HWND h_remove_book, UINT msg, WPARAM wParam, LPARAM lParam);//ɾ���鼮���ڹ��̺���
bool f_remove_book(HWND h_remove_book, char id[]);//ɾ���鼮����
INT_PTR CALLBACK NEWSTU(HWND h_newstu, UINT msg, WPARAM wParam, LPARAM lParam);//�û�ע�ᴰ�ڴ�����
bool log_newstu(HWND h_newbook, char id[], char name[], char pwd[], char aca[], char pho[]);//�û�ע�ắ��
INT_PTR CALLBACK DELESTU(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//ɾ���û��Ի�������
bool f_dele_stu(HWND h_remove_book, char id[]);//�û�ɾ������
INT_PTR CALLBACK RECORD(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam);//ͼ��軹��¼���ڴ�����
void showrecord(HWND);//�軹��¼����
INT_PTR CALLBACK FIND(HWND h_delestu, UINT msg, WPARAM wParam, LPARAM lParam);//ͼ���ѯ���ڴ�����
void n_show(HWND ,char name[]);//������ȥ��ѯ
void i_show(HWND hListview, char name[]);//����Ϣ��ѯ
void a_show(HWND hListview, char name[]);//�����߲�ѯ
INT_PTR CALLBACK BORROW(HWND hdlg1, UINT msg, WPARAM wParam, LPARAM lParam);//�����鼮�ĶԻ�������
bool borrow_book(HWND h_remove_book, char id[], char stu[]);//ͼ����ĺ���
