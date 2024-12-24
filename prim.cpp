#include<iostream>
#include<fstream>
#include<stack>
#include<string>
using namespace std;
#define MAX 100
struct edges {
	int x, y, w;
};
void inputMatrix(int a[][MAX], int& n) {
	cout << "Nhap so dinh: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Nhap dong thu " << i << ": ";
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
		cout << endl;
	}
}
void outputMatrix(int a[][MAX], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void docFile(int a[][MAX], int& n) {
	ifstream myFile("matrantrongso.txt");
	if (myFile.is_open()) {
		string vertex;
		myFile >> n;
		for (int i = 0; i < n; i++) {
			myFile >> vertex;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				myFile >> a[i][j];
			}
		}
		myFile.close();
	}
}
void prim(int a[][MAX], int u, int n) {
	bool tree[MAX] = { false };
	int d = 0, size = 0;
	edges road[MAX];
	tree[u] = true;
	while (size < n - 1) {
		int min_w = INT_MAX;
		int X = -1, Y = -1;
		for (int i = 0; i < n; i++) {
			if (tree[i] == true) {
				for (int k = 0; k < n; k++) {
					int j = k;
					int wei = a[i][j];
					if (wei != 0 && tree[j] == false && wei < min_w) {
						min_w = wei;
						X = j; Y = i;
					}
				}
			}		
		}
		if (X != -1 && Y != -1) {
			edges temp;
			temp.x = Y;
			temp.y = X;
			temp.w = min_w;
			road[size++] = temp;
			tree[X] = true;
			d += min_w;
		}
	}
	for (int i = 0; i < size; i++) {
		cout << road[i].x << " - " << road[i].y << ": " << road[i].w << endl;
	}
	cout << "Weight of tree: " << d << endl;

}
int main() {
	int a[MAX][MAX];
	int n;
	docFile(a, n);
	outputMatrix(a, n);
	prim(a, 0, n);
	system("pause");
	return 0;
}