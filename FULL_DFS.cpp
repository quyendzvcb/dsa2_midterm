#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#define MAX 100
using namespace std;
int degree;
int degrees[MAX];
int parent[MAX];
int parent_dfs[MAX];
int result_dfs[MAX]; int ndfs = 0;
struct Stack {
	int a[MAX];
	int top;
};
void init(Stack& s) {
	s.top = -1;
}
void push(Stack& s, int x) {
	s.a[++s.top] = x;
}
int pop(Stack& s) {
	return s.a[s.top--];
}
bool isEmpty(Stack s) {
	return s.top == -1;
}
void display(Stack& s) {
	while (!isEmpty(s)) {
		int temp = pop(s);
		cout << temp << " ";
	}
	cout << endl;
}
int NhapSoNguyen(string s, string t, int min, int max) {
	int n;
	do {
		cout << s;
		cin >> n;
		if (n < min || n > max)
			cout << t << endl;
	} while (n < min || n > max);
	return n;
}
struct edge {
	int x, y, w;
};
struct Node {
	edge val;
	Node* next;
};
struct Queue {
	Node* head;
};
void init(Queue& q) {
	q.head = NULL;
}
Node* createNode(edge x) {
	Node* p = new Node;
	p->val = x;
	p->next = NULL;
	return p;
}
void push(Queue& q, edge x) {
	if (q.head == NULL)
		q.head = createNode(x);
	else {
		Node* p = q.head;
		while (p->next != NULL)
			p = p->next;
		p->next = createNode(x);
	}
}
Node* pop(Queue& q) {
	if (q.head != NULL) {
		Node* p = q.head;
		q.head = q.head->next;
		p->next = NULL;
		return p;
	}
	return NULL;
}
bool isEmpty(Queue q) {
	return q.head == NULL;
}
void init(bool visit[]) {
	for (int i = 0; i < MAX / 2; i++)
		visit[i] = false;
}
void addLast(Node*& head, edge val) {
	if (head == NULL)
		head = createNode(val);
	else {
		Node* p = head;
		while (p->next != NULL)
			p = p->next;
		p->next = createNode(val);
	}
}
void delFirst(Node*& head) {
	if (head != NULL) {
		Node* p = head;
		head = head->next;
		p->next = NULL;
		delete p;
	}
}
void delNode(Node*& head, int x) {
	if (head != NULL) {
		Node* p = head;
		if (p->val.y == x) {
			head = head->next;
			p->next = NULL;
		}
		else {
			Node* prev = NULL;
			while (p != NULL && p->val.y != x) {
				p = p->next;
			}
			if (p != NULL && prev != NULL)
				prev->next = p->next;
		}
		delete p;
	}
}
struct ListNode {
	Node* list[MAX];
};
void init(ListNode& l) {
	for (int i = 0; i < MAX / 2; i++) {
		l.list[i] = NULL;
	}
}
void createFile() {
	int n;
	cout << "Nhap so luong dinh(n > 0): ";
	do {
		cin >> n;
		if (n <= 0)
			cout << "Luu y: n > 0,Nhap lai: ";
	} while (n <= 0);
	ofstream outFile("input2.txt");
	if (outFile.is_open()) {
		outFile << n << endl;
		cout << "Nhap bac cua tat ca cac dinh: ";
		for (int i = 0; i < n; i++) {
			int degree;
			cin >> degree;
			outFile << degree << " ";
			degrees[i] = degree;
		}
		outFile << endl;
		cout << "Nhap canh ke cua tat ca cac dinh \n";
		for (int i = 0; i < n; i++) {
			int count = degrees[i];
			while (count > 0) {
				int y, w;
				cin >> y >> w;
				outFile << y << " " << w;
				if (--count > 0)
					outFile << " ";
			}
			outFile << endl;
		}
		outFile.close();
	}
	else
		cout << "ERROR" << endl;
}
void readFile(ListNode& l) {
	fstream inputFile("input2.txt");
	if (inputFile.is_open()) {
		inputFile >> degree;
		for (int i = 0; i < degree; i++)
			inputFile >> degrees[i];
		for (int i = 0; i < degree; i++) {
			for (int j = 0; j < degrees[i]; j++) {
				edge e;
				e.x = i;
				inputFile >> e.y;
				inputFile >> e.w;
				addLast(l.list[i], e);
			}
		}
		inputFile.close();
	}
}
void display(ListNode l) {
	for (int i = 0; i < degree; i++) {
		if (l.list[i] != NULL) {
			cout << char(65 + i) << ": ";
			Node* p = l.list[i];
			while (p != NULL) {
				cout << p->val.y << "(" << p->val.w << ")";
				p = p->next;
				if (p != NULL)
					cout << " ";
			}
		}
		cout << endl;
	}
}
void del(ListNode& l) {
	for (int i = 0; i < degree; i++) {
		while (l.list[i] != NULL)
			delFirst(l.list[i]);
	}
}
void DFS(ListNode l, int x, int y = -1) {
	ndfs = 0;
	for (int i = 0; i < degree; i++)
		parent[i] = -1;
	bool visit[MAX / 2];
	init(visit);
	Stack s; init(s);
	push(s, x);
	while (!isEmpty(s)) {
		int temp = pop(s);
		if (ndfs < degree) {
			if (!visit[temp]) {
				result_dfs[ndfs++] = temp;
				visit[temp] = true;
			}
			if (temp == y)
				break;
			Node* p = l.list[temp];
			while (p != NULL) {
				if (!visit[p->val.y]) {
					push(s, temp);
					push(s, p->val.y);
					parent[p->val.y] = temp;
					break;
				}
				p = p->next;
			}
		}
	}
}
bool visit[MAX];
void dfs(ListNode l, int x, int y = -1) {
	visit[x] = true;
	cout << x << " ";
	if (x == y)
		return;
	for (Node* p = l.list[x]; p != NULL; p = p->next) {
		if (visit[p->val.y] == false) {
			parent_dfs[p->val.y] = x;
			dfs(l, p->val.y);
		}
	}
}
void display_dfs() {
	for (int i = 0; i < ndfs; i++) {
		cout << result_dfs[i] << " ";
	}cout << endl;
}
bool checkGraph(ListNode l) {
	for (int i = 0; i < degree; i++) {
		if (l.list[i] != NULL) {
			Node* p = l.list[i];
			while (p != NULL) {
				Node* q = l.list[p->val.y];
				while (q != NULL) {
					if (q->val.y == i)
						break;
					q = q->next;
				}
				if (q == NULL)
					return false;
				p = p->next;
			}
		}
	}
	return true;
	/*	 //unordered_map<int, unordered_set<int>> adjacencyMap;

	  //  // Xây d?ng b?ng b?m t? danh sách k?
	  //  for (int i = 0; i < vertex; i++) {
	  //      Node* p = l.list[i];
	  //      while (p != NULL) {
	  //          adjacencyMap[i].insert(p->val.y); // L?u c?nh (i -> p->val.y)
	  //          p = p->next;
	  //      }
	  //  }

	  //  // Ki?m tra tính ??i x?ng
	  //  for (int i = 0; i < vertex; i++) {
	  //      Node* p = l.list[i];
	  //      while (p != NULL) {
	  //          int u = i, v = p->val.y;
	  //          // N?u không tìm th?y c?nh ng??c (v -> u), tr? v? false
	  //          if (adjacencyMap[v].find(u) == adjacencyMap[v].end()) {
	  //              return false;
	  //          }
	  //          p = p->next;
	  //      }
	  //  }

	  //  return true; // ?? th? ??i x?ng*/
}
void EdgesDegree(ListNode l) {
	for (int i = 0; i < degree; i++) {
		if (l.list[i] != NULL) {
			cout << "Bac cua dinh " << char(65 + i) << " = " << degrees[i] << endl;
		}
	}
}
bool isConnected(ListNode l) {
	DFS(l, 0);
	return ndfs == degree;
}
void prim(ListNode l, int x) {
	int size = 0;
	bool Tree[MAX]; init(Tree);
	Tree[x] = true;
	edge result[MAX];
	while (size < degree - 1) {
		int min_w = INT_MAX;
		int X = -1, Y = -1;
		for (int i = 0; i < degree; i++) {
			if (Tree[i] == true) {
				Node* p = l.list[i];
				while (p != NULL) {
					int w = p->val.w;
					int j = p->val.y;
					if (Tree[j] == false && min_w > w)
					{
						X = i, Y = j, min_w = w;
					}
					p = p->next;
				}
			}
		}
		if (Y != -1) {
			edge e;
			e.x = X, e.y = Y, e.w = min_w;
			result[size++] = e;
			Tree[Y] = true;
		}
	}
	int d = 0;
	for (int i = 0; i < size; i++) {
		cout << "(" << char(65 + result[i].x) << ", " << char(65 + result[i].y) << ") = " << result[i].w << endl;
		d += result[i].w;
	}
	cout << "Tong trong so nho nhat = " << d << endl;
}
int find(int parent[], int dinh) {
	while (dinh != parent[dinh])
		dinh = parent[dinh];
	return dinh;
}
edge setE[MAX]; int nE = 0;
edge setT[MAX]; int nT = 0;
void createE(ListNode& l) {
	for (int i = 0; i < degree; i++) {
		if (l.list[i] != NULL) {
			Node* p = l.list[i];
			while (p != NULL) {
				setE[nE++] = p->val;
				delNode(l.list[p->val.y], p->val.x);
				p = p->next;
			}
		}
	}
}
void swap(edge& e1, edge& e2) {
	edge temp = e1;
	e1 = e2;
	e2 = temp;
}
void sortE() {
	for (int i = 0; i < nE - 1; i++) {
		for (int j = i + 1; j < nE; j++) {
			if (setE[i].w > setE[j].w)
				swap(setE[i], setE[j]);
		}
	}
}
void kruskal() {
	int parentMST[MAX];
	for (int i = 0; i < degree; i++)
		parentMST[i] = i;
	for (int i = 0; i < nE; i++) {
		int X = setE[i].x;
		int Y = setE[i].y;
		int root_X = find(parentMST, X);
		int root_Y = find(parentMST, Y);
		if (root_X != root_Y) {
			setT[nT++] = setE[i];
			parentMST[root_Y] = root_X;
		}
		if (nT == degree - 1)
			return;
	}
}
void display_MST() {
	int d = 0;
	for (int i = 0; i < nT; i++) {
		cout << "(" << char(65 + setT[i].x) << ", " << char(65 + setT[i].y) << ") = " << setT[i].w << endl;
		d += setT[i].w;
	}
	cout << "Tong trong so nho nhat = " << d << endl;
}
int main() {
	ListNode l;
	init(l);
	int opt;
	bool input = false;
	bool read = false;
	do {
		system("cls");
		cout << "====================MENU==================\n"
			<< "1.Tao File Input.txt\n"
			<< "2.Doc file Input.txt\n"
			<< "3.Xuat danh sach ke trong so\n"
			<< "4.Duyet DFS\n"
			<< "5.Kiem tra do thi vo huong hay co huong\n"
			<< "6.Tra ve bac cua moi dinh\n"
			<< "7.Tim so dinh va liet ke dinh tren duong di tu x -> y bang DFS(tinh ca x va y)\n"
			<< "8.Cay khung lon nhat(PRIM)\n"
			<< "9.Cay khung lon nhat(KRUSKAL)\n"
			<< "0.Thoat chuong trinh\n"
			<< "============================================\n";
		cout << "Nhap lua chon: ";
		do {
			cin >> opt;
			if (opt < 0 || opt > 9)
				cout << "Lua chon ko hop le!! Nhap lai: ";
		} while (opt < 0 || opt > 9);
		switch (opt)
		{
		case 1: {
			cout << "Chuc nang 1: Tao File Input.txt" << endl;
			createFile();
			cout << "Tao thanh cong\n";
			input = true;
			system("pause");
			break;
		}
		case 2: {
			if (true) {
				cout << "Chuc nang 2: Doc file Input.txt\n";
				readFile(l);
				cout << "Doc thanh cong\n";
				read = true;
				input = true;
			}
			else
				cout << "Du lieu chua nhap!!\n";
			system("pause");
			break;
		}
		case 3: {
			if (input && read) {
				cout << "Chuc nang 3: Xuat danh sach ke trong so\n";
				display(l);
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 4: {
			if (input && read) {
				cout << "Chuc nang 4: Duyet DFS\n";
				int start;
				cout << "Nhap dinh bat dau: "; cin >> start;
				DFS(l, start);
				display_dfs();
				cout << "DFS de quy" << endl;
				for (int i = 0; i < degree; i++)
					visit[i] = false;
				dfs(l, start);
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 5: {
			if (input && read) {
				cout << "Chuc nang 5: Kiem tra do thi vo huong hay co huong\n";
				cout << "Do thi: " << endl;
				display(l);
				if (checkGraph(l))
					cout << "Do thi vo huong!!\n";
				else
					cout << "Do thi co huong!!\n";
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 6: {
			if (input && read) {
				cout << "Chuc nang 6: Tra ve bac cua moi dinh\n";
				EdgesDegree(l);
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 7: {
			if (input && read) {
				cout << "Chuc nang 7: Tim so dinh va liet ke dinh tren duong di tu x -> y bang DFS(tinh ca x va y)\n";
				int x = NhapSoNguyen("Nhap dinh x: ", "Dinh ko ton tai", 0, degree - 1);
				int y = NhapSoNguyen("Nhap dinh y: ", "Dinh ko ton tai", 0, degree - 1);
				DFS(l, x, y);
				Stack s; init(s);
				for (int dinh = y; dinh != -1; dinh = parent[dinh])
					push(s, dinh);
				display(s);
				for (int i = 0; i < degree; i++)
					parent_dfs[i] = -1;
				dfs(l, x, y);
				cout << endl;
				init(s);
				for (int dinh = y; dinh != -1; dinh = parent_dfs[dinh])
					push(s, dinh);
				display(s);
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 8: {
			if (input && read) {
				int start = NhapSoNguyen("Nhap dinh bat dau: ", "Dinh khong ton tai!!!", 0, degree - 1);
				if (isConnected(l))
					prim(l, start);
				else
					cout << "Do thi ko lien thong , ko co cay bao trum nho nhat!" << endl;
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 9: {
			if (input && read) {
				cout << "Chuc nang 9: Cay khung nho nhat(KRUSKAL)\n";
				if (isConnected(l)) {
					createE(l);
					sortE();
					kruskal();
					display_MST();
				}
				else
					cout << "Do thi ko lien thong , ko co cay bao trum nho nhat!" << endl;
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 0: {
			cout << "Chuong trinh ket thuc!" << endl;
			system("pause");
			del(l);
			cout << "Xoa du lieu thanh cong\n";
			return 1;
		}
		}
	} while (opt >= 1 && opt <= 9);

	return 1;
}
