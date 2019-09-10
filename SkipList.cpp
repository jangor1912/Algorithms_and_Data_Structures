#include <iostream>
using namespace std;

struct Random {
	long long state = 3748349;
	long long m = 1ll << 48;
	long long a = 4*5114+1;
	long long c = 2*5018521+1;

	long long rand() {
		state = (a * state + c) % m;
		return state >> 16;
	}
};

struct Entry {
	int levels;
	int x;
	int y;
	double key;
	Entry** next=nullptr;
	Entry(int x, int y, double key, int levels) {
		this->x = x;
		this->y = y;
		this->key = key;
		this->levels = levels;
		this->next = new Entry * [levels];
		for (int i = 0; i < levels; i++) {
			this->next[i] = nullptr;
		}
	}
};

struct SkipList {
	int x_solo;
	int y_solo;
	int max_levels;
	int size = 0;
	Entry* sentinel;
	Random* rand = new Random();
	SkipList(int levels, int x, int y) {
		max_levels = levels;
		x_solo = x;
		y_solo = y;
		sentinel = new Entry(INT_MIN, INT_MIN, INT_MIN, max_levels);
	}

	double getKey(int x, int y) {
		if (x_solo == x) {
			return INT_MAX;
		}
		double a = (double) (y_solo - y) / (x_solo - x);
		return a;
	}

	int getLevel() {
		int l = 0;
		while (l < max_levels && rand->rand() % 2 == 1) {
			l++;
		}
		return l;
	}

	Entry* findNotGreaterEntry(double key) {
		Entry* entry = sentinel;
		int l = max_levels - 1;
		while (l >= 0) {
			if (entry->next[l] != nullptr && entry->next[l]->key < key) {
				entry = entry->next[l];
			}
			else {
				l--;
			}
		}
		return entry;
	}

	Entry* findLastEntry(double key) {
		Entry* entry = sentinel;
		int l = max_levels - 1;
		while (l >= 0) {
			if (entry->next[l] != nullptr && entry->next[l]->key <= key) {
				entry = entry->next[l];
			}
			else {
				l--;
			}
		}
		return entry;
	}

	void put(int x, int y){
		double key = getKey(x, y);
		size++;
		int level = getLevel();
		Entry* new_entry = new Entry(x, y, key, level+1);
		Entry* entry = sentinel;
		int l = max_levels - 1;
		while (l >= 0) {
			if (entry->next[l] != nullptr && entry->next[l]->key < key) {
				entry = entry->next[l];
			}
			else {
				if (l > level) { l--; }
				else {
					new_entry->next[l] = entry->next[l];
					entry->next[l] = new_entry;
					l--;
				}
			}
		}
	}

};


int main_sdjvchsdb() {
	int x_solo, y_solo, n;
	int x, y;
	cin >> n;
	cin >> x_solo;
	cin >> y_solo;
	SkipList* list = new SkipList(2, x_solo, y_solo);
	for (int i = 0; i < n; i++) {
		cin >> x;
		cin >> y;
		list->put(x, y);
	}
	Entry* entry = list->sentinel->next[0];
	double prev_key = list->sentinel->key;
	double cur_key;
	int shots_fired = 0;
	while (entry != nullptr) {
		cur_key = entry->key;
		if (cur_key != prev_key) {
			shots_fired++;
		}
		entry = list->findLastEntry(cur_key);
		entry = entry->next[0];
		prev_key = cur_key;
	}
	cout << shots_fired;

	/*Random* rand = new Random();
	double counter = 0;
	for (int i = 0; i < 100000; i++) {
		if (rand->rand() % 2 == 1) {
			counter++;
		}
	}
	cout << counter / 100000;*/
	return 0;
}