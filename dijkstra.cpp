#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX 40  
#define INF INT_MAX

class dijk {
public:
    int dist[MAX], path[MAX], vis[MAX];
    int cost[MAX][MAX], v;
    unordered_map<string, int> areaToIndex;
    vector<string> areas;  

    dijk();
    void initial();
    void readStreetData(const string& filename);
    void dijkstra(int startIndex);
    int min();
    void printPath(int endIndex);
    
    string toLowerCase(const string& str);
    string trim(const string& str);
};

dijk::dijk() {
    // Just here :)
}

void dijk::initial() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cost[i][j] = INF;
        }
    }

    readStreetData("streetdata.txt");

    v = areaToIndex.size();

    if (v == 0) {
        cout << "No street data found! Exiting...\n";
        exit(1);
    }

    for (int i = 0; i < v; i++) {
        dist[i] = INF;
        vis[i] = 0;
        path[i] = -1;
    }
}

void dijk::readStreetData(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string area1, area2;
        int distance;
        
        getline(ss, area1, '-');
        ss.ignore(1); 
        getline(ss, area2, ':');
        ss.ignore(1); 
        ss >> distance;

        area1 = toLowerCase(trim(area1)); 
        area2 = toLowerCase(trim(area2));  

        if (areaToIndex.find(area1) == areaToIndex.end()) {
            areaToIndex[area1] = areas.size();
            areas.push_back(area1);
        }
        if (areaToIndex.find(area2) == areaToIndex.end()) {
            areaToIndex[area2] = areas.size();
            areas.push_back(area2);
        }

        int u = areaToIndex[area1];
        int v = areaToIndex[area2];

        cost[u][v] = distance;
        cost[v][u] = distance;  
    }
}

int dijk::min() {
    int min = INF;
    int index = -1;
    for (int i = 0; i < v; i++) {
        if (!vis[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijk::dijkstra(int startIndex) {
    dist[startIndex] = 0;

    for (int count = 0; count < v - 1; count++) {
        int u = min();
        if (u == -1) break;
        vis[u] = 1;

        for (int i = 0; i < v; i++) {
            if (!vis[i] && cost[u][i] != INF && dist[u] + cost[u][i] < dist[i]) {
                dist[i] = dist[u] + cost[u][i];
                path[i] = u;
            }
        }
    }
}

void dijk::printPath(int endIndex) {
    if (dist[endIndex] == INF) {
        cout << "No path found to " << areas[endIndex] << endl;
        return;
    }
    
    cout << "Shortest path to " << areas[endIndex] << ": " << dist[endIndex] << " units\n";
    cout << "Path: ";
    int temp = endIndex;
    while (path[temp] != -1) {
        cout << areas[temp] << " <- ";
        temp = path[temp];
    }
    cout << areas[temp] << " (Source)\n";
}

string dijk::toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

string dijk::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

int main() {
    dijk d;
    d.initial();

    string startArea, endArea;
    cout << "Enter the start area: ";
    cin >> startArea;
    cout << "Enter the end area: ";
    cin >> endArea;

    startArea = d.toLowerCase(d.trim(startArea));
    endArea = d.toLowerCase(d.trim(endArea));

    if (d.areaToIndex.find(startArea) == d.areaToIndex.end() || d.areaToIndex.find(endArea) == d.areaToIndex.end()) {
        cout << "Invalid area names!\n";
        return 1;
    }

    int startIndex = d.areaToIndex[startArea];
    int endIndex = d.areaToIndex[endArea];

    d.dijkstra(startIndex);
    d.printPath(endIndex);

    return 0;
}
