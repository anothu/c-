#pragma once
#define OK 0;
#define ERROR 1;
struct HTNode
{
	int nWeight;//Ȩֵ
	int nParent;//���ڵ�
	int nLchild;//����
	int nRchild;//����
};

typedef HTNode *HuffmanTree;
					 
typedef char **HuffmanCode;

int HuffmanTreeing(HuffmanTree &pHT, int *w, int n);
int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT);
int Selcet(HuffmanTree pHT, int nSize);



