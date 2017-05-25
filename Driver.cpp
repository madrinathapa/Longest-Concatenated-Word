/*
Finds the longest and second longest concatenated word in the given input.
Also counts the total number of concatenated words in the given input

Approach:
Reading the input file using the ifstream iterator and inserting every word encountered in a trie, 
length of the word in a set and both the word and it's length in a map<int, vector<string>>.
End of the while loop, trie will have all the words encountered, set will have all possible length of words
in a sorted order and the map will have all words of same lengths.

Since, the problem is to find the longest word, the set which has the lengths of words is reversed and a foor loop is started. 
All the words of same length is then fetched from the map and loop is started. 

LongestConcatenatedWord method checks if the word is a valid concatenated word or not and returns the total count of
concatenated words. IsValidWord methods checks each character of the given input word for a match and returns true if all 
the characters match and false if any mismatch is encountered. It also returns the index where the mismatch was found. 
LongestConcatenatedWord method is called recursively and every time a valid substring is encontered the count value is incremented.

In the main function, if the totalConcatWordsInLongest value is greater than 1 and the it is a valid word, then firstLongestWord is initialized 
if it is not set. After which secondLongestWord is initialized too. Variable totalConcatWords keeps track of all the valid concatenated words.
*/

#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <iterator>
#include "LongestWord.cpp"

string firstLongestWord = "", secondLongestWord = "";

int main() {
	Word w;
	string inputFilePath =  "./wordsforproblem.txt";

	ifstream file(inputFilePath);
	map<int, vector<string> > collection;
	set<int> wordSize;

	Word::NodePointer root = w.CreateTrieNode();
	clock_t startTime;
    double totalDuration;

    startTime = clock();
	//Read the input file in ifstream object
	ifstream fobject(inputFilePath, ifstream::in);
	istream_iterator<string> itr(fobject);


	while (itr != istream_iterator<string>()) {
		string word(*itr);
		//Insert the word encountered to the trie 
		w.InsertWord(root, word);
		int len = word.length();
		wordSize.insert(len);
		collection[len].push_back(word);
		itr++;
	}
	fobject.close();

	int totalConcatWords = 0;
	int totalConcatWordsInLongest = 0;

	//Start with the longest word
	set<int>::reverse_iterator it;

	for (it = wordSize.rbegin(); it != wordSize.rend(); it++) {
		int len = *it;
		vector<string> sameSizeWords = collection[len];
		int totalWords = sameSizeWords.size();

		//Iterate for each word of same length at the same time
		for (int i = 0; i < totalWords; i++) {
			bool isValid = false;
			totalConcatWordsInLongest = w.LongestConcatenatedWord(root, sameSizeWords[i], 0, len - 1, isValid);

			if (totalConcatWordsInLongest > 1 && isValid) {
				//set if the first longest word is not set
				if (firstLongestWord == "") {
					firstLongestWord = sameSizeWords[i];
					cout << "First Longest Word: " << firstLongestWord << " "<<len<<" letters long\n";
				}
				//set the second longest word if not set
				else if (secondLongestWord == "") {
					secondLongestWord = sameSizeWords[i];
					cout << "Second Longest Word: " << secondLongestWord << " "<<len<<" letters long\n";
					totalDuration = (clock() - startTime ) / (double) CLOCKS_PER_SEC;
					cout<<"Execution time: "<< totalDuration <<"\n";
				}
				totalConcatWords++;
			}
		}
	}
	cout<<"Total number of concatenated words: "<<totalConcatWords<<"\n";

    totalDuration = (clock() - startTime ) / (double) CLOCKS_PER_SEC;
	cout<<"Execution time: "<< totalDuration <<"\n";

	return 0;
}