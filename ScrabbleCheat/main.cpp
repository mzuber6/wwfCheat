//
//  main.cpp
//  ScrabbleCheat
//
//  Created by Max Zuber on 6/12/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

//TW: !
//DW: @
//TL: $
//DL: &
//Start: +


unordered_map<char, vector<int> > lastInstance;

vector<vector<char> > setupTable() {
    for(char c = 'a'; c <= 'z'; c++) {
        lastInstance[c] = {14,14};
    }
    cout << "Load previous game? (y/n): ";
    char load;
    cin >> load;
    vector<vector<char> > Table;
    
    for(int i = 0; i < 15; i++) {
        vector<char> row;
        for(int j = 0; j < 15; j++) {
            row.push_back(' ');
        }
        Table.push_back(row);
    }
    //60
    Table[0][3] = '!';
    Table[0][11] = '!';
    Table[3][0] = '!';
    Table[3][14] = '!';
    Table[11][0] = '!';
    Table[11][14] = '!';
    Table[14][3] = '!';
    Table[14][11] = '!';
    Table[0][6] = '$';
    Table[0][8] = '$';
    Table[3][3] = '$';
    Table[3][11] = '$';
    Table[5][5] = '$';
    Table[5][9] = '$';
    Table[6][0] = '$';
    Table[8][0] = '$';
    Table[6][14] = '$';
    Table[8][14] = '$';
    Table[9][5] = '$';
    Table[9][9] = '$';
    Table[14][6] = '$';
    Table[14][8] = '$';
    Table[11][3] = '$';
    Table[11][11] = '$';
    Table[1][5] = '@';
    Table[1][9] = '@';
    Table[3][7] = '@';
    Table[5][1] = '@';
    Table[5][13] = '@';
    Table[7][3] = '@';
    Table[7][11] = '@';
    Table[9][1] = '@';
    Table[9][13] = '@';
    Table[11][7] = '@';
    Table[13][5] = '@';
    Table[13][9] = '@';
    Table[1][2] = '&';
    Table[1][12] = '&';
    Table[2][1] = '&';
    Table[2][13] = '&';
    Table[2][4] = '&';
    Table[2][10] = '&';
    Table[4][2] = '&';
    Table[4][6] = '&';
    Table[4][8] = '&';
    Table[4][12] = '&';
    Table[6][4] = '&';
    Table[6][10] = '&';
    Table[8][4] = '&';
    Table[8][10] = '&';
    Table[10][2] = '&';
    Table[10][6] = '&';
    Table[10][8] = '&';
    Table[10][12] = '&';
    Table[12][1] = '&';
    Table[12][4] = '&';
    Table[12][10] = '&';
    Table[12][13] = '&';
    Table[13][2] = '&';
    Table[13][12] = '&';
    Table[7][7] = '+';
    
    
    if(load == 'y') {
        
        cout << "Input file name (include .txt):";
        string fileName = "";
        cin >> fileName;
        vector<char> letters;
        ifstream File(fileName);
        char Word;
        File >> noskipws;
        while(File >> Word) {
            letters.push_back(Word);
        }
        for(int i = 0; i < 15; i++) {
            for(int j = 0; j < 15; j++) {
                Table[i][j] = letters[i*15 + j];
                lastInstance[letters[i*15 + j]] = {i,j};
            }
        }
    }
    return Table;
}

void printTable(vector<vector<char> > Table) {
    cout << "Current Board State\n   A B C D E F G H I J K L M N O \n  ===============================";
    for(int i = 0; i < 15; i++) {
        if(i < 10) {
            cout << "\n" << i << " |";
        }
        else {cout << "\n" << i << "|";}
        for(int j = 0; j < 15; j++) {
            cout << Table[i][j] << "|";
        }
        
    }
    cout << "\n  ===============================\n";

}

bool isUserTurn() {
    cout << "Input letter u for user input or any other letter to run on current board: ";
    char userIn;
    cin >> userIn;
    if(userIn == 'u') return true;
    return false;
}

