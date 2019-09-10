#include <iostream>
#define MAX_WORD_LENGTH 12
#define MAX_QUERIES 450000

using namespace std;

struct PriorityQueue {
	int begin = 1;
	int end = 1;
	long long* tab;

	PriorityQueue(int max_size) {
		tab = new long long[max_size];
	}

	void swap(int i, int j) {
		long long tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	}

	void heapify_up(int i) {
		int parent = i / 2;
		if (parent >= begin && tab[i] < tab[parent]) {
			swap(i, parent);
			heapify_up(parent);
		}
	}

	void heapify_down(int i) {
		int l = 2 * i;
		int r = (2 * i) + 1;
		int best = i;
		if (l < end && tab[l] < tab[best]) {
			best = l;
		}
		if (r < end && tab[r] < tab[best]) {
			best = r;
		}
		if (best != i) {
			swap(best, i);
			heapify_down(best);
		}
	}

	void push(long long value) {
		tab[end] = value;
		end++;
		heapify_up(end-1);
	}

	long long pop() {
		end--;
		swap(begin, end);
		heapify_down(begin);
		return tab[end];
	}

	long long top() {
		return tab[begin];
	}
	int size() {
		return end - begin;
	}
	bool empty() {
		return end == begin;
	}

};

bool string_equal(char* str1, const char* str2) {
	int i = 0;
	while (true) {
		if (str1[i] != str2[i]) {
			return false;
		}
		if (str1[i] == '\0') {
			return true;
		}
		i++;
	}
	return false;
}

int main_jkscb() {
	int queries_no;
	cin >> queries_no;
	PriorityQueue* queue = new PriorityQueue(MAX_QUERIES);
	long long value, result;
	for (int i = 0; i < queries_no; i++) {
		char* query = new char[MAX_WORD_LENGTH];
		result = INT_MIN;
		cin >> query;
		if (string_equal(query, "PUSH")) {
			cin >> value;
			queue->push(value);
		}
		else if (string_equal(query, "POLL")) {
			result = queue->pop();
		}
		else if (string_equal(query, "TOP")) {
			result = queue->top();
		}
		else if (string_equal(query, "SIZE")) {
			result = queue->size();
		}
		else if (string_equal(query, "EMPTY")) {
			if (queue->empty()) {
				cout << "EMPTY true\n";
			}
			else {
				cout << "EMPTY false\n";
			}
		}
		if (result != INT_MIN) {
			cout << query << " " << result << "\n";
		}
	}
	return 0;
}