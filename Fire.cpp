//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Entry {
	int x, y;
	Entry* next = nullptr;
	Entry(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct Queue {
	int size = 0;
	Entry* begin = nullptr;
	Entry* end = nullptr;
	int last_x;
	int last_y;

	void push(int x, int y) {
		Entry* new_entry = new Entry(x, y);
		size++;
		last_x = new_entry->x;
		last_y = new_entry->y;

		if (this->begin == nullptr) {
			this->begin = this->end = new_entry;
			return;
		}
		this->end->next = new_entry;
		this->end = new_entry;
	}

	Entry* pop() {
		// Assuming queue is not empty
		Entry* result = this->begin;
		size--;
		this->begin = this->begin->next;
		result->next = nullptr;
		if (this->begin == nullptr) {
			this->end = nullptr;
		}
		return result;
	}

	bool empty() {
		return size == 0;
	}
};

struct Graph {
	int n, m;
	int neighbours_no = 4;
	Entry** neighbours = new Entry *[neighbours_no];

	void fill_neighbours() {
		this->neighbours[0] = new Entry(-1, 0);
		this->neighbours[1] = new Entry(0, -1);
		this->neighbours[2] = new Entry(1, 0);
		this->neighbours[3] = new Entry(0, 1);
	}

	Graph(int n, int m) {
		this->n = n;
		this->m = m;
		this->fill_neighbours();
	}
	void get_neighbours(int x, int y, Entry** result) {
		int size = 0;
		for (int i = 0; i < neighbours_no; i++) {
			int new_x = x + this->neighbours[i]->x;
			int new_y = y + this->neighbours[i]->y;
			if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m) {
				result[size]->x = new_x;
				result[size]->y = new_y;
				size++;
			}
		}
		for (int i = size; i < neighbours_no; i++) {
			result[i]->x = INT_MIN;
			result[i]->y = INT_MIN;
		}
	}
};

Entry* get_last_unburned(Graph* G, int n, int m, Queue* Q, bool** burning) {
	Entry** neighbours = new Entry * [4];
	for (int i = 0; i < 4; i++) {
		neighbours[i] = new Entry(INT_MIN, INT_MIN);
	}
	while (!Q->empty()) {
		Entry* e = Q->pop();
		burning[e->x][e->y] = true;
		//cout << "x = " << e->x << ", y= " << e->y << "\n";
		G->get_neighbours(e->x, e->y, neighbours);
		int i = 0;
		while (i < G->neighbours_no && neighbours[i]->x != INT_MIN) {
			int cur_x = neighbours[i]->x;
			int cur_y = neighbours[i]->y;
			if (!burning[cur_x][cur_y]) {
				burning[cur_x][cur_y] = true;
				Q->push(cur_x, cur_y);
			}
			//delete neighbours[i];
			i++;
		}
		//delete[] neighbours;
		delete e;
	}
	return new Entry(Q->last_x, Q->last_y);	
}

int main_asdnkjdsvjh() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	int k;
	cin >> n;
	cin >> m;
	cin >> k;
	Queue* Q = new Queue();
	Graph* G = new Graph(n, m);

	bool** burning = (bool**)calloc(n, sizeof(bool*));
	for (int i = 0; i < n; i++) {
		burning[i] = (bool*)calloc(m, sizeof(bool));
	}

	int x, y;
	for (int i = 0; i < k; i++) {
		cin >> x;
		cin >> y;
		Q->push(x-1, y-1);
		burning[x - 1][y - 1] = true;
	}
	Entry* result = get_last_unburned(G, n, m, Q, burning);
	cout << result->x+1 << " " << result->y+1;

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (burning[i][j]) {
				cout << "T ";
			}
			else {
				cout << "F ";
			}
		}
		cout << "\n";
	}*/
	return 0;
}