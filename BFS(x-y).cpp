#include<iostream>
#include<fstream>
using namespace std;
#define MAX 100
struct edges {
	int x, y, w;
};
struct Node {
	Node* next;
	edges val;
};
int degree;
Node* First[MAX];
int degrees[MAX];
int parent[MAX];
Node* createNode(edges x) {
	Node* p = new Node;
	p->val = x;
	p->next = NULL;
	return p;
}
void addLast(Node*& head, edges e) {
	Node* p = createNode(e);
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
void readFile() {
	ifstream myFile("input2.txt");
	if (myFile.is_open()) {
		myFile >> degree;
		for (int i = 0; i < degree; i++) {
			myFile >> degrees[i];
		}
		for (int i = 0; i < degree; i++) {
			for (int j = 0; j < degrees[i]; j++) {
				edges e;
				e.x = i;
				myFile >> e.y >> e.w;
				addLast(First[i], e);
			}
		}
		myFile.close();
	}
}
void output() {
	for (int i = 0; i < degree; i++) {
		Node* p = First[i];
		cout << char(i + 65) << ": ";
		while (p != NULL) {
			cout << p->val.y << "(" << p->val.w << ")" << " ";
			p = p->next;
		}
		cout << endl;
	}
}
//Queue
struct Queue {
	int a[MAX];
	int front;
	int rear;
};
void init(Queue& q) {
	q.front = q.rear = -1;
}
bool isEmpty(Queue& q) {
	return q.front == -1 || q.front > q.rear;
}
bool isFull(Queue& q) {
	return q.rear == MAX - 1;
}
void enqueue(Queue& q, int x) {
	if (isFull(q)) {
		cout << "Queue is full!!" << endl;
	}
	if (isEmpty(q)) {
		q.front = 0;
	}
	q.rear++;
	q.a[q.rear] = x;
}
int dequeue(Queue& q) {
	if (isEmpty(q)) {
		cout << "Queue is empty!!!" << endl;
	}
	int ans = q.a[q.front++];
	if (isEmpty(q)) {
		q.front = q.rear = -1;
	}
	return ans;
}
//Stack
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
	if (s.top < MAX - 1) {
		return true;
	}
	return false;
}
void push(stack& s, int x) {
	if (isFull(s)) {
		s.b[++s.top] = x;
	}
}
int pop(stack& s) {
	if (isEmpty(s)) {
		return -1;
	}
	return s.b[s.top--];
}
void BFS(int x, int y) {
	bool visited[MAX] = { false };
	for (int i = 0; i < degree; i++) {
		parent[i] = -1;
	}
	Queue q;
	init(q);
	enqueue(q, x);
	visited[x] = true;
	while (!isEmpty(q)) {
		int temp = dequeue(q);
		if (temp == y) {
			break;
		}
		Node* p = First[temp];
		while (p!= NULL){
			if (visited[p->val.y] == false) {
				visited[p->val.y] = true;
				enqueue(q, p->val.y);
				parent[p->val.y] = temp;
			}
			p = p->next;
		}
	}
	stack s;
	init(s);
	int count = 0;
	for (int i = y; i != -1; i = parent[i]) {
		push(s, i);
		count++;
	}
	cout << "So dinh cua do thi: " << count << endl;

	while (!isEmpty(s)) {
		int top = pop(s);
		cout << top;
		if (!isEmpty(s)) {
			cout << " -> ";
		}
	}
	cout << endl;
}
int main() {
	readFile();
	output();
	BFS(0, 5);
	system("pause");
	return 0;
}