#include <stdio.h>
#include <iostream>
using namespace std;
struct AVLNODE
{
	int Key;
	int bal; // thuộc tính cho biết giá trị cân bằng
	// 0: cân bằng, 1: lệch trái, 2: lệch phải
	AVLNODE* pLeft;
	AVLNODE* pRight;
};
AVLNODE* CreateNode(int Data)
{
	AVLNODE* pNode;
	pNode = new AVLNODE; //Xin cấp phát bộ nhớ động để tạo một phần tử (node) mới
	if (pNode == NULL) {
		return NULL;
	}
	pNode->Key = Data;
	pNode->pLeft = NULL;
	pNode->pRight = NULL;
	pNode->bal = 0;
	return pNode;
}
void LeftRotate(AVLNODE*& P)
{
	AVLNODE* Q;
	Q = P->pRight;
	P->pRight = Q->pLeft;
	Q->pLeft = P;
	P = Q;
}
void RightRotate(AVLNODE*& P)
{
	AVLNODE* Q;
	Q = P->pLeft;
	P->pLeft = Q->pRight;
	Q->pRight = P;
	P = Q;
}
void LeftBalance(AVLNODE*& P)
{
	switch (P->pLeft->bal) {
	case 1: //mất cân bằng trái trái
		RightRotate(P);
		P->bal = 0;
		P->pRight->bal = 0;
		break;
	case 2: //Ghi chú: cho biết đây là trường hợp mất cân bằng nào?
		LeftRotate(P->pLeft);
		RightRotate(P);
		switch (P->bal) {
		case 0:
			P->pLeft->bal = 0;
			P->pRight->bal = 0;
			break;
		case 1:
			P->pLeft->bal = 0;
			P->pRight->bal = 2;
			break;
		case 2:
			P->pLeft->bal = 1;
			P->pRight->bal = 0;
			break;
		}
		P->bal = 0;
		break;
	}
}
void RightBalance(AVLNODE*& P)
{
	switch (P->pRight->bal) {
	case 1: //Ghi chú: cho biết đây là trường hợp mất cân bằng nào?
		RightRotate(P->pRight);
		LeftRotate(P);
		switch (P->bal) {
		case 0:
			P->pLeft->bal = 0;
			P->pRight->bal = 0;
			break;
		case 1:
			P->pLeft->bal = 1;
			P->pRight->bal = 0;
			break;
		case 2:
			P->pLeft->bal = 0;
			P->pRight->bal = 2;
			break;
		}
		P->bal = 0;
		break;
	case 2: //Ghi chú: cho biết đây là trường hợp mất cân bằng nào?
		LeftRotate(P);
		P->bal = 0;
		P->pLeft->bal = 0;
		break;
	}
}
int InsertNode(AVLNODE*& tree, int x)
{
	int res;
	if (tree == NULL) { //Ghi chú: cho biết ý nghĩa của câu lệnh này
		tree = CreateNode(x);
		if (tree == NULL) {
			return -1; //thêm ko thành công vì thiếu bộ nhớ
		}
		return 2;//thêm thành công và làm tăng chiều cao cây
	}
	else {
		if (tree->Key == x) {
			return 0; //khóa này đã tồn tại trong cây
		}
		else if (tree->Key > x) {
			res = InsertNode(tree->pLeft, x);
			if (res < 2) {
				return res;
			}
			switch (tree->bal) { //Ghi chú: giải thích ý nghĩa của câu lệnh switch này
			case 0:
				tree->bal = 1;
				return 2;
			case 1:
				LeftBalance(tree);
				return 1;
			case 2:
				tree->bal = 0;
				return 1;
			}
		}
		else {
			res = InsertNode(tree->pRight, x);
			if (res < 2) {
				return res;
			}
			switch (tree->bal) {
			case 0:
				tree->bal = 2;
				return 2;
			case 1:
				tree->bal = 0;
				return 1;
			case 2:
				RightBalance(tree);
				return 1;
			}
		}
	}
}
void Traverse(AVLNODE* t)
{
	if (t != NULL)
	{
		Traverse(t->pLeft);
		printf("Khoa: %d, can bang: %d\n", t->Key, t->bal);
		Traverse(t->pRight);
	}
}
void RemoveAll(AVLNODE*& t)
{
	if (t != NULL) {
		RemoveAll(t->pLeft);
		RemoveAll(t->pRight);
		delete t;
	}
}

///////////// 8. ////////////////////

AVLNODE* Search(AVLNODE* t, int x)
{
	if (t == NULL)
		return NULL;
	if (x < t->Key)
		Search(t->pLeft, x);
	else
		if (x > t->Key)
			Search(t->pRight, x);
		else
		{
			return t;
		}
}

int Height(AVLNODE* pNode)
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

void SearchStandFor(AVLNODE*& Tree, AVLNODE*& q)
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

