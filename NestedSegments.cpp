#include <iostream>
#define MAX_LENGTH 300000
using namespace std;


struct Segment {
	Segment() {}
	Segment(int val1, int val2, int index) {
		this->begining = val1;
		this->ending = val2;
		this->length = val2 - val1;
		this->index = index;
	}
	int begining;
	int ending;
	int length;
	int index;
};

Segment** tmp = new Segment*[MAX_LENGTH];

void merge_sort(int l, int r, Segment** tab) {
	if (r - l <= 0) return;
	int m = (r + l) / 2;
	merge_sort(l, m, tab);
	merge_sort(m + 1, r, tab);
	int i, j, ind;
	i = l;
	j = m+1;
	ind = l;
	while (i <= m && j <= r) {
		if (tab[i]->begining <= tab[j]->begining) {
			if (tab[i]->begining == tab[j]->begining) {
				if (tab[i]->length > tab[j]->length) {
					tmp[ind] = tab[i];
					i++;
				}
				else {
					tmp[ind] = tab[j];
					j++;
				}
			}
			else {
				tmp[ind] = tab[i];
				i++;
			}
		}
		else {
			tmp[ind] = tab[j];
			j++;
		}
		ind++;
	}
	while (i <= m) {
		tmp[ind] = tab[i];
		i++;
		ind++;
	}
	while (j <= r) {
		tmp[ind] = tab[j];
		j++;
		ind++;
	}
	for (int k = l; k <= r; k++) {
		tab[k] = tmp[k];
	}
}

void print_segments(Segment** tab, int length) {
	for (int i = 0; i < length; i++) {
		cout << "Begigning = " << tab[i]->begining << ", length= " << tab[i]->length << "\n";
	}
}

bool lies_within(Segment *seg1, Segment* seg2) {
	if (seg2->begining <= seg1->begining && seg2->ending >= seg1->ending) {
		return true;
	}
	return false;
}

void test_merge_sort() {
	Segment** tab = new Segment*[5];
	tab[0] = new Segment(10, 9, 1);
	tab[1] = new Segment(1, 9, 1);
	tab[2] = new Segment(3, 9, 1);
	tab[3] = new Segment(2, 9, 1);
	tab[4] = new Segment(8, 9, 1);
	cout << "Segments before sorting:\n";
	print_segments(tab, 5);
	merge_sort(0, 4, tab);
	cout << "Segments after sorting:\n";
	print_segments(tab, 5);
}

int test_all3() {
	test_merge_sort();
	return 0;
}

int mainjkuhu() {
	test_all3();
	return 0;
}

int main_dnvj() {
	int segments_no, begining, ending;
	cin >> segments_no;
	Segment** tab = new Segment*[segments_no];
	for (int i = 0; i < segments_no; i++) {
		cin >> begining;
		cin >> ending;
		tab[i] = new Segment(begining, ending, i + 1);
	}
	merge_sort(0, segments_no-1, tab);
	for (int i = 0; i < segments_no; i++) {
		for (int j = i + 1; j < segments_no && j< i+2; j++) {
			if (lies_within(tab[j], tab[i]) == true) {
				cout << tab[j]->index << " " << tab[i]->index;
				return 0;
			}
		}
	}
	cout << "-1 -1";
	return 0;
}