void enterMoves(vector<vector<char> > *Table) {
    int row = 0;
    while(row != -1) {
        cout << "Enter Location or '-1' to stop entering\nRow:";
        cin >> row;
        if(row == -1) break;
        cout << "Column:";
        char c = ' ';
        cin >> c;
        int col = (int)c - 65;
        if(col >= 32) {
            col -= 32;
        }
        cout << "\nEnter Direction '>' for right '<' for down:";
        char dir = ' ';
        cin >> dir;
        cout << "\nEnter Word: ";
        string word = "";
        cin >> word;
        for(int i = 0; i < word.length(); i++) {
            char tempHolder = word[i];
            if(tempHolder < 97) {
                tempHolder += 32;
            }
            if(dir == '>') {
                (*Table)[row][col+i] = tempHolder;
                lastInstance[tempHolder] = {row,col+i};
            }else {
                (*Table)[row+i][col] = tempHolder;
                lastInstance[tempHolder] = {row+i,col};
            }
            
        }
        
        cout <<"\n";
        printTable(*Table);
    }
    cout << "Done inputing characters.\n";
    cout << "Would you like to save? (enter file name including .txt or n): ";
    string name = "";
    cin >> name;
    if(name == "n") {
        return;
    }
    ofstream MyFile(name);
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            MyFile << (*Table)[i][j];
        }
    }
    cout <<"\n";
}

vector<char> getHand() {
    vector<char> hand;
    cout << "Please input your hand: ";
    string temp = "";
    cin >> temp;
    for(char c : temp) {
        hand.push_back(c);
    }
    return hand;
}

bool isLetter(char c) {
    if(c == 'a' || c == 'b' || c == 'c' || c == 'd'|| c == 'e'|| c == 'f'|| c == 'g'|| c == 'h'|| c == 'i'|| c == 'j'|| c == 'k'|| c == 'l'|| c == 'm'|| c == 'n'|| c == 'o'|| c == 'p'|| c == 'q'|| c == 'r'|| c == 's'|| c == 't'|| c == 'u'|| c == 'v'|| c == 'w'|| c == 'x'|| c == 'y'|| c == 'z') {
        return true;
    }
    return false;
}

bool isAnagram(string word, unordered_map<char, int> lettersTable, unordered_map<char, int> letters, int count) {
    bool hasHandLetter = false;
    if(word.length() > count || word.length() > 15) {
        return false;
    }
    for(int i = 0; i < word.length(); i++) {
        if(letters[word[i]] != 0) {
            hasHandLetter = true;
            letters[word[i]]--;
        }else{
            if(lettersTable[word[i]] != 0) {
                lettersTable[word[i]]--;
            }else{
                
                return false;
            }
        }
    }
    if(hasHandLetter) {
        return true;
    }
    return false;
}
//7
set<string> getAnagrams(unordered_map<string, int> Dictionary, vector<vector<char> > Table, vector<char> hand) {
    set<string> anagrams;
    unordered_map<char, int> handMap;
    unordered_map<char, int> tableMap;
    int count = 0;
    for(char c : hand) {
        handMap[c]++;
        count++;
    }
    for(vector<char> row : Table) {
        for(char c : row) {
            if(isLetter(c)) {
                tableMap[c]++;
                count++;
            }
        }
    }
    
    
    for(auto i = Dictionary.begin(); i != Dictionary.end(); i++) {
        if(isAnagram(i->first, tableMap, handMap, count)) {
            anagrams.insert(i->first);
        }
    }
    
    return anagrams;
}

