#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int Partition(Edge edges[], int l, int r) {
    int pivot = edges[l].w;
    int i = l;
    int j = r + 1;

    while (true) {
        while (edges[++i].w < pivot) {
            if (i == r) break;
        }
        while (edges[--j].w > pivot) {
            if (j == l) break;
        }
        if (i >= j) break;
        swap(edges[i], edges[j]);
    }
    swap(edges[l], edges[j]);
    return j;
}

void QuickSort(Edge edges[], int l, int r) {
    if (l < r) {
        int s = Partition(edges, l, r);
        QuickSort(edges, l, s - 1);
        QuickSort(edges, s + 1, r);
    }
}

int find(int A[], int u, int v) {
    if (A[u] == A[v]) {
        return 1;
    } else {
        return 0;
    }
}


void unions(int A[], int u, int v) {
    int temp = A[u];
    for (int i = 0; i < 6; i++) {
        if (A[i] == temp) {
            A[i] = A[v];
        }
    }
}

void PrintArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

vector<Edge> readStreetData(const string& filename, int& V, int& E) {
    vector<Edge> edges;
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

        int u = stoi(area1.substr(4));
        int v = stoi(area2.substr(4));

        edges.push_back({u, v, distance});
    }
    E = edges.size();
    V = 0;
    for (const auto& edge : edges) {
        V = max(V, max(edge.u, edge.v));
    }
    V++;
    return edges;
}

int main() {
    int V, E;
    
    vector<Edge> edges = readStreetData("streetdata.txt", V, E);

    QuickSort(edges.data(), 0, E - 1);

    int A[V];
    for (int i = 0; i < V; i++) {
        A[i] = i;
    }

    int mstWeight = 0;
    cout << "Edges in the MST:" << endl;
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (!find(A, u, v)) {
            cout << "Area" << u << " - Area" << v << " : " << edges[i].w << endl;
            mstWeight += edges[i].w;
            unions(A, u, v);
        }
    }

    cout << "Total weight of MST: " << mstWeight << endl;
    return 0;
}