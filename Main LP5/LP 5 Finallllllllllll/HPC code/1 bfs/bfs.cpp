#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

class node
{
public:
    int data;
    node *left = nullptr;
    node *right = nullptr;
};

class Tree
{
public:
    // Function to insert a new node into the binary tree level-wise
    node *insert(node *root, int data)
    {
        if (!root)
        {
            root = new node{data}; // If tree is empty, create the root node
            return root;
        }
        queue<node *> q;
        q.push(root);

        while (!q.empty())
        {
            node *temp = q.front();
            q.pop();

            // Insert new node as left child if empty
            if (!temp->left)
            {
                temp->left = new node{data};
                return root;
            }
            else
                q.push(temp->left);

            // Insert new node as right child if empty
            if (!temp->right)
            {
                temp->right = new node{data};
                return root;
            }
            else
                q.push(temp->right);
        }
        return root;
    }

    // Function to perform BFS traversal in parallel using OpenMP
    void bfs(node *root)
    {
        if (!root)
            return; // If tree is empty, do nothing

        queue<node *> q;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size(); // Get the number of nodes at the current level

#pragma omp parallel for
            for (int i = 0; i < size; i++)
            {
                node *curr;

#pragma omp critical
                {
                    curr = q.front(); // Get the current node inside critical section
                    q.pop();          // Pop from queue
                }

                cout << curr->data << "\t"; // Print node data

#pragma omp critical
                {
                    if (curr->left)
                        q.push(curr->left);
                    if (curr->right)
                        q.push(curr->right);
                }
            }
        }
    }
};

int main()
{
    Tree tree;
    node *root = nullptr;
    int n, val;

    cout << "Enter number of nodes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> val;
        root = tree.insert(root, val);
    }

    cout << "\nParallel BFS Traversal is :\n";
    tree.bfs(root);

    return 0;
}


//inputs
// Enter number of nodes: 7
// Enter value for node 1: 1
// Enter value for node 2: 3
// Enter value for node 3: 2
// Enter value for node 4: 5
// Enter value for node 5: 4
// Enter value for node 6: 6
// Enter value for node 7: 7
