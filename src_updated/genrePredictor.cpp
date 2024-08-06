#include "genrePredictor.hpp"
#include "mapStructure.hpp"
#include "unorderedMapStructure.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

set<string> generateStopwords() {
    ifstream stopwords("../resources/stopwords.txt");

    set<string> commonStopwords;
    vector<string> words;

    string stopwordsLine;
    while(getline(stopwords, stopwordsLine, '\n')) {
        commonStopwords.insert(stopwordsLine);
    }
    stopwords.close();
    return commonStopwords;
}


// Function to compute term frequency using unordered maps
unordered_map<string, double> computeTFUnordered(vector<string>& words) {
    unordered_map<string, double> tf;
    for(string word : words) {
        if(!tf[word]) {
            tf[word] = 1;
        } else {
            tf[word]++;
        }
    }
    for(auto& val : tf) {
        val.second /= words.size();
    }
    return tf;
}

// Function to compute term frequency using ordered maps
map<string, double> computeTFOrdered(vector<string>& words) {
    map<string, double> tf;
    for(string word : words) {
        if(!tf[word]) {
            tf[word] = 1;
        } else {
            tf[word]++;
        }
    }
    for(auto& val : tf) {
        val.second /= words.size();
    }
    return tf;
}

// Function to compute inverse document frequency using unordered maps
unordered_map<string, double> computeIDFUnordered(vector<Song>& songs) {
    unordered_map<string, double> idf;          // Stores the idf values of all words in all songs
    unordered_map<string, int> docCount;        // Stores the number of songs that a word is in
    for(auto song : songs) {
        unordered_map<string, bool> seen;
        for(auto word : song.words) {
            if(!seen[word]) {
                docCount[word]++;
                seen[word] = true;
            }
        }
    }
    for (auto val : docCount) {
        string currWord = val.first;
        int wordCountInSongs = val.second;
        idf[currWord] = log((songs.size() + 0.0) / wordCountInSongs);
    }
    return idf;
}

// Function to compute inverse document frequency using ordered maps
map<string, double> computeIDFOrdered(vector<Song>& songs) {
    map<string, double> idf;          // Stores the idf values of all words in all songs
    map<string, int> docCount;        // Stores the number of songs that a word is in
    for(auto song : songs) {
        map<string, bool> seen;
        for(auto word : song.words) {
            if(!seen[word]) {
                docCount[word]++;
                seen[word] = true;
            }
        }
    }
    for (auto val : docCount) {
        string currWord = val.first;
        int wordCountInSongs = val.second;
        idf[currWord] = log((songs.size() + 0.0) / wordCountInSongs);
    }
    return idf;
}

// Function to compute TF-IDF using unordered maps
unordered_map<string, double> computeTFIDFUnordered(vector<string>& words, unordered_map<string, double>& idf) {
    unordered_map<string, double> tfidf;
    unordered_map<string, double> tf = computeTFUnordered(words);
    for (auto& val : tf) {
        string currWord = val.first;
        double tfVal = val.second;

        if (idf.find(currWord) != idf.end()) {              // Word is found in the idf map
            tfidf[currWord] = tfVal * idf.at(currWord);     // The TF-IDF value is the word's tf times its idf
        } else {
            continue;       // If the word is not found in the IDF map, continue
        }
    }
    return tfidf;
}

// Function to compute TF-IDF using ordered maps
map<string, double> computeTFIDFOrdered(vector<string>& words, map<string, double>& idf) {
    map<string, double> tfidf;
    map<string, double> tf = computeTFOrdered(words);
    for (auto& val : tf) {
        string currWord = val.first;
        double tfVal = val.second;

        if (idf.find(currWord) != idf.end()) {              // Word is found in the idf map
            tfidf[currWord] = tfVal * idf.at(currWord);     // The TF-IDF value is the word's tf times its idf
        } else {
            continue;       // If the word is not found in the IDF map, continue
        }
    }
    return tfidf;
}

// Function to compute cosine similarity using unordered maps
double cosineSimilarityUnordered(unordered_map<string, double>& vecA, unordered_map<string, double>& vecB) {
    double dotProduct = 0.0, normA = 0.0, normB = 0.0;
    for (auto val : vecA) {
        string wordInVecA = val.first;
        double tfidfInVecA = val.second;

        if (vecB.find(wordInVecA) != vecB.end()) {          // If word in vecA is found in vecB
            double tfidfInVecB = vecB.at(wordInVecA);
            dotProduct += tfidfInVecA * tfidfInVecB;     // Calculate the dot product
        }
        normA += tfidfInVecA * tfidfInVecA;
    }
    for (auto val : vecB) {
        double tfidfInVecB = val.second;
        normB += tfidfInVecB * tfidfInVecB;
    }
    normA = sqrt(normA);                             // Calculate the norms
    normB = sqrt(normB);
    if (normA == 0 || normB == 0) {
        return 0.0;
    }
    return dotProduct / (normA * normB);       // Return the cosine similarity between the two maps
}

// Function to compute cosine similarity using ordered maps
double cosineSimilarityOrdered(map<string, double>& vecA, map<string, double>& vecB) {
    double dotProduct = 0.0, normA = 0.0, normB = 0.0;
    for (auto val : vecA) {
        string wordInVecA = val.first;
        double tfidfInVecA = val.second;

        if (vecB.find(wordInVecA) != vecB.end()) {          // If word in vecA is found in vecB
            double tfidfInVecB = vecB.at(wordInVecA);
            dotProduct += tfidfInVecA * tfidfInVecB;     // Calculate the dot product
        }
        normA += tfidfInVecA * tfidfInVecA;
    }
    for (auto val : vecB) {
        double tfidfInVecB = val.second;
        normB += tfidfInVecB * tfidfInVecB;
    }
    normA = sqrt(normA);                             // Calculate the norms
    normB = sqrt(normB);
    if (normA == 0 || normB == 0) {
        return 0.0;
    }
    return dotProduct / (normA * normB);       // Return the cosine similarity between the two maps
}

