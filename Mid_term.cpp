#include <iostream>
#include <fstream>
#define MAX 100
using namespace std;

void NhapMang(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "\nNhap phan tu a[" << i << "]: ";
		cin >> a[i];
	}
}

void XuatMang(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
}

void Sap_xep_chan_tang_le_giam(int a[], int n)
{
	int min_chan;
	int max_le;
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] % 2 == 0)
		{
			min_chan = i;
			for (int j = i + 1; j < n; j++)
			{
				if (a[j] % 2 == 0 && a[min_chan] > a[j])
				{
					swap(a[min_chan], a[j]);
				}
			}
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] % 2 != 0)
		{
			max_le = i;
			for (int j = i + 1; j < n; j++)
			{
				if (a[j] % 2 != 0 && a[max_le] < a[j])
				{
					swap(a[max_le], a[j]);
				}
			}
		}
	}
}

void Mang_c(int a[], int n, int c[], int& m)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] % 2 == 0)
		{
			c[m] = a[i];
			m++;
		}
	}
}

void BubbleSort(int c[], int m)
{
	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < m - i - 1; j++)
		{
			if (c[j] < c[j + 1])
			{
				swap(c[j], c[j + 1]);
			}
		}
	}
}

struct NODE
{
	int data;
	NODE* pNext;
};

NODE* CreateNode(int x)
{
	NODE* pHead = new NODE;
	if (pHead == NULL)
	{
		return NULL;
	}
	pHead->data = x;
	pHead->pNext = NULL;
	return pHead;
}

bool AddHead(NODE*& pHead, int data)
{
	NODE* p = CreateNode(data);
	if (p == NULL)
	{
		return false;
	}
	if (pHead == NULL)
	{
		pHead = p;
		return true;
	}
	else
	{
		p->pNext = pHead;
		pHead = p;
	}
	return true;
}

void PrintList(NODE* pHead)
{
	for (NODE* k = pHead; k != NULL; k = k->pNext)
	{
		cout << k->data << " ";
	}
}

void DeleteHead(NODE*& pHead)
{
	if (pHead == NULL)
	{
		cout << "Khong co gi de xoa";
		return;
	}
	else
	{
		pHead = pHead->pNext;
	}
}

void DeleteLast(NODE*& pHead)
{
	if (pHead == NULL)
	{
		cout << "\nKhong co gi de xoa";
		system("pause");
	}
	else if (pHead->pNext == NULL)
	{
		DeleteHead(pHead);
	}
	else
	{
		NODE* g = pHead;
		while (g->pNext != NULL)
		{
			g = g->pNext;
		}
		for (NODE* k = pHead; k != NULL; k = k->pNext)
		{
			if (k->pNext == g)
			{
				delete g;
				k->pNext = NULL;
			}
		}
	}
}

void Delete(NODE*pHead , int k) 
{
	if (k == 0 || pHead == NULL || pHead->pNext == NULL) 
	{
		DeleteHead(pHead); 
	}
	else 
	{
		int dem = 1;
		NODE* p = pHead;
		while (p->pNext->pNext != NULL && dem != k) {
			p = p->pNext;
			++dem;
		}
		if (dem != k) 
		{
			DeleteLast(pHead);
		}
		else {
			p->pNext = p->pNext->pNext;
		}
	}
}


int main()
{
	int choose;
	int n;
	int a[MAX];
	do
	{
		system("cls");
		cout << "\n ===========================================================";
		cout << "\n1. Nhap - Xuat mang.";
		cout << "\n2. Dung selection sort sap xep chan tang le giam.";
		cout << "\n3. Xuat mang c gom cac so chan va sap xep giam dan bang bubble sort.";
		cout << "\n4. Doc file input.txt va tao danh sach lien ket don va xuat danh sach tu cuoi toi dau.";
		cout << "\n5. Nhap phan tu thu k (vi tri) va xoa - in danh sach sau khi xoa.";
		cout << "\n0. Ket thuc.";
		cout << "\n ===========================================================";
		do
		{
			cout << "\nNhap lua chon: ";
			cin >> choose;
			if (choose < 0 || choose > 5)
			{
				cout << "\nNhap khong hop le. Xin kiem tra lai.";
				system("pause");
			}
		} while (choose < 0 || choose > 5);
		switch (choose)
		{
		case 1:
		{
			do
			{
				cout << "\nNhap so luong phan tu: ";
				cin >> n;
				if (n < 0 || n > 5)
				{
					cout << "\nNhap khong hop le. Xin kiem tra lai.";
					system("pause");
				}
			} while (n <= 0);
			NhapMang(a, n);
			cout << "\nMang vua nhap: ";
			XuatMang(a, n);
		
			system("pause");
			break;
		}
		case 2:
		{
			Sap_xep_chan_tang_le_giam(a, n);
			cout << "\nMang sau khi sap xep: ";
			XuatMang(a, n);
			system("pause");
			break;
		}
		case 3:
		{
			int m = 0;
			int c[MAX];
			Mang_c(a, n, c, m);
			BubbleSort(c, m);
			cout << "Mang c gam cac so chan giam dan: ";
			XuatMang(c, m);
			system("pause");
			break;
		}
		case 4:
		{
			ifstream filein;
			filein.open("input.txt", ios::in);
			if (filein.fail() == true)
			{
				cout << "\nFile khong ton tai. Xin kiem tra lai.";
				system("pause");
			}
			filein >> n;
			NODE*pHead = NULL;
			for (int i = 0; i < n; i++)
			{
				int x;
				filein >> x;
				AddHead(pHead, x);
			}

			cout << "\nXuat danh sach tu dau toi cuoi: ";
			PrintList(pHead);
			filein.close();
			system("pause");
			break;
		}
		case 5:
		{
			ifstream filein;
			filein.open("input.txt", ios::in);
			if (filein.fail() == true)
			{
				cout << "\nFile khong ton tai. Xin kiem tra lai.";
				system("pause");
			}
			filein >> n;
			NODE* pHead = NULL;
			for (int i = 0; i < n; i++)
			{
				int x;
				filein >> x;
				AddHead(pHead, x);
			}
			int k;
			cout << "\nDanh sach TRUOC khi xoa: ";
			PrintList(pHead);
			do
			{
				cout << "\nNhap vi tri thu k can xoa: ";
				cin >> k;
				if (k >=  n)
				{
					cout << "\nNhap khong hop le. Xin kiem tra lai.";
					system("pause");
				}
			} while (k >= n);
			Delete(pHead,k);
			cout << "\nDanh sach SAU khi xoa: ";
			PrintList(pHead);
			system("pause");
			break;
		}
		default:
		{
			system("pause");
			break;
		}
		}
	} while (choose <= 5 && choose > 0);
	return 0;
}