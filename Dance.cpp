#include <iostream>
using namespace std;

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

		Neighbour* newer_edge = new Neighbour(v, u);
		newer_edge->next = neighbours[v];
		neighbours[v] = newer_edge;
	}

	bool ldfs(int u, int* M, bool* visited) {
		if (visited[u]) {
			return false;
		}
		visited[u] = true;
		Neighbour* p = neighbours[u];
		while (p != nullptr) {
			int v = p->v;
			if (M[v] == -1 || ldfs(M[v], M, visited)) {
				M[u] = v;
				M[v] = u;
				return true;
			}
			p = p->next;
		}
		return false;
	}

	void turbo_matching(int* M) {
		// M[u] = [v] - gdy para u->v nale¿y do skojarzenia
		// M[u] = -1 - gdy ososba u jest bez pary
		for (int i = 0; i < n; i++) {
			M[i] = -1;
		}
		bool increasing = true;
		bool* visited = new bool[n];
		while (increasing) {
			increasing = false;
			for (int i = 0; i < n; i++) {
				visited[i] = false;
			}
			for (int i = 0; i < n; i++) {
				if (M[i] == -1 && ldfs(i, M, visited)) {
					increasing = true;
				}
			}
		}
		delete[] visited;
	}
};

int main_jsdcjsdcb() {
	int boys_no;
	cin >> boys_no;
	int* boys_skills = new int[boys_no];
	for (int i = 0; i < boys_no; i++) {
		cin >> boys_skills[i];
	}
	int girls_no;
	cin >> girls_no;
	int* girls_skills = new int[girls_no];
	for (int i = 0; i < girls_no; i++) {
		cin >> girls_skills[i];
	}

	int n = boys_no + girls_no;
	Graph* G = new Graph(n);
	for (int i = 0; i < boys_no; i++) {
		for (int j = 0; j < girls_no; j++) {
			if (abs(boys_skills[i] - girls_skills[j]) <= 1) {
				G->add_edge(i, j+boys_no);
			}
		}
	}

	int* M = new int[n];
	G->turbo_matching(M);
	int possible_pairs = 0;
	for (int i = 0; i < n; i++) {
		if (M[i] != -1) {
			//cout << "Person " << i << "has pair " << M[i] << "\n";
			possible_pairs++;
		}
		//else {
		//	cout << "Person " << i << "has no pair\n";
		//}
	}
	possible_pairs =(int) possible_pairs / 2;
	cout << possible_pairs;
	return 0;
}