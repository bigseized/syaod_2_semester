#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

struct Node {
    char character;
    double probability;
    string code;

    Node(char sym, double prob) : character(sym), probability(prob) {}
};

vector<Node*> nodes;
string inputStroke;
string codeStroke;

bool compareNodesProbabilities(const Node* n1, const Node* n2) {
    return n1->probability > n2->probability;
}

void getAndCalculateProbabilities() {
    SetConsoleOutputCP(1251);

    inputStroke = "Мой котёнок очень странный, Он не хочет есть сметану, К молоку не И от рыбки отказался.";

    map<char, int> characters;

    for (char ch : inputStroke)
        characters[ch] = characters[ch] + 1;

    for (const auto& pair : characters) {
        double b = static_cast<double>(pair.second) / inputStroke.size();
        nodes.push_back(new Node(pair.first, b));
        cout << pair.first << " : " << b << endl;
    }

    sort(nodes.begin(), nodes.end(), compareNodesProbabilities);
}

void createShannonFanoCodes(int start, int end) {
    if (start == end)
        return;

    int splitIndex = 0;
    double sumLeft, sumRight, minDifference = numeric_limits<double>::max();

    for (int i = start; i < end; ++i) {
        sumLeft = 0.0;
        sumRight = 0.0;

        for (int j = start; j <= i; ++j)
            sumLeft += nodes[j]->probability;

        for (int j = i + 1; j <= end; ++j)
            sumRight += nodes[j]->probability;

        double difference = abs(sumLeft - sumRight);

        if (difference == 0) {
            splitIndex = i;
            break;
        }

        if (difference < minDifference) {
            minDifference = difference;
            splitIndex = i;
        }
    }

    for (int i = start; i <= splitIndex; ++i)
        nodes[i]->code += "0";

    for (int i = splitIndex + 1; i <= end; ++i)
        nodes[i]->code += "1";

    createShannonFanoCodes(start, splitIndex);
    createShannonFanoCodes(splitIndex + 1, end);
}

void encodeShannonFano() {
    getAndCalculateProbabilities();
    createShannonFanoCodes(0, nodes.size() - 1);

    for (char character : inputStroke) {
        for (Node* node : nodes) {
            if (node->character == character)
                codeStroke += node->code + " ";
        }
    }

    size_t inputSize = inputStroke.size();
    size_t encodedSize = codeStroke.size() / 8;

    double compressionRatio = static_cast<double>(inputSize) / static_cast<double>(encodedSize);

    cout << "\Encoded string: " << codeStroke << endl;
    cout << "\nCompression Ratio: " << compressionRatio << endl;
}

void decodeShannonFano() {
    string decodedResult;
    string currentCode;

    for (char c : codeStroke) {
        if (c == ' ')
            continue;

        currentCode += c;

        for (Node* node : nodes) {
            if (currentCode == node->code) {
                decodedResult += node->character;
                currentCode = "";
                break;
            }
        }
    }

    cout << "Decoded string: " << decodedResult << endl;
}

int main() {
    encodeShannonFano();
    decodeShannonFano();
    return 0;
}
