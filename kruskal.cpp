#include <iostream>
#include <algorithm>
using namespace std;

struct array {
    int u, v, w; 
};

int Partition(array edges[], int l, int r) {
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

void QuickSort(array edges[], int l, int r) {
    if (l < r) {
        int s = Partition(edges, l, r);
        QuickSort(edges, l, s - 1);
        QuickSort(edges, s + 1, r);
    }
}

int find(int A[],int u,int v){
    if(A[u]==A[v])
     return 1;
    else 
     return 0;
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

int main() {
    int E = 12; 
    int V = 6;  

    array edges[E] = {
        {0, 1, 3}, {0, 2, 3}, {2, 5, 3}, {3, 5, 3}, {4, 5, 3},
        {1, 0, 2}, {2, 0, 2}, {1, 3, 2}, {2, 3, 2}, {3, 4, 2},
        {1, 4, 1}, {4, 5, 1}
    };

    QuickSort(edges, 0, E - 1);

    int A[V];
    for (int i = 0; i < V; i++) {
        A[i] = i; 
    }

    int mst = 0;
    cout << "Edges in the MST:" << endl;
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (!find(A, u, v)) {
            cout << u << " - " << v << " : " << edges[i].w << endl;
            mst += edges[i].w;
            unions(A, u, v); 
        }
    }

    cout << "Total weight of MST: " << mst << endl;
    return 0;
}