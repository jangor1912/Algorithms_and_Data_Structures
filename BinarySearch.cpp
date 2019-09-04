#include <iostream>
using namespace std;

int lowerbound(int l, int r, int val, int* tab) {
	int m;
	while (l != r) {
		m = (l + r) / 2;
		if (tab[m] < val) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return l;
}

int upperbound(int l, int r, int val, int* tab) {
	int m;
	while (l != r) {
		m = (l + r) / 2;
		if (tab[m] <= val) {
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return l;
}

int less_than_number(int* tab, int length, int val) {
	return lowerbound(0, length, val, tab);
}

int less_than_or_equal_number(int* tab, int length, int val) {
	return upperbound(0, length, val, tab);
}

int equal_number(int* tab, int length, int val) {
	return upperbound(0, length, val, tab) - lowerbound(0, length, val, tab);
}

int in_range_number(int* tab, int length, int val1, int val2) {
	return upperbound(0, length, val2, tab) - lowerbound(0, length, val1, tab);
}

int* load_input_array(int length) {
	int* tab = new int[length];
	for (int i = 0; i < length; i++) {
		cin >> tab[i];
	}
	return tab;
}	

void execute_queries(int * tab, int length) {
	// loading queries
	int queries_no;
	cin >> queries_no;
	int val, val2, output;
	char query;
	for (int i = 0; i < queries_no; i++) {
		cin >> query;
		cin >> val;
		switch (query) {
		case 'L':
			output = less_than_number(tab, length, val);
			break;
		case 'U':
			output = less_than_or_equal_number(tab, length, val);
			break;
		case 'E':
			output = equal_number(tab, length, val);
			break;
		case 'R':
			cin >> val2;
			output = in_range_number(tab, length, val, val2);
			break;
		default:
			cout << "Error - wrong query!\n";
			return;
		}
		cout << output << "\n";
	}
}

int not_main1() {
	int length;
	cin >> length;
	int * tab = load_input_array(length);
	execute_queries(tab, length);
	return 0;
}