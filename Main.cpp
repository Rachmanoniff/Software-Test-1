#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include "Tourism.h"

using namespace std;

Graph MGraph;

int main()
{
	cout << "ɽ�ǵ�ҹ��������ǧ��������·��" << endl;
	cout << "ɽ�ǵ����������������塱" << endl;
	cout << "�������꽭����磬�����ϱ�·������ɽ�ǵ����飡" << endl;

	int choice = 0;
	while (choice != 6) {
		cout << "\nɽ�����컶ӭ���ĵ�����" << endl;
		cout << "===������Ϣ����ϵͳ===" << endl;
		cout << "1. ��������ͼ" << endl;
		cout << "2. ��ѯ������Ϣ" << endl;
		cout << "3. ������·�滮" << endl;
		cout << "4. ���·�ߵ���" << endl;
		cout << "5. ��콨��滮" << endl;
		cout << "6. �˳�ϵͳ" << endl;
		cout << "======================"<<endl;
		cout << "������ѡ�";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			CreateGraph();
			break;
		case 2:
			GetSpotInfo();
			break;
		case 3:
			TravelPath();
			break;
		case 4:
			FindShortPath();
			break;
		case 5:
			DesignPath();
			break;
		case 6:
			cout << "���˳�ϵͳ����л����ʹ�ã�" << endl;
			break;
		default:
			cout << "������Ŵ������������룡" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}