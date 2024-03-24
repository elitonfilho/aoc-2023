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
    if (a == 'A') return 13;
    if (a == 'K') return 12;
    if (a == 'Q') return 11;
    if (a == 'J') return 1;
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
    int countJoker = 0;
    // Counting hand without joker
    for (auto i : hand) {
        if (i != 'J') {
            if (handType.contains(i)) handType[i]++;
            else handType.insert(make_pair(i, 1));
        }
        else countJoker++;
    }
    // Checking best scenario when there's a joker
    if (countJoker > 0) {
        if (countJoker == 5 || countJoker == 4) return 7;
        if (countJoker == 3) {
            if (handType.size() == 2) return 6;
            if (handType.size() == 1) return 7;
        }
        if (countJoker == 2) {
            if (handType.size() == 3) return 4;
            if (handType.size() == 2) return 6;
            if (handType.size() == 1) return 7;
        }
        if (countJoker == 1) {
            if (handType.size() == 4) return 2;
            if (handType.size() == 3) return 4;
            if (handType.size() == 2) {
                auto anyVal = handType.begin();
                if (anyVal->second == 3 || anyVal->second == 1) return 6;
                else return 5;
            }
            if (handType.size() == 1) return 7;
        }
    }
    // Cases without joker
    else {
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

}
// base-14 rank
int getGlobalRank(const string& hand) {
    int rank = 0;
    for (int i = 0; i < hand.size(); i++) {
        rank += pow(14, 4 - i) * getRank(hand[i]);
    }
    rank += pow(14, 5) * getHandType(hand);
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
        // cout << handRegexMatch[1] << ' ' << handRegexMatch[2] << '\n';
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