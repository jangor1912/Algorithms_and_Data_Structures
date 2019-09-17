#include <iostream>
using namespace std;

struct Neighbour {
	int u;
	int v;
	int weight = 1;
	Neighbour* next = nullptr;
	Neighbour(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->weight = w;
	}

	bool lesser(Neighbour* other) {
		if (this->weight < other->weight) {
			return true;
		}
		return false;
	}
};

struct Entry {
	int v, prev;
	long long distance;
	Entry(int v, long long d, int prev) {
		this->v = v;
		this->distance = d;
		this->prev = prev;
	}

	bool lesser(Entry* other) {
		if (this->distance < other->distance) {
			return true;
		}
		return false;
	}
};

struct PriorityQueue {
	int begin = 1;
	int end = 1;
	int max_size;
	Entry** tab;
	PriorityQueue(int size) {
		this->max_size = size;
		this->tab = new Entry *[size];
	}

	void swap(int a, int b) {
		Entry* tmp = tab[a];
		tab[a] = tab[b];
		tab[b] = tmp;
	}

	void heapify_up(int i) {
		int parent = i / 2;
		if (parent >= begin && tab[i]->lesser(tab[parent])) {
			swap(i, parent);
			heapify_up(parent);
		}
	}

	void heapify_down(int i) {
		int l = i * 2;
		int r = i * 2 + 1;
		int best = i;
		if (l < end && tab[l]->lesser(tab[best])) {
			best = l;
		}
		if (r < end && tab[r]->lesser(tab[best])) {
			best = r;
		}
		if (best != i) {
			swap(i, best);
			heapify_down(best);
		}
	}

	void push(int u, long long d, int prev) {
		Entry* new_entry = new Entry(u, d, prev);
		tab[end] = new_entry;
		end++;
		heapify_up(end - 1);
	}

	Entry* pop() {
		end--;
		swap(begin, end);
		heapify_down(begin);
		return tab[end];
	}

	Entry* top() {
		return tab[begin];
	}

	bool empty() {
		return begin == end;
	}

};

struct Graph {
	int n,m;
	Neighbour** neighbours;
	Graph(int n, int m) {
		this->n = n;
		this->m = m;
		this->neighbours = new Neighbour * [n];
		for (int i = 0; i < n; i++) {
			this->neighbours[i] = nullptr;
		}
	}

	void add_edge(int u, int v, int w) {
		Neighbour* new_edge = new Neighbour(u, v, w);
		new_edge->next = this->neighbours[u];
		this->neighbours[u] = new_edge;

		new_edge = new Neighbour(v, u, w);
		new_edge->next = this->neighbours[v];
		this->neighbours[v] = new_edge;
	}

	void find_shortest_path(int start, int goal, int* path, int& length) {
		Entry** distances = new Entry*[n+1];
		for (int i = 1; i <= n; i++) {
			distances[i] = new Entry(i, LLONG_MAX, -1);
		}
		PriorityQueue* PQ = new PriorityQueue(n+m+3);
		PQ->push(start, 0, -1);
		while (!PQ->empty()) {
			Entry* e = PQ->pop();
			long long cur_distance = e->distance;
			int v = e->v;
			if (distances[v]->distance == LLONG_MAX) {
				distances[v] = e;
				Neighbour* cur_neighbour = this->neighbours[v];
				while (cur_neighbour != nullptr) {
					if (distances[cur_neighbour->v]->distance == LLONG_MAX) {
						PQ->push(cur_neighbour->v, cur_distance + cur_neighbour->weight, v);
					}
					cur_neighbour = cur_neighbour->next;
				}
			}
		}
		int prev_entry_index;
		Entry* cur_entry = distances[goal];
		if (cur_entry->distance == LLONG_MAX) {
			return;
		}
		do {
			path[length] = cur_entry->v;
			prev_entry_index = cur_entry->prev;
			length++;
			cur_entry = distances[cur_entry->prev];
		} while (prev_entry_index != -1);

	}

};


int main_sdcsbdnvn() {
	int n, m;
	cin >> n;
	cin >> m;
	Graph* G = new Graph(n+1, m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u;
		cin >> v;
		cin >> w;
		G->add_edge(u, v, w);
	}
	int length = 0;
	int* path = new int[n];
	G->find_shortest_path(1, n, path, length);
	

	if (length == 0) {
		cout << -1;
	}
	else {
		for (int i = length - 1; i >= 0; i--) {
			cout << path[i] << " ";
		}
	}
	return 0;
}