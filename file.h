#pragma once
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace std;

//����ļ��Ĵ�С �����ֽ���Ŀ
int getFileSize(char *filePath)
{
	struct _stat info;
	_stat(filePath, &info);
	int size = info.st_size;
	cout << "size=" << size;
	return size;
}

//�����ļ� ���ļ���srcFileת����destFile
int myMoveFile(char *srcFile, char *destFile)
{
		DWORD getlastError;
		if (!MoveFile(srcFile, destFile))
		{
			
			getlastError = GetLastError();
			printf_s("�ļ�����ʧ�� Error: %d\n", getlastError);
			return -1;
		}
		return 0;
}