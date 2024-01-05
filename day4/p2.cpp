#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <array>
#include <unordered_set>
#include <math.h>

using namespace std;

void getGamePoints(unordered_set<int>& winningValues, vector<int>& currentCard, int gameNumber, array<int, 219>& totalCards) {
    int numberOfMatches = 0;
    for (auto& i : currentCard) {
        if (winningValues.contains(i)) {
            numberOfMatches++;
        }
    }
    for (int i = 0; i < numberOfMatches; i++) {
        if ((gameNumber + i + 1) < 219) {
            totalCards[gameNumber + i + 1] += totalCards[gameNumber];
        }
    }
}

int main(int argc, char** argv) {
    ifstream stream("input.txt");
    string line;
    int totalPoints = 0;
    int gameNumber = 0;
    // Using a fixed size array to calculate the total of cards
    array<int, 219> totalCards;
    totalCards.fill(1);
    while (getline(stream, line)) {
        bool gettingWV = true;
        unordered_set<int> winningValues{};
        vector<int> currentCard;
        // getting : and | characters
        int pos1 = line.find(':');
        int pos2 = line.find('|');
        int currPos = pos1 + 2;
        while (true) {
            currPos = isnumber(line[currPos]) ? currPos : currPos + 1;
            int nextPos = line[currPos + 1] == ' ' ? currPos + 1 : currPos + 2;
            string test = line.substr(currPos, nextPos - currPos);
            if (gettingWV) {
                winningValues.insert(stoi(test));
            }
            else {
                currentCard.push_back(stoi(test));
            }
            currPos = nextPos + 1;
            if (currPos == pos2) {
                gettingWV = false;
                currPos += 2;
            }
            if (currPos >= line.size()) break;
        }
        getGamePoints(winningValues, currentCard, gameNumber, totalCards);
        gameNumber++;
    }
    for (auto i : totalCards) totalPoints += i;
    cout << totalPoints;
}