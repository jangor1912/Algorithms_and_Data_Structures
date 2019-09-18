#include <iostream>
using namespace std;

int min9(int val1, int val2) {
	if (val1 < val2) {
		return val1;
	}
	return val2;
}

struct Entry {
	int val;
	Entry* next = nullptr;
	Entry(int val) {
		this->val = val;
	}
};

struct Stack {
	Entry* begin = nullptr;
	int size = 0;

	void push(int val) {
		Entry* new_entry = new Entry(val);
		size++;
		new_entry->next = begin;
		begin = new_entry;
	}

	int pop() {
		// Asumption stack is not empty
		Entry* entry = begin;
		size--;
		int result = entry->val;
		begin = begin->next;
		delete entry;
		return result;
	}

	bool empty() {
		return size == 0;
	}
};

struct Neighbour {
	int u, v;
	Neighbour* next = nullptr;
	Neighbour(int u, int v) {
		this->u = u;
		this->v = v;
	}
};

struct Graph {
	Neighbour** neighbours;
	int n;
	// Additional
	int* Preorder;
	int* Low;
	int* Color;
	int* SSS_indexes;
	Stack* stack = new Stack();
	Stack** SSS_nodes;
	Graph(int n) {
		this->n = n;
		this->neighbours = new Neighbour * [n];
		this->Preorder = new int[n];
		this->Low = new int[n];
		this->Color = (int*)calloc(n, sizeof(int));
		this->SSS_indexes = new int[n];
		this->SSS_nodes = new Stack * [n];
		for (int i = 0; i < n; i++) {
			this->Color[i] = 0;
			this->neighbours[i] = nullptr;
			this->SSS_nodes[i] = new Stack();
		}

	}

	void add_edge(int u, int v) {
		Neighbour* new_edge = new Neighbour(u, v);
		new_edge->next = neighbours[u];
		neighbours[u] = new_edge;
	}

	int low_dfs(int u, int& time, int& sss_num) {
		int v;
		if (Color[u] == 0) {
			Preorder[u] = Low[u] = time;
			Color[u] = 1;
			time++;
			stack->push(u);
			Neighbour* p = neighbours[u];
			while (p != nullptr) {
				v = p->v;
				if (Color[v] == 0) {
					Low[u] = min9(Low[u], low_dfs(v, time, sss_num));
				}
				else if (Color[v] == 1) {
					Low[u] = min9(Low[u], Preorder[v]);
				}
				p = p->next;
			}
			if (Low[u] == Preorder[u]) {
				do {
					v = stack->pop();
					SSS_indexes[v] = sss_num;
					SSS_nodes[sss_num]->push(v);
					Color[v] = 2;
				} while (u != v);
				sss_num++;
			}
		}
		return Low[u];
	}
};


int main_asjkcbe() {
	int final_cost = 0;
	int n;
	cin >> n;
	int* cost = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
	}
	Graph* G = new Graph(n);
	for (int i = 0; i < n; i++) {
		int u = i;
		int v;
		cin >> v;
		G->add_edge(u, v-1);
	}
	int time = 0;
	int sss_num = 0;
	for (int u = 0; u < n; u++) {
		if (G->Color[u] == 0) {
			G->low_dfs(u, time, sss_num);
		}
	}


	for (int i = 0; i < sss_num; i++) {
		int cycle_size = G->SSS_nodes[i]->size;
		if (cycle_size > 1) {
			int min_cost = INT_MAX;
			for(int j=0;j<cycle_size;j++){
				int cur_u = G->SSS_nodes[i]->pop() + 1;
				min_cost = min9(min_cost, cost[cur_u]);
			}
			final_cost += min_cost;
		}
		else {
			int u = G->SSS_nodes[i]->pop();
			Neighbour* p = G->neighbours[u];
			while (p != nullptr) {
				if (p->v == p->u) {
					final_cost += cost[p->u + 1];
					break;
				}
				p = p->next;
			}
		}
	}

	/*cout << "Drukuje silnie spojne skladowe:\n";
	for (int i = 0; i < sss_num; i++) {
		cout << "Stos nr " << i << ": ";
		while (!G->SSS_nodes[i]->empty()) {
			cout << G->SSS_nodes[i]->pop()+1 << " ";
		}
		cout << "\n";
	}*/
	std::cout << final_cost;
	return 0;
}