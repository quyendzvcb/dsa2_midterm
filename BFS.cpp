#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
using namespace std;
#define MAX 100
int n;
void inputMatrix(int a[][MAX], int& n) {
	cout << "Nhap so dinh cua do thi: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Nhap dong thu " << i << ": ";
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
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
int vertex() {
	ifstream file("file.txt");
	int curr, count = 0;
	if (file.is_open()) {
		while (!file.eof()) {
			file >> curr;
			count++;
		}
		file.close();
	}
	return count;
}
void docFile(int a[][MAX], int& n) {
	ifstream myFile("file.txt");
	if (myFile.is_open()) {
		n = sqrt(vertex());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				myFile >> a[i][j];
			}
		}
		myFile.close();
	}
}
//Implement queue
struct queue {
	int a[MAX];
	int front;
	int rear;
};
void init(queue& q) {
	q.front = -1;
	q.rear = -1;
}
bool isEmpty(queue& q) {
	return q.front == -1 || q.front > q.rear;
}
bool isFull(queue& q) {
	return q.rear == MAX - 1;
}
void enqueue(queue& q, int val) {
	if (isFull(q)) {
		cout << "Queue is full!!" << endl;
		return;
	}
	if (isEmpty(q)) {
		q.front = 0;
	}
	q.rear++;
	q.a[q.rear] = val;
}
	
int dequeue(queue& q) {
	if (isEmpty(q)) {
		cout << "Queue is empty!! " << endl;
		return -1;
	}
	int ans = q.a[q.front++];
	if (isEmpty(q))
		q.front = q.rear = -1;
	return ans;
}
void BFS(int a[][MAX], int u, int n) {
	bool visited[MAX] = { false };
	queue q;
	init(q);
	enqueue(q, u);
	visited[u] = true;
	while (!isEmpty(q)) {
		int vertex = dequeue(q);
		if (visited[vertex] == true) {
			cout << vertex << " ";
			for (int i = 0; i < n; i++) {
				if (a[vertex][i] != 0 && visited[i] == false) {
					visited[i] = true;
					enqueue(q, i);
				}
			}
		}
	}
}
int main() {
	int a[MAX][MAX];
	int n = 0;
	docFile(a, n);
	/*outputMatrix(a, n);*/
	BFS(a, 0, n);
	system("pause");
	return 0;
}