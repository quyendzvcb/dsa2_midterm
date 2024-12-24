#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
#define MAX 100
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
	ifstream myFile("file.txt");
	if (myFile.is_open()) {
		myFile >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				myFile >> a[i][j];
			}
		}
		myFile.close();
	}
}
//implement of Stack
struct Stack {
	int a[MAX];
	int top;
};
void init(Stack& s) {
	s.top = -1;
}
void push(Stack& s,int val) {
	if (s.top < MAX) {
		s.a[++s.top] = val;
	}
}
bool isEmpty(Stack& s) {
	return s.top == -1;
}
int pop(Stack& s) {
	if (!isEmpty(s)) {
		return s.a[s.top--];
	}
	return -1;
}
void DFS_Matrix(int a[][MAX], int u, int n) {
	bool visited[MAX] = { false };
	Stack s;
	init(s);
	push(s,u);
	int ndfs = 0;
	while (!isEmpty(s)) {
		int vertex = pop(s);
		if (ndfs < n) {
			if (!visited[vertex]) {
				cout << vertex << " ";
				ndfs++;
				visited[vertex] = true;
			}
			for (int i = 0; i < n; i++) {
				if (a[vertex][i] != 0 && visited[i] == false) {
					push(s, vertex);
					push(s,i);
					break;
				}
			}
		}
	}
}
int main() {
	int a[MAX][MAX];
	int n = 0;
	docFile(a, n);
	DFS_Matrix(a, 0, n);
	system("pause");
	return 0;
}