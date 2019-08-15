
#include "stdafx.h"
#include"menu.h"
#include"tool.h"
#include"service.h"
#include<iostream>
#include"model.h"
#include <string> 
#include <stdio.h>
#include "global.h"
#include<fstream>
#include"cardList.h"
#include"billList.h"
using namespace std;

MoneyNode* MoneyListInit(const string billingFilename)
{
	ifstream moneyfile(billingFilename);
	MoneyNode *pMoneyNode, *pMoneyNodeHead, *pMoneyNodeTail;
	Money money;
	if (!moneyfile.is_open())
	{
		return NULL;
	}
	pMoneyNodeHead = NULL;
	pMoneyNodeTail = NULL;
	while (1)
	{
		moneyfile.read((char*)&money, sizeof(Money));
		if (moneyfile.eof())
		{
			break;
		}
		pMoneyNode = new MoneyNode;
		pMoneyNode->data = money;
		if (pMoneyNodeHead == NULL)
		{
			pMoneyNodeHead = pMoneyNode;
			pMoneyNodeTail = pMoneyNode;
		}
		else
		{
			pMoneyNodeTail->next = pMoneyNode;
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
	}
	pMoneyNodeTail->next = NULL;

	moneyfile.close();

	return pMoneyNodeHead;
}//���ļ�������money�������ر�ͷ

bool saveMoney(const Money* pBill, const string pPath)
{
	ofstream ofile(pPath, ios::binary | ios::app);
	ofile.write((char*)pBill, sizeof(Money));
	ofile.close();
	return true;
}

int recharge(string strNo, string strPwd, float fMoney, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	Money money;
	int nCardIndex;
	Card *pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);

	if (pCard == NULL) {
		return NOFINDCARD;
	}

	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0) {
		return NOMATCH;
	}

	if (pCard->nStatus == INVALID) {
		return INVALID;
	}

	pCard->fBalance += fMoney;
	pCard->fTotalUse += fMoney;

	//�����ļ��еĿ���Ϣ
	updateCard(pCard, CARDPATH, nCardIndex);
	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 0;
	money.fMoney = fMoney;
	money.nDel = 0;

	saveMoney(&money, MONEYPATH);//����money��Ϣ��dat��

	MoneyNode *pMoneyNode = new MoneyNode;
	pMoneyNode->data = money;
	MoneyNode* pMoneyNodeTail = *ppMoneyNodeHead;

	if (*ppMoneyNodeHead == NULL) {
		*ppMoneyNodeHead = pMoneyNode;
		pMoneyNodeTail = pMoneyNode;
	}
	else {
		while (pMoneyNodeTail->next != NULL) {
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
		pMoneyNodeTail->next = pMoneyNode;
		pMoneyNodeTail = pMoneyNodeTail->next;
	}
	pMoneyNodeTail->next = NULL;
	//����Ϣ������pinfo��
	strcpy_s(pInfo->aCardName, strNo.c_str());
	pInfo->fMoney = money.fMoney;
	pInfo->fBalance = pCard->fBalance;

	return SUCCESS;
}

int returnMoney(string strNo, string strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	Money money;
	int nCardIndex;
	Card *pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);

	if (pCard == NULL) {
		return NOFINDCARD;
	}

	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0) {
		return NOMATCH;
	}

	if (pCard->nStatus == INVALID) {
		return INVALID;
	}

	if (pCard->nStatus == USING) {
		return USING;
	}

	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 1;
	money.fMoney = pCard->fBalance;
	money.nDel = 0;

	saveMoney(&money, MONEYPATH);

	MoneyNode *pMoneyNode = new MoneyNode;
	pMoneyNode->data = money;

	MoneyNode* pMoneyNodeHead = *ppMoneyNodeHead;
	MoneyNode* pMoneyNodeTail = *ppMoneyNodeHead;

	if (pMoneyNodeHead == NULL) {
		pMoneyNodeHead = pMoneyNode;
		pMoneyNodeTail = pMoneyNode;
	}
	else {
		while (pMoneyNodeTail->next != NULL) {
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
		pMoneyNodeTail->next = pMoneyNode;
		pMoneyNodeTail = pMoneyNodeTail->next;
	}
	pMoneyNodeTail->next = NULL;

	pCard->fBalance = 0;
	pCard->fTotalUse -= money.fMoney;

	//�����ļ��еĿ���Ϣ
	updateCard(pCard, CARDPATH, nCardIndex);

	strcpy_s(pInfo->aCardName, strNo.c_str());
	pInfo->fMoney = money.fMoney;
	pInfo->fBalance = pCard->fBalance;

	return SUCCESS;
}

