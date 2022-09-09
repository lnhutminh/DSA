#include <iostream>
#include<fstream>
#include<string>
#define MAX 100
using namespace std;

struct OTO
{
	string hang;
	string dongxe;
	int tocdo;
};

struct NODE
{
	OTO oto;
	NODE* pNext;
};

NODE* CreateNode(OTO x)
{
	NODE* p = new NODE;
	if (p == NULL)
	{
		return NULL;
	}
	p->oto= x;

	p->pNext = NULL;
	return p;
}

void AddHead(NODE*& pHead, OTO x)
{
	NODE* p = new NODE;
	p = CreateNode(x);
	if (p == NULL)
	{
		return;
	}
	if (pHead == NULL)
	{
		pHead = p;
		return;
	}
	p->pNext = pHead;
	pHead = p;
}

void Doc_1_oto(ifstream& filein, OTO& x)
{
	cin.ignore();
	getline(filein, x.hang, ',');
	getline(filein, x.dongxe, ',');
	cin.ignore();
	filein >> x.tocdo;
}

void Doc_file_oto(ifstream& filein, NODE*&pHead, int &n)
{
	filein.open("input1.txt", ios_base::in);
	if (filein.fail() == true)
	{
		cout << "\nFile khong ton tai";
		return;
	}
	filein >> n;
	for (int i = 0; i < n; i++)
	{
		OTO x;
		Doc_1_oto(filein, x);
		AddHead(pHead, x);
	}
	filein.close();
}

void Xuat_oto(NODE* pHead)
{
	for (NODE* k = pHead; k != NULL; k = k->pNext)
	{
		cout << "\nHang xe: " <<pHead->oto.hang;
		cout << "\nDong xe: " << pHead->oto.dongxe;
		cout << "\nToc do toi da cua xe: " << pHead->oto.tocdo;
	}
}

struct SVNode
{
	long MSSV;
	string sName;
	float gpa;
	SVNode* pLeft, * pRight;
};

void Xuat_mang(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
}

void Sap_xep(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j] < a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

bool Kiem_tra_SNT(int n)
{
	if (n < 2)
	{
		return false;
	}
	for (int i = 2; i < n; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

void Mang_SNT_va_sap_xep(int a[], int n, int b[], int& m)
{
	m = 0;
	for (int i = 0; i < n; i++)
	{
		if (Kiem_tra_SNT(a[i]) == true)
		{
			b[m] = a[i];
			m++;
		}
	}
	Sap_xep(b, m);
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

void Menu()
{
	while (true)
	{
		system("cls");
		cout << "\n===============";
		cout << "\n1. Cau 1";
		cout << "\n2. Cau 2";
		cout << "\n3. Cau 3";
		cout << "\n0.Ket thuc";
		cout << "\n===============";
		int luachon;
		do
		{
			cout << "\nNhap lua chon: ";
			cin >> luachon;
			if (luachon < 0 || luachon >3)
			{
				cout << "\nNhap khong hop le. Xin kiem tra lai";
				system("pause");
			}
		} while (luachon < 0 || luachon >3);
		if (luachon == 0)
		{
			break;
		}
		else if (luachon ==1)
		{
			/*NODE* pHead = NULL;
			int n;
			OTO oto;
			ifstream filein;
			cin.ignore();
			Doc_file_oto(filein, pHead, n);
			cout << "\nDanh sach oto:\n";
			Xuat_oto(pHead);
			cout << "\ny/n\n";
			char c;
			cout << "\nTiep tuc nhap y. Thoat chon n: ";
			cin >> c;
			if (c == 'n' || c == 'N')
			{
				break;
				system("pause");
			}*/
			cout << "\nEm chua lam xong";
			system("pause");
		}
		else if (luachon == 2)
		{
			/*cout << "\ny/n\n";
			char c;
			cout << "\nTiep tuc nhap y. Thoat chon n: ";
			cin >> c;
			if (c == 'n' || c == 'N')
			{
				break;
				system("pause");
			}*/
			cout << "\nEm chua lam xong";
			system("pause");
		}
		else
		{
			ifstream filein;
			filein.open("input3.txt", ios_base::in);
			if (filein.fail() == true)
			{
				cout << "\nFile khong ton tai";
				return;
			}
			int n;
			int a[MAX];
			filein >> n;
			for (int i = n-1; i >= 0; i--)
			{
				filein >> a[i];
			}
			filein.close();
			cout << "\nMang da nhap (xuat theo STACK): ";
			Xuat_mang(a, n);
			int m;
			int b[MAX];
			cout << "\nMang so nguyen to va duoc sap xep giam dan: ";
			Mang_SNT_va_sap_xep(a, n, b, m);
			Xuat_mang(b, m);

			cout << "\nMang A duoc sap xep chan tang le giam: ";
			Sap_xep_chan_tang_le_giam(a, n);
			Xuat_mang(a, n);

			cout << "\ny/n\n";
			char c;
			cout << "\nTiep tuc nhap y. Thoat chon n: ";
			cin >> c;
			if (c == 'n' || c == 'N')
			{
				break;
				system("pause");
			}
			system("pause");
		}
	}
}
int main()
{
	Menu();
	return 0;
}