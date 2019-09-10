#include <iostream>
#define MAX_QUERIES 100003
#define MAX_WORD_LENGTH 35
using namespace std;

bool string_equals1(char* str1, const char* str2) {
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

struct Entry {
	char* key;
	char* value;
	int index = 0;
	Entry* next = nullptr;
	Entry() {};
	Entry(char* k, char* v) {
		key = k;
		value = v;
		index = 0;
	}
	Entry(char* k, char* v, int i) {
		key = k;
		value = v;
		index = i;
	}
};

struct HashMap {
	long long p = 1000039;
	long long q = 1000000033;
	int size = 0;
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

	Entry* put(char* key, char* val) {
		int ind = index(key);
		Entry* e = tab[ind];
		if (e == nullptr) {
			tab[ind] = new Entry(key, val);
			size++;
			return tab[ind];
		}
		while (e != nullptr) {
			if (string_equals1(key, e->key)) {
				int cur_index = e->index;
				cur_index++;
				Entry* new_entry = new Entry(key, val, cur_index);
				new_entry->next = tab[ind];
				tab[ind] = new_entry;
				return new_entry;
			}
			e = e->next;
		}
		e = new Entry(key, val);
		e->next = tab[ind];
		tab[ind] = e;
		size++;
		return e;
	}

	char* get(char* key) {
		int ind = index(key);
		Entry* e = tab[ind];
		while (e != nullptr) {
			if (string_equals1(e->key, key)) {
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
			if (string_equals1(e->key, key)) {
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
};

int main_jdhcg() {
	int queries_no;
	cin >> queries_no;
	HashMap* map = new HashMap(MAX_QUERIES / 10);
	Entry* result;
	int index;
	for (int i = 0; i < queries_no; i++) {
		char* name = new char[MAX_WORD_LENGTH];
		cin >> name;
		result = map->put(name, name);
		index = result->index;
		if (index == 0) {
			cout << "OK\n";
		}
		else {
			cout << name << index << "\n";
		}
	}
	return 0;
}