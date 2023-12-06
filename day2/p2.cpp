#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>

using namespace std;

int main(int argc, char** argv) {
    ifstream stream("input.txt");
    string line;
    int gameNumber = 1;
    int sumMinimalSetCubes = 0;

    regex blueRegex("(\\d{1,2}) blue");
    regex greenRegex("(\\d{1,2}) green");
    regex redRegex("(\\d{1,2}) red");

    match_results<string::iterator> blueMatch;
    match_results<string::iterator> greenMatch;
    match_results<string::iterator> redMatch;

    while (getline(stream, line)) {
        int initialPos = 0;
        int nextPos = line.find(';', initialPos);

        int minRed4Game = 0, minGreen4Game = 0, minBlue4Game = 0;

        while (true) {

            nextPos = nextPos == string::npos ? line.size() : nextPos; // If we are in the end of the line
            auto currentIteratorPos = line.begin() + initialPos;
            auto nextIteratorPos = line.begin() + nextPos;

            regex_search(currentIteratorPos, nextIteratorPos, blueMatch, blueRegex);
            regex_search(currentIteratorPos, nextIteratorPos, redMatch, redRegex);
            regex_search(currentIteratorPos, nextIteratorPos, greenMatch, greenRegex);

            // Converting match to number
            int blueCount = blueMatch.size() ? stoi(blueMatch[1]) : 0;
            int greenCount = greenMatch.size() ? stoi(greenMatch[1]) : 0;
            int redCount = redMatch.size() ? stoi(redMatch[1]) : 0;

            // Tracking minimal amount of cubes per game
            minRed4Game = max(minRed4Game, redCount);
            minBlue4Game = max(minBlue4Game, blueCount);
            minGreen4Game = max(minGreen4Game, greenCount);

            if (nextPos == line.size()) break; // Leaves the loop after the last round of the game
            initialPos = nextPos + 1;
            nextPos = line.find(';', initialPos);
        }

        sumMinimalSetCubes += (minRed4Game * minBlue4Game * minGreen4Game);
        gameNumber++;

    }

    cout << "Minimal sum of cubs: " << sumMinimalSetCubes;

}