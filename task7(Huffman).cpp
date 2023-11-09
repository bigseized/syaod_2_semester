#include <iostream>
#include <string>
#include <queue>
#include <Windows.h>
#include <unordered_map>

using namespace std;

struct Node {
    char character;
    int frequency;
    Node* leftChild, * rightChild;
};

Node* createNode(char character, int frequency, Node* leftChild, Node* rightChild) {
    Node* newNode = new Node();
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->leftChild = leftChild;
    newNode->rightChild = rightChild;
    return newNode;
}

struct NodeComparator {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

void generateHuffmanCodes(Node* rootNode, string code, unordered_map<char, string>& huffmanCode) {
    if (rootNode == nullptr)
        return;

    if (!rootNode->leftChild && !rootNode->rightChild) {
        huffmanCode[rootNode->character] = code;
    }

    generateHuffmanCodes(rootNode->leftChild, code + "0", huffmanCode);
    generateHuffmanCodes(rootNode->rightChild, code + "1", huffmanCode);
}

void buildFrequencyMap(const string& inputText, unordered_map<char, int>& frequencyMap) {
    for (char ch : inputText) {
        frequencyMap[ch]++;
    }
}

void buildNodeQueue(priority_queue<Node*, vector<Node*>, NodeComparator>& nodeQueue, const unordered_map<char, int>& frequencyMap) {
    for (const auto& pair : frequencyMap) {
        nodeQueue.push(createNode(pair.first, pair.second, nullptr, nullptr));
    }
}

Node* buildHuffmanTree(priority_queue<Node*, vector<Node*>, NodeComparator>& nodeQueue) {
    while (nodeQueue.size() != 1) {
        Node* leftNode = nodeQueue.top();
        nodeQueue.pop();
        Node* rightNode = nodeQueue.top();
        nodeQueue.pop();
        int sum = leftNode->frequency + rightNode->frequency;
        nodeQueue.push(createNode('\0', sum, leftNode, rightNode));
    }
    return nodeQueue.top();
}

void printHuffmanCodes(const unordered_map<char, string>& huffmanCode) {
    cout << "\nКоды Хаффмана для каждого символа :\n" << '\n';
    for (const auto& pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }
}

void printOriginalString(const string& inputText) {
    cout << "Начальная строка :\n" << inputText << '\n';
}

void printEncodedString(const string& encodedString) {
    cout << "\nЗакодированная строка :\n" << encodedString << '\n';
}

void printCompressionRatio(const string& inputText, const string& encodedText) {
    cout << " \nКоэффициент сжатия : " << (float) inputText.length() * 8 / (float) encodedText.length() << '\n';
}

void encodeString(const string& inputText) {
    unordered_map<char, int> frequencyMap;
    buildFrequencyMap(inputText, frequencyMap);

    priority_queue<Node*, vector<Node*>, NodeComparator> nodeQueue;
    buildNodeQueue(nodeQueue, frequencyMap);

    Node* rootNode = buildHuffmanTree(nodeQueue);
    unordered_map<char, string> huffmanCode;
    generateHuffmanCodes(rootNode, "", huffmanCode);
    printOriginalString(inputText);


    printHuffmanCodes(huffmanCode);

    string encodedString = "";
    for (char ch : inputText) {
        encodedString += huffmanCode[ch];
    }

    printEncodedString(encodedString);
    printCompressionRatio(inputText, encodedString);
}

int main() {
    SetConsoleOutputCP(1251);
    const string inputText = "Belyaev Mikhail Alekseevich";
    encodeString(inputText);
    return 0;
}
