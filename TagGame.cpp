#include <iostream>
using namespace std;

int max8(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

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
		this->neighbours = new Neighbour * [n+1];
		for (int i = 0; i < n+1; i++) {
			this->neighbours[i] = nullptr;
		}
	}

	void add_edge(int u, int v) {
		// edge does not exists
		Neighbour* new_edge = new Neighbour(u, v);
		new_edge->next = this->neighbours[u];
		this->neighbours[u] = new_edge;

		new_edge = new Neighbour(v, u);
		new_edge->next = this->neighbours[v];
		this->neighbours[v] = new_edge;
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
					bool correct_vertex = get_path(cur_v, v, path, length, visited);
					if (correct_vertex) {
						path[length] = cur_v;
						length++;
						return true;
					}
				}
				current_neighbour = current_neighbour->next;
			}
		}
		return false;
	}

	int get_max_length(int u, bool* visited) {
		int cur_max_length = 0;
		if (!visited[u]) {
			visited[u] = true;
			Neighbour* current_neighbour = this->neighbours[u];
			while (current_neighbour != nullptr) {
				int cur_v = current_neighbour->v;
				int cur_length = this->get_max_length(cur_v, visited);
				cur_max_length = max8(cur_max_length, cur_length);
				current_neighbour = current_neighbour->next;
			}
			cur_max_length++;
		}
		return cur_max_length;
	}
};

int main_jebvcdhucjvkdfvrnjknefj() {
	int bob_moves = 0;
	int n, x;
	cin >> n;
	cin >> x;
	Graph* G = new Graph(n);
	for (int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u;
		cin >> v;
		G->add_edge(u, v);
	}
	int* path = new int[n+1];
	int length = 0;
	bool* visited = (bool*)calloc(n+1, sizeof(bool));
	G->get_path(1, x, path, length, visited);
	path[length] = 1;
	length++;
	bob_moves = length / 2 - 1;
	int new_bob_position = path[bob_moves];
	int alice_position_index = length - 1 - bob_moves;
	int new_alice_position = path[alice_position_index];
	/*cout << "Path = \n";
	for (int i = 0; i < length; i++) {
		cout << path[i] << "\n";
	}
	cout << "Length = " << length << "\n";
	cout << "Bob position = " << new_bob_position << "\n";*/
	for (int i = 0; i < n + 1; i++) {
		visited[i] = false;
	}
	int prev_vertex = -1;
	for (int i = length - 1; path[i] != new_bob_position; i--) {
		int cur_vertex = path[i];
		visited[cur_vertex] = true;
		Neighbour* cur_neighbour = G->neighbours[cur_vertex];
		while (cur_neighbour != nullptr) {
			if (cur_neighbour->v != prev_vertex) {
				visited[cur_neighbour->v] = true;
			}
			cur_neighbour = cur_neighbour->next;
		}
		if (i <= alice_position_index) {
			visited[cur_vertex] = false;
		}
		prev_vertex = cur_vertex;
	}
	visited[new_bob_position] = false;
	length = G->get_max_length(new_alice_position, visited);

	//cout << "Length of longest path from " << new_alice_position << " = " << length << "\n";
	cout << 2*(bob_moves + length - 1);
	return 0;
}