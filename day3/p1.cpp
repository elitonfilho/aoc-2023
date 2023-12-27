#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>

using namespace std;

bool checkValidNeighborhood(std::vector<std::pair<int, int>> &positionsToCheck, std::vector<string> &inputData)
{
    for (auto [i, j] : positionsToCheck)
    {
        int lineLimit = inputData.size();
        int colLimit = inputData[i].size();

        std::vector<std::pair<int, int>> reviewedPositions;

        for (int i_a = max(0, i - 1); i_a < min(lineLimit, i + 2); i_a++)
        {
            for (int j_a = max(0, j - 1); j_a < min(colLimit, j + 2); j_a++)
            {
                reviewedPositions.push_back(std::make_pair(i_a, j_a));
            }
        }

        for (auto [k, l] : reviewedPositions)
        {
            if (inputData[k][l] != '.' && !isdigit(inputData[k][l]))
                return true;
        }
    }
    return false;
};

int main(int argc, char **argv)
{
    ifstream stream("input.txt");
    string line;

    std::vector<string> inputData;

    while (getline(stream, line))
    {
        inputData.push_back(line);
    }

    // for (auto i : inputData) std :: cout << i ;

    // Iterating over data
    int currNumber = 0;

    bool toCheck = false;

    int result = 0;

    std::vector<std::pair<int, int>> positionsToCheck;

    for (int i = 0; i < inputData.size(); i++)
    {
        for (int j = 0; j < inputData[i].size(); j++)
        {
            auto charData = inputData[i][j];
            if (isdigit(charData))
            {
                toCheck = true;
                int charValue = charData - '0';
                currNumber = currNumber == 0 ? charValue : 10 * currNumber + charValue;
                positionsToCheck.push_back(std::pair<int, int>(i, j));
            }
            else if (toCheck == true)
            {
                if (checkValidNeighborhood(positionsToCheck, inputData))
                {
                    result += currNumber;
                    std::cout << " ok" << currNumber << ' ';
                }
                currNumber = 0;
                toCheck = false;
                positionsToCheck.clear();
            }
        }
    }
    std::cout << result;
}