bool isWordValid(unordered_map<string, int> Dictionary, string word, vector<vector<char> > Table, int row, int col, bool right) {
    bool touchesTable = false;
    if(right) {
        if(word.length() + col > 14) {
            return false;
        }
        for(int i = 0; i < word.length(); i++) {
            if(isLetter(Table[row][col+i])) {
                if(Table[row][col+i] != word[i]) {
                    return false;
                }
                touchesTable = true;
            }
            //move as high up and then go down, if length > 1 check validity
            string needsCheck = "";
            int rowTemp = row;
            while(rowTemp > 0 && isLetter(Table[rowTemp-1][col+i])) {
                rowTemp--;
            }
            while(rowTemp < 14 && (isLetter(Table[rowTemp+1][col+i]) || rowTemp + 1 == row)) {
                if(rowTemp == row) {
                    needsCheck += word[i];
                }else {
                    needsCheck += Table[rowTemp][col + i];
                }
                
                rowTemp++;
            }
            if(rowTemp == row) {
                needsCheck += word[i];
            }else {
                needsCheck += Table[rowTemp][col + i];

            }
            if(needsCheck.length() > 1) {
                touchesTable = true;
                if(Dictionary[needsCheck] != 1) {
                    return false;
                }
            }
        }
        //check for continuation before/after word
        string needsCheck = "";
        int colTemp = col;
        while(colTemp > 0 && isLetter(Table[row][colTemp-1])) {
            colTemp--;
        }
        while(colTemp < col) {
            
            needsCheck += Table[row][colTemp];
            colTemp++;
        }
        needsCheck += word;
        colTemp += word.length();
        while(colTemp <= 14 && isLetter(Table[row][colTemp])) {
            
            needsCheck += Table[row][colTemp];
            colTemp++;
        }
        if(needsCheck.length() > word.length()) {
            touchesTable = true;
            if(Dictionary[needsCheck] != 1) {
                return false;
            }
        }
        
    }else {
        if(word.length() + row > 14) {
            return false;
        }
        for(int i = 0; i < word.length(); i++) {
            if(isLetter(Table[row+i][col])) {
                if(Table[row+i][col] != word[i]) {
                    return false;
                }
                touchesTable = true;
            }
            //move as far left and then go right, if length > 1 check validity
            string needsCheck = "";
            int colTemp = col;
            while(colTemp > 0 && isLetter(Table[row + i][colTemp-1])) {
                colTemp--;
            }
            while(colTemp < 14 && (isLetter(Table[row + i][colTemp + 1]) || colTemp + 1 == col)) {
                if(colTemp == col) {
                    needsCheck += word[i];
                }else {
                    needsCheck += Table[row + i][colTemp];
                }
                colTemp++;
            }
            if(colTemp == col) {
                needsCheck += word[i];
            }else {
                needsCheck += Table[row+i][colTemp];
            }
            if(needsCheck.length() > 1) {
                touchesTable = true;
                if(Dictionary[needsCheck] != 1) {
                    return false;
                }
            }
        }
        //check for continuation before/after word
        string needsCheck = "";
        int rowTemp = row;
        while(rowTemp > 0 && isLetter(Table[rowTemp-1][col])) {
            rowTemp--;
        }
        while(rowTemp < row) {
            
            needsCheck += Table[rowTemp][col];
            rowTemp++;
        }
        needsCheck += word;
        rowTemp += word.length();
        while(rowTemp <= 14 && isLetter(Table[rowTemp][col])) {
            
            needsCheck += Table[rowTemp][col];
            rowTemp++;
        }
        if(needsCheck.length() > word.length()) {
            touchesTable = true;
            if(Dictionary[needsCheck] != 1) {
                return false;
            }
        }
    }
    
    //check all touching words
    if(!touchesTable) return false;
    return true;
}

bool letterCountCheck(string word, unordered_map<char, int> letters) {
    for(char c : word) {
        if(letters[c] != 0) {
            letters[c]--;
        }else {
            return false;
        }
    }
    return true;
}

bool checkCollisions(unordered_map<string, int> Dictionary, string * word, vector<vector<char> > Table, vector<char> hand, vector<vector<int> > * words, int * row, int * col) {\
    unordered_map<char, int> lettersWeHaveRight;
    unordered_map<char, int> lettersWeHaveLeft;
    for(char c : hand) {
        lettersWeHaveRight[c]++;
        lettersWeHaveLeft[c]++;
    }
    int origWordCount = (int) (*word).length();
    int firstStop = 1000;
    for(char c : *word) {
        if(lettersWeHaveRight[c] == 0 && lastInstance[c][0] * 15 + lastInstance[c][1] < firstStop) {
            firstStop = (int)lastInstance[c][0] * 15 + lastInstance[c][1];
        }
    }
    for(int i = *row; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if(i*15 + j > firstStop) {
                return false;
            }
            bool tooLongRight = false;
            bool tooLongLeft = false;
            for(int k = 0; k < origWordCount; k++) {
                if(j+k > 14) {
                    tooLongRight = true;
                }else if(isLetter(Table[i][j+k])) {
                    lettersWeHaveRight[Table[i][j+k]]++;
                }
                if(i+k > 14) {
                    tooLongLeft = true;
                }else if(isLetter(Table[i+k][j])) {
                    lettersWeHaveLeft[Table[i+k][j]]++;
                }
                if(tooLongRight && tooLongLeft) {
                    return false;
                }
            }
            vector<int> tempVec;
            tempVec.push_back(i);
            tempVec.push_back(j);
            if(!tooLongRight && letterCountCheck(*word, lettersWeHaveRight) && ((i == *row && j >= *col) || i > *row) && find((*words).begin(), (*words).end(), tempVec) == (*words).end() && isWordValid(Dictionary, *word, Table, i, j, true)) {
                char cc = j + 65;
                string location = "";
                if(i < 10) {
                    location += "0";
                }
                location += to_string(i) + cc + ">";
                (*word).append(location);
                (*words).push_back(tempVec);
                return true;
            }else if(!tooLongLeft && letterCountCheck(*word, lettersWeHaveLeft) && ((i == *row && j >= *col) || i > *row) && find((*words).begin(), (*words).end(), tempVec) == (*words).end() && isWordValid(Dictionary, *word, Table, i, j, false)) {
                char cc = j + 65;
                string location = "";
                if(i < 10) {
                    location += "0";
                }
                location += to_string(i) + cc + "<";
                (*word).append(location);
                (*words).push_back(tempVec);
                return true;
            }
            for(int k = 0; k < origWordCount; k++) {
                if(j+k <= 14 && isLetter(Table[i][j+k])) {
                    lettersWeHaveRight[Table[i][j+k]]--;
                }
                if(i+k <= 14 && isLetter(Table[i+k][j])) {
                    lettersWeHaveLeft[Table[i+k][j]]--;
                }
            }
        }
    }
    
    return false;
}

