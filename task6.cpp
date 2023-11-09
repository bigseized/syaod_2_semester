#include <iostream>
#include <vector>
#include <climits>
#include <Windows.h>

using namespace std;

void BellmanFord(int graph[][3], int V, int E, int src)
{
    vector<int> dis(V, INT_MAX);

    dis[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            if (dis[graph[j][0]] != INT_MAX && dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
        }
    }

    cout << "Расстояние от точки " << src << " до других:" <<  endl;
    for (int i = 0; i < V; i++)
        cout << i << "\t\t" << dis[i] << endl;
}

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int graph[][3] = { {0, 1, 23}, {1, 0, 23},
                 {0, 2, 12}, {2, 0, 12},
                 {1, 2, 25}, {2, 1, 25},
                 {1, 4, 22}, {4, 1, 22},
                 {1, 7, 35}, {7, 1, 35},
                 {2, 3, 18}, {3, 2, 18},
                 {4, 6, 14}, {6, 4, 14},
                 {4, 5, 23}, {5, 4, 23},
                 {7, 6, 16}, {6, 7, 16},
                 {5, 3, 20}, {3, 5, 20},
                 {6, 5, 24},{5,6,24} };

    int V = 8;
    int E = 22;

    BellmanFord(graph, V, E, 2);
    return 0;
}
