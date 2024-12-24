#include <iostream>
#include <fstream>
#include <cstring>
#define MAX 100
using namespace std;
int degree;
int a[MAX][MAX];
char dinh[MAX];
int result_bfs[MAX]; int nbfs = 0;
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
	int val;
	Node* next;
};
struct Queue {
	Node* head;
};
void init(Queue& q) {
	q.head = NULL;
}
Node* createNode(int x) {
	Node* p = new Node;
	p->val = x;
	p->next = NULL;
	return p;
}
void push(Queue& q, int x) {
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
	for (int i = 0; i < MAX; i++)
		visit[i] = false;
}
void BFS(int x) {
	bool visit[MAX]; init(visit);
	Queue q;
	init(q);
	push(q, x);
	while (!isEmpty(q)) {
		Node* temp = pop(q);
		if (!visit[temp->val]) {
			int u = temp->val;
			result_bfs[nbfs++] = u;
			visit[u] = true;
			for (int i = 0; i < degree; i++) {
				if (a[u][i] != 0 && !visit[i]) {
					push(q, i);
				}
			}
		}
	}
}
void bfs(int x) {
	bool visit[MAX]; init(visit);
	Queue q;
	init(q);
	push(q, x);
	visit[x] = true;
	while (!isEmpty(q)) {
		Node* temp = pop(q);
		int u = temp->val;
		cout << u << " ";
		for (int i = 0; i < degree; i++) {
			if (!visit[i] && a[u][i] != 0) {
				push(q, i);
				visit[i] = true;
			}
		}
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
	ofstream outFile("input.txt");
	if (outFile.is_open()) {
		outFile << n << endl;
		cout << "Nhap tat ca du lieu\n";
		for (int i = 0; i < n; i++) {
			char dinh;
			cin >> dinh;
			outFile << dinh << " ";
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int edge;
				cin >> edge;
				outFile << edge << " ";
			}
			outFile << endl;
		}
		outFile.close();
	}
	else
		cout << "ERROR" << endl;
}
void readFile() {
	fstream inputFile("input.txt");
	if (inputFile.is_open()) {
		inputFile >> degree;
		while (!inputFile.eof()) {
			for (int i = 0; i < degree; i++)
				inputFile >> dinh[i];
			for (int i = 0; i < degree; i++) {
				for (int j = 0; j < degree; j++)
					inputFile >> a[i][j];
			}
		}
		inputFile.close();
	}
}
void display() {
	cout << "\t";
	for (int i = 0; i < degree; i++)
		cout << dinh[i] << "\t";
	cout << endl;
	for (int i = 0; i < degree; i++) {
		cout << dinh[i] << "\t";
		for (int j = 0; j < degree; j++)
			cout << a[i][j] << "\t";
		cout << endl;
	}
}
bool checkGraph() {
	for (int i = 0; i < degree; i++) {
		for (int j = i + 1; j < degree; j++) {
			if (a[i][j] != a[j][i])
				return false;
		}
	}
	return true;
}
void degreeVertex() {
	for (int i = 0; i < degree; i++) {
		int count = 0;
		char s = 'A';
		cout << "Bac cua dinh " << char(s + i);
		for (int j = 0; j < degree; j++) {
			if (a[i][j] != 0)
				count++;
		}
		cout << " : " << count << endl;
	}
}
void BFS(int x, int y) {
	bool visit[MAX];
	for (int i = 0; i < MAX; i++) {
		visit[i] = false;
	}

	Queue q;
	init(q);
	push(q, x);
	visit[x] = true;

	int parent[MAX];
	for (int i = 0; i < MAX; i++) {
		parent[i] = -1;
	}

	while (!isEmpty(q)) {
		Node* temp = pop(q);
		int u = temp->val;

		// If the target node is found, exit the loop
		if (u == y) {
			break;
		}

		for (int i = 0; i < degree; i++) {
			if (a[u][i] != 0 && !visit[i]) {
				visit[i] = true;
				parent[i] = u;  // Set parent of vertex i
				push(q, i);
			}
		}
	}

	// Backtrack to find the path
	Stack s;
	init(s);
	int count = 0;

	for (int vertex = y; vertex != -1; vertex = parent[vertex]) {
		push(s, vertex);
		count++;
	}

	cout << "Tong so dinh tu x -> y: " << count << endl;

	while (!isEmpty(s)) {
		int top = pop(s);
		cout << top;
		if (!isEmpty(s)) {
			cout << " -> ";
		}
	}
	cout << endl;
}
bool isConnected(int x) {
	nbfs = 0;
	BFS(x);
	return degree == nbfs;
}
void prim(int x) {
	bool check[MAX];
	for (int i = 0; i < MAX; i++)
		check[i] = false;
	edge result[MAX];
	check[x] = true;
	int size = 0; int d = 0;
	while (size < degree - 1) {
		int min_w = INT_MAX;
		int X = -1, Y = -1;
		for (int i = 0; i < degree; i++) {
			if (check[i] == true) {
				for (int j = 0; j < degree; j++) {
					int wei = a[i][j];
					if (a[i][j] != 0 && check[j] == false && wei < min_w) {
						X = i, Y = j, min_w = wei;
					}
				}
			}
		}
		if (Y != -1) {
			edge e; e.x = X, e.y = Y, e.w = min_w;
			result[size++] = e;
			d += e.w;
			check[Y] = true;
		}
	}
	cout << "Tong trong so min = " << d << endl;
	for (int i = 0; i < size; i++) {
		cout << "(" << result[i].x << ", " << result[i].y << ") = " << result[i].w << endl;
	}
}
edge setE[MAX]; int nE = 0;
edge Tree[MAX]; int nT = 0; int wT = 0;
void createE() {
	for (int i = 0; i < degree; i++) {
		for (int j = i + 1; j < degree; j++) {
			if (a[i][j] != 0) {
				edge e;
				e.x = i, e.y = j, e.w = a[i][j];
				setE[nE++] = e;
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
int findRoot(int parent[], int dinh) {
	while (parent[dinh] != dinh)
		dinh = parent[dinh];
	return dinh;
}
void kruskal() {
	int parent[MAX];
	for (int i = 0; i < degree; i++)
		parent[i] = i;
	for (int i = 0; i < nE; i++) {
		int X = setE[i].x;
		int Y = setE[i].y;
		int root_X = findRoot(parent, X);
		int root_Y = findRoot(parent, Y);
		// check chu trinh
		if (root_X != root_Y) {
			edge e;
			e.x = X;
			e.y = Y;
			e.w = setE[i].w;
			parent[root_Y] = root_X;
			Tree[nT++] = e;
		}
		if (nT == degree - 1)
			break;
	}
}
int main() {
	int opt;
	bool input = false;
	bool read = false;
	do {
		system("cls");
		cout << "====================MENU==================\n"
			<< "1.Tao File Input.txt\n"
			<< "2.Doc file Input.txt\n"
			<< "3.Xuat ma tran trong so\n"
			<< "4.Duyet BFS\n"
			<< "5.Kiem tra do thi vo huong hay co huong\n"
			<< "6.Tra ve bac cua moi dinh\n"
			<< "7.Tim so dinh va liet ke dinh tren duong di tu x -> y bang BFS(tinh ca x va y)\n"
			<< "8.Cay khung nho nhat(PRIM)\n"
			<< "9.Cay khung nho nhat(KRUSKAL)\n"
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
			if (1 == 1) {
				cout << "Chuc nang 2: Doc file Input.txt\n";
				readFile();
				cout << "Doc thanh cong\n";
				read = true;
			}
			else
				cout << "Du lieu chua nhap!!\n";
			system("pause");
			break;
		}
		case 3: {
			if (1 == 1) {
				cout << "Chuc nang 3: Xuat ma tran trong so\n";
				display();
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 4: {
			if (1==1) {
				cout << "Chuc nang 4: Duyet BFS\n";
				int start;
				cout << "Nhap dinh bat dau: "; cin >> start;
				cout << "Cach 1: \n";
				BFS(start);
				for (int i = 0; i < degree; i++)
					cout << result_bfs[i] << " ";
				cout << endl;
				cout << "Cach 2: \n";
				bfs(start);
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
				display();
				if (checkGraph())
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
			if (1 == 1) {
				cout << "Chuc nang 6: Tra ve bac cua moi dinh\n";
				degreeVertex();
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 7: {
			if (1 == 1 ) {
				cout << "Chuc nang 7: Tim so dinh va liet ke dinh tren duong di tu x -> y bang BFS(tinh ca x va y)\n";
				int x = NhapSoNguyen("Nhap dinh x: ", "Dinh ko ton tai", 0, degree - 1);
				int y = NhapSoNguyen("Nhap dinh y: ", "Dinh ko ton tai", 0, degree - 1);
				BFS(x, y);
			}
			else
				cout << "Du lieu chua co!!\n";
			system("pause");
			break;
		}
		case 8: {
			if (input && read) {
				cout << "Chuc nang 8: .Cay khung nho nhat(PRIM)\n";
				int start = NhapSoNguyen("Nhap dinh bat dau: ", "Dinh khong ton tai!!!", 0, degree - 1);
				if (isConnected(start))
					prim(start);
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
				if (isConnected(0)) {
					createE();
					sortE();
					kruskal();
					for (int i = 0; i < nT; i++) {
						wT += Tree[i].w;
						cout << "(" << Tree[i].x << ", " << Tree[i].y << ") = " << Tree[i].w << endl;
					}
					cout << "Tong trong so cua cay bao trum = " << wT << endl;
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
			return 1;
		}
		}
	} while (opt >= 1 && opt <= 9);
	return 1;
}