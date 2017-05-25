#include <string>

#include "LongestWord.h"

//Method for creating new node in trie
Word::NodePointer Word::CreateTrieNode() {
	NodePointer newNode = NULL;
	newNode = new Node();

	if (newNode)
	{
		newNode->isLast = false;
		for (int i = 0; i < 26; i++) {
			newNode->leaves[i] = NULL;
		}
	}
	return newNode;
}

//Method for adding a new word into the trie
void Word::InsertWord(Word::NodePointer root, string word) {

	int length = word.length();
	Word::NodePointer child = root;

	for (int i = 0; i < length; i++)
	{
		if (!child->leaves[word[i] - 97]) {
			child->leaves[word[i] - 97] = CreateTrieNode();
		}
		child = child->leaves[word[i] - 97];
	}
	child->isLast = true;
}

//Check if the word exists in trie
bool Word::IsWordExists(Word::NodePointer root, string word) {
	int length = word.length();
	Word::NodePointer child = root;

	for (int i = 0; i < length; i++)
	{
		if (!child->leaves[word[i] - 97]) {
			return false;
		}
		child = child->leaves[word[i] - 97];
	}
	return (child != NULL && child->isLast);
}

//Checks until a valid word is found and return when invalid character is encountered
bool Word::IsValidWord(Word::NodePointer root, string word, int begin, int end, int &currIndex)
{
	Word::NodePointer child = root;
	for (int i = begin; i <= end; i++) {
		if (child->leaves[word[i] - 97] == NULL) {
			return false;
		}
		child = child->leaves[word[i] - 97];
		if (i >= currIndex && child->isLast) {
			currIndex = i;
			return true;
		}
	}
	currIndex = end;
	return child->isLast;
}

//Returns number of words concatenated to form the input word
int Word::LongestConcatenatedWord(Word::NodePointer root, string word, int begin, int end, bool &isValid)
{
	isValid = false;
	if (begin < end) {
		for (int i = begin; i <= end; i++) {
			//Checks the first half
			bool firstHalf = IsValidWord(root, word, begin, end, i);
			if (i == end) {
				isValid = firstHalf;
				if (isValid) {
					return 1;
				}
				else {
					return 0;
				}
			}
			//Checks the second half
			bool secondHalf = false;
			int count = LongestConcatenatedWord(root, word, i + 1, end, secondHalf);
			if (firstHalf && secondHalf) {
				isValid = true;
				return 1 + count;
			}
		}
	}
	return 0;
}