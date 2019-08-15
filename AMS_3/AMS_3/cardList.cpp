#include "stdafx.h"
#include"menu.h"
#include"tool.h"
#include"service.h"
#include<iostream>
#include"model.h"
#include <string> 
#include "global.h"
#include<fstream>
#include"moneyList.h"
#include"cardList.h"

using namespace std;

Card* cardIsExist(string strNo, int &nCardIndex, CardNode* const pCardNodeHead)
{
	CardNode *pCardNode = pCardNodeHead;
	nCardIndex = 0;
	while (pCardNode != NULL)//����������cardʱ
	{
		if (strcmp(pCardNode->data.aName, strNo.c_str()) == 0)
		{
			return &(pCardNode->data);//����ҵ����ŷ��ϵĿ���������
		}
		pCardNode = pCardNode->next;//��������һ�ſ�
		nCardIndex++;
	}
	return NULL;//���޷��ϵĿ�������NULL
}

bool saveCard(const Card* pCard, const string pPath)
{
	ofstream ofile(pPath, ios::binary | ios::app);
	ofile.write((char*)pCard, sizeof(Card));
	ofile.close();
	return true;
}//��cardд��ָ���ļ���

int addNewCard(string strNo, string strPwd, float fBalance, CardNode** ppCardNodeHead, MoneyNode** ppMoneyNodeHead)
{
	int nCardIndex = 0;
	if (cardIsExist(strNo, nCardIndex, *ppCardNodeHead) != NULL)
	{
		return FINDCARD;
	}
	Card card;
	strcpy(card.aName, strNo.c_str());//�����¿��˺�
	strcpy(card.aPwd, strPwd.c_str());//�����¿�����
	card.fBalance = fBalance;// ����¿�ʱ���ۼƽ����ڿ������
	card.fTotalUse = card.fBalance;
	card.nStatus = UNUSE; // ��״̬
	card.nUseCount = 0; // ʹ�ô���			
	card.tStart = card.tLast = time(NULL);// ����ʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ��
	CardNode* pCardNode = new CardNode;
	pCardNode->data = card;
	CardNode *pCardNodeHead = *ppCardNodeHead;//ppCardNodeHead��ָ��pCardNode��ָ��
	CardNode *pCardNodeTail = *ppCardNodeHead;
	if (pCardNodeHead == NULL)
	{
		// ��һ�ſ���ͨ��ppCardNodeHead����ָ̬�뷵��
		pCardNodeHead = pCardNode;
		pCardNodeTail = pCardNode;
		*ppCardNodeHead = pCardNode;
	}
	else
	{
		//���ǵ�һ�ſ������ڱ�β
		pCardNodeTail = pCardNodeHead;
		while (pCardNodeTail->next != NULL)
			pCardNodeTail = pCardNodeTail->next;
		pCardNodeTail->next = pCardNode;
		pCardNodeTail = pCardNode;
	}
	pCardNodeTail->next = NULL;//����β��Ϊ��

	//**********
	Money money;
	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 0;
	money.fMoney = fBalance;
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
    //**********
	saveCard(&card, CARDPATH);//���濨����Ϣ
	return SUCCESS;
}

CardNode* CardListInit(const string cardFilename)
{
	ifstream cardfile(cardFilename);
	CardNode *pCardNode, *pCardNodeHead, *pCardNodeTail;
	Card card;
	if (!cardfile.is_open())
	{
		return NULL;
	}
	pCardNodeHead = NULL;
	pCardNodeTail = NULL;
	while (1)
	{
		cardfile.read((char*)&card, sizeof(Card));
		if (cardfile.eof())
		{
			break;
		}//���ļ�������˳�
		pCardNode = new CardNode;
		pCardNode->data = card;
		if (pCardNodeHead == NULL)//��һ�ſ�
		{
			pCardNodeHead = pCardNode;
			pCardNodeTail = pCardNode;
		}
		else//����Ŀ�
		{
			pCardNodeTail->next = pCardNode;
			pCardNodeTail = pCardNode;
		}
	}
	pCardNodeTail->next = NULL;//����β��Ϊ��
	cardfile.close();
	return pCardNodeHead;
}

void displayCard(CardNode* pCardNodeHead)
{
	if (pCardNodeHead == NULL)
	{
		cout << endl << endl << "һ���ϻ�����û�У� " << endl << endl;
		return;
	}

	string t;
	cout << "�������ѯ�ĺ��룺";
	cin >> t;
	cout << "����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��" << endl;
	CardNode* pCur = pCardNodeHead;

	char buf[18];
	strcpy(buf, t.c_str());
	while (pCur != NULL)//������û�м�����
	{
		char aLastTime[TIMELENGTH] = { 0 };
		timeToString((pCur->data).tLast, aLastTime);//��ʱ���ʽ��
		if (strncmp(buf, pCur->data.aName, t.length()) == 0)
		{
			cout << pCur->data.aName << "\t";
			if (pCur->data.nStatus == USING)
				cout << "�ϻ�\t";
			else if (pCur->data.nStatus == UNUSE)
				cout << "δ�ϻ�\t";
			else if (pCur->data.nStatus == INVALID)
				cout << "ע��\t";
			else
				cout << "����\t";

			cout << pCur->data.fBalance << "\t";
			cout << pCur->data.fTotalUse << "\t\t" << pCur->data.nUseCount << "\t\t" << aLastTime << endl;
		}
		pCur = pCur->next;//������һ�ſ�
	}
}