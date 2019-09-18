#include <iostream>
using namespace std;

struct Entry {
	int val;
	Entry* next = nullptr;
	Entry(int val) {
		this->val = val;
	}
};

struct PQueue {
	int* tab;
	int begin = 1;
	int end = 1;
	int n;
	PQueue(int n) {
		this->n = n;
		this->tab = new int[n];

	}

	void swap(int a, int b) {
		int tmp = tab[a];
		tab[a] = tab[b];
		tab[b] = tmp;
		return;
	}

	void heapify_up(int i) {
		int parent = i / 2;
		if (parent >= begin && tab[parent] < tab[i]) {
			swap(parent, i);
			heapify_up(parent);
		}
	}

	void heapify_down(int i) {
		int l = i * 2;
		int r = i * 2 + 1;
		int best = i;
		if (l < end && tab[l] > tab[best]) {
			best = l;
		}
		if (r < end && tab[r] > tab[best]) {
			best = r;
		}
		if (best != i) {
			swap(best, i);
			heapify_down(best);
		}
	}

	void push(int val) {
		tab[end] = val;
		end++;
		heapify_up(end - 1);
	}

	int pop() {
		end--;
		swap(begin, end);
		heapify_down(begin);
		return tab[end];
	}

	bool empty() {
		return begin == end;
	}
};

struct Neighbour{
	int u;
	int v;
	Neighbour* next = nullptr;
	Neighbour(int u, int v) {
		this->u = u;
		this->v = v;
	}
};

struct TopoGraph {
	int n;
	Neighbour** neighbours;
	TopoGraph(int n) {
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
	}

	bool topo_sort(int* tp_sort, int& size) {
		int* parents = new int[n];
		for (int i = 0; i < n; i++) {
			parents[i] = 0;
		}

		for (int i = 0; i < n; i++) {
			Neighbour* p = neighbours[i];
			while (p != nullptr) {
				int v = p->v;
				parents[v]++;
				p = p->next;
			}
		}
		PQueue* Q = new PQueue(n);
		for (int i = 0; i < n; i++) {
			if (parents[i] == 0) {
				Q->push(i);
			}
		}
		while (!Q->empty()) {
			int u = Q->pop();
			tp_sort[size] = u;
			size++;

			Neighbour* p = neighbours[u];
			while (p != nullptr) {
				int v = p->v;
				parents[v]--;
				if (parents[v] == 0) {
					Q->push(v);
				}
				p = p->next;
			}
		}
		return size == n;
	}
};

int main_jhasdbcsdhjcbdhj() {
	int n, m;
	cin >> n;
	cin >> m;
	TopoGraph* G = new TopoGraph(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u;
		cin >> v;
		//G->add_edge(u-1, v-1);
		G->add_edge(v - 1, u - 1);
	}
	int size = 0;
	int* tp_sort = new int[n];
	G->topo_sort(tp_sort, size);
	int l = 0;
	int r = n - 1;
	while (l < r) {
		int tmp = tp_sort[l];
		tp_sort[l] = tp_sort[r];
		tp_sort[r] = tmp;
		l++;
		r--;
	}
	/*cout << "Topo sort result:\n";
	for (int i = 0; i < n; i++) {
		cout << tp_sort[i]+1;
	}*/
	int* labels = new int[n];
	for (int i = 0; i < size; i++) {
		labels[tp_sort[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		cout << labels[i] + 1 << " ";
	}

	return 0;
}