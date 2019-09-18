#include <iostream>
using namespace std;

struct Entry {
	int val;
	Entry* next = nullptr;
	Entry(int val) {
		this->val = val;
	}
};

struct Queue {
	Entry* head = nullptr;
	Entry* tail = nullptr;
	int size = 0;

	void push(int val) {
		Entry* new_entry = new Entry(val);
		size++;
		if (tail == nullptr) {
			head = tail = new_entry;
			return;
		}
		tail->next = new_entry;
		tail = new_entry;
	}

	int pop() {
		// assumption queue is not empty
		Entry* entry = head;
		int result = entry->val;
		head = entry->next;
		if (head == nullptr) {
			tail = nullptr;
		}
		size--;
		delete entry;
		return result;
	}

	bool empty() {
		return size == 0;
	}
};

struct Neighbour {
	int u;
	int v;
	Neighbour* next = nullptr;
	Neighbour(int u, int v) {
		this->u = u;
		this->v = v;
	}
};

struct Graph {
	int n;
	Neighbour** neighbours;
	Graph(int n) {
		this->n = n;
		this->neighbours = new Neighbour * [n];
		for (int i = 0; i < n; i++) {
			this->neighbours[i] = nullptr;
		}
	}

	void add_edge(int u, int v) {
		Neighbour* new_edge = new Neighbour(u, v);
		new_edge->next = neighbours[u];
		neighbours[u] = new_edge;

		new_edge = new Neighbour(v, u);
		new_edge->next = neighbours[v];
		neighbours[v] = new_edge;
	}

	void get_bipartite_sets(int root, int* D, int& even_no) {
		for (int i = 0; i < n; i++) {
			D[i] = -1;
		}

		Queue* Q = new Queue();
		Q->push(root);
		even_no = 0;
		D[root] = 0;
		even_no++;
		while (!Q->empty()) {
			int u = Q->pop();
			Neighbour* p = neighbours[u];
			while (p != nullptr) {
				int v = p->v;
				if (D[v] == -1) {
					D[v] = D[u] + 1;
					if (D[v] % 2 == 0) {
						even_no++;
					}
					Q->push(v);
				}
				p = p->next;
			}
		}
	}
};

int main_shcbkwemckl() {
	int n;
	cin >> n;
	Graph* G = new Graph(n);
	for (int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u;
		cin >> v;
		G->add_edge(u-1, v-1);
	}
	int* D = new int[n];
	int even_no = 0;
	G->get_bipartite_sets(0, D, even_no);
	int odd_no = n - even_no;

	long long result = 0;
	for (int i = 0; i < n; i++) {
		if (D[i] % 2 == 0) {
			Neighbour* p = G->neighbours[i];
			int neighbour_no = 0;
			while (p != nullptr) {
				neighbour_no++;
				p = p->next;
			}
			result += (long long)(odd_no - neighbour_no);
		}
	}

	/*int* A = new int[n];
	int* B = new int[n];
	int a_size, b_size;
	a_size = b_size = 0;
	for (int i = 0; i < n; i++) {
		if (D[i] % 2 == 0) {
			A[a_size] = i;
			a_size++;
		}
		else {
			B[b_size] = i;
			b_size++;
		}
	}
	int result = 0;
	for (int i = 0; i < a_size; i++) {
		for (int j = 0; j < b_size; j++) {
			bool edge_exists = false;
			Neighbour* p = G->neighbours[A[i]];
			while (p != nullptr) {
				int v = p->v;
				if (v == B[j]) {
					edge_exists = true;
					break;
				}
				p = p->next;
			}
			if (edge_exists) {
				continue;
			}
			else {
				result++;
			}
		}
	}*/
	cout << result;

	/*cout << "\nPrinting A array:\n";
	for (int i = 0; i < n; i++) {
		if (D[i] % 2 == 0) {
			cout << i + 1 << " ";
		}
	}	
	cout << "\n";
	cout << "Printing B array:\n";
	for (int i = 0; i < n; i++) {
		if (D[i] % 2 == 1) {
			cout << i + 1 << " ";
		}
	}*/
	return 0;
}