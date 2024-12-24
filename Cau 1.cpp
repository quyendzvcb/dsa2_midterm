#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
#define MAX 100
struct edges {
	int x, y, w;
};
int a[MAX][MAX];
int n;
int parent[MAX];
int degrees[MAX];
vector<edges> canh;
void inputMatrix() {
	
	ofstream offFile("input.txt");
	if (offFile.is_open()) {
		do {
			cout << "Nhap so dinh cua do thi: ";
			cin >> n;
			if (n > 50) {
				cout << "Vui long nhap lai!!" << endl;
			}
		} while (n > 50);
		offFile << n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
				offFile << a[i][j];
			}
		}
		offFile.close();
	}
}
//void output() {
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			cout << a[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
void readFile() {
	fstream myFile("input1.txt");
	if (myFile.is_open()) {
		myFile >> n;
		for (int i = 0; i < n; i++) {
			myFile >> degrees[i];
		}
		int y, w;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < degrees[i]; j++) {
				myFile >> y >> w;
				canh.push_back({ i, y, w });
			}
		}
		myFile.close();
	}
}
void output() {
	for (auto it : canh) {
		cout << it.x << " - " << it.y << ": " << it.w << endl;
	}
}
////STACk
//struct stack {
//	int b[MAX];
//	int top;
//};
//void init(stack& s) {
//	s.top = -1;
//}
//bool isEmpty(stack&s) {
//	return s.top == -1;
//}
//void push(stack&s, int x) {
//	s.b[++s.top] = x;
//}
//int pop(stack&s) {
//	if (!isEmpty(s)) {
//		return s.b[s.top--];
//	}
//}
//// QUEUE
//struct queue {
//	int c[MAX];
//	int front, rear;
//};
//void init(queue&q) {
//	q.front = q.rear = -1;
//}
//bool isEmpty(queue&q) {
//	return q.front == -1 || q.front > q.rear;
//}
//void enqueue(queue&q, int x) {
//	q.rear++;
//	q.c[q.rear] = x;
//}
//int dequeue(queue&q) {
//	if (!isEmpty(q)) {
//		cout << "Queue is empty!!" << endl;
//	}
//	else {
//		int ans = q.c[q.front++];
//		if (isEmpty(q)) {
//			q.front = q.rear = -1;
//		}
//		return ans;
//	}
//	return -1;
//}
//void BFS(int x) {
//	
//}
void BFS(int x) {
	bool visited[MAX] = { false };
	queue<int> q;
	q.push(x);
	visited[x] = true;
	while (!q.empty()) {
		int temp = q.front(); q.pop();
		cout << temp << " ";
			for (int i = 0; i < canh.size(); i++) {
				edges e = canh[i];
					if (e.w != 0 && visited[e.y] == false && e.x == temp) {
						visited[e.y] = true;
						q.push(e.y);
					}
		}
	}
}
void DFS(int x) {
	bool visited[MAX] = { false };
	stack<int> s;
	s.push(x);
	int ndfs = 0;
	while (!s.empty()) {
		int temp = s.top(); s.pop();
		if (ndfs < n) {
			if (!visited[temp]) {
				cout << temp << " ";
				visited[temp] = true;
				ndfs++;
			}
			for (int i = 0; i < canh.size(); i++) {
				edges e = canh[i];
				if (e.w != 0 && visited[e.y] == false && e.x == temp) {
					s.push(temp);
					s.push(e.y);
					break;
				}
			}
		}

	}
}
void prim(int x) {
	bool tree[MAX] = { false };
	int d = 0, sz = 0;
	edges road[MAX];
	tree[x] = true;
	while (sz < n - 1) {
		int X = -1, Y = -1;
		int min_w = INT_MAX;
		for (int i = 0; i < canh.size(); i++) {
			edges e = canh[i];
			if (tree[e.x] == true) {
				int j = e.y;
				int wei = e.w;
				if (wei != 0 && tree[j] == false && wei < min_w) {
					min_w = wei;
					X = j; Y = e.x;
				}
			}
		}
		if (X != -1 && Y != -1) {
			edges temp;
			temp.x = Y;
			temp.y = X;
			temp.w = min_w;
			tree[X] = true;
			road[sz++] = temp;
			d += min_w;
		}
	}
	cout << "MST: " << d << endl;
	for (int i = 0; i < sz; i++) {
		cout << road[i].x << " - " << road[i].y << ": " << road[i].w << endl;
	}
}
int sz[MAX];
void make_set() {
	for (int i = 0; i < n; i++) {
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
bool cmp(edges&a, edges& b) {
	return a.w < b.w;
}
void kruskal(int x) {
	vector<edges> mst;
	int count = 0;
	sort(canh.begin(), canh.end(), cmp);
	for (int i = 0; i < canh.size(); i++) {
		if (mst.size() == n - 1) break;
		edges e = canh[i];
		if (Union(e.x, e.y)) {
			mst.push_back(e);
			count += e.w;
		}
	}
	cout << "MST: " << count << endl;
	for (auto it : mst) {
		cout << it.x << " - " << it.y << ": " << it.w << endl;
	}
}
void find_path(int x, int y) {
	bool visited[MAX] = { false };
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
	queue<int> q;
	q.push(x);
	visited[x] = true;
	while (!q.empty()) {
		int temp = q.front(); q.pop();
		if (temp == y) break;
		for (int i = 0; i < canh.size(); i++) {
			edges e = canh[i];
			if (e.w != 0 && visited[e.y] == false && e.x == temp) {
				visited[e.y] = true;
				parent[e.y] = e.x;
				q.push(e.y);
			}
		}
	}
	stack<int> path;
	int d = 0;
	for (int i = y; i != -1; i = parent[i]) {
		path.push(i);
		d++;
	}
	cout << "Distance: " << d << endl;
	while (!path.empty()) {
		int temp = path.top(); path.pop();
		cout << temp;
		if (!path.empty()) {
			cout << " -> ";
		}
	}
}
int main() {
	readFile();
	/*output();*/
	DFS(0);
	cout << endl;
	BFS(0);
	cout << endl;
	prim(0);
	cout << endl;
	make_set();
	kruskal(0);
	cout << endl;
	find_path(0, 4);
	cout << endl;
	system("pause");
	return 0;
}