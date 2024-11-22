#include <iostream>
#include <vector>
#include <climits>  // For INT_MAX
using namespace std;

#define INF INT_MAX  // Representation of infinity for unreachable nodes

// Function to find the node with the minimum distance value
int minDistance(vector<int> &dist, vector<bool> &visited, int nn) {
    int min = INF, min_index;
    for (int i = 0; i < nn; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

// Dijkstra's algorithm for Link State Routing
void dijkstra(int graph[50][50], int nn, int src, char nodes[]) {
    vector<int> dist(nn, INF);      // Distance from source to each node
    vector<bool> visited(nn, false); // Visited nodes
    dist[src] = 0;                  // Distance to the source is 0

    vector<int> parent(nn, -1);     // To reconstruct the shortest path

    for (int count = 0; count < nn - 1; count++) {
        int u = minDistance(dist, visited, nn);
        visited[u] = true;

        for (int v = 0; v < nn; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the shortest path tree
    cout << "\nRouting Table for Node " << nodes[src] << ":\n";
    cout << "Node\tDistance\tPath\n";
    for (int i = 0; i < nn; i++) {
        if (i != src) {
            cout << nodes[i] << "\t" << dist[i] << "\t\t";
            vector<char> path;
            int curr = i;
            while (curr != -1) {
                path.push_back(nodes[curr]);
                curr = parent[curr];
            }
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << path[j];
                if (j > 0) cout << " -> ";
            }
            cout << endl;
        }
    }
}

int main() {
    int graph[50][50];
    int nn;
    
    cout << "Enter the number of nodes: ";
    cin >> nn;

    char nodes[50];
    cout << "Enter node labels: ";
    for (int i = 0; i < nn; i++) {
        cin >> nodes[i];
    }

    cout << "\nEnter adjacency matrix (0 for no connection, -1 for self-loops):\n";
    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < nn; j++) {
            cin >> graph[i][j];
            if (i == j) graph[i][j] = 0;  // No cost to reach self
            if (graph[i][j] == -1) graph[i][j] = INF;  // Mark -1 as no link
        }
    }

    // Execute Dijkstra's algorithm for each node
    for (int src = 0; src < nn; src++) {
        dijkstra(graph, nn, src, nodes);
    }

    return 0;
}


// input
// Enter the number of nodes: 4
// Enter node labels: A B C D

// Enter adjacency matrix:
// 0 3 7 -1
// 3 0 1 2
// 7 1 0 5
// -1 2 5 0
