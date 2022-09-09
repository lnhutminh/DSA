#include <stdio.h>
#include <iostream>
using namespace std;

struct NODE {
	int Key;
	NODE* pNext;
};
NODE* CreateNode(int Data)
{
	NODE* pNode;
	pNode = new NODE;
	if (pNode == NULL)
		return NULL;
	pNode->Key = Data;
	pNode->pNext = NULL;
	return pNode;
}
bool AddHead(NODE*& pHead, int Data)
{
	NODE* pNode;
	pNode = CreateNode(Data);
	if (pNode == NULL)
		return false;
	if (pHead == NULL)
		pHead = pNode;
	else {
		pNode->pNext = pHead;
		pHead = pNode;
	}
	return true;
}
NODE* RemoveHead(NODE*& pHead)
{
	if (pHead == NULL)
		return NULL;
	NODE* pResult = pHead;
	pHead = pHead->pNext;
	return pResult;
}
NODE* RemoveTail(NODE*& pHead)
{
	NODE* pNode;
	if (pHead == NULL) //<1>
	{
		return NULL;
	}
	else if (pHead->pNext == NULL) //<2>
	{
		pNode = pHead;
		pHead = NULL;
		return pNode;
	}
	pNode = pHead;
	while (pNode->pNext->pNext != NULL) //<3>
	{
		pNode = pNode->pNext;
	}
	NODE* pResult = pNode->pNext;
	pNode->pNext = NULL;
	return pResult;
}
//-------STACK :
//----PUSH tương ứng AddHead
//----POP tương ứng RemoveHead
bool PushStack(NODE*& pStack, int Data)
{
	return AddHead(pStack, Data);
}
NODE* PopStack(NODE*& pStack)
{
	return RemoveHead(pStack);
}
//--------QUEUE :
//----ENQUEUE tương ứng AddHead
//----DEQUEUE tương ứng RemoveTail
bool EnQueue(NODE*& pQueue, int Data)
{
	return AddHead(pQueue, Data);
}
NODE* DeQueue(NODE*& pQueue)
{
	return RemoveTail(pQueue);
}

void main()
{
	NODE* pStack = NULL;
	NODE* pQueue = NULL;
	int n = 10;
	while (n != 0)
	{
		PushStack(pStack, n);
		EnQueue(pQueue, n);
		n--;
	}
	NODE* pNode = DeQueue(pQueue);
	if (pNode != NULL) //<4>
		printf("\nGia tri phan tu (Queue) : %d\n", pNode->Key);
	else
		printf("\nNULL\n");
	NODE* pNode2 = PopStack(pStack);
	if (pNode2 != NULL)
		printf("\nGia tri phan tu (Stack) : %d\n", pNode2->Key);
	else
		printf("\nNULL\n");
	int x, y, z;
	cout << "\nNhap gia tri cua 3 phan tu them vao Stack: ";
	cin >> x;
	cin >> y;
	cin >> z;
	PushStack(pStack, x);
	PushStack(pStack, y);
	PushStack(pStack, z);
	if (pStack == NULL)
	{
		cout << "\nSTACK RONG, KHONG LAY DUOC PHAN TU";
	}
	else
	{
		for (int i = 1; i <= 4; i++)
		{
			NODE* p = PopStack(pStack);
			if (p != NULL)
				cout << "\nGia tri phan tu (Stack): " << p->Key;
			else
				cout << "\nNULL\n";
		}

	}

	int a, b, c;
	cout << "\nNhap gia tri cua 3 phan tu them vao Queue: ";
	cin >> a;
	cin >> b;
	cin >> c;
	EnQueue(pQueue, a);
	EnQueue(pQueue, b);
	EnQueue(pQueue, c);
	if (pQueue == NULL)
	{
		cout << "\nQUEUE RONG, KHONG LAY DUOC PHAN TU";
	}
	else
	{
		for (int i = 1; i <= 4; i++)
		{
			NODE* p = DeQueue(pQueue);
			if (p != NULL)
				cout << "\nGia tri phan tu (Queue): " << p->Key;
			else
				cout << "\nNULL\n";
		}

	}
}

/*
1. Khi biên dịch màn hình in:
Giá trị phần tử (Queue): 10
Giá trị phần tử (Stack): 1
2. n = 1 màn hình hiện ra:
Giá trị phần tử (Queue): 1
Giá trị phần tử (Stack): 1
3.
pNode khác NULL: Node sau khi xóa khỏi Queue và được gán cho pNode khác NULL (Có tồn tại Node trong Queue) sau đó in ra màn hình giá trị của pNode
pNode bằng NULL: Node sau khi xóa khỏi Queue và được gán cho pNode bằng NULL (Queue rỗng) sau đó in ra màn hình là NULL
4.
<1>Danh sách dược quản lý bởi pHead rỗng
<2>Danh sách có 1 Node duy nhất là pHead
<3>Lặp từ đầu danh sách đến Node phía trước pTail thì ngừng
5. Giá trị in ra màn hình:
a.   z y x 2
b.   9 8 7 6
*/