#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(int agrc, char** argv) {
    bool readStartLine = true;
    ifstream stream("input.txt");
    string line;
    string path;
    int pathSize;
    unordered_map<string, pair<string, string>> input;

    // Reading data
    while (getline(stream, line)) {
        if (readStartLine) {
            path = line;
            pathSize = path.size();
            readStartLine = false;
            continue;
        }
        string source = line.substr(0, 3);
        string left = line.substr(7, 3);
        string right = line.substr(12, 3);
        input[source] = make_pair(left, right);
    }

    // Initial nodes
    vector<string> currentNodes;
    for (auto& [key, _] : input) {
        if (key[2] == 'A') currentNodes.push_back(key);
    }

    // Preparing for the loop
    string nextNode;
    vector<int> roundPathCompleted;
    for (auto& node : currentNodes) {
        int steps = 0;
        bool runLoop = true;
        string currentNode = node;
        while (runLoop) {
            for (const char c : path) {
                steps++;
                // Getting next values
                if (c == 'L') nextNode = input[currentNode].first;
                if (c == 'R') nextNode = input[currentNode].second;
                // Checking if we arrived in the end
                if (nextNode[2] == 'Z') {
                    runLoop = false;
                    break;
                }
                // Updating current node
                currentNode = nextNode;
            }
        }
        // Core idea: To get to a Z node, we expect to loop the path N times = steps / pathSize
        roundPathCompleted.push_back(steps / pathSize);
    }
    // Ideally we shoud get the lowest common denominator, but i got prime numbers on roundPathCompleted :)
    long long finalRes = 1;
    for (auto& i : roundPathCompleted) {
        finalRes *= i;
    }
    cout << finalRes * pathSize;

}