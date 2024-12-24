#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
#define MAX 100
struct Edges {
	int x, y, w;
};
int n;
vector<Edges> Canh;
int parent[MAX], sz[MAX];
void makeSet() {
	for (int i = 0; i <= n; i++){
		parent[i] = i;
		sz[i] = 1;
	}
}
int find(int v) {
	if (v == parent[v]) {
		return v;
	}
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
void readFile() {
	ifstream myFile("matrantrongso.txt");
		if (myFile.is_open()) {
			string temp;
			int count = 0;
			while (!myFile.eof()) {
				myFile >> temp;
				if (temp == "0") {
					break;
				}
				count++;
			}
			n = count;
			int curr;
			for (int i = 1; i < n; i++) {
				myFile >> curr;
				if (curr != 0) {
					Canh.push_back({0,i,curr});
				}
			}
			int temp1;
			for (int i = 1; i < n; i++) {
				for (int j = 0; j < i; j++) {
					myFile >> temp1;
				}
				for (int j = i; j < n; j++) {
					myFile >> curr;
					if (curr != 0) {
						Canh.push_back({ i,j,curr });
					}
				}
				
			}
			myFile.close();
		}
}
void output() {
	for (int i = 0; i < Canh.size(); i++) {
		cout << Canh[i].x << " " << Canh[i].y << " " << Canh[i].w << endl;
	}

}
bool cmp(const Edges& a, const Edges& b) {
	return a.w < b.w;
}
void kruskal() {
	vector<Edges> mst;
	int d = 0;
	sort(Canh.begin(), Canh.end(), cmp);
	for (int i = 0; i < Canh.size(); i++) {
		if (mst.size() == n - 1) break;
		Edges e = Canh[i];
		if (Union(e.x, e.y)) {
			mst.push_back(e);
			d += e.w;
		}
	}
	if (mst.size() != n - 1) {
		cout << "Do thi khong lien thong!!!" << endl;
	}
	else {
		cout << "MST: " << d << endl;
		for (auto it : mst) {
			cout << it.x << " " << it.y << " " << it.w << endl;
		}
	}
}
int main() {
	readFile();
	makeSet();
	output();
	cout << endl;
	kruskal();
	system("pause");
	return 0;
}