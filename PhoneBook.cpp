#include <iostream>
#define NUMBER_LENGTH 9

using namespace std;

struct Sequence {
	int start;
	int end; //end is the last valid character in the sequence
	char* phone_no;
	Sequence() {};
	Sequence(int s, int e, char* number) {
		start = s;
		end = e;
		phone_no = number;
	}

	bool equal(Sequence* seq) {
		; int i, j;
		i = j = 0;
		if (end - start != seq->end - seq->start) {
			return false;
		}
		while (true) {
			if (i > end || j > seq->end) {
				if (i > end && j > seq->end) {
					return true;
				}
				return false;
			}
			if (phone_no[i] != seq->phone_no[j]) {
				return false;
			}
			i++;
			j++;
		}
	}
};

struct Entry {
	int count=1;
	Sequence* seq = nullptr;
	Entry* next = nullptr;
	Entry(Sequence* s) {
		seq = s;
	}
};

struct Map {
	Entry** tab;
	int size = 0;
	int buckets;
	long long p = 1000003;
	long long q = 1000000007;
	Map(int buckets) {
		this->buckets = buckets;
		tab = new Entry*[buckets];
		for (int i = 0; i < buckets; i++) {
			tab[i] = nullptr;
		}
	}

	long long hash(Sequence* seq) {
		long long cur_hash = 0;
		for (int i = seq->start; i <= seq->end; i++) {
			cur_hash = (p * cur_hash) + seq->phone_no[i];
		}
		return cur_hash % q;
	}

	long long index(Sequence* seq) {
		return abs(hash(seq)) % buckets;
	}

	void put(Sequence * seq) {
		long long key = index(seq);
		Entry* entry = tab[key];
		if (entry == nullptr) {
			size++;
			tab[key] = new Entry(seq);
			return;
		}
		else {
			while (entry != nullptr) {
				if (entry->seq->equal(seq)) {
					entry->count++;
					return;
				}
				entry = entry->next;
			}
			entry = tab[key];
			size++;
			Entry* new_entry = new Entry(seq);
			new_entry->next = entry;
			tab[key] = new_entry;
		}
	}

	int getCount(Sequence * seq) {
		int key = index(seq);
		Entry* entry = tab[key];
		if (entry == nullptr) {
			return 0;
		}
		else {
			while (entry != nullptr) {
				if (entry->seq->equal(seq)) {
					return entry->count;
				}
				entry = entry->next;
			}
			return 0;
		}
	}
};

Sequence** tmp = new Sequence*[9 * 8 / 2];

bool sequence_lesser(Sequence* seq1, Sequence* seq2) {
	int i,j;
	i = seq1->start;
	j = seq2->start;
	int seq1_len, seq2_len;
	seq1_len = seq1->end - seq1->start;
	seq2_len = seq2->end - seq2->start;
	if (seq1_len < seq2_len) {
		return true;
	}
	else if(seq1_len > seq2_len){
		return false;
	}
	while (i<=seq1->end) {
		if (seq1->phone_no[i] < seq2->phone_no[j]) {
			return true;
		}
		else if(seq1->phone_no[i] > seq2->phone_no[j]){
			return false;
		}
		i++;
		j++;
	}
	return true;
}

void merge_sort(int l, int r, Sequence** tab) {
	if (r - l <= 0) { return; }
	int m = (l + r) / 2;
	merge_sort(l, m, tab);
	merge_sort(m + 1, r, tab);
	int i, j, ind;
	i = l;
	j = m+1;
	ind = l;
	while (i <= m && j <= r) {
		if (sequence_lesser(tab[i], tab[j])){//tab[i] < tab[j]) {
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
	}
	while (j <= r) {
		tmp[ind] = tab[j];
		j++;
	}
	for (int k = l; k <= r; k++) {
		tab[k] = tmp[k];
	}
}

Sequence** getAllSequences(char* phone_no, int length) {
	int sequences_no = length * (length - 1) / 2;
	Sequence** sequences = new Sequence*[sequences_no];
	int ind = 0;
	Sequence* cur_sequence;
	for (int i = 0; i < length; i++) {
		for (int j = i; j < length; j++) {
			cur_sequence = new Sequence(i, j, phone_no);
			sequences[ind] = cur_sequence;
			ind++;
		}
	}
	return sequences;
}

void print_sequences(Sequence** tab,int n) {
	for (int i = 0; i < n; i++) {
		cout << "Printing sorted equences for phone_no= " << tab[i]->phone_no << "\n";
		for (int j = tab[i]->start; i <= tab[i]->end; i++) {
			cout << tab[i]->phone_no[j];
		}
		cout << "\n";
	}
}

int main_efjkce() {
	int numbers;
	cin >> numbers;
	int sequences_no = (9 * 8 / 2);
	Map* map = new Map(7000);
	Sequence*** sequences = new Sequence** [numbers];
	for (int i = 0; i < numbers; i++) {
		char* cur_number = new char[12];
		cin >> cur_number;
		sequences[i] = getAllSequences(cur_number, 9);
		merge_sort(0, sequences_no - 1, sequences[i]);
		Sequence* prev_sequence = new Sequence();
		bool first = true;
		for (int j = 0; j < sequences_no; j++) {
			if (first || !sequences[i][j]->equal(prev_sequence)){
				map->put(sequences[i][j]);
				prev_sequence = sequences[i][j];
				first = false;
			}
		}
	}

	for (int i = 0; i < numbers; i++) {
		//print_sequences(sequences[i], sequences_no);
		bool first = true;
		Sequence* prev_sequence = new Sequence();
		for (int j = 0; j < sequences_no; j++) {
			Sequence* seq = sequences[i][j];
			if (first || !seq->equal(prev_sequence)) {
				if (map->getCount(seq) == 1) {
					for (int k = seq->start; k <= seq->end; k++) {
						cout << seq->phone_no[k];
					}
					cout << "\n";
					break;
				}
			}
			first = false;
			prev_sequence = seq;
		}
	}
	return 0;
}