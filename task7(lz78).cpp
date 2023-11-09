#include <vector>
#include <iostream>
#include <string>

struct SymbolCode {
    int index;
    std::string symbol;
    char character;

    SymbolCode(int index, const std::string& symbol) : index(index), symbol(symbol), character('\0') {}
    SymbolCode(int index, char character) : index(index), symbol(""), character(character) {}
};

bool findInDictionary(const std::string& target, const std::vector<SymbolCode*>& dictionary, int& index) {
    for (const auto& entry : dictionary) {
        if (target == entry->symbol) {
            index = entry->index;
            return true;
        }
    }
    return false;
}

void encodeUsingLZ78(const std::string& inputPhrase) {
    std::string currentSubstring = "";
    std::vector<SymbolCode*> dictionary;
    std::vector<SymbolCode*> encodedResult;
    int index = 0;

    for (char character : inputPhrase) {
        currentSubstring += character;
        if (!findInDictionary(currentSubstring, dictionary, index)) {
            dictionary.push_back(new SymbolCode(dictionary.size() + 1, currentSubstring));
            encodedResult.push_back(new SymbolCode(index, character));
            index = 0;
            currentSubstring = "";
        }
    }

    for (const auto& entry : encodedResult) {
        std::cout << "<" << entry->index << ", " << entry->character << "> ";
    }

}

int main() {
    encodeUsingLZ78("sarsalsarsanlasanl 33");
    return 0;
}
