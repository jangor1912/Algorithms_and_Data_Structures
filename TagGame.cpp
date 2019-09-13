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
		// edge does not exists
		Neighbour* new_edge = new Neighbour(u, v);
		new_edge->next = this->neighbours[u];
		this->neighbours[u] = new_edge;
	}

	bool get_path(int u, int v, int* path, int &length, bool* visited) {
		if (!visited[u]) {
			visited[u] = true;
			Neighbour* current_neighbour = this->neighbours[u];
			while (current_neighbour != nullptr) {
				int cur_v = current_neighbour->v;
				if (cur_v == v) {
					path[length] = v;
					length++;
					return true;
				}
				if (!visited[cur_v]) {
					if (get_path(cur_v, v, path, length, visited)) {
						path[length] = cur_v;
						length++;
					}
				}
				current_neighbour = current_neighbour->next;
			}
		}
		return false;
	}
};

int main() {
	int n, x;
	cin >> n;
	cin >> x;
	n = n - 1;
	Graph* G = new Graph(n);
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u;
		cin >> v;
		G->add_edge(u, v);
	}
	int* path = new int[n];
	int length = 0;
	bool* visited = (bool*)calloc(n, sizeof(bool));
	G->get_path(1, x, path, length, visited);
	cout << "Path = \n";
	for (int i = 0; i < length; i++) {
		cout << path[i] << "\n";
	}
	return 0;
}