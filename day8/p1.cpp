#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(int agrc, char** argv) {
    ifstream stream("input.txt");
    string line;

    unordered_map<string, pair<string, string>> input;
    string path;
    bool readStartLine = true;
    // Reading data
    while (getline(stream, line)) {
        if (readStartLine) {
            path = line;
            readStartLine = false;
            continue;
        }
        string source = line.substr(0,3);
        string left = line.substr(7,3);
        string right = line.substr(12,3);
        input[source] = make_pair(left,right);
    }

    int steps = 0;
    auto currNode = input["AAA"];
    bool runLoop = true;    
    string nextNode;
    while (runLoop){
        for (const char c : path){
            steps++;
            if (c == 'L') {
                if (currNode.first == "ZZZ") {
                    runLoop = false;
                    break;
                }
                nextNode = currNode.first;
            }
            else {
                if (currNode.second == "ZZZ") {
                    runLoop = false;
                    break;
                }
                nextNode = currNode.second;
            }
            currNode = input[nextNode];
        }
    }
    cout << steps ;
}
// >8904