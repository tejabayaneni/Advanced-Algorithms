#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
#include <typeinfo>
#include "RBTreeMap.h"
using namespace std;
//RBTreeMap rBTreeMap();
//RBTREE rbTree();
struct wordsFamily {
	int freq;
	set<string> family;
};
typedef RBTreeMap< string, wordsFamily>  wordFamilyMap;

/* Declaring functions */
void PromptYesNoMessage( set<string>& ansYes, set<string>& ansNo );
int PromptWordLength( string& prompt);
bool getAlphabet( string& prompt, set<string> ansYes, set<string> ansNo);
char PromptGuesses( string prompt);
bool PromptGuess( char nextCh, set<char> charUsed );
void readDictionary( ifstream& filename, set<string>& words);
void remDictionary( size_t wordLen, set<string>& master, set<string>& words,
		string prompt);
bool RBTreeMapCompare(const RBTreeMap<string, wordsFamily >& lhs,
		const RBTreeMap<string, wordsFamily >& rhs);
string wrongAlphabet( int wordLen );
int modifyWord( string wordCode, string wrongGuess, char nextCh, vector<char>& word);
void printWord( vector<char> word );
void printRemainingWords( vector<char> word, int noGuesses, bool showWords,
set<char> charUsed, set<string>& mainDictionary );
/* Prompt User for an word length */
int PromptWordLength( string& prompt)
{
	string text; int len;
	while (true) {
		cout << prompt;
		getline( cin, text);
		istringstream sender(text);
		sender >> len;
		if (sender.fail() || len< 0)
			cout << "Please enter valid length between 0 to 30\n" << endl;
		else if (len > 0 && len < 29 && len != 27 && len != 26)
				return len;
		else
				cout<<"Enter valid length between 0 to 30\n";
	}
}

/* Prompt User for an Alphabet */
char PromptGuesses( string prompt)
{
	string text;

	while( true){
		cout << prompt;
		getline(cin, text);
		if (text[text.size() - 1] == '\r') text.resize(text.size() - 1);
		if (text.length()>1 || !isalpha(text[0])) {
			cout << "Not a Single Alphabet, Try Again!" << endl;
		} else {
			cout<< endl;
			return text[0];
		}
	}
}

/* Prompt User for a y/n Answer */
bool getAlphabet( string& prompt, set<string> ansYes, set<string> ansNo )
{
	string text;
	while (true) {
		cout << prompt;
		getline( cin, text);
		if (text[text.size() - 1] == '\r') text.resize(text.size() - 1);
		for (string::iterator itr = text.begin(); itr != text.end(); ++itr)
			*itr = tolower(*itr);
		if (ansYes.find(text) != ansYes.end())
			return 1;
		else if ( ansNo.find(text) != ansNo.end() )
			return 0;
		cout << "Please enter y/n, Try Again!" << endl;
	}
}
/* taking the yes or no answer */
void PromptYesNoMessage( set<string>& ansYes, set<string>& ansNo)
{
	string tempList[] =  {"y"};
	int tempListSize = sizeof tempList / sizeof(string);
	ansYes.insert( tempList, tempList+ tempListSize);
	string tempList1[] = {"n"};
	tempListSize = sizeof tempList1 / sizeof(string);
	ansNo.insert( tempList1, tempList1+ tempListSize);
}

/* Checks whether the alphabet Entered by User was Used Already */
bool PromptGuess( char nextCh, set<char> charUsed )
{
	if ( charUsed.find(nextCh) == charUsed.end() ) return 0;
	else return 1;
}

