#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include "lexicon.h"
#include "vector.h"
#include "console.h"
using namespace std;

vector<string> getPossibleChars(int numLetters);
Lexicon initialiseDict();
void searchForPossibleWords(vector<string>& toFigureOut, string chosen
                            , int totalSize, int currentSize
                            ,Lexicon& dictionary, unordered_set<string>& wordsFound);

int main() {
    Lexicon dictionary = initialiseDict();
    cout << "Number of letter in the word: ";
    int numLetters;
    cin >> numLetters;
    vector<string> toFigureOut = getPossibleChars(numLetters);
    unordered_set<string> wordsFound;
    searchForPossibleWords(toFigureOut, "", numLetters, 0, dictionary, wordsFound);
    return 0;
}

vector<string> getPossibleChars(int numLetters) {
    vector<string> toFigureOut;
    for (int i = 0; i < numLetters; ++i) {
        string possibleChars;
        cout << "possible letters for " << i+1;
        if ((i + 1) % 10 == 1) {
            cout << "st word (no seperation between each character): ";
        } else if ((i + 1)  % 10 == 2) {
            cout << "nd word (no seperation between each character): ";
        } else if ((i + 1)  % 10 == 3) {
            cout << "rd word (no seperation between each character): ";
        } else {
            cout << "th word (no seperation between each character): ";
        }
        cin >> possibleChars;
        toFigureOut.push_back(possibleChars);
    }
    return toFigureOut;
}

Lexicon initialiseDict() {
    ifstream input("words_alpha.txt");
    string word;
    Lexicon dictionary;
    while (input >> word) {
        dictionary.add(word);
    }
    return dictionary;
}

void searchForPossibleWords(vector<string>& toFigureOut, string chosen
                            , int totalSize, int currentSize
                            , Lexicon& dictionary, unordered_set<string>& wordsFound) {
    if (currentSize == totalSize) {
        //cout << "reached base case!" <<endl;
        //cout << chosen <<endl;
        if (dictionary.contains(chosen) && wordsFound.find(chosen) == wordsFound.end()) {
            wordsFound.insert(chosen);
            cout << chosen <<endl;
        }
    } else {
        //cout << "reached recursion!" <<endl;

        for (int i = 0; i < toFigureOut[currentSize].length(); ++i) {
            chosen += toFigureOut[currentSize][i];
            //cout << chosen <<endl;
            if (dictionary.containsPrefix(chosen)) {
                searchForPossibleWords(toFigureOut, chosen, totalSize, currentSize + 1, dictionary, wordsFound);
            }
            chosen.erase(chosen.length() - 1);
        }
    }
}