// Computes genre vectors using unordered maps
unordered_map<string, unordered_map<string, double>> computeGenreVectorsUnordered(vector<Song>& songs, unordered_map<string, double>& idf) {
    unordered_map<string, unordered_map<string, double>> genreVectors;
    unordered_map<string, int> genreSongCounts;

    // Initialize genre vectors and counts
    for (auto& song : songs) {
        if (genreVectors.find(song.genre) == genreVectors.end()) {
            genreVectors[song.genre] = unordered_map<string, double>();
            genreSongCounts[song.genre] = 0;
        }
    }

    // Sum the TF-IDF vectors for each genre
    for (auto& song : songs) {
        vector<string> words = song.words;
        unordered_map<string, double> songTFIDF = computeTFIDFUnordered(words, idf);

        for (auto& val : songTFIDF) {
            string currWord = val.first;
            double currTFIDF = val.second;
            genreVectors[song.genre][currWord] += currTFIDF;
        }
        genreSongCounts[song.genre]++;
    }

    // Average the TF-IDF vectors for each genre
    for (auto& genreVector : genreVectors) {
        for (auto& val : genreVector.second) {
            val.second /= genreSongCounts[genreVector.first];   // Divide the current tfidf value by the number of songs in the current genre
        }
    }

    return genreVectors;
}


// Computes genre vectors using ordered maps
map<string, map<string, double>> computeGenreVectorsOrdered(vector<Song>& songs, map<string, double>& idf) {
    map<string, map<string, double>> genreVectors;
    map<string, int> genreSongCounts;

    // Initialize genre vectors and counts
    for (auto& song : songs) {
        if (genreVectors.find(song.genre) == genreVectors.end()) {
            genreVectors[song.genre] = map<string, double>();
            genreSongCounts[song.genre] = 0;
        }
    }

    // Sum the TF-IDF vectors for each genre
    for (auto& song : songs) {
        vector<string> words = song.words;
        map<string, double> songTFIDF = computeTFIDFOrdered(words, idf);

        for (auto& val : songTFIDF) {
            string currWord = val.first;
            double currTFIDF = val.second;
            genreVectors[song.genre][currWord] += currTFIDF;
        }
        genreSongCounts[song.genre]++;
    }

    // Average the TF-IDF vectors for each genre
    for (auto& genreVector : genreVectors) {
        for (auto& val : genreVector.second) {
            val.second /= genreSongCounts[genreVector.first];   // Divide the current tfidf value by the number of songs in the current genre
        }
    }

    return genreVectors;
}



// Determines the genre of the inputted song lyrics using unordered maps
string determineGenreUnordered(string& inputLyrics, vector<Song>& songs, unordered_map<string, double>& idf) {
    vector<string> inputWords;

    stringstream lyricStream(inputLyrics);
    string word;

    while(getline(lyricStream, word, ' ')) {
        string processedWord = "";
        for (char c: word) {
            if (c >= 'a' && c <= 'z') {
                processedWord.push_back(c);
            } else if (c >= 'A' && c <= 'Z') {
                processedWord.push_back(c - 'A' + 'a');
            } else if (c == '\'') {
                processedWord.push_back(c);
            }
        }
        if (processedWord.size() == 0) {
            continue;
        }
        inputWords.push_back(processedWord);
    }

    unordered_map<string, double> inputTFIDF = computeTFIDFUnordered(inputWords, idf);

    unordered_map<string, unordered_map<string, double>> genreVectors = computeGenreVectorsUnordered(songs, idf);

    string closestGenre;
    double maxSimilarity = 0.0;

    for (auto& genreVector : genreVectors) {
        double similarity = cosineSimilarityUnordered(inputTFIDF, genreVector.second);
        if (similarity > maxSimilarity) {
            maxSimilarity = similarity;
            closestGenre = genreVector.first;
        }
    }

    return closestGenre;
}


// Determines the genre of the inputted song lyrics using ordered maps
string determineGenreOrdered(string& inputLyrics, vector<Song>& songs, map<string, double>& idf) {
    vector<string> inputWords;

    stringstream lyricStream(inputLyrics);
    string word;

    while(getline(lyricStream, word, ' ')) {
        string processedWord = "";
        for (char c: word) {
            if (c >= 'a' && c <= 'z') {
                processedWord.push_back(c);
            } else if (c >= 'A' && c <= 'Z') {
                processedWord.push_back(c - 'A' + 'a');
            } else if (c == '\'') {
                processedWord.push_back(c);
            }
        }
        if (processedWord.size() == 0) {
            continue;
        }
        inputWords.push_back(processedWord);
    }

    map<string, double> inputTFIDF = computeTFIDFOrdered(inputWords, idf);

    map<string, map<string, double>> genreVectors = computeGenreVectorsOrdered(songs, idf);

    string closestGenre;
    double maxSimilarity = 0.0;

    for (auto& genreVector : genreVectors) {
        double similarity = cosineSimilarityOrdered(inputTFIDF, genreVector.second);
        if (similarity > maxSimilarity) {
            maxSimilarity = similarity;
            closestGenre = genreVector.first;
        }
    }

    return closestGenre;
}

