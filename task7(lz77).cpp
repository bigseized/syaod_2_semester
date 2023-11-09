#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Pair {
    int offset;
    int len;
    char symbol;
};

void lz77Encode(const string& phrase) {
    vector<Pair> encoded;

    int phraseLength = phrase.length();
    int currentIndex = 0;

    while (currentIndex < phraseLength) {
        Pair currentPair;
        currentPair.offset = 0;
        currentPair.len = 0;
        currentPair.symbol = phrase[currentIndex];

        for (int i = currentIndex - 1; i >= 0; i--) {
            int j = 0;
            while (i + j < currentIndex && phrase[i + j] == phrase[currentIndex + j] && currentIndex + j < phraseLength) {
                j++;
            }

            if (j > currentPair.len) {
                currentPair.offset = currentIndex - i - 1;
                currentPair.len = j;
                if (currentIndex + j < phraseLength) {
                    currentPair.symbol = phrase[currentIndex + j];
                }
            }
        }

        encoded.push_back(currentPair);
        if (currentPair.len == 0) {
            currentIndex += 1;
        }
        else {
            currentIndex += currentPair.len;
        }
    }

    for (const Pair& pair : encoded) {
        cout << "<" << pair.offset << ", " << pair.len << ", " << pair.symbol << "> ";
    }
    cout << endl;
}

int main() {
    lz77Encode("010110110110100010001");
}
