#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <omp.h>
using namespace std;

vector<int> graph[100]; // adjacency list
bool visited[100];      // visited array

// Parallel DFS function
void parallel_dfs(int start_node)
{
    stack<int> s;
    s.push(start_node);

    while (!s.empty())
    {
        int curr;

#pragma omp critical
        {
            curr = s.top();
            s.pop();
        }

        bool already_visited;

#pragma omp critical
        {
            already_visited = visited[curr];
            if (!already_visited)
                visited[curr] = true;
        }

        if (!already_visited)
        {
            cout << curr << " ";

            // Reverse iterate to maintain correct DFS order
#pragma omp parallel for
            for (int i = graph[curr].size() - 1; i >= 0; i--)
            {
                int adj = graph[curr][i];

#pragma omp critical
                {
                    if (!visited[adj])
                        s.push(adj);
                }
            }
        }
    }
}

int main()
{
    int node, edge, start_node;
    cout << "Enter number of nodes: ";
    cin >> node;
    cout << "Enter number of edges: ";
    cin >> edge;
    cout << "Enter the starting node: ";
    cin >> start_node;

    cout << "Enter edge u and v\n";
    for (int i = 0; i < edge; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        cout << "Edge: " << u << " - " << v << endl;
    }

    // Sort adjacency list to maintain traversal order
    for (int i = 0; i < node; i++)
        sort(graph[i].begin(), graph[i].end());

    fill(visited, visited + node + 1, false);

    cout << "\nParallel DFS Traversal starting from node " << start_node << ":\n";
    parallel_dfs(start_node);

    return 0;
}

//inputs :
// Enter number of nodes : 6 
// Enter number of edges : 7 
// Enter the starting node : 0 
// Enter edge u and v
//  0 1 
//  0 2
//  1 3
//  1 4 
//  2 4 
//  3 5 
//  4 5
