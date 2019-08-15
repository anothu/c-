
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

BillingNode* BillListInit(const string billingFilename)
{
	ifstream billingfile(billingFilename);
	BillingNode *pBillingNode, *pBillingNodeHead, *pBillingNodeTail;
	Billing billing;
	if (!billingfile.is_open())
	{
		return NULL;
	}
	pBillingNodeHead = NULL;
	pBillingNodeTail = NULL;
	while (1)
	{
		billingfile.read((char*)&billing, sizeof(Billing));
		if (billingfile.eof())
		{
			break;
		}//�����ļ�ĩβʱ�˳�ѭ��
		pBillingNode = new BillingNode;
		pBillingNode->data = billing;
		if (pBillingNodeHead == NULL)
		{
			pBillingNodeHead = pBillingNode;
			pBillingNodeTail = pBillingNode;
		}
		else
		{
			pBillingNodeTail->next = pBillingNode;
			pBillingNodeTail = pBillingNode;
		}
	}
	pBillingNodeTail->next = NULL;
	billingfile.close();
	return pBillingNodeHead;
}//�����������ر�ͷ

int logon(string strNo, string strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead,BillingNode **ppBillingNodeHead)
{
	Billing billing; // �Ʒ���Ϣ
	int nCardIndex;//����д�ļ�ʱ��λ
	Card* pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);//�����뿨������Ŀ�
	if (pCard == NULL)
		return NOFINDCARD; // δ�ҵ���
	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0)
		return NOMATCH; // ���벻ƥ��
	if (pCard->nStatus == USING)
	{
		return USING; // �������ϻ�
	}
	if (pCard->nStatus == INVALID)
	{
		return INVALID; // ���Ѿ�ע��
	}
	if (pCard->fBalance <= 0)
	{
		return ENOUGHMONEY; // �������Ϊ0
	}
	// ��������ϻ������¿���Ϣ
	pCard->nStatus = USING; // ״̬Ϊ����ʹ��
	pCard->nUseCount++; // ʹ�ô�����1
	pCard->tLast = time(NULL); // �������ʹ��ʱ��Ϊ��ǰʱ��
    // �����ļ��еĿ���Ϣ
	updateCard(pCard, CARDPATH, nCardIndex);
	// ������Ѽ�¼
	strcpy(billing.aCardName, strNo.c_str()); // �ϻ�����
	billing.tStart = time(NULL); // �ϻ�ʱ��
	billing.tEnd = 0; // �»�ʱ��
	billing.nStatus = NOSETTLEMENT; // ����״̬
	billing.fAmount = 0; // ���ѽ��
						 // �Ƚ��Ʒ���Ϣ���浽�ļ���
	saveBilling(&billing, BILLINGPATH);
	// �ڼƷ�����������һ���Ʒ���Ϣ
	BillingNode* pBillingNode = new BillingNode;
	pBillingNode->data = billing;
	BillingNode* pBillingNodeTail = *ppBillingNodeHead;
	//������û��bill
	if (*ppBillingNodeHead == NULL)
	{
		*ppBillingNodeHead = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	else//�����β
	{
		while (pBillingNodeTail->next != NULL)
			pBillingNodeTail = pBillingNodeTail->next;
		pBillingNodeTail->next = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	pBillingNodeTail->next = NULL;
	// ��װ�ϻ���Ϣ
	strcpy(pInfo->aCardName, strNo.c_str());
	pInfo->fBalance = pCard->fBalance;
	pInfo->tLogon = billing.tStart;
	return SUCCESS;
}

bool updateCard(const Card* pCard, const string pPath, int nCardIndex)
{
	fstream ofile;
	ofile.open(pPath, ios_base::in | ios_base::out);
	ofile.seekp(sizeof(Card)*nCardIndex, ios_base::beg);//ncardindex���Զ�λ
	ofile.write((char*)pCard, sizeof(Card));
	ofile.close();
	return true;
}

bool saveBilling(const Billing* pBill, const string pPath)
{
	ofstream ofile(pPath, ios::binary | ios::app);
	ofile.write((char*)pBill, sizeof(Billing));
	ofile.close();
	return true;
}

void shangji(CardNode* pCardNodeHead, BillingNode **ppBillingNodeHead)
{
	string strNo;
	string strPwd;
	LogonInfo* pInfo = new LogonInfo; // �ϻ���Ϣ��������ʾ
	char aTime[TIMELENGTH] = { 0 }; // �ϻ�ʱ�䣬������ʾ
	if (inputNoPwd(strNo, strPwd))//�����˺ţ�����
	{
		cout << endl << "----------�ϻ���Ϣ----------" << endl;
		// �����ϻ��������ʾ��ͬ��Ϣ
		int nResult = logon(strNo, strPwd, pInfo, pCardNodeHead,ppBillingNodeHead);//ʵ���ϻ����߷����쳣״̬
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
		{
			cout << endl << endl << "�������ڣ�����Ϣ���ԣ������ϻ��� " <<
				endl << endl;
			break;
		}
		case SUCCESS:
		{
			timeToString(pInfo->tLogon, aTime);
			cout << endl;
			cout << "����: \t" << strNo << endl;
			cout << "���: \t" << pInfo->fBalance << endl;
			cout << "�ϻ�ʱ�䣺 \t" << aTime << endl;
			break;
		}
		case USING:
		{
			cout << endl << "�ÿ�����ʹ�ã������ظ��ϻ��� " << endl;
			break;
		}
		case INVALID:
		{
			cout << endl << "�ÿ���ע���������ϻ��� " << endl;
			break;
		}
		case ENOUGHMONEY:
		{
			cout << endl << "�����Ϊ0�������ϻ��� " << endl;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		cout << endl << endl << "���Ż��������ʽ����ȷ���ϻ�ʧ��!" << endl <<
			endl;
	}
	delete pInfo;
}

void xiaJi(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead)
{
	string strNo;
	string strPwd;
	SettleInfo* pInfo = new SettleInfo; // �»���Ϣ
	char aStartTime[TIMELENGTH] = { 0 }; // �ϻ�ʱ��
	char aEndTime[TIMELENGTH] = { 0 }; // �»�ʱ��
	if (inputNoPwd(strNo, strPwd))//�����˺ţ�����
	{
		cout << "----------�»���Ϣ����----------\n";
		int nResult = settle(strNo, strPwd, pInfo, pCardNodeHead,pBillingNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
		{
			cout << endl << endl << "�������ڣ�����Ϣ���ԣ��»�ʧ�ܣ� " <<
				endl << endl;
			break;
		}
		case SUCCESS:
		{
			timeToString(pInfo->tStart, aStartTime);
			timeToString(pInfo->tEnd, aEndTime);
			cout << endl;
			cout << "����: \t" << strNo << endl;
			cout << "����: \t" << pInfo->fAmount << endl;
			cout << "���: \t" << pInfo->fBalance << endl;
			cout << "�ϻ�ʱ�䣺 \t" << aStartTime << endl;
			cout << "�»�ʱ�䣺 \t" << aEndTime << endl;
			break;
		}
		case UNUSE:
		{
			cout << endl << endl << "�ÿ�û���ϻ��� " << endl << endl;
			break;
		}
		case ENOUGHMONEY:
		{
			cout << endl << endl << "�����㣬���ȳ�ֵ���»��� " << endl
				<< endl;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		cout << endl << endl << "���Ż��������ʽ����ȷ���»�ʧ��!" << endl <<
			endl;
	}
	delete pInfo;
}

bool updateBilling(const Billing* pCard, const string pPath, int nCardIndex)
{
	fstream ofile;
	ofile.open(pPath, ios_base::in | ios_base::out);
	ofile.seekp(sizeof(Card)*nCardIndex, ios_base::beg);
	ofile.write((char*)pCard, sizeof(Card));
	ofile.close();
	return true;
}

int settle(string strNo, string strPwd, SettleInfo* pInfo, CardNode* const pCardNodeHead, BillingNode* const pBillingNodeHead)
{
	int nCardIndex;
	Card* pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);//�������˺���ͬ�Ŀ�
	// δ�ҵ���
	if (pCard == NULL)
		return NOFINDCARD;
	// ���벻ƥ��
	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0)
		return NOMATCH;
	// �жϸÿ��Ƿ������ϻ���ֻ�������ϻ������ܽ����»�����
	if (pCard->nStatus != USING)
		return UNUSE;
	// ���ݿ��ţ���ѯ�Ʒ���Ϣ
	int nBillingIndex;
	Billing* pBilling = billingIsExist(strNo, nBillingIndex, pBillingNodeHead);//nbillingindex���ڶ�λ
	// �����ѯ�Ʒ���ϢΪ�գ���ʾ�»�ʧ��
	if (pBilling == NULL)
	{
		cout << "�Ʒ���ϢΪ��" << endl;
		return UNUSE;
	}
	// �������ѽ��
	double dbAmount = getAmount(pBilling->tStart);//�����ϻ��ӻ���Ǯ
	// ������С�����ѽ����ܽ����»�
	float fBalance = pCard->fBalance - (float)dbAmount;//�������
	if (fBalance < 0)
	{
		return ENOUGHMONEY;
	}
	// ���¿���Ϣ
	pCard->fBalance = fBalance; // ���
	pCard->nStatus = UNUSE; // ״̬
	pCard->tLast = time(NULL); // �ϴ�ʹ��ʱ��
	updateCard(pCard, CARDPATH, nCardIndex);// ���¼Ʒ���Ϣ
	pBilling->fAmount = (float)dbAmount; // ������Ϣ
	pBilling->nStatus = YESSETTLEMENT; // ״̬���ѽ���
	pBilling->tEnd = time(NULL); // �»�ʱ��								 
	// �����ļ��еļƷ���Ϣ
	updateBilling(pBilling, BILLINGPATH, nBillingIndex);
	// ��װ�»���Ϣ
	strcpy(pInfo->aCardName, strNo.c_str()); // ����
	pInfo->fAmount = (float)dbAmount; // ���ѽ��
	pInfo->fBalance = fBalance; // ���
	pInfo->tStart = pBilling->tStart; // �ϻ�ʱ��
	pInfo->tEnd = time(NULL); // �»�ʱ��
	return SUCCESS;
}

double getAmount(time_t tStart)
{
	double dbAmount = 0; // ���ѽ��
	int nCount = 0; // �ϻ���ʱ�䵥Ԫ����ÿ����Ԫ15����
	int nSec = 0; // ����ʱ��(��λ����)
	int nMinutes = 0; // ����ʱ��(��λ������)
	time_t tEnd = time(NULL); // ����ʱ��Ϊ��ǰʱ��
							  // ��������ʱ��
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	// �������ѵ�ʱ�䵥Ԫ��
	if (nMinutes % UNIT == 0)
	{
		nCount = nMinutes / UNIT;
	}
	else
	{
		nCount = nMinutes / UNIT + 1;
	}
	if (nCount == 0)
		nCount = 1;
	// �������ѽ��
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

Billing* billingIsExist(string strNo, int& nBillingIndex, BillingNode *pBillingNodeHead)
{
	BillingNode *pBillingNode = pBillingNodeHead;
	nBillingIndex = 0;
	while (pBillingNode != NULL)
	{
		if (strcmp(pBillingNode->data.aCardName, strNo.c_str()) == 0 &&
			pBillingNode->data.nStatus == NOSETTLEMENT)
		{
			return &(pBillingNode->data);
		}
		pBillingNode = pBillingNode->next;
		nBillingIndex++;
	}
	return NULL;
}

int searchBilling( CardNode* pCardNodeHead, BillingNode* pBillingNodeHead) {


	string t0, t1;

	cout << endl << "�������ѯʱ���(��ʼ,��%d-%d-%d-%d:%d)��";
	cin >> t0;
	time_t tbegin = stringToTime(const_cast<char*>(t0.c_str()));//stringΪconst char* 
	if (tbegin == -1) {
		cout << endl << "�����ʽ����" << endl;
		return -1;
	}

	cout << endl << "�������ѯʱ���(����,��%d-%d-%d-%d:%d)��";
	cin >> t1;
	time_t tover = stringToTime(const_cast<char*>(t1.c_str()));
	if (tover == -1) {
		cout << endl << "�����ʽ����" << endl;
		return -1;
	}

	BillingNode* pBillingNode = pBillingNodeHead;
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	float sum = 0;

	cout << endl << endl << "����\t\t�ϻ�ʱ��\t\t�»�ʱ��\t\t���ѽ��\t�Ƿ����\n" << endl << endl;
	while (pBillingNode != NULL) {
		if (pBillingNode->data.tStart >= tbegin && pBillingNode->data.tEnd <= tover) {
			timeToString(pBillingNode->data.tStart, aStartTime);
			timeToString(pBillingNode->data.tEnd, aEndTime);
			cout << pBillingNode->data.aCardName << "\t";
			cout << aStartTime << "\t";
			if (pBillingNode->data.nStatus == 1) {
				cout << aEndTime << "\t";
			}
			else {
				cout << "�ÿ�δ�»�" << "\t\t";
			}
			cout << pBillingNode->data.fAmount << "\t\t" << pBillingNode->data.nStatus << endl;
			sum += pBillingNode->data.fAmount;
		}
		pBillingNode = pBillingNode->next;
	}
	cout << endl << endl << "�����ѽ��Ϊ��" << sum << "Ԫ" << endl;
	return SUCCESS;
}


