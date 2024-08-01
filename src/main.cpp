#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "mapStructure.hpp"
#include "unorderedMapStructure.hpp"
using namespace std;

int main() {
    ifstream file("../resources/dfnew.csv");

    string line;
    getline(file, line);

    MapStructure ordered;

    for(int i = 0; i < 10000; i++){
        getline(file, line);
        stringstream ss(line);
        string genre;
        string dummy;
        for(int i = 0; i < 6; i++){
            if(i == 2)
                getline(ss, genre, ',');
            else    
                getline(ss, dummy, ',');
        }
        ordered.addGenre(genre);
        while(getline(ss, dummy, ' ')){
            string word = "";
            for(char c : dummy){
                if(c >= 'a' && c <= 'z'){
                    word.push_back(c);
                }
                else if(c >= 'A' && c <= 'Z'){
                    word.push_back(c - 'A' + 'a');
                }
                else if(c == '\''){
                    word.push_back(c);
                }
            }
            if(word.size() == 0){
                continue;
            }
            ordered.addWord(genre, word);
        }
    }

    file.close();

    file.open("../resources/dfnew.csv");
    getline(file, line);

    UnorderedMapStructure unordered;

    for(int i = 0; i < 10000; i++){
        getline(file, line);
        stringstream ss(line);
        string genre;
        string dummy;
        for(int i = 0; i < 6; i++){
            if(i == 2)
                getline(ss, genre, ',');
            else    
                getline(ss, dummy, ',');
        }
        unordered.addGenre(genre);
        while(getline(ss, dummy, ' ')){
            string word = "";
            for(char c : dummy){
                if(c >= 'a' && c <= 'z'){
                    word.push_back(c);
                }
                else if(c >= 'A' && c <= 'Z'){
                    word.push_back(c - 'A' + 'a');
                }
                else if(c == '\''){
                    word.push_back(c);
                }
            }
            if(word.size() == 0){
                continue;
            }
            unordered.addWord(genre, word);
        }
    }
    
    file.close();
    cout << ordered.getWordFreq("pop", "wow") << endl;
    cout << unordered.getWordFreq("pop", "wow");
    return 0;
}