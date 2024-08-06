#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include "genrePredictor.hpp"

using namespace std;
using namespace chrono;

int main() {
    ifstream file("../resources/dfnew.csv");

    set<string> commonStopwords = generateStopwords();

    string line;
    getline(file, line);

    MapStructure ordered;

    for (int i = 0; i < 10000; i++) {
        getline(file, line);
        stringstream ss(line);
        string genre;
        string dummy;
        for (int i = 0; i < 6; i++) {
            if (i == 2)
                getline(ss, genre, ',');
            else
                getline(ss, dummy, ',');
        }
        ordered.addGenre(genre);
        while (getline(ss, dummy, ' ')) {
            string word = "";
            for (char c: dummy) {
                if (c >= 'a' && c <= 'z') {
                    word.push_back(c);
                } else if (c >= 'A' && c <= 'Z') {
                    word.push_back(c - 'A' + 'a');
                } else if (c == '\'') {
                    word.push_back(c);
                }
            }
            if (word.size() == 0) {
                continue;
            }
            ordered.addWord(genre, word);
        }
    }

    file.close();

    file.open("../resources/dfnew.csv");
    getline(file, line);

    UnorderedMapStructure unordered;

    for (int i = 0; i < 10000; i++) {
        getline(file, line);
        stringstream ss(line);
        string genre;
        string dummy;
        for (int i = 0; i < 6; i++) {
            if (i == 2)
                getline(ss, genre, ',');
            else
                getline(ss, dummy, ',');
        }
        unordered.addGenre(genre);
        while (getline(ss, dummy, ' ')) {
            string word = "";
            for (char c: dummy) {
                if (c >= 'a' && c <= 'z') {
                    word.push_back(c);
                } else if (c >= 'A' && c <= 'Z') {
                    word.push_back(c - 'A' + 'a');
                } else if (c == '\'') {
                    word.push_back(c);
                }
            }
            if (word.size() == 0) {
                continue;
            }
            unordered.addWord(genre, word);
        }
    }


    file.close();

    file.open("../resources/dfnew.csv");
    getline(file, line);

    MapStructure orderedFiltered;

    for (int i = 0; i < 10000; i++) {
        getline(file, line);
        stringstream ss(line);
        string genre;
        string dummy;
        for (int i = 0; i < 6; i++) {
            if (i == 2)
                getline(ss, genre, ',');
            else
                getline(ss, dummy, ',');
        }
        orderedFiltered.addGenre(genre);
        while (getline(ss, dummy, ' ')) {
            string word = "";
            for (char c: dummy) {
                if (c >= 'a' && c <= 'z') {
                    word.push_back(c);
                } else if (c >= 'A' && c <= 'Z') {
                    word.push_back(c - 'A' + 'a');
                } else if (c == '\'') {
                    word.push_back(c);
                }
            }
            if (word.size() == 0) {
                continue;
            }

            if (commonStopwords.count(word) == 0) {     // If word not in set of stopwords, add to map
                orderedFiltered.addWord(genre, word);
            }
        }
    }

    file.close();

    file.open("../resources/dfnew.csv");
    getline(file, line);

    UnorderedMapStructure unorderedFiltered;

    vector<Song> songs;

    for (int i = 0; i < 10000; i++) {
        Song currSong;

        getline(file, line);
        stringstream ss(line);
        string genre;
        string dummy;
        for (int i = 0; i < 6; i++) {
            if (i == 2)
                getline(ss, genre, ',');
            else
                getline(ss, dummy, ',');
        }
        unorderedFiltered.addGenre(genre);

        currSong.genre = genre;
        while (getline(ss, dummy, ' ')) {
            string word = "";
            for (char c: dummy) {
                if (c >= 'a' && c <= 'z') {
                    word.push_back(c);
                } else if (c >= 'A' && c <= 'Z') {
                    word.push_back(c - 'A' + 'a');
                } else if (c == '\'') {
                    word.push_back(c);
                }
            }
            if (word.size() == 0) {
                continue;
            }

            if (commonStopwords.count(word) == 0) {     // If word not in set of stopwords, add to map
                unorderedFiltered.addWord(genre, word);
            }

            currSong.words.push_back(word);
        }
        songs.push_back(currSong);
    }

    file.close();

    unordered_map<string, double> idfUnordered = computeIDFUnordered(songs);

    map<string, double> idfOrdered = computeIDFOrdered(songs);

    while (true) {
        cout << "---------------------------------------------" << endl;        // Prints menu
        cout << "1. Determine genre of song lyrics" << endl;
        cout << "2. Most common 10 words by genre" << endl;
        cout << "3. Frequency of inputted word for each genre" << endl;
        cout << "4. Quit" << endl;
        cout << "---------------------------------------------" << endl;
        cout << endl;

        string y = "";
        cout << "Please enter a menu option: " << endl;
        cin >> y;

        cin.ignore();               // Clear any extra input left in the buffer

        if (y.size() != 1) {
            cout << "Please enter an integer between 1 and 4" << endl;
            continue;
        }

        if (!isdigit(y[0])) {
            cout << "Please enter an integer between 1 and 4" << endl;
            continue;
        }

        int option = stoi(y);
        if (option < 1 || option > 4) {
            cout << "Please enter an integer between 1 and 4" << endl;
            continue;
        } else if (option == 4) {
            cout << "Program ended." << endl;
            break;
        } else if (option == 1) {
            string x, temp;
            cout << "Enter song lyrics to be analyzed (press enter 3 times after lyrics are entered): " << endl;

            while (true) {
                cin.ignore();
                getline(cin, temp);
                if (temp.empty()) break;
                x += temp + "\n";
            }

            cout << endl;

            auto start1 = high_resolution_clock::now();

            cout << "Predicted Genre: " << determineGenreUnordered(x, songs, idfUnordered) << endl;

            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<milliseconds>(stop1 - start1);

            cout << "Time taken for Unordered Map Implementation: " << duration1.count() << " milliseconds." << endl;

            auto start2 = high_resolution_clock::now();

            determineGenreOrdered(x, songs, idfOrdered);

            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<milliseconds>(stop2 - start2);

            cout << "Time Taken for Ordered Map Implementation: " << duration2.count() << " milliseconds." << endl;
            cout << endl;

            continue;
        }
    }

    return 0;
}
