#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include "Tourism.h"

using namespace std;

Graph MGraph;

int main()
{
	cout << "山城的夜景，不负千里迢迢的路程" << endl;
	cout << "山城的浪漫，至死不“渝”" << endl;
	cout << "吹吹嘉陵江的晚风，走走南滨路，感受山城的热情！" << endl;

	int choice = 0;
	while (choice != 6) {
		cout << "\n山城重庆欢迎您的到来！" << endl;
		cout << "===旅游信息管理系统===" << endl;
		cout << "1. 创建景点图" << endl;
		cout << "2. 查询景点信息" << endl;
		cout << "3. 旅游线路规划" << endl;
		cout << "4. 最短路线导航" << endl;
		cout << "5. 轻轨建设规划" << endl;
		cout << "6. 退出系统" << endl;
		cout << "======================"<<endl;
		cout << "请输入选项：";
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
			cout << "已退出系统，感谢您的使用！" << endl;
			break;
		default:
			cout << "输入序号错误，请重新输入！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}