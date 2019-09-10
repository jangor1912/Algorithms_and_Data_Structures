#include <iostream>
#define MAX_QUERIES 250000
#define MAX_WORD_LENGTH 12
using namespace std;

/*long long abs(long long val) {
	if (val < 0) {
		return -1 * val;
	}
	return val;
}*/

bool string_equals(char* str1, const char* str2) {
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

bool string_greater(char* str1, const char* str2) {
	int i = 0;
	while (true) {
		if (str1[i] == '\0') {
			return false;
		}
		if (str2[i] == '\0') {
			return true;
		}

		if (str1[i] > str2[i]) {
			return true;
		}
		else if(str1[i] < str2[i]){
			return false;
		}
		i++;
	}
	return false;
}

struct Entry {
	char* key;
	char* value;
	Entry* next=nullptr;
	Entry() {};
	Entry(char* k, char* v) {
		key = k;
		value = v;
	}
};

struct HashMap {
	long long p = 1000039;
	long long q = 1000000033;
	int size=0;
	int buckets_no;
	Entry** tab;
	HashMap(int buckets_number) {
		buckets_no = buckets_number;
		tab = new Entry * [buckets_no];
		for (int i = 0; i < buckets_no; i++) {
			tab[i] = nullptr;
		}
	}

	long long hash(char* key) {
		long long my_hash = 0;
		for (int i = 0; key[i] != '\0'; i++) {
			my_hash = (p * my_hash + key[i]);
		}
		return my_hash % q;
	}

	int index(char* key) {
		return abs(hash(key)) % buckets_no;
	}

	void put(char* key, char* val) {
		int ind = index(key);
		Entry* e = tab[ind];
		if (e == nullptr) {
			tab[ind] = new Entry(key, val);
			size++;
			return;
		}
		while (e != nullptr) {
			if (string_equals(key, e->key)) {
				e->value = val;
				return;
			}
			e = e->next;
		}
		e = new Entry(key, val);
		e->next = tab[ind];
		tab[ind] = e;
		size++;
	}

	char* remove(char* key) {
		// Assumption - key exists
		char* result;
		int ind = index(key);
		Entry* prev = tab[ind];
		Entry * cur = tab[ind]->next;
		if (string_equals(prev->key, key)){
			result = prev->value;
			tab[ind] = prev->next;
			delete prev;
			size--;
			return result;
		}
		while (cur != nullptr) {
			if (string_equals(cur->key, key)){
				prev->next = cur->next;
				result = cur->value;
				delete cur;
				size--;
				return result;
			}
			cur = cur->next;
			prev = prev->next;
		}
	}

	char* get(char* key) {
		int ind = index(key);
		Entry* e = tab[ind];
		while (e != nullptr) {
			if (string_equals(e->key, key)){
				return e->value;
			}
			e = e->next;
		}
		throw(runtime_error("No such entry"));
	}

	bool contains(char* key) {
		int ind = index(key);
		Entry* e = tab[ind];
		while (e != nullptr) {
			if (string_equals(e->key, key)){
				return true;
			}
			e = e->next;
		}
		return false;
	}

	int getSize() {
		return size;
	}

	bool empty() {
		return size == 0;
	}

	Entry* iterator() {
		Entry* first = nullptr;
		Entry* last = nullptr;
		Entry* cur = nullptr;
		for (int i = 0; i < buckets_no; i++) {
			cur = tab[i];
			while (cur != nullptr) {
				Entry* new_entry = new Entry(cur->key, cur->value);
				if (first == nullptr) {
					first = last = new_entry;
				}
				else {
					last->next = new_entry;
					last = last->next;
				}
				cur = cur->next;
			}
		}
		return first;
	}
};

Entry** tmp = new Entry * [MAX_QUERIES];

void merge_sort(int l, int r, Entry** tab) {
	if (r - l <= 0) return;
	int m = (r + l) / 2;
	merge_sort(l, m, tab);
	merge_sort(m + 1, r, tab);

	int i, j, ind;
	i = l;
	j = m+1;
	ind = l;
	while (i <= m && j <= r) {
		if (!(string_greater(tab[i]->key, tab[j]->key))) {
			tmp[ind] = tab[i];
			i++;
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

int main_dsbvc() {
	int queries_no;
	cin >> queries_no;
	HashMap* map = new HashMap(MAX_QUERIES / 10);
	for (int i = 0; i < queries_no; i++) {
		char* query = new char[MAX_WORD_LENGTH];
		char* key = new char[MAX_WORD_LENGTH];
		char* val = new char[MAX_WORD_LENGTH];
		char* result = nullptr;
		cin >> query;
		if (string_equals(query, "PUT")) {
			cin >> key;
			cin >> val;
			map->put(key, val);
		}
		else if (string_equals(query, "REMOVE")) {
			cin >> key;
			cout << query << " (" << key << "," << map->remove(key) << ")\n";
		}
		else if (string_equals(query, "GET")) {
			cin >> key;
			cout << query << " (" << key << "," << map->get(key) << ")\n";
		}
		else if (string_equals(query, "CONTAINS")) {
			cin >> key;
			if (map->contains(key)) {
				cout << query << " " << key << " true\n";
			}
			else {
				cout << query << " " << key << " false\n";
			}
		}
		else if (string_equals(query, "SIZE")) {
			int size = map->getSize();
			cout << "SIZE " << size << "\n";
		}
		else if (string_equals(query, "EMPTY")) {
			if (map->empty()) {
				cout << query << " true\n";
			}
			else {
				cout << query << " false\n";
			}
		}
		else if (string_equals(query, "PRINT")) {
			cout << "PRINT ";
			Entry* iter = map->iterator();
			Entry* next;
			int size = map->getSize();
			Entry** tab = new Entry * [size];
			int i = 0;
			while (iter != nullptr) {
				tab[i] = iter;
				iter = iter->next;
				i++;
			}
			merge_sort(0, size-1, tab);
			for (i = 0; i < size; i++) {
				cout << "(" << tab[i]->key << "," << tab[i]->value << ") ";
				//delete tab[i];
			}
			delete tab;
			cout << "\n";
		}
		if (result != nullptr) {
			cout << query << " " << result << "\n";
		}
	}
	return 0;
}