void Can_bang_cay(AVLNODE*& Tree)
{
	if (Tree != NULL)
	{
		Can_bang_cay(Tree->pLeft);
		Can_bang_cay(Tree->pRight);
		if (Height(Tree->pRight) - Height(Tree->pLeft) > 1)
		{
			RightBalance(Tree);
		}
		else if (Height(Tree->pLeft) - Height(Tree->pRight) > 1)
		{
			LeftBalance(Tree);
		}
	}
}
void RemoveNode(AVLNODE*& Tree, int x)
{
	AVLNODE* p;
	if (Tree == NULL)
		printf("%d khong co trong cay", x);
	else
	{
		if (x < Tree->Key)
		{
			RemoveNode(Tree->pLeft, x);
		}
		else if (x > Tree->Key)
		{
			RemoveNode(Tree->pRight, x);
		}
		else
		{
			p = Tree;
			if (p->pRight == NULL)
				Tree = p->pLeft;
			else if (p->pLeft == NULL)
					Tree = p->pRight;
			else
				SearchStandFor(Tree->pLeft, p);
			delete p;
		}
	}
	Can_bang_cay(Tree);
}

void Traverse_1(AVLNODE* t)
{
	if (t != NULL)
	{
		Traverse(t->pLeft);
		printf("Khoa: %d, can bang: %d\n", t->Key);
		Traverse(t->pRight);
	}
}

void Chieu_cao_sau_khi_xoa(AVLNODE* Tree)
{
	if (Tree != NULL)
	{
		Chieu_cao_sau_khi_xoa(Tree->pLeft);
		Chieu_cao_sau_khi_xoa(Tree->pRight);
		cout << "\nChieu cao cua Node " << Tree->Key << " ben trai: " << Height(Tree->pLeft)+1 << " ben phai : " << Height(Tree->pRight)+1;
	}
}

//////////////////////

int main()
{
	AVLNODE* tree;
	//Ghi chu: Tại sao lại phải thực hiện phép gán phía dưới?
	tree = NULL;
	int Data;
	do
	{
		printf("Nhap vao du lieu, -1 de ket thuc: ");
		scanf_s("%d", &Data);
		if (Data == -1)
			break;
		InsertNode(tree, Data);
	} while (Data != -1);
	printf("\nCay AVL vua tao: \n");
	Traverse(tree);
	////////// Phần thêm vào /////////

	AVLNODE* p;
	int x;
	printf("Nhap vao 1 gia tri de tim: \n");
	scanf_s("%d", &x);
	p = Search(tree, x);
	if (p != NULL)
	{
		printf("%d co xuat hien trong cay.\n", x);
		printf("Chieu cao cua nut %d la %d\n", x, Height(p));
	}
	else
		printf("%d khong co trong cay.\n", x);

	int y;
	printf("Nhap vao 1 gia tri de xoa: ");
	scanf_s("%d", &y);
	RemoveNode(tree, y);
	printf("\nCay sau khi xoa: \n");
	Traverse(tree);
	Chieu_cao_sau_khi_xoa(tree);



	//////////////////////////////////
	RemoveAll(tree);
	return 0;
}

/*
2.
Khi nhâp: -1  -> Cây AVL vừa tạo:
Khi nhập: 10 30 35 32 20 8 -1 ->in: Khóa: 8, cân bằng: 0
									Khóa: 10, cân bằng: 0
									Khóa: 20, cân bằng: 0
									Khóa: 30, cân bằng: 0
									Khóa: 32, cân bằng: 0
									Khóa: 35, cân bằng: 1
Khi nhập: 30 40 50 -10 -5 -1 ->in: Khóa: -10, cân bằng: 0
								   Khóa: -5, cân bằng: 0
								   Khóa: 30, cân bằng: 0
								   Khóa: 40, cân bằng: 1
								   Khóa: 50, cân bằng: 0
3.
Các Node được xuất ra màn hình theo thứ tự tăng dần vì câu lệnh Traverse(tree) duyệt theo thứ tự Node Trái - Node Gốc - Node Phải
5.
Khóa: -5, cân bằng: 2
Khóa: 7, cân bằng: 0
Khóa: 10, cân bằng: 0
Khóa: 15, cân bằng: 0
Khóa: 20, cân bằng: 1
Khóa: 30, cân bằng: 0
Khóa: 35, cân bằng: 0
Khóa: 50, cân bằng: 2
Khóa: 55, cân bằng: 0
Khóa: 57, cân bằng: 0
Khóa: 65, cân bằng: 0

6.
				30
			  /    \
			10      50
		   /  \    /  \
		-5    20 35   57
		 \   /       /  \
		 7   15     55  65

7.
InsertNode
+tree == NULL: Node tree đang rỗng có thể chứa giá trị
+switch(tree->bal): vòng lặp kiểm tra Node tree đang cân bằng, lệch phải hay lệch trái
RightBalance:
+case:1: mất cân bằng phải - trái
+case:2: mất cân bằng phải - phải
LeftBalance:
+case:2: mất cân bằng trái - phải
main()
+tree = NULL; đại chỉ của tree là NULL không phải tree trỏ đến NULL

*/