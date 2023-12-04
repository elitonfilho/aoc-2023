#include <iostream>
#include <fstream>
#include <string.h>

int main() {

    std::ifstream stream("input.txt");
    std::string text;

    int result = 0;

    while (getline(stream, text)) {
        std::string inter ;
        // Reading from the beginning 
        for (int i = 0; i < text.length(); i++) {
            if (isdigit(text[i])) {
                inter += text[i];
                break;
            }
        }

        // Reading from the end
        for (int i = text.length(); i >= 0; i--) {
            if (isdigit(text[i])) {
                inter += text[i];
                break;
            }
        }

        if (inter.length() == 2) {
            result += std::stoi(inter);
        }

    }
    std::cout << result;
}