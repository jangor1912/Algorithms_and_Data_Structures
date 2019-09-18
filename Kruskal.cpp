#include <iostream>
using namespace std;

struct Neighbour {
	int u, v;
	Neighbour* next = nullptr;
	Neighbour(int u, int v) {
		this->u = u;
		this->v = v;
	}
};

struct FUGraph {
	int n;
	Neighbour** neighbours;
	int* L;
	int* S;
	FUGraph(int n) {
		this->n = n;
		this->neighbours = new Neighbour * [n];
		this->L = new int[n];
		this->S = new int[n];
		for (int i = 0; i < n; i++) {
			this->neighbours[i] = nullptr;
			this->L[i] = i;
			this->S[i] = 1;
		}
	}

	int fu_find(int i) {
		if (L[i] != i) {
			L[i] = fu_find(L[i]);
		}
		return L[i];
	}

	bool fu_union(int x, int y) {
		int fx = fu_find(x);
		int fy = fu_find(y);
		if (fx == fy) {
			return false;
		}
		if (S[fx] >= S[fy]) {
			L[fy] = L[fx];
			S[fx] += S[fy];
		}
		else {
			L[fx] = L[fy];
			S[fy] += S[fx];
		}
		return true;
	}

	int get_minimum_set_no() {
		int set_no = n;
		for (int i = 0; i < n; i++) {
			Neighbour* cur_edge = neighbours[i];
			while (cur_edge != nullptr) {
				if (cur_edge->u != cur_edge->v && fu_union(cur_edge->u, cur_edge->v)) {
					set_no--;
				}
				cur_edge = cur_edge->next;
			}
		}
		return set_no;
	}

	void add_edge(int u, int v) {
		Neighbour* new_edge = new Neighbour(u, v);
		new_edge->next = neighbours[u];
		neighbours[u] = new_edge;

		new_edge = new Neighbour(v, u);
		new_edge->next = neighbours[v];
		neighbours[v] = new_edge;
	}
};

int main() {
	int n;
	cin >> n;
	FUGraph* G = new FUGraph(n);
	for (int u = 0; u < n; u++) {
		int relative;
		cin >> relative;
		G->add_edge(u, relative-1);
	}
	int result = G->get_minimum_set_no();
	cout << result;
	return 0;
}