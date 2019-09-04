#include <iostream>
#define MAX_WORD_LEN 501
using namespace std;

class TrieNode {
public:
	TrieNode() {
		this->ending_words = 0;
		this->used = false;
		for (int i = 0; i < 26; i++) {
			this->next[i] = nullptr;
		}
	};
	int getEndingWords() {
		return this->ending_words;
	}
	bool getUsed() {
		return this->used;
	}
	void setUsed(bool val) {
		this->used = val;
	}

	int countAllWords() {
		int result = 0;
		if (this->ending_words > 0) {
			result++;
		}
		for (int i = 0; i < 26; i++) {
			if (this->next[i] != nullptr) {
				result += this->next[i]->countAllWords();
			}
		}
		return result;
	}
	TrieNode* getNode(char *word, int level) {
		if (word[level] == '\0') {
			return this;
		}
		int letter = word[level] - 'a';
		if (this->next[letter] == nullptr) {
			return 0;
		}
		return this->next[letter]->getNode(word, level + 1);
	}
	int getWordsNumber(char* word, int level) {
		if (word[level] == '\0') {
			return this->ending_words;
		}
		int letter = word[level] - 'a';
		if (this->next[letter] == nullptr) {
			return 0;
		}
		return this->next[letter]->getWordsNumber(word, level + 1);
	}

	void useWord(char* word, int level) {
		if (word[level] == '\0') {
			this->used = true;
			return;
		}
		int letter = word[level] - 'a';
		if (this->next[letter] == nullptr) {
			return;
		}
		this->next[letter]->useWord(word, level + 1);
	}

	bool wasUsed(char* word, int level) {
		if (word[level] == '\0') {
			return this->used;
		}
		int letter = word[level] - 'a';
		if (this->next[letter] == nullptr) {
			return false;
		}
		return this->next[letter]->wasUsed(word, level + 1);
	}

	bool exists(char* word, int level) {
		if (word[level] == '\0') {
			if (this->ending_words > 0) {
				return true;
			}
			return false;
		}
		int letter = word[level] - 'a';
		if (this->next[letter] == nullptr) {
			return false;
		}
		return this->next[letter]->exists(word, level + 1);
	}

	void insert(char* word, int level) {
		if (word[level] == '\0') {
			this->ending_words++;
			return;
		}
		int letter = word[level] - 'a';
		if (this->next[letter] == nullptr) {
			this->next[letter] = new TrieNode();
		}
		this->next[letter]->insert(word, level+1);
	}

private:
	bool used;
	int ending_words;
	TrieNode* next[26];
};

void print_words(char** words, int word_no) {
	int j = 0;
	for (int i = 0; i < word_no; i++) {
		j = 0;
		while (words[i][j] != '\0') {
			cout << words[i][j];
			j++;
		}
		cout << "\n";
	}
}

bool start_game(char** poland_words, char** enemy_words, int poland_words_no, int enemy_words_no) {
	char* word;
	TrieNode* root = new TrieNode();
	for (int i = 0; i < poland_words_no; i++) {
		word = poland_words[i];
		root->insert(word, 0);
	}

	for (int i = 0; i < enemy_words_no; i++) {
		word = enemy_words[i];
		root->insert(word, 0);
	}

	int all_words_no = root->countAllWords();
	int poland_unique_words = 0;
	int enemy_unique_words = 0;
	
	for (int i = 0; i < poland_words_no; i++) {
		word = poland_words[i];
		if (root->getWordsNumber(word, 0) == 1) {
			poland_unique_words++;
		}
	}

	for (int i = 0; i < enemy_words_no; i++) {
		word = enemy_words[i];
		if (root->getWordsNumber(word, 0) == 1) {
			enemy_unique_words++;
		}
	}

	if (all_words_no % 2 == 1) {
		if (poland_unique_words >= enemy_unique_words) {
			return true;
		}
		return false;
	}
	else {
		if (poland_unique_words > enemy_unique_words) {
			return true;
		}
		return false;
	}
	
}

int maindfvfd() {
	int poland_words_no, enemy_words_no;
	cin >> poland_words_no;
	cin >> enemy_words_no;
	char** poland_words = new char*[poland_words_no];
	char** enemy_words = new char*[enemy_words_no];
	for (int i = 0; i < poland_words_no; i++) {
		char* word = new char[MAX_WORD_LEN];
		cin >> word;
		poland_words[i] = word;
	}
	for (int i = 0; i < enemy_words_no; i++) {
		char* word = new char[MAX_WORD_LEN];
		cin >> word;
		enemy_words[i] = word;
	}
	bool result = start_game(poland_words, enemy_words, poland_words_no, enemy_words_no);
	if (result == true) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	return 0;
}


void test14() {
	cout << "Starting new test\n";
	char poland_words_tmp[6][MAX_WORD_LEN] = { "polandball", "is", "a","cool","character","nope"};
	char enemy_words_tmp[5][MAX_WORD_LEN] = { "polandball", "is", "a","cool","character"};
	int poland_words_no = 6;
	int enemy_words_no = 5;
	char** poland_words = new char*[poland_words_no];
	for (int i = 0; i < poland_words_no; i++) {
		poland_words[i] = new char[MAX_WORD_LEN];
		poland_words[i] = poland_words_tmp[i];
	}
	char** enemy_words = new char* [enemy_words_no];
	for (int i = 0; i < enemy_words_no; i++) {
		enemy_words[i] = new char[MAX_WORD_LEN];
		enemy_words[i] = enemy_words_tmp[i];
	}
	cout << "Result is: ";
	bool result = start_game(poland_words, enemy_words, poland_words_no, enemy_words_no);
	cout << result;
	cout << "\nExpected result is: YES\n";
	cout << "Ending test\n";
}

void test15() {
	cout << "Starting new test\n";
	char poland_words_tmp[3][MAX_WORD_LEN] = { "lol", "polandball", "is" };
	char enemy_words_tmp[5][MAX_WORD_LEN] = { "polandball", "is", "a","cool","character" };
	int poland_words_no = 3;
	int enemy_words_no = 5;
	char** poland_words = new char* [poland_words_no];
	for (int i = 0; i < poland_words_no; i++) {
		poland_words[i] = new char[MAX_WORD_LEN];
		poland_words[i] = poland_words_tmp[i];
	}
	char** enemy_words = new char* [enemy_words_no];
	for (int i = 0; i < enemy_words_no; i++) {
		enemy_words[i] = new char[MAX_WORD_LEN];
		enemy_words[i] = enemy_words_tmp[i];
	}
	cout << "Result is: ";
	bool result = start_game(poland_words, enemy_words, poland_words_no, enemy_words_no);
	cout << result;
	cout << "\nExpected result is: NO\n";
	cout << "Ending test\n";
}

void test_all1() {
	test14();
	test15();
}

int mainrgfvergbtre() {
	test_all1();
	return 0;
}