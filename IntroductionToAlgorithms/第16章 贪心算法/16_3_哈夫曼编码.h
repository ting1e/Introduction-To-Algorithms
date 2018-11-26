#pragma once
#include "..//base.h"

#define nums 256
const int huff_flag = 1234;

//构造赫夫曼树。
typedef struct HUFFMANNODE
{
	unsigned char ch;
	int freq;
	struct HUFFMANNODE *left;
	struct HUFFMANNODE *right;
}HuffmanNode;


typedef struct MINQUEUE 
{
	HuffmanNode *node;
	struct MINQUEUE *next;
} MinQueue;

MinQueue *BuildQueue()
{
	MinQueue *que = (MinQueue *)malloc(sizeof(MinQueue));
	if (que)
	{
		que->next = NULL;
		que->node = NULL;
	}
	return que;
}


void InsertQueue(MinQueue *queue, HuffmanNode *node)
{
	while ((queue->next != NULL) && (queue->next->node->freq < node->freq))
	{
		queue = queue->next;
	}
	MinQueue *temp = queue->next;
	MinQueue *new_node = (MinQueue *)malloc(sizeof(MinQueue));
	new_node->next = temp;
	new_node->node = node;
	queue->next = new_node;
}

HuffmanNode * RetMinHuffman(MinQueue *queue)
{
	MinQueue *temp = queue->next;
	HuffmanNode *node = temp->node;
	queue->next = queue->next->next;
	free(temp);
	return node;
}

HuffmanNode *Huffman(int freqs[])
{
	MinQueue * queue = BuildQueue();
	HuffmanNode *huffman;
	for (int i = 0; i < nums; i++)
	{
		if (freqs[i] != 0)
		{
			huffman = (HuffmanNode *)malloc(sizeof(HuffmanNode));
			huffman->ch = i;
			huffman->freq = freqs[i];
			huffman->left = NULL;
			huffman->right = NULL;
			InsertQueue(queue, huffman);
		}
	}
	while (queue->next->next != NULL)
	{
		huffman = (HuffmanNode *)malloc(sizeof(HuffmanNode));
		huffman->left =RetMinHuffman(queue);
		huffman->right = RetMinHuffman(queue);
		huffman->freq = huffman->left->freq + huffman->right->freq;
		InsertQueue(queue, huffman);
	}
	return queue->next->node;
}

void Encode(HuffmanNode *root, char *code[], char *str)
{
	if (root == NULL)
		return;
	else if (root->left == NULL && root->right == NULL)
	{
		code[root->ch] = str;
	}
	else
	{
		
		int length = strlen(str);
		char *left = (char *)malloc(sizeof(char)*(length+2));
		strcpy(left, str);
		left[length] = '0';
		left[length+1] = '\0';

		char *right = (char *)malloc(sizeof(char)*(length + 2));
		strcpy(right, str);
		right[length] = '1';
		right[length+1] = '\0';

		Encode(root->left, code, left);
		Encode(root->right, code,right);
		if (str[0] != '\0')
		{
			free(str);
		}

	}
}

int Decode(HuffmanNode *root, char *str)
{
	int size = strlen(str);
	for (int i = 0; i < size; i++)
	{
		if (str[i] == '0')
			root = root->left;
		else if (str[i] == '1')
			root = root->right;
	}

	if (root->left == NULL && root->right == NULL)
		return root->ch;

	return -1;
}

void Int2bin(int val2,char *str)	//倒序二进制
{
	
	int k = 0;
	do {
		str[k++] = val2 % 2+'0';
		val2 /= 2;
	} while (val2 != 0);
	str[k] = '\0';
}

void Bin2int(char *str,int val2)	//倒序二进制0.0.0.0
{
	
	int k = 0;
	do {
		str[k++] = val2 % 2+'0';
		val2 /= 2;
	} while (val2 != 0);
	str[k] = '\0';
}

void FreeHuffman(HuffmanNode *root)
{
	if (root == NULL)
		return;
	if (root->left == NULL && root->right == NULL)
		free(root);
	else
	{
		FreeHuffman(root->left);
		FreeHuffman(root->right);
	}
}

void FreeCode(char *code[])
{
	for (int i = 0; i < nums; i++)
	{
		if (code[i]!=NULL)
		{
			free(code[i]);
		}
	}
}

