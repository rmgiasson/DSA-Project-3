#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "genrePredictor.hpp"
//#include "test.cpp"
using namespace std;

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

    vector<Song> songs;

    for(int i = 0; i < 10000; i++){
        Song currSong;

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

        currSong.genre = genre;
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

            currSong.words.push_back(word);
        }
        songs.push_back(currSong);
    }

    file.close();

//    string x;
//    cout << "Enter song lyrics to be analyzed: " << endl;
//    cin >> x;

    unordered_map<string, double> idfUnordered = computeIDFUnordered(songs);

    map<string, double> idfOrdered = computeIDFOrdered(songs);

    //// Write menu code here









    return 0;
}

