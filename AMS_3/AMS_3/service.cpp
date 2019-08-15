#include"stdafx.h"
#include <string>
#include <iostream>
#include"cardList.h"
#include"moneyList.h"
#include "menu.h"
#include"model.h"
#include "global.h"
#include"tool.h"
#include<fstream>
#include"billList.h"
#include"service.h"

using namespace std;

void addCard(CardNode** ppCardNodeHead,MoneyNode** ppMoneyNodeHead)
{
	string strNo;
	string strPwd;
	float fBalance;
	if (inputNoPwdBalance(strNo, strPwd, fBalance))//���뿨�ţ����룬���
	{
		int nResult = addNewCard(strNo, strPwd, fBalance, ppCardNodeHead, ppMoneyNodeHead);//����¿�
		switch (nResult)
		{
		case FINDCARD:
		{
			cout << endl << endl << "���� " << strNo << "���Ѿ����ڣ�����¿�ʧ�ܣ� " << endl << endl;
			break;
		}
		case SUCCESS:
		{
			cout << endl << endl << "����¿��ɹ�!" << endl << endl;
			cout << "�¿����ţ� " << strNo << endl;
			cout << "�¿��� " << fBalance << endl;
			break;
		}
		default:
		{
			cout << endl << endl << "ϵͳ����!" << endl << endl;
			break;
		}
		}
	}
	else
	{
		cout << endl << endl << "����ġ����ţ����룬������Ϣ��ʽ������Ҫ��			��ӿ�ʧ��!" << endl << endl;
	}
}

void queryCard(CardNode* const pCardNodeHead)
{
	displayCard(pCardNodeHead);
}

void clearData(CardNode* pCardNodeHead)
{
	CardNode *pCardNode;
	while (pCardNodeHead != NULL)
	{
		pCardNode = pCardNodeHead;
		pCardNodeHead = pCardNodeHead->next;
		delete pCardNode;
	}//�������ͷ��ʼɾ������
}

void logout(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	string strNo;
	string strPwd;

	MoneyInfo* pInfo = new MoneyInfo;

	if (inputNoPwd(strNo, strPwd)) {
		cout << "----------ע����Ϣ����----------\n";

		int nResult = annulCard(strNo, strPwd, pInfo, pCardNodeHead, ppMoneyNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
			cout << endl << endl << "�������ڣ�����Ϣ���ԣ�ע��ʧ��" << endl << endl;
			break;
		case SUCCESS:
			cout << endl;
			cout << "����: \t" << strNo << endl;;
			cout << "�˿���: \t" << pInfo->fMoney << endl;
			break;
		case USING:
			cout << endl << "�ÿ������ϻ�������ע����" << endl;
			break;
		case INVALID:
			cout << endl << "���Ѿ�ע�����ˣ�";
			break;
		default:
			break;
		}
	}
	else {
		cout << endl << endl << "���Ż������ʽ����ȷ��ע��ʧ�ܣ�" << endl << endl;
	}

	delete pInfo;

}

void statistics(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead, MoneyNode* pMoneyNodeHead) {
	char selection;

	cout << endl;
	cout << "�ﻶӭ�����ѯͳ��ϵͳ��" << endl;
	cout << endl;

	do
	{
		outputStatisticsMenu();

		selection = 'a';
		cin >> selection;
		cin.ignore(1000, '\n'); //��ռ��̻�����

		switch (selection)
		{
		case'1':
		{
			cout << endl << "-------�������--------" << endl << endl;
			aboutCard(pCardNodeHead, pBillingNodeHead, pMoneyNodeHead);
			break;
		}
		case'2':
		{
			cout << endl << "-------�ϻ��»����--------" << endl << endl;
			searchBilling( pCardNodeHead, pBillingNodeHead);
			break;
		}
		case'3':
		{
			cout << endl << "-------��ֵ�˷����--------" << endl << endl;
			aboutMoney(pCardNodeHead, pBillingNodeHead, pMoneyNodeHead);
			break;
		}
		case'0':
		{
			cout << endl << "��ɲ�ѯͳ�ƹ�����" << endl << endl;
			break;
		}
		default:
		{
			cout << "����ı�Ŵ���" << endl;
			break;
		}
		}
		cout << endl;
	} while (selection != '0');

}

