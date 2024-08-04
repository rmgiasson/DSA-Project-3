#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class MapStructure{
private:
    //maps the genres to an index
    map<string, int> genreIndex;

    //total number of words for each genre by index
    vector<int> genreTotal;

    //stores maps for each genre that map words to their number of occurrences
    vector<map<string, int>> genreWords;

public:
    //constructor
    MapStructure(){}

    //Takes a genre as a parameter and puts it into the maps.
    void addGenre(string genre){
        if(genreIndex.count(genre) == 0){
            genreIndex[genre] = genreTotal.size();
            genreTotal.push_back(0);
            genreWords.push_back(map<string, int>());
        }
    }

    //Takes a genre and a word as parameters and adds the word into the genre's map
    void addWord(string genre, string word){
        int index = genreIndex[genre];
        genreTotal[index]++;
        if(genreWords[index].count(word) == 0){
            genreWords[index][word] = 1;
        }
        else{
            genreWords[index][word]++;
        }
    }

    //Returns a vector of the genres.
    vector<string> getGenres(){
        vector<string> ans;
        for (map<string, int>::iterator it = genreIndex.begin(); it != genreIndex.end(); ++it) {
            ans.push_back(it->first);
        }
        return ans;
    }

    map<string, int> getIndex() {
        return genreIndex;
    }

    vector<map<string, int>> getWords() {
        return genreWords;
    }

    //Takes a genre as a parameter and returns the total number of words in the genre's songs.
    int getTotal(string genre){
        if(genreTotal[genreIndex[genre]] > 0) {
            return genreTotal[genreIndex[genre]];
        } else {
            return 0;
        }
    }

    //Takes a genre and a word as a parameter and returns the number of times that word was found in the genre's songs.
    int getWordCount(string genre, string word){
        if(genreWords[genreIndex[genre]][word] > 0) {
            return genreWords[genreIndex[genre]][word];
        } else {
            return 0;
        }
    }

    //Takes a genre and a word as a parameter and returns the frequency of the word in the genre's songs.
    float getWordFreq(string genre, string word){
        if((genreWords[genreIndex[genre]][word] + 0.0) / genreTotal[genreIndex[genre]] > 0) {
            return (genreWords[genreIndex[genre]][word] + 0.0) / genreTotal[genreIndex[genre]];
        } else {
            return 0.0;
        }
    }

};