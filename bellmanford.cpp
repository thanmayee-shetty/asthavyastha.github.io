#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int src, dest, weight;
};

void BellmanFord(vector<vector<int>>& graph, int V, int src) {
    vector<int> dist(V, INF); 
    dist[src] = 0; 

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Detect negative cycle
    for (int j = 0; j < graph.size(); ++j) {
        int u = graph[j][0];
        int v = graph[j][1];
        int w = graph[j][2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    // Print the results
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; ++i)
        cout << i << " \t\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
}

int main() {
    // Example graph (replace with your own graph)
    vector<vector<int>> graph = {{0, 1, -1}, 
                                {0, 2, 4}, 
                                {1, 2, 3}, 
                                {1, 3, 2}, 
                                {2, 1, -2}}; 
    int V = 4; // Number of vertices
    int src = 0; // Source vertex

    BellmanFord(graph, V, src);

    return 0;
}
