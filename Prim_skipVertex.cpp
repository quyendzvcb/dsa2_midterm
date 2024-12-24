#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#define MAX 100
struct edges {
	int x, y, w;
};
int a[MAX][MAX];
char degree[MAX];
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
		cout << degree[i]<<" ";
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
int main() {
	int u = 0;
	readFile();
	//output();
	edges e;
	cout << "Nhap canh can xoa " << endl;
	cout << "Nhap x: ";
	cin >> e.x;
	cout << "Nhap y: ";
	cin >> e.y;
	cout << "Nhap trong so: ";
	cin >> e.w;
	prim(0, e);
	system("pause");
	return 0;
}