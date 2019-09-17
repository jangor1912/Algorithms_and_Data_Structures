#include <iostream>
#define MAX_STRING 100
using namespace std;

int index(char c) {
	int result = (int)c - 'a';
	return result;
}

struct Entry {
	int val;
	Entry* next = nullptr;
	Entry(int val) {
		this->val = val;
	}
};

struct Queue {
	Entry* begin = nullptr;
	Entry* end = nullptr;
	int size = 0;

	void push(int val) {
		Entry* new_entry = new Entry(val);
		size++;
		if (begin == nullptr) {
			begin = end = new_entry;
			return;
		}
		end->next = new_entry;
		end = new_entry;
	}

	int pop() {
		// assumption queue is not empty
		Entry* entry = begin;
		int result = begin->val;
		size--;
		begin = begin->next;
		if (begin == nullptr) {
			end = nullptr;
		}
		delete entry;
		return result;
	}

	bool empty() {
		return size == 0;
	}
};

struct Neighbour {
	char u;
	char v;
	Neighbour* next = nullptr;
	Neighbour(char u, char v) {
		this->u = u;
		this->v = v;
	}
};

struct AlphabeticalGraph {
	int max_n;
	int n = 0;
	Neighbour** neighbours;
	bool* vertices;
	AlphabeticalGraph(int max_n) {
		this->max_n = max_n;
		this->neighbours = new Neighbour * [max_n];
		for (int i = 0; i < max_n; i++) {
			this->neighbours[i] = nullptr;
		}
		this->vertices = (bool*) calloc(max_n, sizeof(bool));
	}

	void add_edge(char u_char, char v_char) {
		int u = index(u_char);
		int v = index(v_char);

		if (!vertices[u]) {
			vertices[u] = true;
			n++;
		}
		if (!vertices[v]) {
			vertices[v] = true;
			n++;
		}

		Neighbour* new_edge = new Neighbour(u_char, v_char);
		new_edge->next = neighbours[u];
		neighbours[u] = new_edge;
	}

	bool edge_exist(char u_char, char v_char) {
		int u = index(u_char);
		int v = index(v_char);
		Neighbour* cur_neighbour = neighbours[u];
		while (cur_neighbour != nullptr) {
			if (cur_neighbour->v == v_char) {
				return true;
			}
			cur_neighbour = cur_neighbour->next;
		}
		return false;
	}

	bool topo_sort(char* alphabet, int& size) {
		int* parents = (int*)calloc(max_n, sizeof(int));
		size = 0;
		for (int u = 0; u < max_n; u++) {
			Neighbour* p = neighbours[u];
			while (p != nullptr) {
				int v = index(p->v);
				parents[v]++;
				p = p->next;
			}
		}
		Queue* Q = new Queue();
		for (int u = 0; u < max_n; u++) {
			if (parents[u] == 0 && neighbours[u] != nullptr) {
				Q->push(u);
			}
		}

		while (!Q->empty()) {
			int u = Q->pop();
			alphabet[size] = (char) u + 'a';
			size++;
			Neighbour* p = neighbours[u];
			while (p != nullptr) {
				int v = index(p->v);
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

bool in_list(char c, char* list, int size) {
	for (int i = 0; i < size; i++) {
		if (c == list[i]) {
			return true;
		}
	}
	return false;
}

int main_jshdjdsfvdfj() {
	int n;
	cin >> n;
	char** names = new char* [n];
	for (int i = 0; i < n; i++) {
		char* string = new char[MAX_STRING];
		cin >> string;
		names[i] = string;
	}

	AlphabeticalGraph* G = new AlphabeticalGraph(30);

	for (int i = 0; i < n - 1; i++) {
		for (int j = i; j < n; j++) {
			int letter_no = 0;
			char first_letter = names[i][0];
			char second_letter = names[j][0];
			while (first_letter == second_letter && first_letter != '\0') {
				letter_no++;
				first_letter = names[i][letter_no];
				second_letter = names[j][letter_no];
			}
			if (first_letter == '\0' || second_letter == '\0') {
				if (first_letter != '\0' && second_letter == '\0') {
					cout << "Impossible";
					return 0;
				}
				continue;
			}
			if (!G->edge_exist(first_letter, second_letter)) {
				G->add_edge(first_letter, second_letter);
			}
		}
	}
	char* alphabet = new char[30];
	int size = 0;
	bool sorted = G->topo_sort(alphabet, size);
	if (sorted) {
		bool* dont_print = (bool*)calloc(26, sizeof(bool));
		for (int i = 0; i < size; i++) {
			cout << alphabet[i];
			dont_print[alphabet[i] - 'a'] = true;
		}
		for (int i = 0; i < 26; i++) {
			if (!dont_print[i]) {
				char c = (char)i + 'a';
				cout << c;
			}
		}
	}
	else {
		cout << "Impossible";
	}
	return 0;
}