#pragma once

#include "mapStructure.hpp"
#include "unorderedMapStructure.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

struct Song{
    vector<string> words;
    string genre;
};

set<string> generateStopwords();

unordered_map<string, double> computeTFUnordered(vector<string>& words);
map<string, double> computeTFOrdered(vector<string>& words);

unordered_map<string, double> computeIDFUnordered(vector<Song>& songs);
map<string, double> computeIDFOrdered(vector<Song>& songs);

unordered_map<string, double> computeTFIDFUnordered(vector<string>& words, unordered_map<string, double>& idf);
map<string, double> computeTFIDFOrdered(vector<string>& words, map<string, double>& idf);

double cosineSimilarityUnordered(unordered_map<string, double>& vecA, unordered_map<string, double>& vecB);
double cosineSimilarityOrdered(map<string, double>& vecA, map<string, double>& vecB);

unordered_map<string, unordered_map<string, double>> computeGenreVectorsUnordered(vector<Song>& songs, unordered_map<string, double>& idf);
map<string, map<string, double>> computeGenreVectorsOrdered(vector<Song>& songs, map<string, double>& idf);

string determineGenreUnordered(string& inputLyrics, vector<Song>& songs, unordered_map<string, double>& idf);
string determineGenreOrdered(string& inputLyrics, vector<Song>& songs, map<string, double>& idf);







