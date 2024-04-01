#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <math.h>

using namespace std ;

// Checking if array if filled by 0's
bool checkElementsZero(vector<int> v, int a){
    for (int i = 0; i < a; i++){
        if (v[i] != 0) return false; 
    }
    return true;
}

int main(int agrc, char** argv) {
    ifstream stream("input.txt");
    string line;
    regex numberRegex("(-?\\d+)");
    match_results<string::iterator> regexMatch;
    vector<vector<int>> input;

    // Reading file with regex
    while (getline(stream, line)){
        vector<int> currentLine; 
        for (smatch sm; regex_search(line, sm, numberRegex);) {
            currentLine.push_back(stoi(sm.str()));
            line = sm.suffix();
        };
        input.push_back(currentLine) ;
    }

    int result = 0;
    vector<int> extrapolations;
    // Strategy: doing 'in-place' (with a copy of the line) operations until the line if filled with 0's
    // The extrapolation is equal to the sum of every last element of the reduction iterations
    // a b c d e
    // b-a c-b d-c e-d
    // c-2b+a d-2c+b e-2d+c
    // 0 0
    // In this case, interpolation = (e-2d+c) + (e-d) + e
    for (vector<int> v : input) {
        // Tree is symetrical, if we want to extrapolate to the left if suffices to reverse the input
        reverse(v.begin(), v.end());
        // Starting wiht v.length()
        int toCheck  = v.size() - 1;
        int extrapolation = 0;
        vector<int> lastElements;
        while (!checkElementsZero(v, toCheck)) {
            lastElements.push_back(v[toCheck]);
            for (int i = 0; i < toCheck; i++){
                v[i] = v[i+1] - v[i];
            }
            toCheck--;
        }
        for (const auto& i: lastElements) extrapolation += i;
        extrapolations.push_back(extrapolation);
    }
    for (const auto& i: extrapolations) result += i;
        cout << result << '\n' ;
    
}