#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
#define MAX 100
int n, m = 0;
int parent[MAX], sz[MAX];
struct edges {
	int x, y, w;
};
struct Node {
	edges val;
	Node* next;
};
vector<edges> canh;
Node* First[MAX];
void init() {
	for (int i = 0; i < MAX; i++) {
		First[i] = NULL;
	}
}
Node* createNode(edges x) {
	Node* p = new Node;
	p->next = NULL;
	p->val = x;
	return p;
}
void insertLast(Node*&head, edges x) {
	Node* p = createNode(x);
	if (head == NULL) {
		head = p;
	}
	else {
		Node* q = head;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	}
}
void make_set() {
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		sz[i] = 1;
	}
}
int find(int v) {
	if (parent[v] == v) {
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
		string s;
		edges e;
		int count = 0;
		while (!myFile.eof()) {
			myFile >> s;
			if (s == "0") {
				break;
			}
			count++;
		}
		n = count;
		int curr;
		for (int i = 1; i < n; i++) {
			myFile >> curr;
			if (curr != 0) {
				e.x = 0;
				e.y = i;
				e.w = curr;
				insertLast(First[m], e);
				m++;
			}
		}
		int temp;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				myFile >> temp;
			}
			for (int k = i; k < n ; k++){
				myFile >> curr;
				if (curr != 0) {
					e.x = i;
					e.y = k;
					e.w = curr;
					insertLast(First[m], e);
					m++;
				}
			}
		}
		myFile.close();
	}
}
void output() {
	for (int i = 0; i < m; i++) {
		Node* p = First[i];
		while (p != NULL) {
			cout << p->val.x <<" "<< p->val.y <<" "<<p->val.w;
			p = p->next;
		}
		cout << endl;
	}
}
void swap(Node*& a, Node*& b) {
	Node* p = a;
	a = b;
	b = p;
}
void sort() {
	for (int i = 0; i < m - 1; i++) {
		for (int j = i + 1; j < m; j++) {
			if (First[i]->val.w > First[j]->val.w) {
				swap(First[i], First[j]);
			}
		}
	}
}
void kruskal_linkedList() {
	Node* result[MAX];
	int count = 0;
	int d = 0;
	sort();
	for (int i = 0; i < m; i++) {
		if (count == n - 1) break;
		Node* p = First[i];
		if (Union(p->val.x, p->val.y)) {
			result[count++] = p;
			d += p->val.w;
		}
	}
	if (count != n - 1) {
		cout << "Do thi khong lien thong!!\n";
	}
	else {
		cout << "MST: " << d << endl;
		for (int i = 0; i < count; i++) {
			cout <<char( result[i]->val.x + 65) << " - " << char(result[i]->val.y + 65)<<": " << result[i]->val.w << endl;
		}
	}
}
int main() {
	readFile();
	make_set();
	//cout << m << endl;
	sort();
	cout << n << endl;
	output();
	kruskal_linkedList();
	system("pause");
	return 0;
}