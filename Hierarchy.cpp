#include <iostream>
using namespace std;

struct Neighbour {
	int u, v, cost;
	Neighbour* next = nullptr;
	Neighbour(int u, int v, int cost) {
		this->u = u;
		this->v = v;
		this->cost = cost;
	}

	bool lesser(Neighbour* other) {
		if (this->cost < other->cost) {
			return true;
		}
		return false;
	}
};

struct MST_Graph {
	int n,m;
	Neighbour** neighbours;
	Neighbour** tmp_edges;
	int* qualifications;
	int* supervisor;
	MST_Graph(int n, int m, int* qualifications) {
		this->n = n;
		this->m = m;
		this->neighbours = new Neighbour * [n];
		this->supervisor = new int [n];
		this->tmp_edges = new Neighbour * [m];
		for (int i = 0; i < n; i++) {
			this->neighbours[i] = nullptr;
		}
		for (int i = 0; i < m; i++) {
			this->tmp_edges[i] = nullptr;
		}
		this->qualifications = qualifications;

		for (int i=0; i < n; i++) {
			supervisor[i] = -1;
		}
	}

	/*void _get_edges(int cur_vertex, Neighbour** edges, int& size, bool* visited) {
		if (!visited[cur_vertex]) {
			visited[cur_vertex] = true;
			Neighbour* cur_neighbour = neighbours[cur_vertex];
			while (cur_neighbour != nullptr) {
				edges[size] = new Neighbour(cur_neighbour->u, cur_neighbour->v, cur_neighbour->cost);
				size++;
				if (!visited[cur_neighbour->v]) {
					_get_edges(cur_neighbour->v, edges, size, visited);
				}
				cur_neighbour = cur_neighbour->next;
			}
		}
	}*/

	Neighbour** get_edges(int& size) {
		Neighbour** edges = new Neighbour * [m];
		size = 0;
		for (int i = 0; i < n; i++) {
			Neighbour* cur_neighbour = neighbours[i];
			while (cur_neighbour != nullptr) {
				edges[size] = new Neighbour(cur_neighbour->u, cur_neighbour->v, cur_neighbour->cost);
				size++;
				cur_neighbour = cur_neighbour->next;
			}
		}
		return edges;
	}

	void sort_edges(int l, int r, Neighbour** edges) {
		if (r-l <= 0) {
			return;
		}
		int m = (r + l) / 2;
		sort_edges(l, m, edges);
		sort_edges(m + 1, r, edges);
		int i = l;
		int j = m + 1;
		int ind = l;
		while (i <= m && j <= r) {
			if (edges[i]->lesser(edges[j])) {
				tmp_edges[ind] = edges[i];
				i++;
			}
			else {
				tmp_edges[ind] = edges[j];
				j++;
			}
			ind++;
		}
		while (i <= m) {
			tmp_edges[ind] = edges[i];
			ind++;
			i++;
		}
		while (j <= r) {
			tmp_edges[ind] = edges[j];
			j++; 
			ind++;
		}
		for (int k = l; k <= r; k++) {
			edges[k] = tmp_edges[k];
		}
	}

	void add_edge(int u, int v, int cost) {
		Neighbour* new_edge = new Neighbour(u, v, cost);
		new_edge->next = neighbours[u];
		neighbours[u] = new_edge;
	}

	int mst_find(int i, int* L) {
		if (L[i] != i) {
			L[i] = mst_find(L[i], L);
		}
		return L[i];
	}

	bool mst_union(int x, int y, int* L, int* S) {
		int fx = mst_find(x, L);
		int fy = mst_find(y, L);
		if (fx == fy || supervisor[y] != -1) {
			return false;
		}  
		if (S[fx] >= S[fy]) {
			L[fy] = fx;
			S[fx] += S[fy];
			supervisor[y] = fx;
		}
		else {
			L[fx] = fy;
			S[fy] += S[fx];
			supervisor[y] = fy;
		}
		return true;
	}

	long long mst_build() {
		int size = 0;
		for (int i = 0; i < n; i++) {
			supervisor[i] = -1;
		}
		Neighbour** edges = this->get_edges(size);
		this->sort_edges(0, m-1, edges);
		int* L = new int[n];
		int* S = new int[n];
		for (int i = 0; i < n; i++) {
			L[i] = i;
			S[i] = 1;
		}
		long long cost = 0;
		for (int i = 0; i < m; i++) {
			Neighbour* edge = edges[i];
			if (mst_union(edge->u, edge->v, L, S)) {
				cost += (long long)edge->cost;
			}
		}

		bool found = false;
		for (int i = 1; i < n; i++) {
			if (supervisor[i] == -1) {
				if (found) {
					return -1;
				}
				found = true;
			}
		}
		return cost;
	}
};


int main_snbdcvbsdbvhj() {
	int n;
	cin >> n;
	int* qualifications = new int[n+1];
	for (int i = 1; i <= n; i++) {
		cin >> qualifications[i];
	}
	int m;
	cin >> m;
	MST_Graph* G = new MST_Graph(n+1, m, qualifications);
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u;
		cin >> v;
		cin >> cost;
		G->add_edge(u, v, cost);
	}
	long long cost = G->mst_build();
	cout << cost;
	return 0;
}