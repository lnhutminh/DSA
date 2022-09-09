#include "stdio.h"
using namespace std;
#include <iostream>

struct NODE {
	int Key;
	NODE* pLeft;
	NODE* pRight;
};
void Init(NODE*& TREE)
{
	TREE = NULL;
}
void Insert(NODE*& pRoot, int x)
{
	if (pRoot == NULL)
	{
		NODE* q;
		q = new NODE;
		q->Key = x;
		q->pLeft = q->pRight = NULL;
		pRoot = q;
	}
	else
	{
		if (x < pRoot->Key)
			Insert(pRoot->pLeft, x);
		else if (x > pRoot->Key)
			Insert(pRoot->pRight, x);

	}
}
void CreateTree(NODE*& pRoot)
{
	int Data;
	do {
		printf("Nhap vao du lieu, -1 de ket thuc: ");
		scanf_s("%d", &Data);
		if (Data == -1)
			break;
		Insert(pRoot, Data);
	} while (1);
}
void NLR(NODE * pTree)
{
	if (pTree != NULL)
	{
		printf("%4d", pTree->Key);
		NLR(pTree->pLeft);
		NLR(pTree->pRight);
	}
}
NODE* Search(NODE * pRoot, int x)
{
	if (pRoot == NULL)
		return NULL;
	if (x < pRoot->Key)
		Search(pRoot->pLeft, x);
	else
		if (x > pRoot->Key)
			Search(pRoot->pRight, x);
		else
		{
			//Ghi chú: Trong trường hợp nào dòng bên dưới được thực hiện?
			return pRoot;
		}

}
int Height(NODE* pNode)
{
	if (pNode == NULL)
		return 0;
	int HL, HR;
	HL = Height(pNode->pLeft);
	HR = Height(pNode->pRight);
	if (HL > HR)
		return (1 + HL);
	return (1 + HR);
}

void SearchStandFor(NODE*& Tree, NODE*& q)
{
		if (Tree->pRight)
			SearchStandFor(Tree->pRight, q);
		else
		{
			q->Key = Tree->Key;
			q = Tree;
			Tree = Tree->pLeft;
		}
}
void RemoveNode(NODE*& Tree, int x)
{
	NODE* p;
	if (Tree == NULL)
		printf("%d khong co trong cay", x);
	else
	{
		if (x < Tree->Key)
			RemoveNode(Tree->pLeft, x);
		else
			if (x > Tree->Key)
				RemoveNode(Tree->pRight, x);
			else
			{
				//Ghi chú: Mục đích phép gán này là gì?
				p = Tree;
				if (p->pRight == NULL)
					Tree = p->pLeft;
				else
					if (p->pLeft == NULL)
						Tree = p->pRight;
					else {
						//Ghi chú: Hàm bên dưới dùng để làm gì?
						SearchStandFor(Tree->pLeft, p);
					}
				delete p;
			}

	}
}

int CountNode(NODE* Tree) {
	if (Tree != NULL) {
		return 1 + CountNode(Tree->pLeft) + CountNode(Tree->pRight);
	}
	else {
		return 0;
	}
}

int CountNodeLeaf(NODE* Tree) {
	if (Tree != NULL) {
		if (Tree->pLeft == NULL && Tree->pRight == NULL)
			return 1;
		else
			return CountNodeLeaf(Tree->pLeft) + CountNodeLeaf(Tree->pRight);
	}
	else {
		return 0;
	}
}

int SumTree (NODE*pTree, int&s)
{
	if (pTree != NULL)
	{
		s += pTree->Key;
		SumTree(pTree->pLeft, s);
		SumTree(pTree->pRight, s);
	}
	return s;
}

NODE* MinTree(NODE* pTree, NODE*& result)
{
	if (pTree != NULL)
	{
		result = pTree;
		MinTree(pTree->pLeft, result);
	}
	return result;
}

NODE* MaxTree(NODE* pTree, NODE*& res)
{

	if (pTree != NULL)
	{
		res = pTree;
		MaxTree(pTree->pRight, res);
	}
	return res;
}

void main()
{
	NODE* pTree, * p;
	int x;
	Init(pTree);
	CreateTree(pTree);
	NLR(pTree);
	printf("Nhap vao 1 gia tri de tim: ");
	scanf_s("%d", &x);
	p = Search(pTree, x);
	if (p != NULL)
	{
		printf("%d co xuat hien trong cay.\n", x);
		printf("Chieu cao cua nut %d la %d\n", x, Height(p));
		RemoveNode(pTree, x);
		NLR(pTree);
	}
	else
		printf("%d khong co trong cay.\n", x);

	int count = CountNode(pTree);
	cout << endl << "So luong nut cua cay la: " << count << endl;

	int countleaf = CountNodeLeaf(pTree);
	cout << endl << "So luong nut la (leaf) cua cay la: " << countleaf << endl;

	int tmp = 0;
	int ans = SumTree(pTree, tmp);
	cout << "\nTong gia tri cac nut nguyen tren cay la: " << ans;
	NODE* tam1;
	NODE* tam2;

	NODE* temp;
	temp = MaxTree(pTree, tam1);
	int maxnode = temp->Key;
	temp = MinTree(pTree, tam2);
	int minnode = temp->Key;
	cout << "\nMax node = " << maxnode << " min node = " << minnode << ".\n";
}

/*
Câu 2:
-1 không có trong cây
---------------------
5
-1 không có trong cây
---------------------
  7 -23 -25  -4   1  10
  -23 có xuất hiện trong cây.
chiều cao của nút -23 là 3
---------------------
-23 co xuat hien trong cay.
Chieu cao cua nut -23 la 4
 -25   7  -4   1  10
---------------------
-23 co xuat hien trong cay.
Chieu cao cua nut -23 la 3
   7 -25  -4   1  10
 ---------------------
 5 khong co trong cay.
 Câu3
 Thêm vào: Node đầu tiên là node gốc các node tiếp theo được thêm vào theo quy tắc nhỏ hơn node gốc qua nhánh trái, lớn hơn node gốc qua nhánh phải
 Xuất: theo thứ thự Gốc - Trái - Phải
 Câu 4:
 5

         7
        / \
	  -23 10
	  / \ 
	-25  4
	      \
		   1

Câu 5:
Không có cấu trúc cây được tạo ra vì hàm Init là hàm Khởi tạo cây (TREE = NULL)
Câu 6:
-1 co xuat hien trong cay.
Chieu cao cua nut -1 la 1

-1 co xuat hien trong cay.
Chieu cao cua nut -1 la 1
   5

   -23 co xuat hien trong cay.
Chieu cao cua nut -23 la 4
   7 -25  -4   1  -1  10

   -23 co xuat hien trong cay.
Chieu cao cua nut -23 la 5
 -25   7  -4   1  -1  10

   7 -23 -25  -4   1  -1  10
-23 co xuat hien trong cay.
Chieu cao cua nut -23 la 4
   7 -25  -4   1  -1  10
    

-1 sẽ được thêm vào cây và chiều cao tăng lên
Câu 7
In theo thứ tự Trái - Gốc - Phải

*/