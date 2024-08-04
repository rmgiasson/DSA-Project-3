#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>


using namespace std::chrono;

bool cmp(pair<string, int>& a,
        pair<string, int>& b)
{
    return a.second < b.second;
}

void topTenUnordered(UnorderedMapStructure umap, string genre) {
    auto start = high_resolution_clock::now();
 //get the frequency of every word in the given genre
    //get the index of the genre for words vector

    int genreIndex = 0;
    for(auto i : umap.getIndex()) {
        if(i.first == genre) {
            genreIndex = i.second;
            break;
        }
    }

    //go to found index and add words to vector
    unordered_map<string, int> m = umap.getWords()[genreIndex];

    vector<pair<string, int> > A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : m) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    cout << "The top 10 words in the " << genre << " genre are (Unordered): " << endl;
    int count = 0;
    for (auto it = A.rbegin(); it != A.rend() && count < 10; ++it, ++count) {
        cout << it->first << " appears " << it->second << " times." <<endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "This took " << duration.count() << " milliseconds." << endl;
}

void topTenOrdered(MapStructure omap, string genre) {
    auto start = high_resolution_clock::now();

    //get the frequency of every word in the given genre
    //get the index of the genre for words vector

    int genreIndex = 0;
    for(auto i : omap.getIndex()) {
        if(i.first == genre) {
            genreIndex = i.second;
            break;
        }
    }

    //go to found index and add words to vector
    map<string, int> m = omap.getWords()[genreIndex];;

    vector<pair<string, int> > A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : m) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    cout << "The top 10 words in the " << genre << " genre are (Standard): " << endl;
    int count = 0;
    for (auto it = A.rbegin(); it != A.rend() && count < 10; ++it, ++count) {
        cout << it->first << " appears " << it->second << " times" <<endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "This took " << duration.count() << " milliseconds." << endl;
}