void addMoney(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	string strNo;
	string strPwd;
	float fMoney;

	MoneyInfo* pInfo = new MoneyInfo;

	if (inputNoPwdBalance(strNo, strPwd, fMoney)) {
		cout << "----------��ֵ��Ϣ����----------\n";

		int nResult = recharge(strNo, strPwd, fMoney, pInfo, pCardNodeHead, ppMoneyNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
			cout << endl << endl << "�������ڣ�����Ϣ���ԣ���ֵʧ��" << endl << endl;
			break;
		case SUCCESS:
			cout << endl;
			cout << "����: \t" << strNo << endl;;
			cout << "��ֵ���: \t" << pInfo->fMoney << endl;
			cout << "��\t" << pInfo->fBalance << endl;
			break;
		case INVALID:
			cout << endl << "�ÿ���ע�������ܳ�ֵ��" << endl;
			break;
		default:
			break;
		}
	}
	else {
		cout << endl << endl << "���Ż������ʽ����ȷ����ֵʧ�ܣ�" << endl << endl;
	}

	delete pInfo;

}

void refundMoney(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	string strNo;
	string strPwd;

	MoneyInfo* pInfo = new MoneyInfo;

	if (inputNoPwd(strNo, strPwd)) {
		cout << "----------�˷���Ϣ����----------\n";

		int nResult = returnMoney(strNo, strPwd, pInfo, pCardNodeHead, ppMoneyNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
			cout << endl << endl << "�������ڣ�����Ϣ���ԣ��˷�ʧ��" << endl << endl;
			break;
		case SUCCESS:

			cout << endl;
			cout << "����: \t" << strNo << endl;;
			cout << "�˷ѽ��: \t" << pInfo->fMoney << endl;
			cout << "��\t" << pInfo->fBalance << endl;

			break;
		case INVALID:
			cout << endl << "�ÿ���ע���������˷ѣ�" << endl;
			break;
		case USING:
			cout << endl << "�ÿ������ϻ��������˷ѣ�" << endl;
			break;
		default:
			break;
		}
	}
	else {
		cout << endl << endl << "���Ż������ʽ����ȷ���˷�ʧ�ܣ�" << endl << endl;
	}

	delete pInfo;

}

int annulCard(string strNo, string strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	Money money;
	int nCardIndex;
	Card *pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);

	if (pCard == NULL) {
		return NOFINDCARD;
	}

	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0) {
		return NOMATCH;
	}

	if (pCard->nStatus == USING) {
		return USING;
	}

	if (pCard->nStatus == INVALID) {
		return INVALID;
	}

	//����money��Ϣ
	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 1;
	money.fMoney = pCard->fBalance;
	money.nDel = 0;



	//������Ϣ��dat
	saveMoney(&money, MONEYPATH);



	//��������������Ϣ
	MoneyNode *pMoneyNode = new MoneyNode;
	pMoneyNode->data = money;
	MoneyNode* pMoneyNodeHead = *ppMoneyNodeHead;
	MoneyNode* pMoneyNodeTail = *ppMoneyNodeHead;
	if (pMoneyNodeHead == NULL) {
		pMoneyNodeHead = pMoneyNode;
		pMoneyNodeTail = pMoneyNode;
	}
	else {
		while (pMoneyNodeTail->next != NULL) {
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
		pMoneyNodeTail->next = pMoneyNode;
		pMoneyNodeTail = pMoneyNodeTail->next;
	}
	pMoneyNodeTail->next = NULL;


	//�����ļ��еĿ���Ϣ
	pCard->fBalance = 0;
	pCard->nStatus = INVALID;
	updateCard(pCard, CARDPATH, nCardIndex);


	strcpy_s(pInfo->aCardName, strNo.c_str());
	pInfo->fMoney = money.fMoney;
	pInfo->fBalance = pCard->fBalance;

	return SUCCESS;
}//����