vector<string> getPlayableWords(unordered_map<string, int> Dictionary, vector<vector<char> > Table, vector<char> hand) {
    
    vector<string> validWords;
    set<string> anagrams = getAnagrams(Dictionary, Table, hand);
    //to test a set string uncomment the following 2 lines and comment line above.
    //set<string> anagrams;
    //anagrams.insert("didie");
    cout << anagrams.size() << " anagrams found, checking for valid words.\nThis may take awhile...\n0: ";
    
    int countOfWords = 1;
    int lineCounter = 1;
    int lessDash = 0;
    for(string word : anagrams) {
        vector<vector<int> > wordLocations;
        int row = 0;
        int col = 0;
        countOfWords++;
        if(countOfWords % 10 == 0 && lessDash == 0) {
            cout << "-";
        }else if(countOfWords %10 == 0) {
            lessDash--;
        }
        if(countOfWords % 400 == 0) {
            cout << word << "\n" << lineCounter << ": ";
            lineCounter++;
        }
        while(checkCollisions(Dictionary, &word, Table, hand, &wordLocations, &row, &col)) {
            validWords.push_back(word);
            //cout << "Valid Word: " << word << "\n";
            word = word.substr(0, word.length()-4);
            cout << ".";
            lessDash++;
        }
        if(anagrams.size() >= 10 && countOfWords % (anagrams.size() / 10) == 0) {
            cout << "\nHave checked " << countOfWords << " anagrams and have found " << validWords.size() << " valid words...\n";
            lineCounter = 0;
        }
    }
    //==================
    cout << "\nFound " << validWords.size() << " valid words!\n";
    //string winningWord = "words11D>";
    //validWords.push_back(winningWord);
    
    return validWords;
}

