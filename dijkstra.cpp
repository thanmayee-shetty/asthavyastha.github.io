#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 6
#define INF 9999

class dijk {
public:
    int dist[MAX], path[MAX], vis[MAX];
    int cost[MAX][MAX], v;

    dijk();
    void initial(); 
    void dijkstra();
    int min();
};

dijk::dijk() {  
    cout << "Enter the number of vertices (<= " << MAX << "): ";
    cin >> v;
    if (v > MAX || v <= 0) {
        cout << "Invalid number of vertices! Exiting...\n";
        exit(1);
    }
}

void dijk::initial() { 
    int i, j;
    cout << "Enter the adjacency matrix (use " << INF << " for no edge):\n";
    for (i = 0; i < v; i++) {
        for (j = 0; j < v; j++) { 
            cin >> cost[i][j];
        }
    }

    for (int i = 0; i < v; i++) {
        dist[i] = INF;  
        vis[i] = 0;  
        path[i] = -1;  
    }

    dist[0] = 0;  
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

void dijk::dijkstra() {
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
    
    cout << "Vertex\tDistance from Source\tPath\n";
    for (int i = 0; i < v; i++) {
        cout << i << "\t" << dist[i] << "\t\t\t";
        
        int temp = i;
        while (path[temp] != -1) {
            cout << path[temp] << " <- ";
            temp = path[temp];
        }
        cout << "Source" << endl;
    }
}

int main() {
    dijk d;
    d.initial();
    d.dijkstra();
    return 0;
}