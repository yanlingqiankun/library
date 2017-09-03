#include"stdafx.h"
#pragma comment(lib,"libmysql.lib")

using namespace std;

FILE * fp;//便于测试程序运行到某处
extern char stu_id[100];

//宽字符宽字符
void TcharToChar (TCHAR * tchar, char * _char)
{
	int iLength ;
	//获取字节长度    
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char     
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

//字符转宽字符
void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

//管理员登录函数
bool log(HINSTANCE hInst, char name[],char pwd[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	bool bl = false;
	char  query[50] = "select * from l_administrator where a_id=\'" ;
	char query1[5] = "\'";
	strcat(query, name);
	strcat(query, query1);
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	re = mysql_query(&sql,query);
	if (!re)
	{
		result = mysql_store_result(&sql);
		
		if (result)
		{
			while (row = mysql_fetch_row(result))
			{
				if (strcmp(row[2], pwd) == 0)
					bl=true;
				else
				{
					bl = false;
				}
			}
		}
	}
	return bl;
}
//学生登录函数
bool log_studen(HINSTANCE hInst, char name[], char pwd[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	bool bl = false;
	char  query[50] = "select * from reader where r_id=\'";
	char query1[5] = "\'";
	strcat(query, name);
	strcat(query, query1);
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	re = mysql_query(&sql, query);
	if (!re)
	{
		result = mysql_store_result(&sql);

		if (result)
		{
			while (row = mysql_fetch_row(result))
			{
				if (strcmp(row[2], pwd) == 0)
				{
					bl = true;
					strcpy(stu_id, row[0]);
				}
				else
				{
					bl = false;
				}
			}
		}
	}
	return bl;
}
//录入新书的函数
char * newbook(char name[], char weizhi[], char author[], char publicer[], char info[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	char id[11];
	char bl = '\0';
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	re = mysql_query(&sql, "select unix_timestamp()");
	if (!re)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			while (row = mysql_fetch_row(result))
			{
				strcpy(id, row[0]);
			}
		}
	}
	if (name[0] == '\0' || weizhi[0] == '\0' || author[0] == '\0' || publicer[0] == '\0')
		return &bl;
	char query[500]="insert into book (b_id,b_name,b_bkcaseid,b_author,b_info,b_public)values(\'";
	char query1[5] = "\',\'";
	char query2[5] = "\')";
	strcat(query, id);
	strcat(query, query1);
	strcat(query, name);
	strcat(query, query1);
	strcat(query, weizhi);
	strcat(query, query1);
	strcat(query, author);
	strcat(query, query1);
	strcat(query, info);
	strcat(query, query1);
	strcat(query, publicer);
	strcat(query, query2);
	re = mysql_query(&sql, query);
	if (!re)
	{
		char query3[50] = "update book set b_state=1 where b_id=\'";
		char query4[5] = "\'";
		strcat(query3, id);
		strcat(query3, query4);
		mysql_query(&sql,query3);
		return id;
	}
	else return &bl;
}
//图书移除函数
bool f_remove_book(HWND h_remove_book, char id[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	char bl[50] = "delete from book where b_id=\'";
	TCHAR str[50] ;
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	char query[50] = "select b_name from book where b_id=\'";
	char query1[6] = "\'";
	strcat(query, id);
	strcat(query, query1);
	strcat(bl, id);
	strcat(bl, query1);
	re = mysql_query(&sql, query);
	if (!re)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			if(row = mysql_fetch_row(result))
			{
				CharToTchar(row[0], str);
				if (IDOK == MessageBox(h_remove_book, str, L"确定删除该书？", MB_OKCANCEL))
				{
					mysql_query(&sql, bl);
					MessageBox(h_remove_book, L"该书已经移除", L"删除成功", 0);
					return 1;
				}
				else
					MessageBox(h_remove_book, L"已取消", L"未删除", 0);
					return 0;
			}
			else
			{
				MessageBox(h_remove_book, L"未找到该书", L"Error", 0);
				return 0;
			}
		}
	}
	else
	{
		MessageBox(h_remove_book, L"出了点问题，请一会再试", L"Error", 0);
		return 0;
	}
}
//学生注册函数
bool log_newstu(HWND h_newbook, char id[], char name[], char pwd[], char aca[], char pho[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	char query[500] = "insert into reader values (\'";
	char query1[10] = "\',\'";
	char query2[10] = "\')";
	char query3[80] = "select * from reader where r_id=\*";
	strcat(query, id);
	strcat(query, query1);
	strcat(query, name);
	strcat(query, query1);
	strcat(query, pwd);
	strcat(query, query1);
	strcat(query, aca);
	strcat(query, query1);
	strcat(query, pho);
	strcat(query, query2);
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	strcat(query3, id);
	strcat(query3, query2);
	re = mysql_query(&sql, query3);
	if (!re)
	{
		MessageBox(h_newbook, L"该用户已存在", L"error", 0);
		return 0;
	}
	re = mysql_query(&sql, query);
	return 1;
}
//用户删除函数
bool f_dele_stu(HWND h_remove_book, char id[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	char bl[50] = "delete from reader where r_id=\'";
	TCHAR str[50];
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	char query[50] = "select r_name from reader where r_id=\'";
	char query1[6] = "\'";
	strcat(query, id);
	strcat(query, query1);
	strcat(bl, id);
	strcat(bl, query1);
	re = mysql_query(&sql, query);
	if (!re)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			if (row = mysql_fetch_row(result))
			{
				CharToTchar(row[0], str);
				if (IDOK == MessageBox(h_remove_book, str, L"确定删除该用户？", MB_OKCANCEL))
				{
					mysql_query(&sql, bl);
					MessageBox(h_remove_book, L"该用户已经移除", L"删除成功", 0);
					return 1;
				}
				else
					MessageBox(h_remove_book, L"已取消", L"未删除", 0);
				return 0;
			}
			else
			{
				MessageBox(h_remove_book, L"未找到该用户", L"Error", 0);
				return 0;
			}
		}
	}
	else
	{
		MessageBox(h_remove_book, L"出了点问题，请一会再试", L"Error", 0);
		return 0;
	}
}
//显示借还记录
void showrecord(HWND hListview) 
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result,* result1,* result2;
	MYSQL_ROW row,row1,row2;
	int re1,re2,re3;
	TCHAR str[50];
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	re1 = mysql_query(&sql, "select re_readerid,re_bookid,re_date,re_state from record");
	if (!re1)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			LVITEM vitem;
			vitem.mask = LVIF_TEXT;
			for(int i=0;row=mysql_fetch_row(result);i++)
			{
				char q1[50] = "select r_name from reader where r_id=\'";
				char q2[50] = "select b_name from book where b_id=\'";
				char q3[10] = "\'";
				strcat(q1, row[0]);
				strcat(q1, q3);
				strcat(q2, row[1]);
				strcat(q2, q3);
				TCHAR r_name[50];
				TCHAR b_name[50];
				TCHAR time[50];
				re2 = mysql_query(&sql, q1);
				if (!re2)
				{
					result1 = mysql_store_result(&sql);
					if (result1)
					{
						while (row1 = mysql_fetch_row(result1))
						{
							CharToTchar(row1[0], r_name);
						}
					}
				}
				re3 = mysql_query(&sql, q2);
				if (!re3)
				{
					result2 = mysql_store_result(&sql);
					if (result2)
					{
						while (row2 = mysql_fetch_row(result2))
						{
							CharToTchar(row2[0], b_name);
						}
					}
				}
				CharToTchar(row[2], time);
				{vitem.pszText =r_name;
				vitem.iItem = i;
				vitem.iSubItem = 0;
				ListView_InsertItem(hListview, &vitem);
				// 设置子项 
				vitem.iSubItem = 1;
				vitem.pszText = b_name;
				ListView_SetItem(hListview, &vitem);
				vitem.iSubItem = 2;
				vitem.pszText = time;
				ListView_SetItem(hListview, &vitem); 
				if (row[3][0] == '1') {
					vitem.iSubItem = 3;
					vitem.pszText = L"已还";
					ListView_SetItem(hListview, &vitem);
				}
				else {
					vitem.iSubItem = 3;
					vitem.pszText = L"未还";
					ListView_SetItem(hListview, &vitem);
				}
				}
			}
		}
	}
	mysql_free_result(result);
}
//按书名查询函数
void n_show(HWND hListview, char name[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result, *result1, *result2;
	MYSQL_ROW row, row1, row2;
	int re1, re2, re3;
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	char query[100] = "select b_name,b_bkcaseid,b_state from book where b_name like \'%";
	char query1[10] = "%\'";
	strcat(query, name);
	strcat(query, query1);
	re1 = mysql_query(&sql, query);
	if (!re1)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			LVITEM vitem;
			vitem.mask = LVIF_TEXT;
			for (int i = 0; row = mysql_fetch_row(result);i++)
			{
				TCHAR name[100];
				TCHAR shujia[20];
				CharToTchar(row[0], name);
				CharToTchar(row[1], shujia);
				vitem.pszText = name;
				vitem.iItem = i;
				vitem.iSubItem = 0;
				ListView_InsertItem(hListview, &vitem);
				// 设置子项 
				vitem.iSubItem = 1;
				vitem.pszText = shujia;
				ListView_SetItem(hListview, &vitem);
				if (row[2][0] == '1') {
					vitem.iSubItem = 2;
					vitem.pszText = L"在书架";
					ListView_SetItem(hListview, &vitem);
				}
				else {
					vitem.iSubItem = 2;
					vitem.pszText = L"被借走";
					ListView_SetItem(hListview, &vitem);
				}
			}
		}
	}
}
//按介绍查询函数
void i_show(HWND hListview, char name[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result, *result1, *result2;
	MYSQL_ROW row, row1, row2;
	int re1, re2, re3;
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	char query[100] = "select b_name,b_bkcaseid,b_state from book where b_info like \'%";
	char query1[10] = "%\'";
	strcat(query, name);
	strcat(query, query1);
	re1 = mysql_query(&sql, query);
	if (!re1)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			LVITEM vitem;
			vitem.mask = LVIF_TEXT;
			for (int i = 0; row = mysql_fetch_row(result); i++)
			{
				TCHAR name[100];
				TCHAR shujia[20];
				CharToTchar(row[0], name);
				CharToTchar(row[1], shujia);
				vitem.pszText = name;
				vitem.iItem = i;
				vitem.iSubItem = 0;
				ListView_InsertItem(hListview, &vitem);
				// 设置子项 
				vitem.iSubItem = 1;
				vitem.pszText = shujia;
				ListView_SetItem(hListview, &vitem);
				if (row[2][0] == '1') {
					vitem.iSubItem = 2;
					vitem.pszText = L"在书架";
					ListView_SetItem(hListview, &vitem);
				}
				else {
					vitem.iSubItem = 2;
					vitem.pszText = L"被借走";
					ListView_SetItem(hListview, &vitem);
				}
			}
		}
	}
}
//按作者查询
void a_show(HWND hListview, char name[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result, *result1, *result2;
	MYSQL_ROW row, row1, row2;
	int re1, re2, re3;
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	char query[100] = "select b_name,b_bkcaseid,b_state from book where b_author like \'%";
	char query1[10] = "%\'";
	strcat(query, name);
	strcat(query, query1);
	fp = fopen("test.txt", "w+");
	fprintf(fp, "%s", query);
	fclose(fp);
	re1 = mysql_query(&sql, query);
	if (!re1)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			LVITEM vitem;
			vitem.mask = LVIF_TEXT;
			for (int i = 0; row = mysql_fetch_row(result); i++)
			{
				TCHAR name[100];
				TCHAR shujia[20];
				CharToTchar(row[0], name);
				CharToTchar(row[1], shujia);
				vitem.pszText = name;
				vitem.iItem = i;
				vitem.iSubItem = 0;
				ListView_InsertItem(hListview, &vitem);
				// 设置子项 
				vitem.iSubItem = 1;
				vitem.pszText = shujia;
				ListView_SetItem(hListview, &vitem);
				if (row[2][0] == '1') {
					vitem.iSubItem = 2;
					vitem.pszText = L"在书架";
					ListView_SetItem(hListview, &vitem);
				}
				else {
					vitem.iSubItem = 2;
					vitem.pszText = L"被借走";
					ListView_SetItem(hListview, &vitem);
				}
			}
		}
	}
}
bool borrow_book(HWND h_remove_book, char id[],char stu_id[])
{
	mysql_library_init(NULL, 0, 0);
	MYSQL sql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	int re;
	char bl[50] = "update book set b_state=0 where b_id=\'";
	TCHAR str[50];
	mysql_init(&sql);
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_real_connect(&sql, "localhost", "zuyi", "183208", "library", 3306, NULL, CLIENT_MULTI_STATEMENTS);
	mysql_query(&sql, "set character set gbk");
	char query[50] = "select b_name from book where b_id=\'";
	char query1[6] = "\'";
	char query2[100] = "insert into record (re_bookid,re_readerid,re_state) values (\'";
	char query3[10] = "\',\'";
	char query5[10] = "0";
	char query4[10] = "\')";
	strcat(query2, id);
	strcat(query2, query3);
	strcat(query2, stu_id);
	strcat(query2, query3);
	strcat(query2, query5);
	strcat(query2, query4);
	fp = fopen("test.txt", "w+");
	fprintf(fp, "%s", query2);
	fclose(fp);
	strcat(query, id);
	strcat(query, query1);
	strcat(bl, id);
	strcat(bl, query1);
	re = mysql_query(&sql, query);
	if (!re)
	{
		result = mysql_store_result(&sql);
		if (result)
		{
			if (row = mysql_fetch_row(result))
			{
				CharToTchar(row[0], str);
				if (IDOK == MessageBox(h_remove_book, str, L"确定借阅该书？", MB_OKCANCEL))
				{
					mysql_query(&sql, bl);
					mysql_query(&sql, query2);
					MessageBox(h_remove_book, L"该书已经借阅", L"借阅成功", 0);
					return 1;
				}
				else
					MessageBox(h_remove_book, L"已取消", L"未借阅", 0);
				return 0;
			}
			else
			{
				MessageBox(h_remove_book, L"未找到该书", L"Error", 0);
				return 0;
			}
		}
	}
	else
	{
		MessageBox(h_remove_book, L"出了点问题，请一会再试", L"Error", 0);
		return 0;
	}
}