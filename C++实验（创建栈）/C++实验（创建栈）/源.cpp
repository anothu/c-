#include <iostream>
#include"stack.h";
using namespace std;
int main()
{
	Istack<char> sta;
	int choice;
	menu();
	while (true)
	{
		cout << "���������ѡ��:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			char n;
			cout << "������Ҫ��ջ��Ԫ��:" << endl;
			cin >> n;
			sta.Push(n);
			break;
		case 2:
			sta.Pop();
			break;
		case 3:
			if (sta.Empty())
				cout << "��ʱջΪ��!" << endl;
			else
				cout << "ջ��Ԫ��Ϊ:" << sta.GetTop();
			break;
		case 4:
			if (sta.Empty())
				cout << "��ʱջΪ��!" << endl;
			else
				cout << "ջ��Ϊ��!" << endl;
			break;
		case 5:
			cout << "ջ��Ԫ�ظ���Ϊ:" << sta.Size() << endl;
			break;
		case 6:
			sta.ClearStack();
			cout << "ջ�����" << endl;
			break;
		}
	}
}
