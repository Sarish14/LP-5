//============================================================================
// Name        : HPC_Assignment-01-BFS-DFS.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// TIME COMPLEXITIES
//Nomral DFS    : O(V+E)
//Normal BFS	: O(V+E)
//Parallel DFS  : O(V+E)
//Parallel BFS  : O(V+E)

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Graph class representing the adjacency list
class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) {
    	this->V=V;
    	this->adj.resize(V);
    }

    // Add an edge to the graph
    void addEdge(int fromVertex, int toVertex) {
        adj[fromVertex].push_back(toVertex);
    }

    // Parallel Depth-First Search
    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }

    // Parallel DFS utility function
    void parallelDFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        # pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int n = adj[v][i];
            if (!visited[n])
                parallelDFSUtil(n, visited);
        }
    }

    // Parallel Breadth-First Search
    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); ++i) {
                int n = adj[v][i];
                if (!visited[n]) {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
};

int main() {
    // Create a graph
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    /*
        0 -------->1
        |         / \
        |        /   \
        |       /     \
        v       v       v
        2 ----> 3       4
        |\
        | \
        v  v
        5  6
    */

    cout << "Depth-First Search (DFS): ";
    g.parallelDFS(0);
    cout << endl;

    cout << "Breadth-First Search (BFS): ";
    g.parallelBFS(0);
    cout << endl;

    return 0;

    //g++ 1_bfs_dfs.cpp -lgomp -o 1_bfs_dfs && ./1_bfs_dfs
}






// CUSTOM INPUT FOR GRAPH


//#include <bits/stdc++.h>
//using namespace std;
//class Graph
//{
//
//    int nodes, edges;
//    vector<vector<pair<int, int>>> graph;
//
//public:
//    Graph(int nn, int ne)
//    {
//        nodes = nn;
//        edges = ne;
//        graph.resize(nodes);
//    }
//    void acceptgraph()
//    {
//        int src, dest, wt;
//        for (int i = 0; i < edges; i++)
//        {
//            cout << "Enter the source\n";
//            cin >> src;
//            cout << "Enter the destination\n";
//            cin >> dest;
//            cout << "Enter the weight\n";
//            cin >> wt;
//            graph[src].push_back({dest, wt});
//            graph[dest].push_back({src, wt});
//        }
//    }
//    void display_graph()
//    {
//        cout << "Graph is:";
//
//        for (int i = 0; i < nodes; i++)
//        {
//            cout << i << "->";
//            for (int j = 0; j < graph[i].size(); j++)
//            {
//                cout << "{" << graph[i][j].first << "," << graph[i][j].second << "} , ";
//            }
//            cout << endl;
//        }
//    }
//
//    void bfs()
//    {
//        cout << "Enter the source node for bfs\n";
//        int src;
//        cin >> src;
//        cout << "BFS :";
//        queue<int> q;
//        q.push(src);
//        vector<int> vis(nodes, 0);
//        vis[src] = 1;
//        while (!q.empty())
//        {
//            int dest = q.front();
//            q.pop();
//
//            cout << "{" << dest << "} -> ";
//            for (auto it : graph[dest])
//            {
//                if (vis[it.first] == 0)
//                {
//                    q.push(it.first);
//                    vis[it.first] = 1;
//                }
//            }
//        }
//    }
//
//    void dfs_helper(int src, vector<int> &vis)
//    {
//
//        vis[src] = 1;
//        cout << src << "->";
//        for (auto it : graph[src])
//        {
//            if (vis[it.first] == 0)
//            {
//
//                dfs_helper(it.first, vis);
//            }
//        }
//    }
//    void dfs(int src)
//    {
//        vector<int> vis(nodes, 0);
//        return dfs_helper(src, vis);
//    }
//};
//
//int main()
//{
//    int nn, ne;
//    cout << "Enter the number of nodes in the graph\n";
//    cin >> nn;
//    cout << "Enter the number of edges in the graph\n";
//    cin >> ne;
//    Graph G(nn, ne);
//    G.acceptgraph();
//    G.bfs();
//    cout << endl;
//    cout << "Enter the source node\n";
//    int src;
//    cin >> src;
//    cout << "DFS : ";
//    G.dfs(src);
//    cout << endl;
//    G.display_graph();
//
//    return 0;
//}








// ERROR HANDLING

//int main() {
//    int option;
//    int n;
//    string input;
//
//    do {
//        cout << " ---------------------- MENU ---------------------- " << endl;
//        cout << " 1. Fibonacci Sequence Non-Recursive" << endl;
//        cout << " 2. Fibonacci Sequence Recursive" << endl;
//        cout << " 3. Exit" << endl;
//        cout << "Enter the option : ";
//        while (true) {
//            if ((!(cin >> option)) || (option < 1 || option > 3))                         // !(cin >> option) if input is not an integer
//            {
//                cout << "Invalid option. Please enter a valid option (1-3): ";
//                cin.clear();
//                cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            }
//            else
//            {
//                break;
//            }
//        }
//
//        if (option != 3) {
//            cout << "Enter the number of terms to be present in fibo numbers : ";
//            while (true) {
//                if (!(cin >> n) || n <= 0) {
//                    cout << "Invalid input. Please enter a positive number: ";
//                    cin.clear();
//                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                } else {
//                    break;
//                }
//            }
//        }
//
//        switch (option) {
//            case 1:
//                nonrecur(n);
//                break;
//
//            case 2:
//                recur(n);
//                break;
//
//            case 3:
//                cout << "Exiting the program." << endl;
//                return 0;
//
//            default:
//                cout << "Invalid Option" << endl;
//                break;
//        }
//    } while (true);
//
//    return 0;
//}











// UNDIRECTED GRAPH


// Define the graph structure (undirected graph)
//class Graph
//{
//    int V;                   // Number of vertices
//    vector<vector<int>> adj; // Adjacency list
//
//public:
//    Graph(int V)
//    {
//        this->V = V;
//        adj.resize(V);
//    }
//
//    // Function to add an edge to the graph
//    void addEdge(int u, int v)
//    {
//        adj[u].push_back(v);
//        adj[v].push_back(u);
//    }
//
//    // Parallel Breadth First Search
//    // Parallel Breadth First Search
//    void parallelBFS(int source)
//    {
//       vector<bool> visited(adj.size(), false);
//        queue<int> q;
//        visited[source] = true;
//        q.push(source);
//        while (!q.empty())
//        {
//            int u;
//#pragma omp parallel shared(q, visited)
//            {
//#pragma omp single
//                {
//                    u = q.front();
//                    q.pop();
//                    cout << u << " ";
//                }
//                if (!(adj[u].size() == 0))
//                {
//#pragma omp for
//                    for (int i = 0; i <= adj[u].size() - 1; ++i)
//                    {
//                        if (!visited[adj[u][i]])
//                        {
//#pragma omp critical
//                            {
//                                q.push(adj[u][i]);
//                                visited[adj[u][i]] = true;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // Parallel Depth First Search
//    // Parallel Depth First Search
//    void parallelDFSUtil(int v, vector<bool> &visited)
//    {
//        visited[v] = true;
//        cout << v << " ";
//
//// Traverse all adjacent vertices
//#pragma omp parallel for
//        for (int i = 0; i < adj[v].size(); ++i)
//        {
//            int u = adj[v][i];
//            if (!visited[u])
//            {
//                parallelDFSUtil(u, visited);
//            }
//        }
//    }
//
//    void parallelDFS(int source)
//    {
//        vector<bool> visited(V, false);
//        parallelDFSUtil(source, visited);
//    }
//};
//
//int main()
//{
//    // Create a graph
//    Graph g(6);
//    g.addEdge(0, 1);
//    g.addEdge(0, 2);
//    g.addEdge(1, 3);
//    g.addEdge(1, 4);
//    g.addEdge(2, 4);
//    g.addEdge(3, 5);
//    g.addEdge(4, 5);
//
//    cout << "Parallel Breadth First Search (BFS) starting from vertex 0: ";
//    g.parallelBFS(0);
//    cout << endl;
//
//    cout << "Parallel Depth First Search (DFS) starting from vertex 0: ";
//    g.parallelDFS(0);
//    cout << endl;
//
//    return 0;
//}








