#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

void task_a(string sentence){

    vector<string> words = vector<string>();

    boolean isWord = true;
    string word = "";

    // разбив строки на отдельные слова
    for (char c : sentence) {
        if (c == ' ' || c == ',') {
            isWord = false;
            if (word.length() != 0) {
                words.push_back(word);
                word = "";
            }
        }
        else {
            isWord = true;
        }
        if (isWord) {
            word += c;
        }
    }
    if (word.length() != 0)
        words.push_back(word);

    // нахождение обращений
    for (int i = 0; i < words.size(); i++) {
        string reverseString = words[i];
        reverse(reverseString.begin(), reverseString.end());
        for (int j = 0; j < words.size(); j++) {
            if (i == j)
                continue;
            if (reverseString == words[j]) {
                cout << words[j] << " <- " << words[i] << endl;;
            }
        }
    }
}

vector<int> computePrefixFunction(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> prefix(m, 0);
    int k = 0;

    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = prefix[k - 1];
        }

        if (pattern[k] == pattern[q]) {
            k++;
        }

        prefix[q] = k;
    }

    return prefix;
}

int KMPSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> prefix = computePrefixFunction(pattern);
    int q = 0;
    int max = -1;

    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = prefix[q - 1];
        }

        if (pattern[q] == text[i]) {
            q++;
        }

        if (q == m) {
            max = i - m + 1;
            q = prefix[q - 1];  // Начать поиск следующего вхождения
        }
    }
    return max;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABABDFASF";

    task_a("сел в озере,,,    берёзов лес");

    int max = 0;
    int result = 0;
    int final_result = 0;
    for (int i = 1; i < pattern.length(); i++) {
        result = KMPSearch(text, pattern.substr(0, i));
        if (result == -1) {
            break;
        }
        max = i;
        final_result = result;
    }

    cout << "Максимальная длина: " << max << "\nИндекс вхождения: " << final_result << endl;
    
    return 0;
}
