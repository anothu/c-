#include"IntArray.h"

IntArray::~IntArray() {
	delete[] ia;
	cout << "�ѳ����������Ŀռ�!" << endl;
}
void IntArray::common() {
	ia = new int[size];
}
IntArray::IntArray(int sz) {
	size = sz;         // �������ݳ�Ա 
	common();
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = 0;     // ��ʼ������Ԫ��
}
IntArray::IntArray(int *array, int sz) {
	size = sz;         // �������ݳ�Ա 
	common();
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = array[ix];    // �������ݳ�Ա
}
IntArray::IntArray(const IntArray &rhs)
{
	size = rhs.size;
	common();
	for (int ix = 0; ix < size; ix++)
		ia[ix] = rhs.ia[ix];
}
void IntArray::printAll()
{
	for (int ix = 0; ix < size; ++ix)
		cout << ia[ix] << "  ";
	cout << endl;
}
//��������