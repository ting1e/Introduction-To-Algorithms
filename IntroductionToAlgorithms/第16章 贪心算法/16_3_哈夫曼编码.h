#pragma once
#include "..//base.h"


//¹¹ÔìºÕ·òÂüÊ÷¡£
typedef struct HUFFMANNODE
{
	char ch;
	int freq;
	struct HUFFMANNODE *left;
	struct HUFFMANNODE *right;
}HuffmanNode;

int ExtreactMin(HuffmanNode *huffman[100],int n)
{
	int min = INT_MAX;
	int temp;
	for (int i = 0; i < n; i++)
	{
		if (huffman[i] != NULL && min > huffman[i]->freq)
		{
			min = huffman[i]->freq;
			temp = i;
		}
	}
	return temp;
}

HuffmanNode *Huffman(char chs[], int freqs[], int n)
{
	int temp;
	HuffmanNode *huffman[100] = { 0 };
	for (int i = 0; i < n; i++)
	{
		huffman[i] = (HuffmanNode *)malloc(sizeof(HuffmanNode));
		huffman[i]->ch = chs[i];
		huffman[i]->freq = freqs[i];
		huffman[i]->left = NULL;
		huffman[i]->right = NULL;
	}
	for (int i = 0; i < n - 1; i++)
	{
		huffman[n+i] = (HuffmanNode *)malloc(sizeof(HuffmanNode));

		temp = ExtreactMin(huffman, n + i);;
		huffman[n + i]->left = huffman[temp];
		huffman[temp] = NULL;

		temp = ExtreactMin(huffman, n + i);;
		huffman[n + i]->right = huffman[temp];
		huffman[temp] = NULL;

		huffman[n + i]->freq = huffman[n + i]->left->freq + huffman[n + i]->right->freq;
	}

	return huffman[ExtreactMin(huffman, 2 * n)];
}

void print_2(int val2)
{
	int b[16];
	int k = 0;
	do {
		b[k++] = val2 % 2;
		val2 /= 2;
	} while (val2 != 0);
	for (int i = k - 1; i >= 0; i--)
	{
		printf("%d", b[i]);
	}
	printf("\n");
}

void Print(HuffmanNode *root,int i)
{
	if (root == NULL)
		return;
	else if (root->left == NULL && root->right == NULL)
	{
		printf("%c:", root->ch);
		print_2(i);
		printf("\n");
	}
	else
	{
		Print(root->left, i << 1);
		Print(root->right, (i << 1) + 1);
	}
}

void test()
{
	char chs[] = { 'f','e','c','b','d','a' };
	int freqs[] = { 5,9,12,13,16,45 };
	HuffmanNode *root = Huffman(chs, freqs, 6);
	Print(root, 0);
}