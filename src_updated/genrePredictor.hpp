#include "mapStructure.hpp"
#include "unorderedMapStructure.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

float cosineSimilarity(vector<float> A, vector<float> B) {
    float dotProduct = 0.0, normA = 0.0, normB = 0.0 ;
    for(int i = 0; i < A.size(); i++) {
        dotProduct += A[i] * B[i];
        normA += A[i] * A[i];
        normB += B[i] * B[i];
    }
    if(normA == 0 || normB == 0) {
        return 0;
    } else {
        return dotProduct / (sqrt(normA) * sqrt(normB));
    }
}


set<string> generateStopwords() {
    ifstream stopwords("../resources/stopwords.txt");        /////// Move to its own file later
    //stopwords.open("../resources/stopwords.txt");   // Create set of stopwords (the words to remove from the filtered maps)

    set<string> commonStopwords;
    vector<string> words;

    string stopwordsLine;
    while(getline(stopwords, stopwordsLine, '\n')) {
        commonStopwords.insert(stopwordsLine);
    }
    stopwords.close();
    return commonStopwords;
}


string calculateGenreUnordered(string songLyrics, UnorderedMapStructure unorderedFiltered) {
    set<string> commonStopwords = generateStopwords();

    int totalWords = 0;
    vector<string> words;
    unordered_map<string, int> unorderedFilteredLyrics;

    stringstream ss(songLyrics);
    string line;

    while(getline(ss, line)){
        stringstream lineStream(line);
        string word;

        while(getline(lineStream, word, ' ')) {
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

            totalWords++;

            if (commonStopwords.count(processedWord) == 0) {     // If word not in set of stopwords, add to map
                if (unorderedFilteredLyrics.count(processedWord) == 0) {
                    unorderedFilteredLyrics[processedWord] = 1;
                    words.push_back(processedWord);
                } else {
                    unorderedFilteredLyrics[processedWord]++;
                }
            }
        }
    }

    vector<string> allGenres = unorderedFiltered.getGenres();

    unordered_map<string, float> wordLyricFrequencies;              // Aka vector A in the cosineSimilarity
    vector<pair<string, unordered_map<string, float>>> allGenreFrequencies;      // Aka all vector B's in the cosineSimilarity


    for(const auto & word : words) {    // For each word in the lyrics, add it and its frequency to the wordLyricFrequencies map
        wordLyricFrequencies[word] = (unorderedFilteredLyrics[word] + 0.0) / totalWords;
    }

    for(int i = 0; i < allGenres.size(); i++) {
        string currGenre = allGenres[i];
        unordered_map<string, float> currGenreFrequencies;

        for(int j = 0; j < words.size(); j++) {    // For all words in the lyrics, get their corresponding frequencies from the unorderedFiltered map for all the genres
            string currWord = words[j];
            float wordFreq = unorderedFiltered.getWordFreq(currGenre, currWord);
            currGenreFrequencies[currWord] = wordFreq;
        }

        pair<string, unordered_map<string, float>> genrePair;   // Push back the genre name with all of its corresponding word frequencies for the given lyrics to allGenreFrequencies
        genrePair.first = currGenre;
        genrePair.second = currGenreFrequencies;

        allGenreFrequencies.push_back(genrePair);
    }

    vector<pair<string, float>> genreSimilarities;

    vector<float> lyricFrequencies(words.size(), 0.0f);

    for(int i = 0; i < allGenres.size(); i++) {    // Put values into vectors and calculate cosine similarities for all genres, then store them in genreSimilarities
        string currGenre = allGenres[i];

        vector<float> genreFrequencies(words.size(), 0.0f);

        for(int j = 0; j < words.size(); j++) {
            string currWord = words[j];

            lyricFrequencies[j] = wordLyricFrequencies[currWord];

            for(auto pair : allGenreFrequencies) {
                if(pair.first == currGenre) {
                    unordered_map<string, float> genreFreqMap = pair.second;
                    genreFrequencies[j] = genreFreqMap[currWord];
                }
            }
        }

        float genreCosSimilarity = cosineSimilarity(lyricFrequencies, genreFrequencies);
        pair<string, float> genreSimilarityPair;
        genreSimilarityPair.first = currGenre;
        genreSimilarityPair.second = genreCosSimilarity;

        genreSimilarities.push_back(genreSimilarityPair);
    }

    string closestGenre = "None";
    float maxSimilarity = -1.0;

    for(auto value : genreSimilarities) {
        if(value.second > maxSimilarity) {
            maxSimilarity = value.second;
            closestGenre = value.first;
        }
    }

    return closestGenre;
}




