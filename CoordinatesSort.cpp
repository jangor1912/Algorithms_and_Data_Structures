#include <iostream>
#define MAX_LENGTH 200000
using namespace std;


class Coordinate {
public:
	Coordinate() {};
	Coordinate(long long x_val, long long y_val) {
		x = x_val;
		y = y_val;
	};
	long long get_x() {
		return x;
	};
	long long get_y() {
		return y;
	};
	
private:
	long long x;
	long long y;
};

Coordinate ** T = new Coordinate*[MAX_LENGTH];

void merge_sort(int l, int r, Coordinate** tab) {
	if (r - l <= 0) return;
	int m = (r + l) / 2;
	merge_sort(l, m, tab);
	merge_sort(m + 1, r, tab);
	int i = l;
	int j = m + 1;
	int ind = l;
	while (i <= m && j <= r) {
		if (tab[i]->get_x() <= tab[j]->get_x()) {
			if (tab[i]->get_x() == tab[j]->get_x()) {
				if (tab[i]->get_y() <= tab[j]->get_y()) {
					T[ind] = tab[i];
					i++;
				}
				else {
					T[ind] = tab[j];
					j++;
				}
			}
			else {
				T[ind] = tab[i];
				i++;
			}
		}
		else {
			T[ind] = tab[j];
			j++;
		}
		ind++;
	}
	while (i <= m) {
		T[ind] = tab[i];
		i++;
		ind++;
	}
	while (j <= r) {
		T[ind] = tab[j];
		j++;
		ind++;
	}
	for (int k = l; k <= r; k++) {
		tab[k] = T[k];
	}
};

Coordinate** load_coordinates(int n) {
	long long x, y;
	Coordinate** tab = new Coordinate * [n];
	for (int i = 0; i < n; i++) {
		cin >> x;
		cin >> y;
		tab[i] = new Coordinate(x, y);
	}
	return tab;
}

void print_coordinates(Coordinate** tab, int length) {
	for (int i = 0; i < length; i++) {
		cout << "(" << tab[i]->get_x() << ", " << tab[i]->get_y() << ")\n";
	}
}

int test_merge_sort(){
	//int tab[9] = {3, 10, -16, 0, -20, 100, 300, 34, -5};
	long long tab[10] = { 72831672, -11366539445690, -24533233793960, -897273032315, 8328, 1, -1, 21334, -1, 4148162956223 };
	Coordinate * c_tab[9];
	int length = 9;
	std::cout << "Printing input array\n";
	for (int i = 0; i < length; i++) {
		c_tab[i] = new Coordinate(tab[i], 1);
		std::cout << c_tab[i]->get_x() << ", ";
	}

	std::cout << "Starting merge-sort\n";
	merge_sort(0, length - 1, c_tab);
	std::cout << "Finished merge-sort\n";

	std::cout << "Printing sorted array\n";
	print_coordinates(c_tab, length);
	std::cout << "\n";
	return 0;
}

int not_main() {
	int length;
	cin >> length;
	Coordinate** tab = load_coordinates(length);
	merge_sort(0, length - 1, tab);
	print_coordinates(tab, length);
	//test_merge_sort();
	return 0;
}