#pragma once
#include<iostream>
using namespace std;
const int MaxSize = 100; 
template<typename T>
class  Istack
{
public:
	Istack();          
	void Push(T& n);    
	void Pop();         
	T GetTop();       
	bool Empty();      
	int Size();         
	void ClearStack(); 
	~Istack();

private:
	T elem[MaxSize];  
	int Top;          
};
void menu();

void menu()
{
	cout << "1.��Ԫ����ջ" << endl;
	cout << "2.��Ԫ�س�ջ" << endl;
	cout << "3.���طǿ�ջ��ջ��Ԫ��" << endl;
	cout << "4.�ж�ջ�Ƿ�Ϊ��" << endl;
	cout << "5.����ջ��Ԫ�صĸ���" << endl;
	cout << "6.��ջ���" << endl;
}

template<typename T>
Istack<T>::Istack()
{
	int *elem = new int[MaxSize];
	Top = 0;
}

template<typename T>
Istack<T>::~Istack()
{
	delete[] elem;
	Top = 0;
}

template<typename T>
void Istack<T>::Push(T& n)
{
	elem[Top++] = n;
}

template<typename T>
void Istack<T>::Pop()
{
	if (Top == 0)
		cout << "ջΪ��!" << endl;
	else
	{
		cout << "��ջ��Ԫ��ֵ: " << elem[Top - 1] << endl;
		Top--;
	}

}

template<typename T>
T Istack<T>::GetTop()
{
	if (Top == 0)
		cout << "ջΪ��!" << endl;
	else
		return elem[Top - 1];
}

template<typename T>
bool Istack<T>::Empty()
{
	if (Top == 0)
		return true;
	else
		return false;
}

template<typename T>
int Istack<T>::Size()
{
	return Top;
}

template<typename T>
void Istack<T>::ClearStack()
{
	Top = 0;
}