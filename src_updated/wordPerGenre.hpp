#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>

using namespace std::chrono;

void wordPerGenreUnordered(UnorderedMapStructure umap, string word) {
    auto start = high_resolution_clock::now();

    //look at each genre
    vector<string> v = umap.getGenres();
    //in each genre find the word
    cout << "Looking for instances of '" << word << "' in the Unordered database." << endl;
    for(auto i : v) {
        //print stuff and things
        cout << i << ": " << word << " appears " << umap.getWordCount(i, word) << " times." << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "This function took " << duration.count() << " milliseconds." << endl;
}

void wordPerGenreOrdered(MapStructure omap, string word) {
    auto start = high_resolution_clock::now();

    //look at each genre
    vector<string> v = omap.getGenres();
    //in each genre find the word
    cout << "Looking for instances of '" << word << "' in the Standard database." << endl;
    for(auto i : v) {
        //print stuff and things
        cout << i << ": " << word << " appears " << omap.getWordCount(i, word) << " times." << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "This function took " << duration.count() << " milliseconds." << endl;
}