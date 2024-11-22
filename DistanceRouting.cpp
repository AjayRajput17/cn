#include <iostream>
#include <limits.h> // For INT_MAX
using namespace std;

int main() {
    int graph[50][50];
    int i, j, k, t;
    int nn;

    cout << "\nEnter total number of nodes: ";
    cin >> nn;

    // Initialize graph with -1 (indicating no direct connection)
    for (i = 0; i < nn; i++) {
        for (j = 0; j < nn; j++) {
            graph[i][j] = -1;
        }
    }

    char ch[50]; // Adjusted for nn <= 50
    cout << "Enter node labels: ";
    for (i = 0; i < nn; i++) {
        cin >> ch[i];
    }

    // Input distance between nodes
    for (i = 0; i < nn; i++) {
        for (j = 0; j < nn; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else if (graph[i][j] == -1) {
                cout << "\nEnter Distance between " << ch[i] << " - " << ch[j] << " : ";
                cin >> t;
                graph[i][j] = graph[j][i] = t;
            }
        }
    }

    // Initialize via and final matrices
    int via[50][50], final[50][50];
    for (i = 0; i < nn; i++) {
        for (j = 0; j < nn; j++) {
            final[i][j] = graph[i][j];
            via[i][j] = (i != j && graph[i][j] != -1) ? i : -1;
        }
    }

    // Floyd-Warshall Algorithm for all-pairs shortest path
    for (k = 0; k < nn; k++) {
        for (i = 0; i < nn; i++) {
            for (j = 0; j < nn; j++) {
                if (final[i][k] != -1 && final[k][j] != -1) {
                    if (final[i][j] == -1 || final[i][j] > final[i][k] + final[k][j]) {
                        final[i][j] = final[i][k] + final[k][j];
                        via[i][j] = k;
                    }
                }
            }
        }
    }

    // Display the final distance and via matrices
    for (i = 0; i < nn; i++) {
        cout << "\n" << ch[i] << " Table";
        cout << "\nNode\tDist\tVia";
        for (j = 0; j < nn; j++) {
            cout << "\n" << ch[j] << "\t" << final[i][j] << "\t";
            if (via[i][j] == -1)
                cout << "-";
            else
                cout << ch[via[i][j]];
        }
        cout << endl;
    }

    cout << "\nEND.";
    return 0;
}


// INPUT 
// Enter total number of nodes: 4
// Enter node labels: A B C D

// Enter Distance between A - B : 3

// Enter Distance between A - C : 7

// Enter Distance between A - D : -1

// Enter Distance between B - C : 1

// Enter Distance between B - D : 2

// Enter Distance between C - D : 5

// Enter Distance between D - A : -1