#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <sstream>

std::string decodingLZW(std::vector<int> code) {
    std::unordered_map<unsigned int, std::string> map;
    std::string result;

    for (int i = 0; i < 128; i++) {
        map[i] = std::string(1, (char) i);
    }
    int ch = 128;
    for (int i = 0; i < code.size(); i++) {
        std::string word = map[code[i]];
        result += word;
        if (i + 1 < code.size()) {
            char additional_sym;
            if(map.find(code[i + 1]) == map.end()) {
                additional_sym = word[0];
            }
            else {
                additional_sym = map[code[i + 1]][0];
            }
            map[ch++] = word + additional_sym;
        }
    }
    return result;
}

int main() {
    int num;
    std::cin >> num;
    std::cin.ignore();
    std::vector<int> code;
    code.reserve(num);

    std::string str;
    std::getline(std::cin, str);
    std::istringstream stream(str);
    while (stream >> num) {
        code.push_back(num);
    }

    auto result = decodingLZW(code);
    std::cout << result;
    return 0;
}