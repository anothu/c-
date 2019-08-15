// AMS.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include"billList.h"
#include"cardList.h"
#include"moneyList.h"
#include"global.h"
#include"menu.h"
#include"model.h"
#include"service.h"
#include"tool.h"
#include<iostream>
using namespace std;


int main()
{
	char selection; // ����˵�����

	CardNode* pCardNodeHead = NULL;
	pCardNodeHead = CardListInit(CARDPATH);//���ļ�������card�������ر�ͷ

	BillingNode *pBillingNodeHead = NULL;
	pBillingNodeHead = BillListInit(BILLINGPATH);//���ļ�������bill�������ر�ͷ

	MoneyNode* pMoneyNodeHead = NULL;
	pMoneyNodeHead = MoneyListInit(MONEYPATH);//���ļ�������money�������ر�ͷ

	cout << endl;
	cout << "�ﻶӭ����Ʒѹ���ϵͳ��" << endl;
	cout << endl;
	do
	{
		outputMenu();
		selection = 'a'; // ��ʼ��ѡ��Ĳ˵�����Ϊ'a'
		cin >> selection; // ����˵�����
		cin.clear();
		cin.sync();//��ջ�����
		switch (selection) //ѡ��Ĳ˵����
		{
		case '1'://��ӿ�
		{
			cout << endl << "-------��ӿ�--------" << endl << endl;
			addCard(&pCardNodeHead,&pMoneyNodeHead);
			break;
		}
		case '2': //��ѯ��
		{
			
			queryCard(pCardNodeHead);
			cout << endl << "-------��ѯ��--------" << endl << endl;
			break;
		}
		case '3'://�ϻ�
		{
			shangji(pCardNodeHead, &pBillingNodeHead);
			cout << endl << "-------�ϻ�----------" << endl << endl;
			break;
		}
		case '4': // �»�
		{
			xiaJi(pCardNodeHead, pBillingNodeHead);
			cout << endl << "-------�»�----------" << endl << endl;
			break;
		}
		case '5'://��ֵ
		{
			addMoney(pCardNodeHead, &pMoneyNodeHead);
			cout << endl << "-------��ֵ----------" << endl << endl;
			break;
		}
		case '6'://�˷�
		{
			refundMoney(pCardNodeHead, &pMoneyNodeHead);
			cout << endl << "-------�˷�----------" << endl << endl;
			break;
		}
		case '7'://��ѯͳ��
		{
			statistics(pCardNodeHead, pBillingNodeHead, pMoneyNodeHead);
			cout << endl << "-----��ѯͳ��--------" << endl << endl;
			break;
		}
		case '8'://ע����
		{
			logout(pCardNodeHead, &pMoneyNodeHead);
			cout << endl << "------ע����---------" << endl << endl;
			break;
		}
		case '0': // �˳�
		{
			clearData(pCardNodeHead);
			cout << endl << "лл��ʹ�ñ�ϵͳ�� " << endl << endl;
			break;
		}
		default:
		{
			cout << "����Ĳ˵���Ŵ��� \n";
			break;
		}
		}
		cout << endl;
	} while (selection != '0');

	return 0;
}
// ϵͳ�˵�

