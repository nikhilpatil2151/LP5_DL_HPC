// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class Tree {
public:
    int nodes;
    vector<vector<int>> adj;

    Tree(int n) {
        nodes = n;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected tree
    }

    void DFS(int node, int parent) {
        #pragma omp critical
        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); ++i) {
            int child = adj[node][i];
            if (child != parent) {
                DFS(child, node);
            }
        }
    }
};

int main() {
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;

    Tree t(n);

    cout << "Enter number of edges (should be n-1 for a tree): ";
    cin >> e;

    cout << "Enter " << e << " edges (u v):" << endl;
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        t.addEdge(u, v);
    }

    cout << "Parallel DFS Traversal starting from node 0:" << endl;
    t.DFS(0, -1);

    return 0;
}
