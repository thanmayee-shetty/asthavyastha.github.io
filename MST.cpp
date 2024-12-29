#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int find(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void KruskalMST(vector<Edge>& edges, int V) {
    // Sort edges in increasing order of weight
    sort(edges.begin(), edges.end(), compareEdges);

    vector<int> parent(V);
    vector<int> rank(V, 0);

    // Initialize parent array
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    int e = 0; // An index variable, used for sorted edges
    int i = 0; // An index variable, used for result[]

    vector<Edge> result; 

    while (e < V - 1) {
        Edge next_edge = edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            unionSets(parent, rank, x, y);
            e++;
        }
    }

    cout << "Following are the edges in the constructed MST" << endl;
    for (i = 0; i < result.size(); ++i)
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
}

int main() {
    // Example graph (replace with your own graph)
    int V = 4; // Number of vertices in graph
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 2, 5}, {1, 3, 15}, {2, 3, 4}
    };

    KruskalMST(edges, V);

    return 0;
}
