//
//  largestWordValue.cpp
//  ScrabbleCheat
//
//  Created by Max Zuber on 6/14/22.
//

#include "largestWordValue.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

int points(string word) {
    unordered_map<char, int> letterVals;
    letterVals['a'] = 1;
    letterVals['b'] = 4;
    letterVals['c'] = 4;
    letterVals['d'] = 2;
    letterVals['e'] = 1;
    letterVals['f'] = 4;
    letterVals['g'] = 3;
    letterVals['h'] = 3;
    letterVals['i'] = 1;
    letterVals['j'] = 10;
    letterVals['k'] = 5;
    letterVals['l'] = 2;
    letterVals['m'] = 4;
    letterVals['n'] = 2;
    letterVals['o'] = 1;
    letterVals['p'] = 4;
    letterVals['q'] = 10;
    letterVals['r'] = 1;
    letterVals['s'] = 1;
    letterVals['t'] = 1;
    letterVals['u'] = 2;
    letterVals['v'] = 5;
    letterVals['w'] = 4;
    letterVals['x'] = 8;
    letterVals['y'] = 3;
    letterVals['z'] = 10;
    letterVals['?'] = 0;
    
    int count = 0;
    for(char c : word) {
        count += letterVals[c];
    }
    return count;
}

bool validWord(string word) {
    unordered_map<char, int> letterVals;
    letterVals['a'] = 9;
    letterVals['b'] = 2;
    letterVals['c'] = 2;
    letterVals['d'] = 5;
    letterVals['e'] = 13;
    letterVals['f'] = 2;
    letterVals['g'] = 3;
    letterVals['h'] = 4;
    letterVals['i'] = 1;
    letterVals['j'] = 1;
    letterVals['k'] = 1;
    letterVals['l'] = 4;
    letterVals['m'] = 2;
    letterVals['n'] = 5;
    letterVals['o'] = 8;
    letterVals['p'] = 2;
    letterVals['q'] = 1;
    letterVals['r'] = 6;
    letterVals['s'] = 5;
    letterVals['t'] = 7;
    letterVals['u'] = 4;
    letterVals['v'] = 2;
    letterVals['w'] = 2;
    letterVals['x'] = 1;
    letterVals['y'] = 2;
    letterVals['z'] = 1;
    if(word.length() > 15){
        return false;
    }
    for(char c : word) {
        if(letterVals[c] == 0) return false;
        letterVals[c]--;
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    //
    string name = "run";
    
    //ifstream File("words_alpha.txt");
    ifstream File("enable1.txt");
    string Word;
    unordered_map<int, int> highest;
    string high = "";
    while(File >> Word)
    {
        if(validWord(Word) && points(Word) > highest[(int)Word.length()]) {
            highest[(int)Word.length()] = points(Word);
            high = Word;
        }
         
    }
    cout << "Hello, Maxwell!\n";
    cout << "Found largest words to be:\n";
    for(int i = 2; i < 16; i++) {
        cout << i << ": " << highest[i] << "\n";
    }
    
    
    
    return 0;
}
