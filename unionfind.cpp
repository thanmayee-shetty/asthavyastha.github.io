#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Initially, each node is its own parent
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression optimization
        }
        return parent[x];
    }

    void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                parent[root_x] = root_y;
            } else if (rank[root_x] > rank[root_y]) {
                parent[root_y] = root_x;
            } else {
                parent[root_y] = root_x;
                rank[root_x]++;
            }
        }
    }
};

int main() {
    int n = 5; // Number of nodes
    UnionFind uf(n);

    // Example usage:
    uf.union_sets(0, 1);
    uf.union_sets(2, 3);
    uf.union_sets(1, 4);

    cout << "0 and 2 are in the same set: " << (uf.find(0) == uf.find(2) ? "Yes" : "No") << endl;
    cout << "1 and 4 are in the same set: " << (uf.find(1) == uf.find(4) ? "Yes" : "No") << endl;

    return 0;
}
