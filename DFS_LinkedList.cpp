#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
#define MAX 100
struct Node {
	Node* First[MAX];
	Node* next;
	int val;
};
void init(Node* First[]) {
	for (int i = 0; i < MAX; i++) {
		First[i] = NULL;
	}
}
Node* createNode(int x) {
	Node* p = new Node;
	p->val = x;
	p->next = NULL;
	return p;
}
void insertFirst(Node*& head, int x) {
	Node* p = createNode(x);
	if (head == NULL) {
		head = p;
	}
	p->next = head;
	head = p;
}
void insertLast(Node*& head, int x) {
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
//void readFile(Node* First[], int& n) {
//	ifstream myFile("matrix.txt");
//	if (myFile.is_open()) {
//		string temp;
//		int count = 0;
//		while (!myFile.eof()) {
//			myFile >> temp;
//			if (temp == "0") {
//				break;
//			}
//			count++;
//		}
//		n = count;
//		insertLast(First[0], 0);
//		for (int i = 0; i < n - 1; i++) {
//			int cur;
//			myFile >> cur;
//			insertLast(First[0], cur);
//		}
//		for (int i = 1; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				int cur1;
//				myFile >> cur1;
//				insertLast(First[i], cur1);
//			}
//		}
//		myFile.close();
//	}
//}
void readFile(Node* First[], int& n) {
	ifstream myFile("matrix.txt");
	if (myFile.is_open()) {
		myFile >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int temp;
				myFile >> temp;
				insertLast(First[i], temp);
			}
		}
	}
}
void outputMatrix(Node* First[], int n) {
	for (int i = 0; i < n; i++) {
		Node* p = First[i];
		while (p != NULL) {
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}
}
// Stack
struct Stack {
	int a[MAX];
	int top;
};
void init(Stack& s) {
	s.top = -1;
}
bool isEmpty(Stack& s) {
	return s.top == -1;
}
bool isFull(Stack& s) {
	return s.top > MAX;
}
void push(Stack& s, int x) {
	if (isFull(s)) {
		return;
	}
	s.a[++s.top] = x;
}
int pop(Stack& s) {
	if (isEmpty(s)) {
		return -1;
	}
	return s.a[s.top--];
}
void DFS_LinkedList(Node* First[],int u, int n) {
	bool visited[MAX] = { false };
	Stack s;
	init(s);
	push(s, u);
	while (!isEmpty(s)) {
		int vertex = pop(s);
		if (visited[vertex] == false) {
			cout << vertex << " ";
			visited[vertex] = true;
		}
		int count = 0;
		Node* p = First[vertex];
		while (p != NULL) {
			if (p->val == 1 && visited[count] == false) {
				push(s, vertex);
				push(s, count);
				break;
			}
			count++;
			p = p->next;
		}
	}
}
int main() {
	Node* First[MAX];
	init(First);
	int n;
	readFile(First, n);
	/*outputMatrix(First, n);*/
	DFS_LinkedList(First, 0, n);
	system("pause");
	return 0;
}