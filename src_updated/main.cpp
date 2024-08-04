#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <set>
#include "genrePredictor.hpp"
#include "topTen.hpp"

using namespace std;

// The stopwords from ../resources/stopwords.txt are from the default stopwords list on https://www.ranks.nl/stopwords


int main() {
    ifstream file("../resources/dfnew.csv");

    set<string> commonStopwords = generateStopwords();

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

    file.open("../resources/dfnew.csv");
    getline(file, line);

    MapStructure orderedFiltered;

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
        orderedFiltered.addGenre(genre);
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

            if(commonStopwords.count(word) == 0) {     // If word not in set of stopwords, add to map
                orderedFiltered.addWord(genre, word);
            }
        }
    }



    file.close();

    file.open("../resources/dfnew.csv");
    getline(file, line);

    UnorderedMapStructure unorderedFiltered;

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
        unorderedFiltered.addGenre(genre);
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

            if(commonStopwords.count(word) == 0) {     // If word not in set of stopwords, add to map
                unorderedFiltered.addWord(genre, word);
            }
        }
    }
    file.close();

    topTenUnordered(unorderedFiltered, "pop");

    cout << endl;

    topTenOrdered(orderedFiltered, "pop");


//    string x;
//    cout << "Enter song lyrics to be analyzed: " << endl;
//    cin >> x;

//    cout << endl;
//    cout << "Predicted genre unordered filtered: " << calculateGenreUnordered(x, unorderedFiltered) << endl;
//    cout << endl;

    return 0;
}