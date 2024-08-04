#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <vector>


using namespace std;

bool cmp(pair<string, int>& a,
        pair<string, int>& b)
{
    return a.second < b.second;
}

void topTenUnordered(UnorderedMapStructure map, string genre) {
 //get the frequency of every word in the given genre
    //get the index of the genre for words vector
    int genreIndex = 0;
    for(auto i : map.getIndex()) {
        if(i.first == genre) {
            genreIndex = i.second;
            break;
        }
    }

    //go to found index and add words to vector
    unordered_map<string, int> m = map.getWords()[genreIndex];

    vector<pair<string, int> > A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : m) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    for (auto& it : A) {

        cout << it.first << ' '
            << it.second << endl;
    }





}