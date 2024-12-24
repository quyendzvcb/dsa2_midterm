#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define MAX 100
struct Edges {
	int x, y, w;
};
struct Node {
	int val;
	Node* First[MAX];
	Node* next;
};
void init(Node* First[]) {
	for (int i = 0; i < MAX; i++) {
		First[i] = NULL;
	}
}
Node* createNode(int x) {
	Node* p = new Node;
	p->next = NULL;
	p->val = x;
	return p;
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
void readFile(Node* First[], int& n) {
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
		insertLast(First[0], 0);
		int curr;
		for (int i = 1; i < n; i++) {
			myFile >> curr;
			insertLast(First[0], curr);
		}
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				myFile >> curr;
				insertLast(First[i], curr);
			}
		}
		
	}
}
void outputFile(Node* First[], int n) {
	for (int i = 0; i < n; i++) {
		Node* p = First[i];
		while (p != NULL) {
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}
}
void Prim_linkedList(Node* First[], int u, int n) {
	bool visited[MAX] = { false };
	int d = 0, size = 0;
	Edges road[MAX];
	visited[u] = true;
	while (size < n - 1) {
		int min_w = INT_MAX;
		int X = -1, Y = -1;
		for (int i = 0; i < n; i++) {
			Node* p = First[i];
			if (visited[i] == true) {
				for (int k = 0; k < n; k++) {
					int j = k;
					int wei = p->val;
					p = p->next;
					if (wei != 0 && visited[k] == false && min_w > wei) {
						min_w = wei;
						X = j; Y = i;
					}
				}
			}
		}
		if (X != -1 && Y != -1) {
			Edges temp;
			temp.x = Y;
			temp.y = X;
			temp.w = min_w;
			visited[X] = true;
			road[size++] = temp;
			d += min_w;
		}
	}
	for (int i = 0; i < size; i++) {
		cout << road[i].x << " - " << road[i].y << ": " << road[i].w << endl;
	}
	cout << "Weight of grahp: " << d << endl;
}
int main() {
	Node* First[MAX];
	init(First);
	int n;
	readFile(First, n);
	//outputFile(First, n);
	Prim_linkedList(First, 0, n);
	system("pause");
	return 0;
}