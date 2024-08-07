#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include "unorderedMapStructure.hpp"
#include "mapStructure.hpp"

using namespace std;
using namespace chrono;

void wordPerGenreUnordered(UnorderedMapStructure umap, string word) {
    //start function timer
    auto start = high_resolution_clock::now();

    //look at each genre
    vector<string> v = umap.getGenres();
    //in each genre find the word
    cout << endl;
    cout << "Looking for instances of '" << word << "' in the Unordered Map database." << endl;
    cout << endl;
    for(auto i : v) {
        //print word count
        cout << i << ": " << word << " appears " << umap.getWordCount(i, word) << " times." << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << endl;
    cout << "This function took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void wordPerGenreOrdered(MapStructure omap, string word) {
    auto start = high_resolution_clock::now();

    //look at each genre
    vector<string> v = omap.getGenres();
    //in each genre find the word
    cout << "Looking for instances of '" << word << "' in the Standard Map database." << endl;
    cout << endl;
    for(auto i : v) {
        //print word count
        cout << i << ": " << word << " appears " << omap.getWordCount(i, word) << " times." << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << endl;
    cout << "This function took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}