/* Main Function */
int main() {
	// reading filename as string
	string filen;
	ifstream filename;
	cout<<"Enter filename";
	cin>>filen;
	//copying that file content to other file
	filename.open(filen.c_str());
	if( !filename.is_open() ) {
		cout << "Unable to Load File" << endl;
		return 0;
	}
	set<string> words;
	//reading values from
	readDictionary( filename, words);
	// making game as true to run until it is false.
	bool playgame=1;
	while( playgame ) {
		// Initializing Sets used to check for correct Yes/No Answer
		set<string> ansYes, ansNo;
		PromptYesNoMessage( ansYes, ansNo);
		// Prompt for the Number of Guesses
		string prompt = "Please enter how many guesses:  ";
		int noGuesses = PromptWordLength( prompt);

	  prompt = "Turn debugging on?(y/n)";
		bool showWords = getAlphabet( prompt, ansYes, ansNo);

		if (!noGuesses) {
			prompt = "No Guesses, No Game! Would You Like To Play Again (Y/N)? ";
			playgame = getAlphabet( prompt, ansYes, ansNo);
			if (playgame)
				continue;
			else
				break;
		}
		// Prompt whether User wants to see Remaining Word List
		// Prompt User for the Word Length
		prompt = "Enter the Word Length for the Hangman: ";
		size_t wordLen = PromptWordLength( prompt);
		cout << endl;
		// string of all 0's indicating incorrect guess
		string wrongGuess = wrongAlphabet( wordLen );
		/*remove the words from dictionary */
		set<string> mainDictionary;
		remDictionary( wordLen, mainDictionary, words, prompt);
		// Initialize word with *
		vector<char> word(wordLen, '*');
		// Initialize set of characters Used
		set<char> charUsed;
		// Print Word
		printWord( word);
		// Repeat until word Length is Reached or the no. of Guesses Expire
		while( wordLen > 0 && noGuesses > 0 ) {
			// Prompt for Next Guess and Update Results
			prompt = "Enter Your Guess: ";
			char nextCh = PromptGuesses( prompt);
			// Check if alphabet is Not Used Already
			bool isBadCh = PromptGuess( nextCh, charUsed );
			if (isBadCh) {
				cout << "Character Used Already" << endl;
				continue;
			} else
				charUsed.insert(nextCh);
				wordFamilyMap wordFamilies;
					RBTree.addNode(string,wordsFamily);
					RBTreeMap<string, wordsFamily> maxwordsFamily = *max_element( wordFamilies.begin(),
					wordFamilies.end(), RBTreeMapCompare);
					mainDictionary.clear();
					mainDictionary = maxwordsFamily.second.family;
					string wordCode = maxwordsFamily.first;
					int characGuessed = modifyWord( wordCode, wrongGuess, nextCh,  word);
					// Update wordLen
					if( characGuessed == 0 )
					noGuesses--;
						else
						wordLen -= characGuessed;
						// Print remaining Words in the dictionary
						printRemainingWords( word, noGuesses, showWords, charUsed, mainDictionary );
		}

		// State the Result: Win or Lose
		if ( noGuesses == 0 ) {
			cout << "Better Luck Next Time" << endl;
			cout << "The Word was: " << *mainDictionary.begin() << "\n" << endl;
		} else
			cout << "You won! \n" << endl;

		// Prompt for Another Try
		prompt = "Would you like to play again (Y/N)? ";
		playgame = getAlphabet( prompt, ansYes, ansNo);
		cout << endl;
	}

	return 0;
}
/* Outputs the result after Each Turn: Word, No. of Guesses, alphabets Used */
void printRemainingWords( vector<char> word, int noGuesses, bool showWords,
		set<char> charUsed, set<string>& mainDictionary )
{
	printWord( word);
	cout << "No of Guesses Left: " << noGuesses << endl;
	if ( showWords ) {
		cout << "New Dictionary Length: " << mainDictionary.size() << endl;
		cout << "Words are: ";
		for ( set<string>::iterator itr = mainDictionary.begin(); itr != mainDictionary.end(); ++itr ){
			cout << *itr << ", ";
		}
		cout << "\b\b " << endl;
	}
}

/* Update the Blank Word with the Guessed alphabet */
int modifyWord( string wordCode, string wrongGuess, char nextCh, vector<char>& word)
{
	if ( wordCode == wrongGuess )
		return 0;

	int count = 0;
	for (int i = 0; i < wordCode.length(); i++){
		if ( wordCode[i] == '1') {
			word[i] = nextCh;
			count++;
		}
	}
	return count;
}

/* Comparator Function to be Used with max_element for set */
bool RBTreeMapCompare(const RBTreeMap<string, wordsFamily >& lhs,
		const RBTreeMap<string, wordsFamily >& rhs)
{
	return lhs.length < rhs.length;
}

/* Prints the word */
void printWord( vector<char> word)
{
	for (size_t i = 0; i < word.size(); i++) {
		cout << word[i];
	}
	cout << '\n' << endl;
}
/* Removes the Dictionary to Keep only the specific Word Length Words */
void remDictionary( size_t wordLen, set<string>& mainDictionary, set<string>& words,
		string prompt)
{
	while( mainDictionary.empty() ) {
		for( set<string>::iterator itr = words.begin(); itr != words.end(); ++itr) {
			if ( (*itr).length() == wordLen ) {
				mainDictionary.insert(*itr);
			}
		}

		if( mainDictionary.empty()) {
			cout << "No word that long in the Dictionary, Try Again!" << endl;
			wordLen = PromptWordLength( prompt);
		}
	}
	return;
}

/* Generates a Word of All 0 to represent an Incorrect Guess */
string wrongAlphabet( int wordLen )
{
	string dummy;
	for (int i = 0; i < wordLen; i++ ) {
		dummy += '0';
	}
	return dummy;
}

/* Read Dictionary Words into a set */
void readDictionary( ifstream& filename, set<string>& words)
{
	string text;
	while( getline(filename, text))
		words.insert( text);
}
