#pragma once
#include<iostream>  
using namespace std;
class IntArray {
public:
	IntArray(int sz);      // �����ʼ��Ϊsz��Ԫ�أ���ֵȫΪ0
	IntArray(int *array, int sz);  // �þ�̬����array��ǰsz��Ԫ�س�ʼ��������
	IntArray(const IntArray &rhs); // �������캯��
	void printAll();
	void common();//������
	~IntArray();//��������
private:
	int *ia;
	int size;
};