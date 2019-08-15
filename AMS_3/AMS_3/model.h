#pragma once
#include<time.h>


struct Card
{
	 char aName[18]; // ����
	char aPwd[8]; // ����
	int nStatus; // ��״̬(UNUSE-δ�ϻ��� USING-�����ϻ��� INVALID-��ע��)
	 time_t tStart; // ����ʱ�䣬 long
	float fTotalUse; // �ۼƽ��
	 time_t tLast; // ���ʹ��ʱ�䣬 long
	int nUseCount; // ʹ�ô���
	float fBalance; // ���

};

struct CardNode
{
	Card data;
	struct CardNode* next;
};


//�Ʒ���Ϣ�ṹ��
struct Billing
{
	char aCardName[18];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	int nStatus;
	int nDel;
};

//�Ʒ���Ϣnode
struct BillingNode
{
	Billing data;
	struct BillingNode *next;
};

//�ϻ��ṹ��
struct LogonInfo
{
	char aCardName[18];
	time_t tLogon;
	float fBalance;
};


//�»��ṹ��
struct SettleInfo
{
	char aCardName[18];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	float fBalance;
};

struct Money
{
	char aCardName[18]; // ����
	char aPwd[8]; // ����
	int nStatus; // ��״̬(UNUSE-δ�ϻ��� USING-�����ϻ��� INVALID-��ע��)
	time_t tTime; // ����ʱ�䣬 long
	float fBalance; // ���
	float fMoney;//���ϵ�Ǯ
	int nDel;
};

struct MoneyNode
{
	Money data;
	struct MoneyNode *next;
};

struct MoneyInfo
{
	char aCardName[18]; // ����
	char aPwd[8]; // ����
	int nStatus; // ��״̬(UNUSE-δ�ϻ��� USING-�����ϻ��� INVALID-��ע��)
	time_t tTime; // ����ʱ�䣬 long
	float fMoney; // �ۼƽ��
	time_t tLast; // ���ʹ��ʱ�䣬 long
	int nUseCount; // ʹ�ô���
	float fBalance; // ���
};