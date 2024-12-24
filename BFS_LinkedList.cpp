#include<iostream>
#include<fstream>
using namespace std;
#define MAX 20
struct Node {
	int val;
	Node* next;
	Node* First[MAX];
};
void init(Node*First[]) {
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
	else {
		p->next = head;
		head = p;
	}
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
void docFile(Node* First[], int& n) {
	ifstream myFile("matrix.txt");
	if (myFile.is_open()) {
		myFile >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int tmp;
				myFile >> tmp;
				insertLast(First[i], tmp);
			}
			myFile.ignore();
		}
		myFile.close();
	}
}
void output(Node* First[], int n) {
	for (int i = 0; i < n; i++) {
		Node* p = First[i];
		while (p != NULL){
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}
}
// queue
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
void enqueue(Queue& q, int val) {
	if (isEmpty(q)) {
		q.front = 0;
	}
	q.rear++;
	q.a[q.rear] = val;
}
int dequeue(Queue& q) {
	if (isEmpty(q)) {
		cout << "Queue is empty!! " << endl;
		return -1;
	}
	int ans = q.a[q.front++];
	if (isEmpty(q)) {
		q.front = q.rear = -1;
	}
	return ans;
}
void BFS_LinkedList(Node* First[], int u, int n) {
	bool visited[MAX] = { false };
	Queue q;
	init(q);
	enqueue(q, u);
	visited[u] = true;
	while (!isEmpty(q)) {
		int vertex = dequeue(q);
		int count = 0;
		cout << vertex << " ";
		while (First[vertex] != NULL) {
			if (First[vertex]->val == 1 && visited[count] == false) {
				visited[count] = true;
				enqueue(q, count);
			}
			count++;
			First[vertex] = First[vertex]->next;
		}
	}
}
int main() {
	Node* First[MAX];
	init(First);
	int n;
	docFile(First, n);
	/*output(First, n);*/
	BFS_LinkedList(First, 0, n);
	system("pause");
	return 0;
}