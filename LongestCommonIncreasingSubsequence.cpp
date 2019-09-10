#include <iostream>
using namespace std;

struct Tuple {
	int tab_size = 0;
	int* tab;
	Tuple(int* tab, int size) {
		this->tab = tab;
		this->tab_size = size;
	}
};

int lowerbound2(int l, int r, int val, int* tab) {
	while (l != r) {
		int m = (l + r) / 2;
		if (tab[m] < val) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return l;
}

int max2(int val1, int val2) {
	if (val1 > val2) {
		return val1;
	}
	return val2;
}

Tuple* lcis(int* A, int a_size, int* B, int b_size) {
	int t_size = max2(a_size, b_size);
	int* T = new int[t_size];
	int* path = new int[t_size];
	for (int i = 0; i < t_size; i++) {
		T[i] =	INT_MAX;
		path[i] = INT_MAX;
	}
	int l = 0;
	int r = 1;
	for (int i = 0; i < a_size; i++) {
		for (int j = 0; j < b_size; j++) {
			if (A[i] == B[j]) {
				int ind = lowerbound2(l, r, A[i], T);
				T[ind] = A[i];

				if (ind == r) {
					r++;
				}
			}
		}
	}
	return new Tuple(A, r-1);

}

int main() {
	int a_size, b_size;
	cin >> a_size;
	int * A = new int[a_size];
	for (int i = 0; i < a_size; i++) {
		cin >> A[i];
	}
	cin >> b_size;
	int* B = new int[b_size];
	for (int i = 0; i < b_size; i++) {
		cin >> B[i];
	}
	Tuple* tuple = lcis(A, a_size, B, b_size);
	cout << tuple->tab_size<< "\n";
	for (int i = 0; i < tuple->tab_size; i++) {
		cout << tuple->tab[i] << " ";
	}
	return 0;
}