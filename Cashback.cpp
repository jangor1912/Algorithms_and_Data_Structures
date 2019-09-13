#include <iostream>
using namespace std;

struct Element {
	int value;
	int index;
	Element(int val, int ind) {
		value = val;
		index = ind;
	}
};

struct Node {
	Element* el;
	Node* next = nullptr;
	Node* prev = nullptr;
	Node(int val, int ind) {
		el = new Element(val, ind);
	}
};

struct Dequeue {
	int c;
	int begin_index;
	Node* begin = nullptr;
	Node* end = nullptr;
	int size = 0;
	Dequeue(int c) {
		this->c = c;
		this->begin_index = 0;
	}

	Element* pop_front() {
		// assumption queue is not empty
		Element* result = this->begin->el;
		size--;
		Node* n = this->begin;
		this->begin = this->begin->next;
		delete n;
		if (this->begin == nullptr) {
			this->end = nullptr;
		}
		else {
			begin->prev = nullptr;
		}
		return result;
	}

	Element* pop_back() {
		//assumption queue is not empty
		Element* result = this->end->el;
		size--;
		Node* n = this->end;
		this->end = this->end->prev;
		delete n;
		if (this->end == nullptr) {
			this->begin = nullptr;
		}
		else {
			this->end->next = nullptr;
		}
		return result;
	}

	void push_back(int val, int index) {
		/*if (this->begin != nullptr) {
			while (this->begin != nullptr && index - this->begin->el->index > c) {
				delete this->pop_front();
			}
		}*/
		Node* new_node = new Node(val, index);
		size++;
		while (index - this->begin_index >= c) {
			begin_index++;
		}
		if (this->begin != nullptr) {
			while (this->begin != nullptr && this->begin->el->index < this->begin_index) {
				delete this->pop_front();
			}
		}

		while (this->end != nullptr && this->end->el->value > new_node->el->value) {
			delete this->pop_back();
		}

		if (this->begin == nullptr) {
			this->begin = new_node;
			this->end = new_node;
			return;
		}
		this->end->next = new_node;
		new_node->prev = this->end;
		this->end = new_node;
	}

	int get_min() {
		return this->begin->el->value;
	}

};

long long* count_prefix_sum(int* A, int n) {
	long long* P = new long long[n+1];
	P[0] = 0;
	for (int i = 1; i <= n; i++) {
		P[i] = (long long) P[i - 1] + A[i];
	}
	return P;
}

int* count_prev(int* A, int n) {
	int* prev = new int[n + 1];
	prev[0] = -1;
	for (int i = 1; i <= n; i++) {
		int j = i - 1;
		while (j >= 0 && A[j] >= A[i]) {
			j = prev[j];
		}
		prev[i] = j;
	}
	return prev;
}

int min5(int val1, int val2) {
	if (val1 < val2) {
		return val1;
	}
	return val2;
}

long long min8(long long val1, long long val2) {
	if (val1 < val2) {
		return val1;
	}
	return val2;
}

int count_min(int* A, int n, int* prev, int start, int end) {
	int i = end;
	int min = A[end];
	while (i >= start) {
		min = min5(min, A[i]);
		i = prev[i];
	}
	return min;
}

long long count_smallest_sum(int* A, int n, int c) {
	long long* P = count_prefix_sum(A, n);
	long long* D = new long long[n + 1];
	int* prev = count_prev(A, n);
	Dequeue* queue = new Dequeue(c);
	D[0] = 0;
	for (int i = 1; i <= n; i++) {
		queue->push_back(A[i], i);
		if (i < c) {
			D[i] = P[i];
		}
		else {
			long long new_partition = D[i - 1] + A[i];

			long long sum_between = P[i] - P[(i - c + 1) - 1];
			int min_between = queue->get_min();
			long long append_to_old = D[i - c] + sum_between - min_between;
			D[i] = min8(new_partition, append_to_old);
		}
	}
	return D[n];

}

int main_asjcmldv() {
	int n, c;
	cin >> n;
	cin >> c;
	int* A = new int[n+1];
	A[0] = INT_MIN;
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
	}
	long long result = count_smallest_sum(A, n, c);
	cout << result;
	return 0;
}