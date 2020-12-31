
/*
Author: Sriram Acharya
Class: CS 301
*/
#include <string>
#include <iostream>

#include "FamilySet.h"
using namespace std;
const int MAX_WORD_SIZE = 45;
bool debug;	// Global variable to indicate debugging

bool PromptYesNoMessage(string msg) {
	while (true) {
		cout << msg << "(y/n) ";
		string response;
		cin >> response;
		if (response == "y")
			return true;
		if (response == "n")
			return false;
		cout << "Please enter y or n..." << endl;
	}
}

int PromptGuesses()
{
	while (true) {
		int len;
		cout << "Please enter how many guesses: ";
		cin >> len;
		if (len > 0)
			return len;
	}
}

int PromptWordLength()
{
	int len = 0;

	// Your code here...
	
	cout << "choose your desired word length: ";
	cin >> len;
	while (len <= 0 || len > MAX_WORD_SIZE) {
		cout << "no word of that length exists, pick again: ";
		cin >> len;
	}
	return len;
}

string PromptGuess(string& guessedLetters)
{
	string guess = "";
	
	// Your code here...
	cout << "guess: ";
	cin >> guess;
	char character = guess[0];
	while (isalpha(character)) {
		cout << character << "was not a letter in the alphabet, try again: ";
		cin >> guess;
		string temp = guessedLetters + guess;
		if (temp == guessedLetters) {
			cout << "you already guessed that letter! guess again";
			cin >> guess;
		}
		guessedLetters += guess;
	}
	return guess;
}

string ChooseFamily(string guess, string guessProgress, FamilySet& set)
{
	// filter families by guess and guessProgress/guessPattern

	string maxFamily;
	string curr_family;
	string next_family;

	int curr_family_size;
	int next_family_size;
	/*
	 * Use the iterator to loop through each family and
	 * figure out the biggest family size.
	 * Return this family
	 */
	set.filterFamilies(guess, guessProgress);
	while (set.hasNext()) {
		// the current family and its size
		curr_family = set.getNextFamily();
		curr_family_size = set.familySize(curr_family);
		
		// the next family and its size
		next_family = set.getNextFamily();
		next_family_size = set.familySize(next_family);
		
		// compare the size of the two families
		if (curr_family_size < next_family_size) {
			maxFamily = next_family;
			
		}
		else {
			maxFamily = curr_family;
		}
		// moves up curr_family up to the next family
		curr_family = set.getNextFamily();
	}
	set.resetFamilyIter();
	return maxFamily;
}

bool isWin(string guessedProgress)
{
	return guessedProgress.find("*") == string::npos;
}

void PlayEvilHangman(string file)
{
	string guessProgress;
	int len = 0, guessesLeft = 0;
	// Prompt user for word length and number of guesses
	len = PromptWordLength();

	guessesLeft = PromptGuesses();
	// Load dictionary based on word length
	cout << "Loading dictionary..." << endl;
	
	//set object
	FamilySet families(file, len);

	string guessedLetters = "";
	string correctlyGuessed = "";	// correctly guessed positions
	for (int i = 0; i < len; i++)
		guessProgress += "*";
	
	
	
	

	// Actual game loop...
	while (true) {
		
		// Your code here...
		cout << "number of guesses left" << len << endl;

		
		// prompt guesses
		guessedLetters += PromptGuess(guessedLetters);
		cout << "guessed letters: "<< guessedLetters << endl;
		cout << "guesss progress: " << guessProgress << endl;

		if (debug) {
			for()
		}

		string family;
		// finds the largest family to set current family to
		family = ChooseFamily(guessedLetters, guessProgress, families);
		//sets master list to the largest possible family
		families.setFamily(family);

		if (family != "") {
			cout << "your guess is from family: " << family << endl;
		}

		if (isWin(guessProgress)) {
			cout << "Wow! You won!" << endl;
			break;
		}

		if (guessesLeft <= 0) {
			cout << "Wow... you are a really bad guesser..." << endl;
			cout << "The mystery word was " <<endl;
			break;
		}
	}
}

int main()
{
	string file;
	/*cout << "Enter file: ";
	cin >> file;	*/			// Can comment out this line and include the following while developing
	file = "dictionary.txt";  // Convenient to hard code while developing
	
	while (true) {
		debug = PromptYesNoMessage("Turn debugging on?");
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again ?"))
			break;
	}
}

