#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#define MAX 100
struct edges {
	int x, y, w;
};
vector<edges> canh;
int degree;
int parent[MAX];
int degrees[MAX];
void readFile() {
	fstream myFile("input2.txt");
	if (myFile.is_open()) {
		myFile >> degree;
		for (int i = 0; i < degree; i++) {
			myFile >> degrees[i];
		}
		int y, w;
		for (int i = 0; i < degree; i++) {
			for (int j = 0; j < degrees[i]; j++) {
				myFile >> y;
				myFile >> w;
				canh.push_back({ i, y, w });
			}
		}
		myFile.close();
	}
}
void output() {
	for (auto it: canh) {
		cout << it.x << "-" << it.y << ": " << it.w << endl;
	}
}

// STACK
struct stack {
	int b[MAX];
	int top;
};
void init(stack& s) {
	s.top = -1;
}
bool isEmpty(stack& s) {
	return s.top == -1;
}
bool isFull(stack& s) {
	if (s.top > MAX - 1) {
		return true;
	}
	return false;
}
void push(stack& s, int x) {
	if (!isFull(s)) {
		s.b[++s.top] = x;
	}
}
int pop(stack& s) {
	if (!isEmpty(s)) {
		return s.b[s.top--];
	}
	return -1;
}
void DFS(int x, int y) {
	bool visited[MAX] = { false };
	for (int i = 0; i < degree; i++) {
		parent[i] = -1;
	}
	int ndfs = 0;
	stack s;
	init(s);
	push(s, x);
	while (!isEmpty(s)) {
		int temp = pop(s);
		if (ndfs < degree) {
			if (!visited[temp]) {
				visited[temp] = true;
				ndfs++;
			}
			if (temp == y) break;
			for (int i = 0; i < canh.size(); i++) {
				edges curr = canh[i];
				if (curr.x == temp && visited[curr.y] == false) {
					push(s, curr.x);
					push(s, curr.y);
					parent[curr.y] = curr.x;
					break;
				}
			}
		}
	}
	stack result;
	init(result);
	int count = 0;
	for (int i = y; y != -1; y = parent[y]) {
		push(result, y);
		count++;
	}
	cout << "So dinh di tu x->y: " << count << endl;
	while (!isEmpty(result)) {
		int top = pop(result);
		cout << top;
		if (!isEmpty(result)) {
			cout << " -> ";
		}
	}
}
int main() {
	readFile();
	output();
	DFS(0, 5);
	system("pause");
	return 0;
}