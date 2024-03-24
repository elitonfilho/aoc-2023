#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <algorithm>

using namespace std;
int getRank(const char& a) {
    if (a == 'A') return 14;
    if (a == 'K') return 13;
    if (a == 'Q') return 12;
    if (a == 'J') return 11;
    if (a == 'T') return 10;
    return a - '0';
}

// Hand rank: 
// 7 - Five of a kind
// 6 - Four of a kind
// 5 - Full house
// 4 - Three of a kind
// 3 - Two pairs
// 2 - One pair
// 1 - High card
int getHandType(const string& hand) {
    unordered_map<char, int> handType;
    for (auto i : hand) {
        if (handType.contains(i)) handType[i]++;
        else handType.insert(make_pair(i, 1));
    }
    if (handType.size() == 1) return 7;
    if (handType.size() == 2) {
        auto anyVal = handType.begin();
        if (anyVal->second == 1 || anyVal->second == 4) return 6;
        return 5;
    }
    if (handType.size() == 3) {
        auto anyVal = handType.begin();
        if (anyVal->second == 2 || (++anyVal)->second == 2) return 3;
        return 4;
    }
    if (handType.size() == 4) return 2;
    return 1;
}
// base-15 rank
int getGlobalRank(const string& hand) {
    int rank = 0;
    for (int i = 0; i < hand.size(); i++) {
        rank += pow(15, 4 - i) * getRank(hand[i]);
    }
    rank += pow(15, 5) * getHandType(hand);
    return rank;
}

int main(int agrc, char** argv) {
    ifstream stream("input.txt");
    string line;
    regex handRegex("(\\w{5}) (\\d{1,4})");
    match_results<string::iterator> handRegexMatch;

    vector<pair<string, int>> input;
    long totalWinnings = 0;
    // Reading data
    while (getline(stream, line)) {
        regex_search(line.begin(), line.end(), handRegexMatch, handRegex);
        auto lineInput = make_pair(string(handRegexMatch[1]), stoi(handRegexMatch[2]));
        input.push_back(lineInput);
    }
    sort(input.begin(), input.end(),
        [](const pair<string, int>& p1, const pair<string, int>& p2) {
            if (getGlobalRank(p1.first) < getGlobalRank(p2.first)) return true;
            return false;
        });
    for (int i = 0; i < input.size(); i++) {
        totalWinnings += (i + 1) * input[i].second;
    }
    cout << totalWinnings;
}