void aboutCard(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead, MoneyNode* pMoneyNodeHead) {
	cout << "----------���Ŵ��������Ϣ����----------\n";

	string t0, t1;

	cout << endl << "�������ѯʱ���(��ʼ,��%d-%d-%d-%d:%d)��";
	cin >> t0;
	time_t tbegin = stringToTime(const_cast<char*>(t0.c_str()));//stringΪconst char* 
	if (tbegin == -1) {
		cout << endl << "�����ʽ����" << endl;
		return;
	}

	cout << endl << "�������ѯʱ���(����,��%d-%d-%d-%d:%d)��";
	cin >> t1;
	time_t tover = stringToTime(const_cast<char*>(t1.c_str()));
	if (tover == -1) {
		cout << endl << "�����ʽ����" << endl;
		return;
	}

	CardNode* pCardNode = pCardNodeHead;
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	int sum = 0;

	cout << endl << endl << "����\t����ʱ��\tʹ�ô���\t���ʹ��ʱ��\t���\n" << endl << endl;
	while (pCardNode != NULL)// ѭ��ֱ��card������
	{
		if (pCardNode->data.tStart >= tbegin && pCardNode->data.tStart <= tover) //�������ʱ���ڼ���ʱ��֮��
		{
			timeToString(pCardNode->data.tStart, aStartTime);
			timeToString(pCardNode->data.tLast, aEndTime);
			cout << pCardNode->data.aName << "\t" << aStartTime << "\t"
				<< pCardNode->data.nUseCount << "\t" << aEndTime << "\t"
				<< pCardNode->data.fBalance << endl;
			sum++;//ͳ�ƿ�������
		}
		pCardNode = pCardNode->next;
	}
	cout << endl << endl << "�ܿ�������Ϊ��" << sum << "��" << endl;
}

void aboutMoney(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead, MoneyNode* pMoneyNodeHead) {
	cout << "----------��ֵ�˷������Ϣ����----------\n";

	string t0, t1;

	cout << endl << "�������ѯʱ���(��ʼ,��%d-%d-%d-%d:%d)��";
	cin >> t0;
	time_t tbegin = stringToTime(const_cast<char*>(t0.c_str()));//stringΪconst char* 
	if (tbegin == -1) {
		cout << endl << "�����ʽ����" << endl;
		return;
	}

	cout << endl << "�������ѯʱ���(����,��%d-%d-%d-%d:%d)��";
	cin >> t1;
	time_t tover = stringToTime(const_cast<char*>(t1.c_str()));
	if (tover == -1) {
		cout << endl << "�����ʽ����" << endl;
		return;
	}

	MoneyNode* pMoneyNode = pMoneyNodeHead;
	char aTime[TIMELENGTH] = { 0 };
	//char aEndTime[TIMELENGTH] = { 0 };
	float sum1 = 0;
	float sum2 = 0;

	cout << endl << endl << "����\t��ֵ�˷�ʱ��\t��ֵ(0)���˷�(1)\t��ֵ�˷ѽ��\n" << endl << endl;
	while (pMoneyNode != NULL) {
		if (pMoneyNode->data.tTime >= tbegin && pMoneyNode->data.tTime <= tover) {
			timeToString(pMoneyNode->data.tTime, aTime);
			cout << pMoneyNode->data.aCardName << "\t" << aTime << "\t"
				<< pMoneyNode->data.nStatus << "\t\t" << pMoneyNode->data.fMoney << "\t" << endl;
			if (pMoneyNode->data.nStatus == 0) {
				sum1 += pMoneyNode->data.fMoney;
			}
			else {
				sum2 += pMoneyNode->data.fMoney;
			}
		}
		pMoneyNode = pMoneyNode->next;
	}
	cout << endl << endl << "�ܳ�ֵ��Ϊ��" << sum1 << "Ԫ" << endl;
	cout << endl << endl << "���˷Ѷ�Ϊ��" << sum2 << "Ԫ" << endl;
}





