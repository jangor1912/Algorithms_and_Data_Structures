#include <iostream>
#define MAX_NUM 200000
using namespace std;

void count_sort(int* tab, int length) {
	int* C = (int*) calloc(MAX_NUM+1, sizeof(int));
	for (int i = 0; i < length; i++) {
		C[tab[i]]++;
	}
	int ind = 0;
	for (int i = 0; i <= MAX_NUM; i++) {
		for (int j = 0; j < C[i]; j++) {
			tab[ind] = i;
			ind++;
		}
	}
}

int* load_array(int length) {
	int* tab = new int[length];
	for (int i = 0; i < length; i++) {
		cin >> tab[i];
	}
	return tab;
}

void print_array(int* tab, int length) {
	for (int i = 0; i < length; i++) {
		cout << tab[i] << " ";
	}
}

void test13() {
	int tab[9] = { 2, 1, 9, 4, 1, 1, 5, 1, 2 };
	int expected_tab[9] = { 1, 1, 1, 1, 2, 2, 4, 5, 9 };
	cout << "Printing input tab:\n";
	print_array(tab, 9);
	cout << "\nPrinting expected tab:\n";
	print_array(expected_tab, 9);
	cout << "\nPrinting sorted tab:\n";
	count_sort(tab, 9);
	print_array(tab, 9);
}

void test_all() {
	test13();
}

int main893479283() {
	test_all();
	return 0;
}

int main5345() {
	int length;
	cin >> length;
	int* tab = load_array(length);
	count_sort(tab, length);
	print_array(tab, length);
	return 0;
}