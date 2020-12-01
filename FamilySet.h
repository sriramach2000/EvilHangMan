#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;

class FamilySet
{
public:
	FamilySet();
	// Default

	FamilySet(string file);
	// Initializes from a word file

	FamilySet(string file, int len);
	// Initializes from a word file where the word
	// must be of length len.

	~FamilySet();

	void filterFamilies(string letter, string guessPattern);
	// Filters each word from the master list based on the
	// letter and guessPattern.
	// Example:  letter:  "a", 
	//           word:    "ally"  (a word from the master list)
	//           pattern: "***y"
	//           In this case, the family is a**y. Once this
	//           is determined, then "ally" can be added to
	//           this family dictionary.

	void setFamily(string family);
	// This updates the master list.  The new master list
	// should contain the words within the dictionary for family.
	// dictionaries should be cleared after updating the master list.

	string getRandomWord();
	// Gets a random word from the master list

	int numWords();
	// Returns total number of words in master list

	int numFamilies();
	// Returns total number of families

	int familySize(string family);
	// Returns the number of words in a family

	vector<string> getFamily(string family);


	// Iterator
	void resetFamilyIter();
	bool hasNext();
	string getNextFamily();

private:
	vector<string> masterList;
	// This stores all words currently "valid"

	unordered_map<string, vector<string>> dictionaries;
	// Stores a dictionary for each family. Each word from
	// the masterList is contained within one of these
	// these vector dictionaries.
	unordered_map<string, vector<string>>::iterator family_iterator;
	int iterCount;	// Used for iterator
};