void HuffManCompress(const char *in,const char *out)
{
	HuffmanNode *root;
	char *code[nums] = { '\0' };
	int freqs[nums] = { 0 };

	FILE *fp_in = fopen(in, "rb");
	FILE *fp_out = fopen(out, "wb");

	fseek(fp_in, 0L, SEEK_END);
	unsigned int size = ftell(fp_in);
	fseek(fp_in, 0, SEEK_SET);

	unsigned char *input = (unsigned char *)malloc(sizeof(unsigned char)*size);

	fread(input, sizeof(unsigned char), size, fp_in);
	
	for (unsigned int i = 0; i < size; i++)
	{
		freqs[input[i]]++;
	}

	root = Huffman(freqs);
	Encode(root, code, "");

	unsigned int output_size = 0;
	for (int i = 0; i < nums; i++)
	{
		if(code[i]!=NULL)
			output_size += (strlen(code[i]))*freqs[i];
	}
	output_size = output_size / 8 + 1;
	unsigned char *output = (unsigned char *)malloc(sizeof(unsigned char)*output_size);

	fwrite(&huff_flag, sizeof(int), 1, fp_out);
	fwrite(freqs, sizeof(int), nums, fp_out);

	unsigned char huf = 0;
	int length = 0;
	char *str;
	int temp = 0;
	for(unsigned int i=0;i<size;i++)
	{
		str = code[input[i]];
		int str_size = strlen(str);
		for (int i = 0; i < str_size; i++)
		{
			huf |= str[i] - '0';
			length++;
			if (length == 8)
			{
				output[temp] = huf;
				temp++;
				length = 0;
				huf = 0;
			}
			huf <<= 1;
		}
	}
	if (length != 0)
	{
		huf <<= (8 - length-1);
		output[temp] = huf;
	}
	fwrite(output, sizeof(unsigned char), output_size, fp_out);

	free(input);
	free(output);
	FreeHuffman(root);
	FreeCode(code);
	fclose(fp_in);
	fclose(fp_out);
}


void HuffmanExtract(const char *in, const char *out)
{
	FILE *fp_in = fopen(in, "rb");
	FILE *fp_out = fopen(out, "wb");
	fseek(fp_in, 0L, SEEK_END);
	unsigned int file_size = ftell(fp_in);

	int flag;
	fseek(fp_in, 0L, SEEK_SET);
	
	fread(&flag, sizeof(int), 1, fp_in);
	if (flag != huff_flag)
	{
		printf("文件格式错误\n");
		return ;
	}

	int freqs[nums] = { 0 };
	fread(freqs, sizeof(int), nums, fp_in);
	int decode_size=0;
	for (int i = 0; i < nums; i++)
	{
		if (freqs[i] != 0)
			decode_size += freqs[i];
	}
	unsigned char *out_str = (unsigned char *)malloc(sizeof(unsigned char)*decode_size);

	int size = file_size - sizeof(int)*(1 + nums);
	unsigned char *in_str = (unsigned char *)malloc(size);
	fread(in_str, sizeof(unsigned char), size,fp_in);

	HuffmanNode *root= Huffman(freqs);
	char *code[nums] = { 0 };
	Encode(root, code, "");

	int pos = 7;
	
	unsigned char mask = 1;
	int i = 0,j=0;
	while (i<size)
	{
		char huff[32] = "";
		while (strlen(huff) == 0 || Decode(root, huff)<0)
		{
			if (pos < 0)
			{
				if (i>=size)
					return;
				i++;
				pos = 7;
			}
			if (strlen(huff) == 0)
			{
				huff[0] = (in_str[i] >> pos & mask) + '0';
				huff[1] = '\0';
				pos--;
			}
			else
			{
				int now = strlen(huff);
				huff[now] = (in_str[i] >> pos & mask) + '0';
				huff[now + 1] = '\0';
				pos--;
			}
		}
		out_str[j++] = (unsigned char)Decode(root, huff);
	}
	fwrite(out_str, sizeof(unsigned char), decode_size, fp_out);

	free(in_str);
	free(out_str);
	FreeHuffman(root);
	FreeCode(code);
	fclose(fp_in);
	fclose(fp_out);
}





/*

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
	HuffmanNode *huffman[2000] = { 0 };
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
*/
void test()
{
	HuffManCompress("C:\\Users\\HP\\Desktop\\1234.mp4", "C:\\Users\\HP\\Desktop\\demo.huf");
	HuffmanExtract("C:\\Users\\HP\\Desktop\\demo.huf", "C:\\Users\\HP\\Desktop\\demo.mp4");

}