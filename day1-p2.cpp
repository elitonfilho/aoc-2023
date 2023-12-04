#include <iostream>
#include <fstream>
#include <string.h>

char getNextNumber (std::string& str, int pos){
    int strLen = str.length();
    // zero
    if (pos + 4 <= strLen && str.substr(pos, 4) == "zero") return '0' ;
    // one
    else if (pos + 3 <= strLen && str.substr(pos, 3) == "one") return '1' ;
    // two
    else if (pos + 3 <= strLen && str.substr(pos, 3) == "two") return '2' ;
    // three
    else if (pos + 5 <= strLen && str.substr(pos, 5) == "three") return '3' ;
    // four
    else if (pos + 4 <= strLen && str.substr(pos, 4) == "four") return '4' ;
    // five
    else if (pos + 4 <= strLen && str.substr(pos, 4) == "five") return '5' ;
    // six
    else if (pos + 3 <= strLen && str.substr(pos, 3) == "six") return '6' ;
    // seven
    else if (pos + 5 <= strLen && str.substr(pos, 5) == "seven") return '7' ;
    // eight
    else if (pos + 5 <= strLen && str.substr(pos, 5) == "eight") return '8' ;
    // nine
    else if (pos + 4 <= strLen && str.substr(pos, 4) == "nine") return '9' ;
    else return 'a';
}

int main() {

    std::ifstream stream("input.txt");
    std::string text;

    int result = 0;

    while (getline(stream, text)) {
        std::vector<char> listOfNumbers ;
        // Reading from the beginning 
        for (int i = 0; i < text.length(); i++) {
            if (isdigit(text[i])) listOfNumbers.push_back(text[i]);
            else if (getNextNumber(text, i) != 'a') listOfNumbers.push_back(getNextNumber(text, i));
        }
        int a = listOfNumbers[0] - '0';
        int b = listOfNumbers[listOfNumbers.size()-1] - '0';

        std::cout << a << ' ' << b << '\n';

        result += 10 * a + b;
    }
    std::cout << result;
}