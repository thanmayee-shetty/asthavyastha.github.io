#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

void bfs(int m[10][10], int v, int source, unordered_map<int, string>& indexToArea, unordered_map<string, int>& areaToIndex) {
    int queue[20];
    int front = 0, rear = 0, u;
    int visited[10];

    for (int i = 0; i < v; i++)
        visited[i] = 0;

    queue[rear] = source;
    visited[source] = 1;

    cout << "The BFS Traversal is... \n";

    while (front <= rear) {
        u = queue[front];
        cout << indexToArea[u] << "\t";
        front++;

        for (int i = 0; i < v; i++) {
            if (m[u][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                rear++;
                queue[rear] = i;
            }
        }
    }
}

void readStreetData(const string& filename, unordered_map<string, int>& areaToIndex, unordered_map<int, string>& indexToArea, int m[10][10], int& v) {
    ifstream file(filename);
    string line;
    int areaCount = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string area1, area2;

        getline(ss, area1, '-');
        ss.ignore(1); 
        getline(ss, area2, ':');
        
        area1 = area1.substr(4);
        area2 = area2.substr(4);

        if (areaToIndex.find(area1) == areaToIndex.end()) {
            areaToIndex[area1] = areaCount;
            indexToArea[areaCount] = area1;
            areaCount++;
        }
        if (areaToIndex.find(area2) == areaToIndex.end()) {
            areaToIndex[area2] = areaCount;
            indexToArea[areaCount] = area2;
            areaCount++;
        }

        int u = areaToIndex[area1];
        int v = areaToIndex[area2];

        m[u][v] = 1;
        m[v][u] = 1;
    }

    v = areaCount;
}

int main() {
    int m[10][10] = {0};  
    int v = 0;  
    unordered_map<string, int> areaToIndex;  
    unordered_map<int, string> indexToArea;  

    readStreetData("StreetData.txt", areaToIndex, indexToArea, m, v);

    string sourceArea;
    cout << "Enter the source area: ";
    cin >> sourceArea;

    if (areaToIndex.find(sourceArea) == areaToIndex.end()) {
        cout << "Invalid area name!\n";
        return 1;
    }

    int sourceIndex = areaToIndex[sourceArea];

    bfs(m, v, sourceIndex, indexToArea, areaToIndex);

    return 0;
}