int points(string word, vector<vector<char> > Table, vector<char> hand) {
    //pull in hand and if length >= 8 check if contains all of hand (make sure the letters on the table aren't pretending to be in hand):: 35 bonus points for bingo
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
    
    int pointCount = 0;
    int addPointCount = 0;
    //cout << word;
    string position = word.substr(word.length()-4, word.length());
    string realWord = word.substr(0, word.length()-4);
    int col = (int)position[2] - 65;
    int row = (position[0] - '0') * 10 + (position[1] - '0');
    //cout << row << " " << col << "\n";
    if(position.back() == '>') {
        int multiplier = 1;
        for(int i = 0; i < realWord.length(); i++) {
            int letMult = 1;
            bool doubleCount = false;
            //TW: !
            //DW: @
            //TL: $
            //DL: &
            if(Table[row][col+i] == '!') {
                multiplier *= 3;
                int upDown = 1;
                while(row + upDown <= 14 && isLetter(Table[row + upDown][col+i])) {
                    addPointCount += letterVals[Table[row + upDown][col+i]] * 3;
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(row - upDown >= 0 && isLetter(Table[row - upDown][col+i])) {
                    addPointCount += letterVals[Table[row - upDown][col+i]] * 3;
                    upDown++;
                    doubleCount = true;
                }
            }else if(Table[row][col+i] == '@') {
                multiplier *= 2;
                int upDown = 1;
                while(row + upDown <= 14 && isLetter(Table[row + upDown][col+i])) {
                    addPointCount += letterVals[Table[row + upDown][col+i]] * 2;
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(row - upDown >= 0 && isLetter(Table[row - upDown][col+i])) {
                    addPointCount += letterVals[Table[row - upDown][col+i]] * 2;
                    upDown++;
                    doubleCount = true;
                }
            }else if(Table[row][col+i] == '$') {
                letMult *= 3;
                int upDown = 1;
                while(row + upDown <= 14 && isLetter(Table[row + upDown][col+i])) {
                    addPointCount += letterVals[Table[row + upDown][col+i]];
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(row - upDown >= 0 && isLetter(Table[row - upDown][col+i])) {
                    addPointCount += letterVals[Table[row - upDown][col+i]] ;
                    upDown++;
                    doubleCount = true;
                }
            }else if(Table[row][col+i] == '&') {
                letMult *= 2;
                int upDown = 1;
                while(row + upDown <= 14 && isLetter(Table[row + upDown][col+i])) {
                    addPointCount += letterVals[Table[row + upDown][col+i]] ;
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(row - upDown >= 0 && isLetter(Table[row - upDown][col+i])) {
                    addPointCount += letterVals[Table[row - upDown][col]] ;
                    upDown++;
                    doubleCount = true;
                }
            }else if(!isLetter(Table[row][col+i])){
                int upDown = 1;
                while(row + upDown <= 14 && isLetter(Table[row + upDown][col+i])) {
                    addPointCount += letterVals[Table[row + upDown][col+i]];
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(row - upDown >= 0 && isLetter(Table[row - upDown][col+i])) {
                    addPointCount += letterVals[Table[row - upDown][col+i]];
                    upDown++;
                    doubleCount = true;
                }
            }
            
            pointCount += letterVals[realWord[i]] * letMult;
            //cout << pointCount << "\n";
            if(doubleCount) {
                pointCount += letterVals[realWord[i]] * letMult;
            }
        }
        pointCount *= multiplier;
        //cout << pointCount << "\n";
        pointCount += addPointCount;
        //cout << pointCount << "\n";
        int count = (int)hand.size();
        if(count == 7 && realWord.length() >= 7) {
            for(int i = 0; i < realWord.length(); i++) {
                if(!isLetter(Table[row][col+i])) {
                    count--;
                }
            }
            pointCount += 35;
        }
    }else {
        int multiplier = 1;
        for(int i = 0; i < realWord.length(); i++) {
            int letMult = 1;
            bool doubleCount = false;
            //TW: !
            //DW: @
            //TL: $
            //DL: &
            if(Table[row+i][col] == '!') {
                multiplier *= 3;
                int upDown = 1;
                while(col + upDown <= 14 && isLetter(Table[row+i][col + upDown])) {
                    addPointCount += letterVals[Table[row+i][col + upDown]] * 3;
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(col - upDown >= 0 && isLetter(Table[row+i][col - upDown])) {
                    addPointCount += letterVals[Table[row+i][col - upDown]] * 3;
                    upDown++;
                    doubleCount = true;
                }
            }else if(Table[row+i][col] == '@') {
                multiplier *= 2;
                int upDown = 1;
                while(col + upDown <= 14 && isLetter(Table[row+i][col + upDown])) {
                    addPointCount += letterVals[Table[row+i][col + upDown]] * 2;
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(col - upDown >= 0 && isLetter(Table[row+i][col - upDown])) {
                    addPointCount += letterVals[Table[row+i][col - upDown]] * 2;
                    upDown++;
                    doubleCount = true;
                }
            }else if(Table[row+i][col] == '$') {
                letMult *= 3;
                int upDown = 1;
                while(col + upDown <= 14 && isLetter(Table[row+i][col + upDown])) {
                    addPointCount += letterVals[Table[row+i][col + upDown]];
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(col - upDown >= 0 && isLetter(Table[row+i][col - upDown])) {
                    addPointCount += letterVals[Table[row+i][col - upDown]] ;
                    upDown++;
                    doubleCount = true;
                }
            }else if(Table[row+i][col] == '&') {
                letMult *= 2;
                int upDown = 1;
                while(col + upDown <= 14 && isLetter(Table[row+i][col + upDown])) {
                    addPointCount += letterVals[Table[row+i][col + upDown]] ;
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(col - upDown >= 0 && isLetter(Table[row+i][col - upDown])) {
                    addPointCount += letterVals[Table[row+i][col - upDown]] ;
                    upDown++;
                    doubleCount = true;
                }
            }else if(!isLetter(Table[row+i][col])){
                int upDown = 1;
                while(col + upDown <= 14 && isLetter(Table[row+i][col + upDown])) {
                    addPointCount += letterVals[Table[row+i][col + upDown]];
                    upDown++;
                    doubleCount = true;
                }
                upDown = 1;
                while(col - upDown >= 0 && isLetter(Table[row+i][col - upDown])) {
                    addPointCount += letterVals[Table[row+i][col - upDown]];
                    upDown++;
                    doubleCount = true;
                }
            }
            
            pointCount += letterVals[realWord[i]] * letMult;
            if(doubleCount) {
                addPointCount += letterVals[realWord[i]] * letMult;
            }
        }
        pointCount *= multiplier;
        pointCount += addPointCount;
        int count = (int)hand.size();
        if(count == 7 && realWord.length() >= 7) {
            for(int i = 0; i < realWord.length(); i++) {
                if(!isLetter(Table[row+i][col])) {
                    count--;
                }
            }
            pointCount += 35;
        }
    }
    return pointCount;
}

void playToTable(string word, vector<vector<char> > * Table) {
    string position = word.substr(word.length()-4, word.length());
    string realWord = word.substr(0, word.length()-4);
    int col = (int)position[2] - 65;
    int row = (position[0] - '0') * 10 + (position[1] - '0');
    if(position.back() == '>') {
        for(int i = 0; i < realWord.length(); i++) {
            (*Table)[row][col + i] = realWord[i];
        }
    }else {
        for(int i = 0; i < realWord.length(); i++) {
            (*Table)[row + i][col] = realWord[i];
        }
    }
}

void givePossibilities(unordered_map<string, int> Dictionary, vector<vector<char> > Table) {
    
    vector<char> hand = getHand();
    vector<string> playableWords = getPlayableWords(Dictionary, Table, hand);
    //vector<string> playableWords;
    //playableWords.push_back("didie08A<");
    string winningWord = "";
    string secondWord = "";
    int count = 0;
    cout << "Calculating word worth most points...\n";
    for(string word : playableWords) {
        int tp = points(word, Table, hand);
        if(tp > count) {
            secondWord = winningWord;
            count = tp;
            winningWord = word;
        }
    }
    playToTable(winningWord, &Table);
    printTable(Table);
    cout << "You should play: " << winningWord.substr(0, winningWord.length()-4) << " at "<< winningWord.substr(winningWord.length()-4, winningWord.length()) << "\n";
    cout << "For " << count << " points!\n";
    cout << "You can try " << secondWord.substr(0, secondWord.length()-4) << " at "<< secondWord.substr(secondWord.length()-4, secondWord.length()) << " if that doesn't work\n";
    string name = "results.txt";
    ofstream MyFile(name);
    MyFile << "You should play: " << winningWord.substr(0, winningWord.length()-4) << " at "<< winningWord.substr(winningWord.length()-4, winningWord.length()) << "\n";
    MyFile << "For " << count << " points!\n";
    MyFile << "You can try " << secondWord.substr(0, secondWord.length()-4) << " at "<< secondWord.substr(secondWord.length()-4, secondWord.length()) << " if that doesn't work\n";
    
}

int main(int argc, const char * argv[]) {
    //
    string name = "run";
    
    unordered_map<string, int> Dictionary;
    //ifstream File("words_alpha.txt");
    ifstream File("enable1.txt");
    string Word;
    while(File >> Word)
    {
        if(Word.length() != 1 && Word.length() < 16){
            Dictionary[Word] = 1;
        }
         
    }
    cout << "Hello!\n";
    cout << "Loaded in dictionary of size: " << Dictionary.size() << "\n";
    
    vector<vector<char> > Table = setupTable();
    printTable(Table);
    while(name == "run") {
        if (isUserTurn()) {
            enterMoves(&Table);
        }
        givePossibilities(Dictionary, Table);
        cout << "Enter run to keep playing or q to end: ";
        cin >> name;
    }
    
    
    cout <<"Please Enter a save name (include .txt) or q to end without saving: ";
    cin >> name;
    if(name == "q") return 0;
    ofstream MyFile(name);
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            MyFile << Table[i][j];
        }
    }
    cout <<"\n";
    return 0;
}



