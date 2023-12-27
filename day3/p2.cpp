#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

int findValue(int currLine, int currCol, std::vector<string> &inputData)
{
    int lineLimit = inputData.size();
    int colLimit = inputData[currLine].size();

    int currStart = currCol, currEnd = currCol;
    while (currStart > 0 && isdigit(inputData[currLine][currStart - 1]))
    {
        currStart--;
    }
    while (currEnd < colLimit && isdigit(inputData[currLine][currEnd + 1]))
    {
        currEnd++;
    }

    std::string valueStr(inputData[currLine], currStart, currEnd);

    return stoi(valueStr);
}

int checkValidNeighborhood(int currLine, int currCol, std::vector<string> &inputData)
{
    // Check neighbors
    int lineLimit = inputData.size();
    int colLimit = inputData[currLine].size();
    int numCount = 0;
    std::vector<int> closestValues;

    /*
     Strategy: using the following convention
    1 2 3
    4 5 6
    7 8 9
    When analysing the upper-neighboorhood of 5 :
    If 2 == . , wh should check if there are any numbers on the right or left of 2
    Otherwise, if 2 is a number, it means that we have a unique upper-neighboor (we still need to find its span)
    Similar for the lower-neighboorhood (8)
    When analysing the neighboorhood in the same line of 5:
    If 4 is a digit, we have a neighboor in the left. Similar for 428314
    */

    if (currLine > 0) // Checking upper line
    {
        if (inputData[currLine - 1][currCol] == '.')
        {

            if (currCol > 0 && currCol < colLimit && isdigit(inputData[currLine - 1][currCol - 1]) && isdigit(inputData[currLine - 1][currCol + 1]))
            {
                numCount += 2; // Special case if upper symbol is a point (separates two numbers)
                closestValues.push_back(findValue(currLine - 1, currCol - 1, inputData));
                closestValues.push_back(findValue(currLine - 1, currCol + 1, inputData));
            }
            else if (currCol > 0 && isdigit(inputData[currLine - 1][currCol - 1]))
            {
                numCount++; // Otherwise there's just one number
                closestValues.push_back(findValue(currLine - 1, currCol - 1, inputData));
            }
            else if (currCol < colLimit && isdigit(inputData[currLine - 1][currCol + 1]))
            {
                numCount++; // Otherwise there's just one number
                closestValues.push_back(findValue(currLine - 1, currCol + 1, inputData));
            }
        }
        else if (isdigit(inputData[currLine - 1][currCol - 1]) || isdigit(inputData[currLine - 1][currCol]) || isdigit(inputData[currLine - 1][currCol + 1]))
        {
            numCount++; // Otherwise there's just one number
            closestValues.push_back(findValue(currLine - 1, currCol, inputData));
        }
    }

    if (currCol > 0 && isdigit(inputData[currLine][currCol - 1]))
    {
        numCount++; // Checking left
        closestValues.push_back(findValue(currLine, currCol - 1, inputData));
    }
    if (currCol < colLimit && isdigit(inputData[currLine][currCol + 1]))
    {
        numCount++; // Checking right
        closestValues.push_back(findValue(currLine, currCol + 1, inputData));
    }

    if (currLine < lineLimit) // Checking lower line
    {

        if (inputData[currLine + 1][currCol] == '.')
        {

            if (currCol > 0 && currCol < colLimit && isdigit(inputData[currLine + 1][currCol - 1]) && isdigit(inputData[currLine + 1][currCol + 1]))
            {
                numCount += 2; // Special case if upper symbol is a point (separates two numbers)
                closestValues.push_back(findValue(currLine + 1, currCol - 1, inputData));
                closestValues.push_back(findValue(currLine + 1, currCol + 1, inputData));
            }
            else if (currCol > 0 && isdigit(inputData[currLine + 1][currCol - 1]))
            {
                numCount++; // Otherwise there's just one number
                closestValues.push_back(findValue(currLine + 1, currCol - 1, inputData));
            }
            else if (currCol < colLimit && isdigit(inputData[currLine + 1][currCol + 1]))
            {
                numCount++; // Otherwise there's just one number
                closestValues.push_back(findValue(currLine + 1, currCol + 1, inputData));
            }
        }
        else if (isdigit(inputData[currLine + 1][currCol - 1]) || isdigit(inputData[currLine + 1][currCol]) || isdigit(inputData[currLine + 1][currCol + 1]))
        {
            numCount++; // Otherwise there's just one number
            closestValues.push_back(findValue(currLine + 1, currCol, inputData));
        }
    }
    if (numCount == 2)
    {
        int product = 1;
        for (auto i : closestValues)
            product *= i;
        return product;
    }
    return 0;
}

int main(int argc, char **argv)
{
    ifstream stream("input.txt");
    string line;

    std::vector<string> inputData;

    while (getline(stream, line))
    {
        inputData.push_back(line);
    }

    // Iterating over data
    int result = 0;

    for (int i = 0; i < inputData.size(); i++)
    {
        for (int j = 0; j < inputData[i].size(); j++)
        {
            auto charData = inputData[i][j];
            if (charData == '*')
                result += checkValidNeighborhood(i, j, inputData);
        }
    }
    std::cout << result;
}