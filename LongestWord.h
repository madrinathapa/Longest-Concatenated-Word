#include <iostream>

using namespace std;

class Word{

public:
	struct Node {
		struct Node *leaves[26];
		bool isLast;
	};

	struct Node *CreateTrieNode();
	void InsertWord(struct Node *root, string word);
	bool IsWordExists(struct Node *root, string word);
	int LongestConcatenatedWord(Node *root, string word, int start, int end, bool &isValid);
	bool IsValidWord(Node *root, string word, int start, int end, int &currIndex);

	typedef Node * NodePointer;
};
