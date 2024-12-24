#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 100
struct edges {
	int x, y, w;
};
int a[MAX][MAX];
int degree[MAX];
vector<edges> canh;
int n;
void readFile() {
	fstream myFile("matrantrongso.txt");
	if (myFile.is_open()) {
		myFile >> n;
		for (int i = 0; i < n; i++) {
			myFile >> degree[i];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				myFile >> a[i][j];
			}
			myFile.ignore();
		}

		myFile.close();
	}
}
void output() {
	for (int i = 0; i < n; i++) {
		cout << degree[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void prim(int u, edges e) {
	bool visited[MAX] = { false };
	int d = 0, size = 0;
	edges road[MAX];
	visited[u] = true;
	while (size < n - 1) {
		int min_w = INT_MAX;
		int X = -1, Y = -1;
		for (int i = 0; i < n; i++) {
			if (visited[i] == true) {
				for (int k = 0; k < n; k++) {
					int j = k;
					int wei = a[i][j];
					if (e.x == i && e.y == j) continue;
					if (wei != 0 && visited[k] == false && wei < min_w) {
						min_w = wei;
						X = j;
						Y = i;
					}
				}
			}
		}
		if (X != -1 && Y != -1) {
			edges e;
			e.x = Y;
			e.y = X;
			e.w = min_w;
			visited[X] = true;
			road[size++] = e;
			d += min_w;
		}
	}
	cout << "MST: " << d << endl;
	for (int i = 0; i < size; i++) {
		cout << road[i].x << " - " << road[i].y << ": " << road[i].w << endl;
	}
}
void readFile1() {
	ifstream myFile("input2.txt");
	if (myFile.is_open()) {
		edges e;
		myFile >> n;
		for (int i = 0; i < n; i++) {
			myFile >> degree[i];
		}
		int y, w;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < degree[i]; j++) {
				myFile >> y >> w;
				canh.push_back({ i, y, w });
			}
		}
	}
}
void output1() {
	for (auto it : canh) {
		cout << it.x << " - " << it.y << ": " << it.w << endl;
	}
}
int parent[MAX], sz[MAX];
void make_set() {
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
		sz[i] = 1;
	}
}
int find(int v) {
	if (v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}
bool Union(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return false;
	if (sz[a] < sz[b]) swap(a, b);
	parent[b] = a;
	sz[a] += sz[b];
	return true;
}
bool cmp(edges &a, edges& b) {
	return a.w < b.w;
}
void kruskal() {
	vector<edges> mst;
	int d = 0;
	sort(canh.begin(), canh.end(), cmp);
	for (int i = 0; i < canh.size(); i++) {
		if (mst.size() == n - 1) break;
		edges curr = canh[i];
		if (Union(curr.x, curr.y)) {
			mst.push_back(curr);
			d += curr.w;
		}
	}
	if (mst.size() != n - 1) {
		cout << "Do thi khong lien thong!!" << endl;
	}
	else {
		cout << "MST: " << d << endl;
		for (auto it : mst) {
			cout << it.x << " - " << it.y << ": " << it.w << endl;
		}
	}

}
int main() {
	int u = 0;
	bool read = false;
	bool riel = false;
	int choose;
	do {
		system("cls");
		cout << "======================================\n";
		cout << "1> Doc File\n";
		cout << "2> Prim skip 1 canh\n";
		cout << "3> Xuat ds ke\n";
		cout << "4> Kruskal\n";
		cout << "0> Thoat chuong trinh!!\n";
		cout << "======================================\n";
		cout << "\nNhap lua chon cua ban: ";
		do {
			cin >> choose;
			if (choose < 0 || choose > 4) {
				cout << "Lua chon ko hop le!! Nhap lai: ";
			}
		} while (choose < 0 || choose > 4);
		switch (choose) {
		case 1: {
			read = true;
			readFile1();
			cout << "Ban da doc file!!" << endl;
			system("pause");
			break;
		}
		case 2: {
			if (read) {
				do {
					edges e;
					cout << "Nhap canh can xoa " << endl;
					cout << "Nhap x: ";
					cin >> e.x;
					cout << "Nhap y: ";
					cin >> e.y;
					cout << "Nhap trong so: ";
					cin >> e.w;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							int curr = a[i][j];
							if (curr != 0 && e.x == i && e.y == j && e.w == curr) {
								riel = true;
							}
						}
					}
					if (riel) {
						prim(0, e);
					}
					else {
						cout << "Khong ton tai canh nay!!";
					}
				} while (!riel);
				
			}
			else {
				cout << "Du lieu chua duoc nhap!!";
			}
			system("pause");
			break;
		}
		case 3: {
			if (read) {
				output1();
			}
			else {
				cout << "Du lieu chua duoc nhap!!";
			}
			system("pause");
			break;
		}
		
		case 4: {
			if (read) {
				make_set();
				kruskal();
				system("pause");
			}
			else {
				cout << "Chua nhap file!!" << endl;
			}
			break;
		}
		case 0: {
			cout << "Cam on ban da su dung!!" << endl;
			system("pause");
			return 1;
		}
		}
	} while (choose >= 1 && choose <= 4);
		system("pause");
		return 0;
}