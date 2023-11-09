#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

vector<vector<pair<int, int>>> grid;

void initializeGrid() {
    grid = {
        {{-1, 5}, {-1, 4}, {-1, 3}, {-1, 2}, {-1, -1}},
        {{6, 1}, {2, 9}, {4, 3}, {8, 2}, {-1, 5}},
        {{3, 7}, {1, 4}, {5, 2}, {9, 1}, {-1, 2}},
        {{11, 13}, {15, 8}, {3, 6}, {7, 4}, {-1, 7}},
        {{9, 6}, {4, 3}, {8, 1}, {10, 5}, {-1, 1}}
    };
}

pair<pair<int, int>, pair<int, int>> inputCoordinates() {
    pair<int, int> start, finish;
    cout << "¬ведите координаты начальной и конечной точек:\n";
    cin >> start.first >> start.second >> finish.first >> finish.second;
    start.first--;
    start.second--;
    finish.first--;
    finish.second--;
    return make_pair(start, finish);
}

int shortestPath(pair<int, int> start, pair<int, int> finish) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols, 1e9));
    dp[start.first][start.second] = 0;

    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {
            if (i != rows - 1) {
                dp[i][j] = min(dp[i][j], dp[i + 1][j] + grid[i + 1][j].first);
            }
            if (j != 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j - 1].second);
            }
        }
    }
    return dp[finish.first][finish.second];
}

int main() {
    SetConsoleOutputCP(1251);
    initializeGrid();
    auto coordinates = inputCoordinates();
    pair<int, int> start = coordinates.first;
    pair<int, int> finish = coordinates.second;
    cout << " ратчайший путь: " << shortestPath(start, finish) << endl;
    return 0;
}
