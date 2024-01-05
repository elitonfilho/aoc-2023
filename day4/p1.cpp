#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <unordered_set>
#include <math.h>

using namespace std;

int getGamePoints(unordered_set<int>& winningValues, vector<int>& currentCard) {
    int numberOfMatches = 0;
    for (auto& i : currentCard) {
        if (winningValues.contains(i)) {
            numberOfMatches++;
        }

    }
    return numberOfMatches == 0 ? 0 : pow(2, numberOfMatches - 1);
}

int main(int argc, char** argv) {
    ifstream stream("input.txt");
    string line;
    int totalPoints = 0;
    while (getline(stream, line)) {
        bool gettingWV = true;
        unordered_set<int> winningValues{};
        vector<int> currentCard{};
        // getting : and | characters
        int pos1 = line.find(':');
        int pos2 = line.find('|');
        int currPos = pos1 + 2;
        while (true) {
            currPos = isnumber(line[currPos]) ? currPos : currPos + 1;
            int nextPos = line[currPos + 1] == ' ' ? currPos + 1 : currPos + 2;
            string test = line.substr(currPos, nextPos - currPos);
            // Parsing winning values or current card
            if (gettingWV) {
                winningValues.insert(stoi(test));
            }
            else {
                currentCard.push_back(stoi(test));
            }
            currPos = nextPos + 1;
            // When reaching |
            if (currPos == pos2) {
                gettingWV = false;
                currPos += 2;
            }
            if (currPos >= line.size()) break;
        }
        totalPoints += getGamePoints(winningValues, currentCard);
    }

    cout << totalPoints;
}