string calculateGenreOrdered(string songLyrics, MapStructure ordered) {
    int totalWords = 0;
    vector<string> words;
    map<string, int> orderedLyrics;

    stringstream ss(songLyrics);
    string line;

    while(getline(ss, line)){
        stringstream lineStream(line);
        string word;

        while(getline(lineStream, word, ' ')) {
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

            totalWords++;

            if (orderedLyrics.count(processedWord) == 0) {
                orderedLyrics[processedWord] = 1;
                words.push_back(processedWord);
            } else {
                orderedLyrics[processedWord]++;
            }
        }
    }

    vector<string> allGenres = ordered.getGenres();

    map<string, float> wordLyricFrequencies;              // Aka vector A in the cosineSimilarity
    vector<pair<string, map<string, float>>> allGenreFrequencies;      // Aka all vector B's in the cosineSimilarity


    for(const auto & word : words) {    // For each word in the lyrics, add it and its frequency to the wordLyricFrequencies map
        wordLyricFrequencies[word] = (orderedLyrics[word] + 0.0) / totalWords;
    }

    for(int i = 0; i < allGenres.size(); i++) {
        string currGenre = allGenres[i];
        map<string, float> currGenreFrequencies;

        for(int j = 0; j < words.size(); j++) {    // For all words in the lyrics, get their corresponding frequencies from the unorderedFiltered map for all the genres
            string currWord = words[j];
            float wordFreq = ordered.getWordFreq(currGenre, currWord);
            currGenreFrequencies[currWord] = wordFreq;
        }

        pair<string, map<string, float>> genrePair;   // Push back the genre name with all of its corresponding word frequencies for the given lyrics to allGenreFrequencies
        genrePair.first = currGenre;
        genrePair.second = currGenreFrequencies;

        allGenreFrequencies.push_back(genrePair);
    }

    vector<pair<string, float>> genreSimilarities;

    vector<float> lyricFrequencies(words.size(), 0.0f);

    for(int i = 0; i < allGenres.size(); i++) {    // Put values into vectors and calculate cosine similarities for all genres, then store them in genreSimilarities
        string currGenre = allGenres[i];

        vector<float> genreFrequencies(words.size(), 0.0f);

        for(int j = 0; j < words.size(); j++) {
            string currWord = words[j];

            lyricFrequencies[j] = wordLyricFrequencies[currWord];
            for(auto pair : allGenreFrequencies) {
                if(pair.first == currGenre) {
                    map<string, float> genreFreqMap = pair.second;
                    genreFrequencies[j] = genreFreqMap[currWord];
                }
            }
        }

        float genreCosSimilarity = cosineSimilarity(lyricFrequencies, genreFrequencies);
        pair<string, float> genreSimilarityPair;
        genreSimilarityPair.first = currGenre;
        genreSimilarityPair.second = genreCosSimilarity;

        genreSimilarities.push_back(genreSimilarityPair);
    }

    string closestGenre = "None";
    float maxSimilarity = -1.0;

    for(auto value : genreSimilarities) {
        if(value.second > maxSimilarity) {
            maxSimilarity = value.second;
            closestGenre = value.first;
        }
    }

    return closestGenre;
}